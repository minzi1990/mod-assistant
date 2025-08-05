#include "mod_assistant.h"

bool Assistant::OnGossipHello(Player* player, Creature* creature)
{
    ClearGossipMenuFor(player);

    if (UtilitiesEnabled)
    {
        AddGossipItemFor(player, GOSSIP_ICON_CHAT, GOSSIP_UTILITIES, GOSSIP_SENDER_MAIN, ASSISTANT_GOSSIP_UTILITIES);
    }

    SendGossipMenuFor(player, ASSISTANT_GOSSIP_TEXT, creature->GetGUID());
    return true;
}

bool Assistant::OnGossipSelect(Player* player, Creature* creature, uint32 sender, uint32 action)
{
    if (sender != GOSSIP_SENDER_MAIN)
    {
        return false;
    }

    if (action == ASSISTANT_GOSSIP_UTILITIES)
    {
        ClearGossipMenuFor(player);
        AddGossipItemFor(player, GOSSIP_ICON_VENDOR, GOSSIP_UTILITIES_NAME, GOSSIP_SENDER_MAIN, ASSISTANT_GOSSIP_UTILITIES + 1, GOSSIP_CONTINUE_TRANSACTION, NameChangeCost, false);
        AddGossipItemFor(player, GOSSIP_ICON_VENDOR, GOSSIP_UTILITIES_APPEARANCE, GOSSIP_SENDER_MAIN, ASSISTANT_GOSSIP_UTILITIES + 2, GOSSIP_CONTINUE_TRANSACTION, CustomizeCost, false);
        AddGossipItemFor(player, GOSSIP_ICON_VENDOR, GOSSIP_UTILITIES_RACE, GOSSIP_SENDER_MAIN, ASSISTANT_GOSSIP_UTILITIES + 3, GOSSIP_CONTINUE_TRANSACTION, RaceChangeCost, false);
        AddGossipItemFor(player, GOSSIP_ICON_VENDOR, GOSSIP_UTILITIES_FACTION, GOSSIP_SENDER_MAIN, ASSISTANT_GOSSIP_UTILITIES + 4, GOSSIP_CONTINUE_TRANSACTION, FactionChangeCost, false);
        SendGossipMenuFor(player, ASSISTANT_GOSSIP_TEXT, creature->GetGUID());
    }
    else if (action >= ASSISTANT_GOSSIP_UTILITIES + 1 && action <= ASSISTANT_GOSSIP_UTILITIES + 4)
    {
        ClearGossipMenuFor(player);

        AtLoginFlags flag = AT_LOGIN_NONE;
        uint32 cost = 0;

        switch (action)
        {
        case ASSISTANT_GOSSIP_UTILITIES + 1:
            flag = AT_LOGIN_RENAME;
            cost = NameChangeCost;
            break;
        case ASSISTANT_GOSSIP_UTILITIES + 2:
            flag = AT_LOGIN_CUSTOMIZE;
            cost = CustomizeCost;
            break;
        case ASSISTANT_GOSSIP_UTILITIES + 3:
            flag = AT_LOGIN_CHANGE_RACE;
            cost = RaceChangeCost;
            break;
        case ASSISTANT_GOSSIP_UTILITIES + 4:
            flag = AT_LOGIN_CHANGE_FACTION;
            cost = FactionChangeCost;
            break;
        }

        SetLoginFlag(player, flag, cost);
        CloseGossipMenuFor(player);
    }

    return true;
}