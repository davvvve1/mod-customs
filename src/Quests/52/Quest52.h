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
    extern bool Enabled;

    class Quest52 : public PlayerScript
    {
    public:
        Quest52() : PlayerScript("Quest52", {
            PLAYERHOOK_ON_CREATURE_KILL
        }){ }

    private:
        void OnPlayerCreatureKill(Player* player, Creature* creature) override;
    };
};

#endif //MOD_CUSTOMS_QUEST52_H
