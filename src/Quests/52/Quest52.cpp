//
// Created by development on 5/24/26.
//

#include "Quest52.h"

namespace CustomQuests
{
    // Quest 52
    constexpr uint32 QUEST_ID = 52;
    constexpr uint32 CREATURE_PROWLER_ID = 118;
    constexpr uint32 CREATURE_GRAY_FOREST_WOLF = 1922;

    void OnAfterConfigLoad(bool /*reload*/)
    {
        Enabled = sConfigMgr->GetOption<bool>("Quests52.Enabled", true);
    }

    void Quest52::OnPlayerCreatureKill(Player* player, Creature* creature)
    {
        if (!Enabled || !player || !creature)
        {
            return;
        }

        // https://www.wowhead.com/cata/quest=52/protect-the-frontier
        // Quest 52 - Kill 8 Prowlers or Gray Forest Wolves and 5 Young Forest Bears, and then return to Guard Thomas at the east Elwynn bridge.
        if (creature->GetEntry() == CREATURE_GRAY_FOREST_WOLF)
        {
            if (player->GetQuestStatus(QUEST_ID) == QUEST_STATUS_INCOMPLETE)
            {
                player->KilledMonsterCredit(CREATURE_PROWLER_ID);
            }
        }
    }
};
