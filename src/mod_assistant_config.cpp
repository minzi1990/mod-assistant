#include "mod_assistant.h"

void Assistant::OnAfterConfigLoad(bool /*reload*/)
{
    // Character Services
    UtilitiesEnabled = sConfigMgr->GetOption<bool>("Assistant.Utilities.Enabled", 1);
    NameChangeCost = sConfigMgr->GetOption<uint32>("Assistant.Utilities.NameChange.Cost", 1);
    CustomizeCost = sConfigMgr->GetOption<uint32>("Assistant.Utilities.Customize.Cost", 2);
    RaceChangeCost = sConfigMgr->GetOption<uint32>("Assistant.Utilities.RaceChange.Cost", 5);
    FactionChangeCost = sConfigMgr->GetOption<uint32>("Assistant.Utilities.FactionChange.Cost", 10);
}