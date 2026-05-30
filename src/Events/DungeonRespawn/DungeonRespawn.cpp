//
// Created by development on 5/24/26.
//

#include "DungeonRespawn.h"

namespace DungeonRespawn
{
    bool DSPlayerScript::IsInsideDungeonRaid(Player* player)
    {
        if (!player)
        {
            return false;
        }

        Map* map = player->GetMap();

        if (!map)
        {
            return false;
        }

        if (!map->IsDungeon() && !map->IsRaid())
        {
            return false;
        }

        return true;
    }

    void DSPlayerScript::OnPlayerReleasedGhost(Player* player)
    {
        if (!Enabled || !IsInsideDungeonRaid(player))
        {
            return;
        }

        std::lock_guard<std::mutex> lock(teleportMutex);
        playersToTeleport.push_back(player->GetGUID());
    }

    void DSPlayerScript::ResurrectPlayer(Player* player)
    {
        player->ResurrectPlayer(respawnHpPct / 100.0f, false);
        player->SpawnCorpseBones();
    }

    bool DSPlayerScript::OnPlayerBeforeTeleport(Player* player, uint32 mapid, float /*x*/, float /*y*/, float /*z*/, float /*orientation*/, uint32 /*options*/, Unit* /*target*/)
    {
        if (!Enabled || !player)
        {
            return true;
        }

        if (player->GetMapId() != mapid)
        {
            auto prData = GetOrCreateRespawnData(player);
            prData->isTeleportingNewMap = true;
        }

        if (!IsInsideDungeonRaid(player) || !player->isDead())
        {
            return true;
        }

        bool canRestore = false;

        {
            std::lock_guard<std::mutex> lock(teleportMutex);
            auto it = std::find(playersToTeleport.begin(), playersToTeleport.end(), player->GetGUID());

            if (it != playersToTeleport.end())
            {
                playersToTeleport.erase(it);
                canRestore = true;
            }
        }

        if (!canRestore)
        {
            return true;
        }

        auto prData = GetOrCreateRespawnData(player);

        if (prData && prData->dungeon.map != -1 && prData->dungeon.map == int32(player->GetMapId()))
        {
            player->TeleportTo(prData->dungeon.map, prData->dungeon.x, prData->dungeon.y, prData->dungeon.z, prData->dungeon.o);
            ResurrectPlayer(player);
            return false;
        }

        return true;
    }

    void DSWorldScript::OnAfterConfigLoad(bool reload)
    {
        if (reload)
        {
            SaveRespawnData();
            respawnData.clear();
        }

        Enabled = sConfigMgr->GetOption<bool>("DungeonRespawn.Enable", false);

        LOG_INFO("module", "DungeonRespawn enabled: {}", Enabled ? "true" : "false");

        respawnHpPct = sConfigMgr->GetOption<float>("DungeonRespawn.RespawnHealthPct", 50.0f);

        LOG_INFO("module", "Respawn Health Percentage: {}", respawnHpPct);

        QueryResult qResult = CharacterDatabase.Query("SELECT `guid`, `map`, `x`, `y`, `z`, `o` FROM `dungeonrespawn_playerinfo`");

        if (qResult)
        {
            uint32 dataCount = 0;

            do
            {
                Field* fields = qResult->Fetch();

                PlayerRespawnData prData;
                prData.guid = ObjectGuid(fields[0].Get<uint64>());
                prData.dungeon.map = fields[1].Get<int32>();
                prData.dungeon.x = fields[2].Get<float>();
                prData.dungeon.y = fields[3].Get<float>();
                prData.dungeon.z = fields[4].Get<float>();
                prData.dungeon.o = fields[5].Get<float>();
                prData.isTeleportingNewMap = false;
                prData.inDungeon = false;

                respawnData[prData.guid] = prData;
                dataCount++;
            }
            while (qResult->NextRow());

            LOG_INFO("module", "Loaded '{}' rows from 'dungeonrespawn_playerinfo' table.", dataCount);
        }
        else
        {
            LOG_INFO("module", "Loaded '0' rows from 'dungeonrespawn_playerinfo' table.");
            return;
        }
    }

    void DSWorldScript::OnShutdown()
    {
        SaveRespawnData();
    }

    void DSWorldScript::SaveRespawnData()
    {
        for (const auto& [guid, prData] : respawnData)
        {
            if (prData.inDungeon)
            {
                CharacterDatabase.Execute(
                    "INSERT INTO `dungeonrespawn_playerinfo` (guid, map, x, y, z, o) VALUES ({}, {}, {}, {}, {}, {}) ON DUPLICATE KEY UPDATE map={}, x={}, y={}, z={}, o={}",
                    prData.guid.GetRawValue(),
                    prData.dungeon.map,
                    prData.dungeon.x,
                    prData.dungeon.y,
                    prData.dungeon.z,
                    prData.dungeon.o,
                    prData.dungeon.map,
                    prData.dungeon.x,
                    prData.dungeon.y,
                    prData.dungeon.z,
                    prData.dungeon.o
                );
            }
            else
            {
                CharacterDatabase.Execute(
                    "DELETE FROM `dungeonrespawn_playerinfo` WHERE guid = {}",
                    prData.guid.GetRawValue()
                );
            }
        }
    }

    PlayerRespawnData* DSPlayerScript::GetOrCreateRespawnData(Player* player)
    {
        ObjectGuid guid = player->GetGUID();

        if (respawnData.find(guid) == respawnData.end())
        {
            PlayerRespawnData newPrData;
            newPrData.guid = guid;
            newPrData.dungeon = {
                -1,
                0.0f,
                0.0f,
                0.0f,
                0.0f
            };
            newPrData.isTeleportingNewMap = false;
            newPrData.inDungeon = false;
            respawnData[guid] = newPrData;
        }

        return &respawnData[guid];
    }

    void DSPlayerScript::OnPlayerMapChanged(Player* player)
    {
        if (!player)
        {
            return;
        }

        auto prData = GetOrCreateRespawnData(player);

        if (!prData)
        {
            return;
        }

        bool inDungeon = IsInsideDungeonRaid(player);
        prData->inDungeon = inDungeon;

        if (!inDungeon)
        {
            return;
        }

        if (!prData->isTeleportingNewMap)
        {
            return;
        }

        prData->dungeon.map = player->GetMapId();
        prData->dungeon.x = player->GetPositionX();
        prData->dungeon.y = player->GetPositionY();
        prData->dungeon.z = player->GetPositionZ();
        prData->dungeon.o = player->GetOrientation();

        prData->isTeleportingNewMap = false;
    }

    void DSPlayerScript::OnPlayerLogin(Player* player)
    {
        if (!player)
        {
            return;
        }

        GetOrCreateRespawnData(player);
    }

    void DSPlayerScript::OnPlayerLogout(Player* player)
    {
        if (!player)
        {
            return;
        }

        std::lock_guard<std::mutex> lock(teleportMutex);
        auto it = std::find(playersToTeleport.begin(), playersToTeleport.end(), player->GetGUID());

        if (it != playersToTeleport.end())
        {
            playersToTeleport.erase(it);
        }
    }
};
