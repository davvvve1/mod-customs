//
// Created by development on 5/24/26.
//

#include "SeasonOfDiscovery.h"

#include <algorithm>
#include <limits>

namespace SeasonOfDiscovery
{
    constexpr uint32 SPELL_WARCHIEFS_BLESSING = 16609;
    constexpr uint32 SPELL_SPIRIT_OF_ZANDALAR = 24425;
    constexpr uint32 WORLD_BUFF_REFRESH_INTERVAL = 30 * 60 * 1000;

    void SeasonOfDiscovery_WorldScript::OnAfterConfigLoad(bool /*reload*/)
    {
        Enabled = sConfigMgr->GetOption<bool>("SOD.Enabled", true);
        XPRate = sConfigMgr->GetOption<float>("SOD.XPRate", 4.0f);

        if (XPRate < 0.0f)
        {
            XPRate = 0.0f;
        }

        LOG_INFO("module", "Season of Discovery enabled: {}", Enabled ? "true" : "false");
        LOG_INFO("module", "Season of Discovery XP rate: {:.2f}x", XPRate);
    }

    void SeasonOfDiscovery_PlayerScript::OnPlayerLogin(Player* player)
    {
        if (!Enabled || !player)
        {
            return;
        }

        _buffCheckTimers[player->GetGUID().GetCounter()] = WORLD_BUFF_REFRESH_INTERVAL;

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

        if (!player->HasAura(SPELL_WARCHIEFS_BLESSING))
        {
            player->CastSpell(player, SPELL_WARCHIEFS_BLESSING, true);
        }

        if (!player->HasAura(SPELL_SPIRIT_OF_ZANDALAR))
        {
            player->CastSpell(player, SPELL_SPIRIT_OF_ZANDALAR, true);
        }
    }

    void SeasonOfDiscovery_PlayerScript::OnPlayerLogout(Player* player)
    {
        if (!player)
        {
            return;
        }

        _buffCheckTimers.erase(player->GetGUID().GetCounter());

        player->RemoveAura(SPELL_WARCHIEFS_BLESSING);
        player->RemoveAura(SPELL_SPIRIT_OF_ZANDALAR);
    }

    void SeasonOfDiscovery_PlayerScript::OnPlayerGiveXP(Player* player, uint32& amount, Unit* /*victim*/, uint8 /*xpSource*/)
    {
        if (!Enabled || !player || amount == 0 || XPRate <= 0.0f)
        {
            return;
        }

        double scaledAmount = static_cast<double>(amount) * static_cast<double>(XPRate);
        scaledAmount = std::min(scaledAmount, static_cast<double>(std::numeric_limits<uint32>::max()));
        amount = static_cast<uint32>(scaledAmount);
    }
} // namespace SeasonOfDiscovery
