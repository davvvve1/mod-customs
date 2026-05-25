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

    void SeasonOfDiscovery::OnAfterConfigLoad(bool /*reload*/)
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
    }

    void SeasonOfDiscovery::OnPlayerLogin(Player* player)
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

        // check if player already have aura then if not then cast aura to player
        if ((SPELL_CUSTOM_BUFFS[BuffLevel] != 0) && !player->HasAura(SPELL_CUSTOM_BUFFS[BuffLevel]))
        {
            player->CastSpell(player, SPELL_CUSTOM_BUFFS[BuffLevel], true);
        }
    }

    void SeasonOfDiscovery::OnPlayerLogout(Player* player)
    {
        if (!Enabled || !player)
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
    }
};
