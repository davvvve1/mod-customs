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

    SpellScript* HearthstoneSpellCooldown::GetSpellScript() const
    {
        return new HearthstoneSpellScript();
    }

    void HearthstoneSpellCooldown::HearthstoneSpellScript::HandleAfterCast()
    {
        if (!Enabled)
        {
            return;
        }

        if (Player* player = GetCaster()->ToPlayer())
        {
            uint32 spellId = GetSpellInfo()->Id;
            uint32 itemId = 6948;

            player->RemoveSpellCooldown(spellId, true);

            if (Cooldown > 0)
            {
                player->AddSpellCooldown(spellId, itemId, time(nullptr) + Cooldown, true);
            }
        }
    }

    void HearthstoneSpellCooldown::HearthstoneSpellScript::Register()
    {
        AfterCast += SpellCastFn(HearthstoneSpellCooldown::HearthstoneSpellScript::HandleAfterCast);
    }
} // Hearthstone