#include "mod_assistant.h"

Assistant::Assistant() : CreatureScript("npc_assistant"), WorldScript("AssistantWorldScript") {}

void void AddSC_mod_assistant()
{
    new Assistant();
}
