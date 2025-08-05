#include "mod_assistant.h"

bool Assistant::HasLoginFlag(Player* player)
{
    if (player->HasAtLoginFlag(AT_LOGIN_RENAME) || 
        player->HasAtLoginFlag(AT_LOGIN_CUSTOMIZE) || 
        player->HasAtLoginFlag(AT_LOGIN_CHANGE_RACE) || 
        player->HasAtLoginFlag(AT_LOGIN_CHANGE_FACTION))
    {
        return true;
    }

    return false;
}

bool Assistant::HasEnoughCurrency(Player* player, uint32 cost)
{
    return player->GetItemCount(FRAGMENT_OF_NORTHREND_ID) >= cost;
}

void Assistant::DeductCurrency(Player* player, uint32 cost)
{
    player->DestroyItemCount(FRAGMENT_OF_NORTHREND_ID, cost, true);
}

void Assistant::SetLoginFlag(Player* player, AtLoginFlags flag, uint32 cost)
{
    if (HasLoginFlag(player))
    {
        ChatHandler(player->GetSession()).PSendSysMessage(GOSSIP_UTILITIES_IN_PROGRESS);
        return;
    }

    if (!HasEnoughCurrency(player, cost))
    {
        ChatHandler(player->GetSession()).PSendSysMessage(GOSSIP_UTILITIES_NOT_ENOUGH_CURRENCY);
        return;
    }

    DeductCurrency(player, cost);
    player->SetAtLoginFlag(flag);
    ChatHandler(player->GetSession()).PSendSysMessage(GOSSIP_UTILITIES_DONE);
}
