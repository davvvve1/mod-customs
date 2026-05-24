//
// Created by development on 5/24/26.
//

#ifndef MOD_CUSTOMS_HEARTHSTONE_H
#define MOD_CUSTOMS_HEARTHSTONE_H

#include "ScriptMgr.h"
#include "Player.h"
#include "Config.h"
#include "SpellScript.h"
#include "SpellScriptLoader.h"

namespace Hearthstone
{
    extern bool Enabled;
    extern uint32 cooldown;

    class HearthstoneWorld : public WorldScript
    {
    public:
        HearthstoneWorld() : WorldScript("HearthstoneWorld", {
            WORLDHOOK_ON_BEFORE_CONFIG_LOAD
        }) { }

        void OnBeforeConfigLoad(bool /*reload*/) override;
    };

    class HearthstoneSpellCooldown : public SpellScriptLoader
    {
    public:
        HearthstoneSpellCooldown() : SpellScriptLoader("HearthstoneSpellCooldown") { }

        SpellScript* GetSpellScript() const override;

        class HearthstoneSpellScript : public SpellScript
        {
            PrepareSpellScript(HearthstoneSpellScript);

            void HandleAfterCast();
            void Register() override;
        };
    };
} // Hearthstone

#endif //MOD_CUSTOMS_HEARTHSTONE_H