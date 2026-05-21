#include "Custom.h"

namespace
{
    // 
    constexpr uint32 QUEST_ID = 52;
    constexpr uint32 CREATURE_PROWLER_ID = 118;
    constexpr uint32 CREATURE_GRAY_FOREST_WOLF = 1922;

    // EventCustomPlayerScript -> sod buff
    // constexpr uint32 SPELL_CUSTOM_BUFF = 80865; // 50%
    // constexpr uint32 SPELL_CUSTOM_BUFF = 80866; // 100%
    // constexpr uint32 SPELL_CUSTOM_BUFF = 80867; // 150%
    // constexpr uint32 SPELL_CUSTOM_BUFF = 80868; // 200%
    // constexpr uint32 SPELL_CUSTOM_BUFF = 80869; // 250%
    constexpr uint32 SPELL_CUSTOM_BUFF = 80870; // 300%
}

void QuestCustomPlayerScript::OnPlayerCreatureKill(Player* player, Creature* creature)
{
    if (!player || !creature)
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

void EventCustomPlayerScript::OnPlayerLogin(Player* player)
{
    if (!player)
    {
        return;
    }
    
    // check if player already have aura then if not then cast aura to player
    if (!player->HasAura(SPELL_CUSTOM_BUFF))
    {
        player->CastSpell(player, SPELL_CUSTOM_BUFF, true);
    }
}

void EventCustomPlayerScript::OnPlayerLogout(Player* player)
{
    if (!player)
    {
        return;
    }

    // check if player has that aura then remove
    if (player->HasAura(SPELL_CUSTOM_BUFF))
    {
        player->RemoveAura(SPELL_CUSTOM_BUFF);
    }
}

void CustomScripts()
{
    new QuestCustomPlayerScript();
    new EventCustomPlayerScript();
}
