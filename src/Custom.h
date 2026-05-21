#ifndef MODULE_CUSTOM_H
#define MODULE_CUSTOM_H

#include "ScriptMgr.h"
#include "Player.h"
#include "Creature.h"
#include "QuestDef.h"

class QuestCustomPlayerScript : public PlayerScript
{
public:
    QuestCustomPlayerScript() : PlayerScript("QuestCustomPlayerScript", {
        PLAYERHOOK_ON_CREATURE_KILL
    }){ }

    void OnPlayerCreatureKill(Player* player, Creature* creature) override;
};

class EventCustomPlayerScript : public PlayerScript
{
public:
    EventCustomPlayerScript() : PlayerScript("EventCustomPlayerScript", {
        PLAYERHOOK_ON_LOGIN,
        PLAYERHOOK_ON_LOGOUT,
    }) { }

    void OnPlayerLogin(Player* player) override;
    void OnPlayerLogout(Player* player) override;
}

#endif // MODULE_CUSTOM_H
