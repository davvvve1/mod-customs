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
            WORLDHOOK_ON_BEFORE_CONFIG_LOAD,
            WORLDHOOK_ON_STARTUP
        }) { }

        void OnBeforeConfigLoad(bool /*reload*/) override;
        void OnStartup() override;
    };
} // Hearthstone

#endif //MOD_CUSTOMS_HEARTHSTONE_H