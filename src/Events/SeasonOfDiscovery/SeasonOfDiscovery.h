//
// Created by development on 5/24/26.
//

#ifndef MOD_CUSTOMS_SOD_H
#define MOD_CUSTOMS_SOD_H

#include "Config.h"
#include "Player.h"
#include "ScriptMgr.h"

#include <unordered_map>

namespace SeasonOfDiscovery
{
    inline bool Enabled = true;
    inline float XPRate = 4.0f;

    class SeasonOfDiscovery_PlayerScript : public PlayerScript
    {
    public:
        SeasonOfDiscovery_PlayerScript() : PlayerScript("SeasonOfDiscovery_PlayerScript", {
            PLAYERHOOK_ON_LOGIN,
            PLAYERHOOK_ON_UPDATE,
            PLAYERHOOK_ON_LOGOUT,
            PLAYERHOOK_ON_GIVE_EXP,
        }) { }

    private:
        void OnPlayerLogin(Player* player) override;
        void OnPlayerUpdate(Player* player, uint32 diff) override;
        void OnPlayerLogout(Player* player) override;
        void OnPlayerGiveXP(Player* player, uint32& amount, Unit* victim, uint8 xpSource) override;

        std::unordered_map<uint32, uint32> _buffCheckTimers;
    };

    class SeasonOfDiscovery_WorldScript : public WorldScript
    {
    public:
        SeasonOfDiscovery_WorldScript() : WorldScript("SeasonOfDiscovery_WorldScript", {
            WORLDHOOK_ON_AFTER_CONFIG_LOAD
        }) { }

    private:
        void OnAfterConfigLoad(bool reload) override;
    };
} // namespace SeasonOfDiscovery

#endif // MOD_CUSTOMS_SOD_H
