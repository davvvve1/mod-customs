//
// Created by development on 5/24/26.
//

#ifndef MOD_CUSTOMS_QUEST52_H
#define MOD_CUSTOMS_QUEST52_H

#include "ScriptMgr.h"
#include "Player.h"
#include "Creature.h"
#include "QuestDef.h"

namespace CustomQuests
{
    inline bool Enabled;

    class Quest52_PlayerScript : public PlayerScript
    {
    public:
        Quest52_PlayerScript() : PlayerScript("Quest52_PlayerScript", {
            PLAYERHOOK_ON_CREATURE_KILL
        }){ }

    private:
        void OnPlayerCreatureKill(Player* player, Creature* creature) override;
    };

    class Quest52_WorldScript : public WorldScript
    {
    public:
        Quest52_WorldScript() : WorldScript("Quest52_WorldScript", {
            WORLDHOOK_ON_AFTER_CONFIG_LOAD
        }){ }

    private:
        void OnAfterConfigLoad(bool /*reload*/) override;
    };
};

#endif //MOD_CUSTOMS_QUEST52_H
