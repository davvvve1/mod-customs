//
// Created by development on 5/24/26.
//

#include "Hearthstone.h"

namespace Hearthstone
{
    bool Enabled = true;
    uint32 Cooldown = 1;

    void HearthstoneWorld::OnBeforeConfigLoad(bool /*reload*/)
    {
        Enabled = sConfigMgr->GetOption<bool>("Hearthstone.cEnabled", true);
        Cooldown = sConfigMgr->GetOption<uint32>("Hearthstone.Cooldown", 1);
    }

    void HearthstoneWorld::OnStartup()
    {
        if (!Enabled)
        {
            return;
        }

        SpellInfo* hsPell = const_cast<SpellInfo*>(sSpellMgr->GetSpellInfo(8690));

        if (hsSpell)
        {
            // The core stores RecoveryTime in milliseconds, so we multiply by 1000
            uint32 newCooldownMs = Cooldown * 1000;

            // Update both the spell's absolute cooldown and its category shared cooldown
            hsSpell->RecoveryTime = newCooldownMs;
            hsSpell->CategoryRecoveryTime = newCooldownMs;
        }
    }
} // Hearthstone