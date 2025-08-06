#ifndef MOD_ASSISTANT_H
#define MOD_ASSISTANT_H

#include "Chat.h"
#include "Config.h"
#include "Player.h"
#include "ScriptMgr.h"
#include "ScriptedGossip.h"
#include <string>

void Addmod_assistantScripts();

enum
{
    ASSISTANT_GOSSIP_UTILITIES       = 1000,
    ASSISTANT_GOSSIP_TEXT            = 190001, // Changed from 48 to our custom text ID
    FRAGMENT_OF_NORTHREND_ID         = 60100
};

#define GOSSIP_UTILITIES "I wish to walk the ancient pathways of transformation"
#define GOSSIP_UTILITIES_NAME "I wish to shed my current name"
#define GOSSIP_UTILITIES_APPEARANCE "I desire to reshape my form"
#define GOSSIP_UTILITIES_RACE "I seek to embrace a new lineage"
#define GOSSIP_UTILITIES_FACTION "I would align myself with new allies"
#define GOSSIP_UTILITIES_IN_PROGRESS "The pathways are already shifting around you. Complete your current transformation before attempting to walk another path."
#define GOSSIP_UTILITIES_DONE "The ancient pathway opens before you. When next you awaken from rest, the transformation will be complete."
#define GOSSIP_UTILITIES_NOT_ENOUGH_CURRENCY "The pathways require crystallized essence - Fragments of Northrend - which you do not possess in sufficient quantity."

#define GOSSIP_CONTINUE_TRANSACTION "The pathway once opened cannot be unchanged. Do you truly wish to proceed?"

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
