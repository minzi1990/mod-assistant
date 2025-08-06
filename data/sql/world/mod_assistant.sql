SET
@Entry      := 190003,
@Model      := 16496,
@Name       := "Lyra Shiftwhisper",
@Title      := "Veil of Metamorphosis",
@Icon       := "Speak",
@MinLevel   := 30,
@MaxLevel   := 30,
@Faction    := 35,
@NPCFlag    := 3,
@Type       := 7,
@FlagsExtra := 16777218,
@Script     := "npc_assistant";

DELETE FROM `creature_template` WHERE `entry`=@Entry;
INSERT INTO `creature_template` (`entry`, `name`, `subname`, `IconName`, `minlevel`, `maxlevel`, `faction`, `npcflag`, `unit_class`, `unit_flags`, `type`, `flags_extra`, `ScriptName`) VALUES
(@Entry, @Name, @Title, @Icon, @MinLevel, @MaxLevel, @Faction, @NPCFlag, 1, 2, @Type, @FlagsExtra, @Script);

DELETE FROM `creature_template_model` WHERE `CreatureID`=@Entry;
INSERT INTO `creature_template_model` (`CreatureID`, `Idx`, `CreatureDisplayID`, `DisplayScale`, `Probability`) VALUES
(@Entry, 0, @Model, 1, 1);

DELETE FROM `creature` WHERE `id1`=@Entry;
INSERT INTO `creature` (`id1`, `map`, `position_x`, `position_y`, `position_z`, `orientation`) VALUES
(@Entry, 0, -8824.65, 649.467, 94.5585, 4.47955), -- Stormwind City
(@Entry, 0, -4956.91, -932.369, 501.66, 4.77523), -- City of Ironforge
(@Entry, 0, 1590.66, 272.521, -55.3428, 0.361283), -- Undercity
(@Entry, 1, 9929.71, 2507.59, 1318.17, 4.78701), -- Darnassus
(@Entry, 1, 1619.08, -4443.65, 10.869, 1.73804), -- Orgrimmar
(@Entry, 1, -1292.12, 116.913, 131.175, 5.78446), -- Thunder Bluff
(@Entry, 530, -3955.07, -11670, -138.757, 3.29082), -- The Exodar
(@Entry, 530, 9469.83, -7294.44, 14.3078, 0.105431), -- Silvermoon City
(@Entry, 530, -1814.49, 5425.97, -12.4281, 2.87456), -- Shattrath City
(@Entry, 571, 5791.71, 560.464, 650.657, 1.79314); -- Dalaran

-- Create a custom gossip text entry
SET @CustomGossipTextId = 190001; 

DELETE FROM `npc_text` WHERE `ID` = @CustomGossipTextId;
INSERT INTO `npc_text` (`ID`, `text0_0`, `text0_1`, `BroadcastTextId0`, `lang0`, `Probability0`, `em0_0`, `em0_1`, `em0_2`, `em0_3`, `em0_4`, `em0_5`) VALUES 
(@CustomGossipTextId, 
"Greetings, Keeper of the Ancient Legacy. I am Lyra Shiftwhisper, the third awakened guardian of the Eternal Covenant.$B$BWhile my sister Lyralei guards the sacred vault and its treasures, I am the Pathkeeper - guardian of the ancient arts of transformation and identity. The titan-touched magics that flow through me can reshape form, lineage, and even the very bonds of allegiance.$B$BThe shattering of the Lich King's dominion has not only released the crystallized fragments you now collect, but also restored the full power of our transformation rituals. What once required centuries of preparation can now be accomplished through the concentrated essence of broken dominion.$B$BSpeak your desire, and I shall weave the ancient pathways to guide your metamorphosis.", 
"", 0, 0, 1.0, 1, 0, 0, 0, 0, 0);

-- Create the gossip menu entry
DELETE FROM `gossip_menu` WHERE `MenuId` = @CustomGossipTextId;
INSERT INTO `gossip_menu` (`MenuId`, `TextId`) VALUES 
(@CustomGossipTextId, @CustomGossipTextId);