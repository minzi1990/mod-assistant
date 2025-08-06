#include "mod_assistant.h"

bool Assistant::OnGossipHello(Player* player, Creature* creature)
{
    uint32 welcomeQuestId = 70004; 
    
    // Check if player has completed the welcome quest
    if (!player->GetQuestRewardStatus(welcomeQuestId))
    {
        return false; // This tells AzerothCore to use default quest handling
    }
    
    ClearGossipMenuFor(player);
    
    if (UtilitiesEnabled)
    {
        AddGossipItemFor(player, GOSSIP_ICON_CHAT, "I wish to walk the ancient pathways of transformation", GOSSIP_SENDER_MAIN, ASSISTANT_GOSSIP_UTILITIES);
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
        
        // Build dynamic gossip text with actual costs
        std::string nameText = "Pathway of Renaming - Forge a new identity";
        std::string customizeText = "Pathway of Reshaping - Transform your physics";
        std::string raceText = "Pathway of Lineage - Embrace new racial heritage";
        std::string factionText = "Pathway of Allegiance - Shift your factional bonds";
        
        // Build confirmation texts with actual costs
        std::string nameConfirm = "Through the crystallized essence of broken dominion, I can weave a pathway that allows you to choose a new name. This requires " + std::to_string(NameChangeCost) + " Fragments of Northrend. Shall I open this path?";
        std::string customizeConfirm = "The ancient magics can reshape your physical form while preserving your essence and memories. This transformation requires " + std::to_string(CustomizeCost) + " Fragments of Northrend. Shall I open this path?";
        std::string raceConfirm = "This powerful pathway allows you to walk among a different race while retaining your abilities and experiences. The crystallized essence required is " + std::to_string(RaceChangeCost) + " Fragments of Northrend. Shall I open this path?";
        std::string factionConfirm = "The most complex pathway - one that changes not just your form, but your standing in this world's great conflict. This profound transformation requires " + std::to_string(FactionChangeCost) + " Fragments of Northrend. Shall I open this path?";
        
        AddGossipItemFor(player, GOSSIP_ICON_VENDOR, nameText.c_str(), GOSSIP_SENDER_MAIN, ASSISTANT_GOSSIP_UTILITIES + 1, nameConfirm.c_str(), 0, false);
        AddGossipItemFor(player, GOSSIP_ICON_VENDOR, customizeText.c_str(), GOSSIP_SENDER_MAIN, ASSISTANT_GOSSIP_UTILITIES + 2, customizeConfirm.c_str(), 0, false);
        AddGossipItemFor(player, GOSSIP_ICON_VENDOR, raceText.c_str(), GOSSIP_SENDER_MAIN, ASSISTANT_GOSSIP_UTILITIES + 3, raceConfirm.c_str(), 0, false);
        AddGossipItemFor(player, GOSSIP_ICON_VENDOR, factionText.c_str(), GOSSIP_SENDER_MAIN, ASSISTANT_GOSSIP_UTILITIES + 4, factionConfirm.c_str(), 0, false);
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
