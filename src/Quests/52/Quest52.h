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
    bool Enabled;

    class Quest52 : public PlayerScript, public WorldScript
    {
    public:
        Quest52() : PlayerScript("Quest52", {
            PLAYERHOOK_ON_CREATURE_KILL
        }),
        WorldScript("Quest52", {
            WORLDHOOK_ON_AFTER_CONFIG_LOAD
        }){ }

    private:
        void OnAfterConfigLoad(bool /*reload*/) override;
        void OnPlayerCreatureKill(Player* player, Creature* creature) override;
    };
};

#endif //MOD_CUSTOMS_QUEST52_H
