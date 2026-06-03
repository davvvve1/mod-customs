#include "Customs.h"

void SC_addCustomsScripts()
{
    new CustomQuests::Quest52_WorldScript();
    new CustomQuests::Quest52_PlayerScript();

    new SeasonOfDiscovery::SeasonOfDiscovery_WorldScript();
    new SeasonOfDiscovery::SeasonOfDiscovery_PlayerScript();

    new DungeonRespawn::DSWorldScript();
    new DungeonRespawn::DSPlayerScript();
}
