#ifndef MOD_ASSISTANT_H
#define MOD_ASSISTANT_H

#include "Chat.h"
#include "Config.h"
#include "Player.h"
#include "ScriptMgr.h"
#include "ScriptedGossip.h"

enum
{
    ASSISTANT_GOSSIP_UTILITIES       = 1000,
    ASSISTANT_GOSSIP_TEXT            = 48,
    FRAGMENT_OF_NORTHREND_ID         = 60100
};

#define GOSSIP_UTILITIES "I want character services"
#define GOSSIP_UTILITIES_NAME "I want to change my name"
#define GOSSIP_UTILITIES_APPEARANCE "I want to change my appearance"
#define GOSSIP_UTILITIES_RACE "I want to change my race"
#define GOSSIP_UTILITIES_FACTION "I want to change my faction"
#define GOSSIP_UTILITIES_IN_PROGRESS "You must complete the previously activated feature before trying to perform another."
#define GOSSIP_UTILITIES_DONE "You can now log out to continue using the activated feature."
#define GOSSIP_UTILITIES_NOT_ENOUGH_CURRENCY "You do not have enough Fragments of Northrend for this service."

#define GOSSIP_CONTINUE_TRANSACTION "Do you wish to continue the transaction?"

class Assistant : public CreatureScript, WorldScript
{
public:
    Assistant();

    // CreatureScript
    bool OnGossipHello(Player* /*player*/, Creature* /*creature*/) override;
    bool OnGossipSelect(Player* /*player*/, Creature* /*creature*/, uint32 /*sender*/, uint32 /*action*/) override;

    // WorldScript
    void OnAfterConfigLoad(bool /*reload*/) override;

private:
    // Utilities
    bool UtilitiesEnabled;
    uint32 NameChangeCost;
    uint32 CustomizeCost;
    uint32 RaceChangeCost;
    uint32 FactionChangeCost;

    bool HasLoginFlag(Player* /*player*/);
    void SetLoginFlag(Player* /*player*/, AtLoginFlags /*flag*/, uint32 /*cost*/);
    bool HasEnoughCurrency(Player* /*player*/, uint32 /*cost*/);
    void DeductCurrency(Player* /*player*/, uint32 /*cost*/);
};

#endif