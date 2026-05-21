#ifndef MODULE_CUSTOM_H
#define MODULE_CUSTOM_H

#include "ScriptMgr.h"
#include "LFGMgr.h"
#include "Player.h"
#include "Creature.h"
#include "Config.h"
#include "Chat.h"
#include "QuestDef.h"
#include "DatabaseEnv.h"

#include <vector>
#include <unordered_map>
#include <mutex>

#pragma region Quests

class QuestCustomPlayerScript : public PlayerScript
{
public:
    QuestCustomPlayerScript() : PlayerScript("QuestCustomPlayerScript", {
        PLAYERHOOK_ON_CREATURE_KILL
    }){ }

    void OnPlayerCreatureKill(Player* player, Creature* creature) override;
};

#pragma endregion

#pragma region Events

class EventCustomPlayerScript : public PlayerScript
{
public:
    EventCustomPlayerScript() : PlayerScript("EventCustomPlayerScript", {
        PLAYERHOOK_ON_LOGIN,
        PLAYERHOOK_ON_LOGOUT,
    }) { }

    void OnPlayerLogin(Player* player) override;
    void OnPlayerLogout(Player* player) override;
};

#pragma endregion

#pragma region DungeonRespawn

struct DungeonData
{
    int32 map;
    float x;
    float y;
    float z;
    float o;
};

struct PlayerRespawnData
{
    ObjectGuid guid;
    DungeonData dungeon;
    bool isTeleportingNewMap;
    bool inDungeon;
};

class DSPlayerScript : public PlayerScript
{
public:
    DSPlayerScript() : PlayerScript("DSPlayerScript", {
        PLAYERHOOK_ON_PLAYER_RELEASED_GHOST,
        PLAYERHOOK_ON_BEFORE_TELEPORT,
        PLAYERHOOK_ON_MAP_CHANGED,
        PLAYERHOOK_ON_LOGIN,
        PLAYERHOOK_ON_LOGOUT,
    }) { }

private:
    std::vector<ObjectGuid> playersToTeleport;
    std::mutex teleportMutex;

    bool IsInsideDungeonRaid(Player* /*player*/);
    void ResurrectPlayer(Player* /*player*/);
    PlayerRespawnData* GetOrCreateRespawnData(Player* /*player*/);

    void OnPlayerReleasedGhost(Player* /*player*/) override;
    bool OnPlayerBeforeTeleport(Player* /*player*/, uint32 /*mapid*/, float /*x*/, float /*y*/, float /*z*/, float /*orientation*/, uint32 /*options*/, Unit* /*target*/) override;
    void OnPlayerMapChanged(Player* /*player*/) override;
    void OnPlayerLogin(Player* /*player*/) override;
    void OnPlayerLogout(Player* /*player*/) override;
};

class DSWorldScript : public WorldScript
{
public:
    DSWorldScript() : WorldScript("DSWorldScript") { }

private:
    void OnAfterConfigLoad(bool /*reload*/) override;
    void OnShutdown() override;
    void SaveRespawnData();
};

#pragma endregion

#endif // MODULE_CUSTOM_H
