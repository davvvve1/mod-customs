//
// Created by development on 5/24/26.
//

#include "SeasonOfDiscovery.h"

namespace SeasonOfDiscovery
{
    // EventCustomPlayerScript -> sod buff
    constexpr uint32 SPELL_CUSTOM_BUFFS[] = {
        0,      // 0 - Disabled
        80865,  // 1 - 50%
        80866,  // 2 - 100%
        80867,  // 3 - 150%
        80868,  // 4 - 200%
        80869,  // 5 - 250%
        80870   // 6 - 300%
    };

    constexpr uint32 SPELL_WARCHIEFS_BLESSING = 16609;
    constexpr uint32 SPELL_SPIRIT_OF_ZANDALAR = 24425;
    constexpr uint32 WORLD_BUFF_REFRESH_INTERVAL = 30 * 60 * 1000;

    void SeasonOfDiscovery_WorldScript::OnAfterConfigLoad(bool /*reload*/)
    {
        BuffLevel = sConfigMgr->GetOption<uint32>("SOD.buff", 6);

        if (BuffLevel < 1 || BuffLevel > 6)
        {
            Enabled = false;
        }
        else
        {
            Enabled = true;
        }

        LOG_INFO("module", "Season of Discovery enabled: {}", Enabled ? "true" : "false");
    }

    void SeasonOfDiscovery_PlayerScript::OnPlayerLogin(Player* player)
    {
        if (!player)
        {
            return;
        }

        // This prevents them from stacking a sod's buff if the admin changed the config.
        for (uint32 i = 0; i < sizeof(SPELL_CUSTOM_BUFFS) / sizeof(uint32); ++i)
        {
            uint32 spellToCheck = SPELL_CUSTOM_BUFFS[i];

            // If they have a buff that IS NOT the currently configured one, remove it
            if ((spellToCheck != 0) && (spellToCheck != SPELL_CUSTOM_BUFFS[BuffLevel]) && player->HasAura(spellToCheck))
            {
                player->RemoveAura(spellToCheck);
            }
        }

        if (!Enabled)
        {
            return;
        }

        _buffCheckTimers[player->GetGUID().GetCounter()] = WORLD_BUFF_REFRESH_INTERVAL;

        // check if player already have aura then if not then cast aura to player
        if ((SPELL_CUSTOM_BUFFS[BuffLevel] != 0) && !player->HasAura(SPELL_CUSTOM_BUFFS[BuffLevel]))
        {
            player->CastSpell(player, SPELL_CUSTOM_BUFFS[BuffLevel], true);
        }

        if (!player->HasAura(SPELL_WARCHIEFS_BLESSING))
        {
            player->CastSpell(player, SPELL_WARCHIEFS_BLESSING, true);
        }

        if (!player->HasAura(SPELL_SPIRIT_OF_ZANDALAR))
        {
            player->CastSpell(player, SPELL_SPIRIT_OF_ZANDALAR, true);
        }
    }

    void SeasonOfDiscovery_PlayerScript::OnPlayerUpdate(Player* player, uint32 diff)
    {
        if (!Enabled || !player)
        {
            return;
        }

        uint32& buffCheckTimer = _buffCheckTimers[player->GetGUID().GetCounter()];

        if (buffCheckTimer > diff)
        {
            buffCheckTimer -= diff;
            return;
        }

        buffCheckTimer = WORLD_BUFF_REFRESH_INTERVAL;
        player->CastSpell(player, SPELL_WARCHIEFS_BLESSING, true);
        player->CastSpell(player, SPELL_SPIRIT_OF_ZANDALAR, true);
    }

    void SeasonOfDiscovery_PlayerScript::OnPlayerLogout(Player* player)
    {
        if (!player)
        {
            return;
        }

        _buffCheckTimers.erase(player->GetGUID().GetCounter());

        if (!Enabled)
        {
            return;
        }

        // check if player has sod buffs
        for (uint32 i = 0; i < sizeof(SPELL_CUSTOM_BUFFS) / sizeof(uint32); ++i)
        {
            uint32 spellToCheck = SPELL_CUSTOM_BUFFS[i];

            if ((spellToCheck != 0) && player->HasAura(spellToCheck))
            {
                player->RemoveAura(spellToCheck);
            }
        }

        player->RemoveAura(SPELL_WARCHIEFS_BLESSING);
        player->RemoveAura(SPELL_SPIRIT_OF_ZANDALAR);
    }
};
