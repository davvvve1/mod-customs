//
// Created by development on 5/24/26.
//

#ifndef MOD_CUSTOMS_SOD_H
#define MOD_CUSTOMS_SOD_H

#include "ScriptMgr.h"
#include "Player.h"
#include "Config.h"

namespace SeasonOfDiscovery
{
    extern bool Enabled;

    class sod : public PlayerScript
    {
    public:
        sod() : PlayerScript("sod", {
            PLAYERHOOK_ON_LOGIN,
            PLAYERHOOK_ON_LOGOUT,
        }) { }

        void OnPlayerLogin(Player* player) override;
        void OnPlayerLogout(Player* player) override;
    };
};

#endif //MOD_CUSTOMS_SOD_H
