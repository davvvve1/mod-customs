//
// Created by development on 5/24/26.
//

#include "sod.h"

namespace SeasonOfDiscovery
{
    bool Enabled = true;

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

    // Helper function to read the config and safely get the spell ID
    static uint32 GetConfiguredSodBuff()
    {
        uint32 buffLevel = sConfigMgr->GetOption<uint32>("SOD.buff", 6);

        if (buffLevel < 1 || buffLevel > 6)
        {
            Enabled = false;
            return 0;
        }

        return SPELL_CUSTOM_BUFFS[buffLevel];
    }

    void sod::OnPlayerLogin(Player* player)
    {
        if (!Enabled || !player)
        {
            return;
        }

        uint32 abuff = GetConfiguredSodBuff();

        // This prevents them from stacking a sod's buff if the admin changed the config.
        for (int i = 0; i <= 6; ++i)
        {
            uint32 spellToCheck = SPELL_CUSTOM_BUFFS[i];

            // If they have a buff that IS NOT the currently configured one, remove it
            if ((spellToCheck != 0) && (spellToCheck != abuff) && player->HasAura(spellToCheck))
            {
                player->RemoveAura(spellToCheck);
            }
        }

        // check if player already have aura then if not then cast aura to player
        if ((abuff != 0) && !player->HasAura(abuff))
        {
            player->CastSpell(player, abuff, true);
        }
    }

    void sod::OnPlayerLogout(Player* player)
    {
        if (!Enabled || !player)
        {
            return;
        }

        // check if player has sod buffs
        for (int i = 0; i <= 6; ++i)
        {
            uint32 spellToCheck = SPELL_CUSTOM_BUFFS[i];

            if ((spellToCheck != 0) && player->HasAura(spellToCheck))
            {
                player->RemoveAura(spellToCheck);
            }
        }
    }
};
