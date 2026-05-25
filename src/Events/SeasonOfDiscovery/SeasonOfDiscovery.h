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
    bool Enabled;
    uint32 BuffLevel;

    class SeasonOfDiscovery : public PlayerScript, public WorldScript
    {
    public:
        SeasonOfDiscovery() : PlayerScript("SeasonOfDiscovery", {
            PLAYERHOOK_ON_LOGIN,
            PLAYERHOOK_ON_LOGOUT,
        }),
        WorldScript("SeasonOfDiscovery", {
            WORLDHOOK_ON_AFTER_CONFIG_LOAD
        }) { }

    private:
        void OnAfterConfigLoad(bool /*reload*/) override;
        void OnPlayerLogin(Player* player) override;
        void OnPlayerLogout(Player* player) override;
    };
}; // SeasonOfDiscovery

#endif //MOD_CUSTOMS_SOD_H
