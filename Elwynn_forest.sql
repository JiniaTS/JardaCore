-- Extinguishing Hope Elwynn Forest

DELETE FROM conditions WHERE SourceTypeOrReferenceId=13 AND SourceEntry=80208;
INSERT INTO conditions(SourceTypeOrReferenceId, SourceEntry, ConditionTypeOrReference, ConditionValue1, ConditionValue2, comment)
VALUES (13, 80208, 19, 42940, 2, 'Water Spray'); -- Spray Water requires target Trigger 42940


-- Northshire Vineyards Fire Trigger
SET @ENTRY := 42940;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,25,0,100,0,0,0,0,0,22,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Reset Set Phase 1"),
(@ENTRY,@SOURCETYPE,1,0,23,1,100,0,80175,0,0,0,11,80175,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"--Fire visual"),
(@ENTRY,@SOURCETYPE,2,3,8,1,100,0,80208,0,0,0,33,42940,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Spell Hit"),
(@ENTRY,@SOURCETYPE,3,0,61,1,100,0,0,0,0,0,22,2,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On spell hit set phase 2"),
(@ENTRY,@SOURCETYPE,4,0,8,2,100,0,80208,0,0,0,37,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On spell hit die");

-- Mage
UPDATE quest_template SET NextQuestIdChain=28769 WHERE Id=28757; -- Beating Them Back!
UPDATE quest_template SET NextQuestIdChain=3104, PrevQuestId=28757 WHERE Id=28769; -- Lions for Lambs.
UPDATE quest_template SET NextQuestIdChain=26916, PrevQuestId=28769 WHERE Id=3104; -- Glyphic Letter
UPDATE quest_template SET NextQuestIdChain=28784, PrevQuestId=3104 WHERE Id=26916; -- Mastering the Arcane
UPDATE quest_template SET NextQuestIdChain=28792, PrevQuestId=26916 WHERE Id=28784; -- Join the Battle
UPDATE quest_template SET NextQuestIdChain=28823, PrevQuestId=28784 WHERE Id=28792; -- They Sent Assassins
UPDATE quest_template SET NextQuestIdChain=26389, PrevQuestId=28792 WHERE Id=28823; -- The Rear is Clear
UPDATE quest_template SET RequiredClasses=128, RequiredRaces=1 WHERE Id IN(28757, 28769, 3104, 26916, 28784, 28792);
-- Paladin 
UPDATE quest_template SET NextQuestIdChain=28770 WHERE Id=28762; -- Beating Them Back!
UPDATE quest_template SET NextQuestIdChain=3101, PrevQuestId=28762 WHERE Id=28770; -- Lions for Lambs.
UPDATE quest_template SET NextQuestIdChain=26918, PrevQuestId=28770 WHERE Id=3101; -- Consecrated Letter
UPDATE quest_template SET NextQuestIdChain=28785, PrevQuestId=3101 WHERE Id=26918; -- The Power of the Light
UPDATE quest_template SET NextQuestIdChain=28797, PrevQuestId=26918 WHERE Id=28785; -- Join the Battle
UPDATE quest_template SET NextQuestIdChain=28823, PrevQuestId=28785 WHERE Id=28797; -- They Sent Assassins
UPDATE quest_template SET NextQuestIdChain=26389, PrevQuestId=28797 WHERE Id=28823; -- The Rear is Clear
UPDATE quest_template SET RequiredClasses=2, RequiredRaces=1 WHERE Id IN(28762, 28770, 3101, 26918, 28785, 28797);

DELETE FROM creature_questrelation WHERE quest=26913;
DELETE FROM creature_involvedrelation WHERE quest=3102;
DELETE FROM creature_questrelation WHERE id IN(197, 198, 823, 925, 911, 915, 43278, 375, 459);
DELETE FROM creature_involvedrelation WHERE id IN(197, 198, 823, 925, 911, 915, 43278, 375, 459);

-- Mage
UPDATE quest_template SET NextQuestIdChain=28823, PrevQuestId=28784 WHERE Id=28792; -- They Sent Assassins
UPDATE quest_template SET NextQuestIdChain=26389, PrevQuestId=28792 WHERE Id=28823; -- The Rear is Clear
UPDATE quest_template SET RequiredClasses=128, RequiredRaces=1 WHERE Id IN(28757, 28769, 3104, 26916, 28784, 28792, 28823);

-- Paladin
UPDATE quest_template SET NextQuestIdChain=28817, PrevQuestId=28785 WHERE Id=28797; -- They Sent Assassins
UPDATE quest_template SET NextQuestIdChain=26389, PrevQuestId=28797 WHERE Id=28817; -- The Rear is Clear
UPDATE quest_template SET RequiredClasses=2, RequiredRaces=1 WHERE Id IN(28762, 28770, 3101, 26918, 28785, 28797, 28817);

-- Rogue
UPDATE quest_template SET NextQuestIdChain=28772 WHERE Id=28764; -- Beating Them Back!
UPDATE quest_template SET NextQuestIdChain=3102, PrevQuestId=28764 WHERE Id=28772; -- Lions for Lambs
UPDATE quest_template SET NextQuestIdChain=26915, PrevQuestId=28764 WHERE Id=3102; -- Encrypted Letter
UPDATE quest_template SET NextQuestIdChain=28787, PrevQuestId=3102 WHERE Id=26915; -- The Deepest Cut
UPDATE quest_template SET NextQuestIdChain=28795, PrevQuestId=26915 WHERE Id=28787; -- Join the Battle
UPDATE quest_template SET NextQuestIdChain=28821, PrevQuestId=28787 WHERE Id=28795; -- They Sent Assassins
UPDATE quest_template SET NextQuestIdChain=26389, PrevQuestId=28795 WHERE Id=28821; -- The Rear is Clear
UPDATE quest_template SET RequiredClasses=8, RequiredRaces=1 WHERE Id IN(28772, 28764, 3102, 26915, 28787, 28795, 28821);

-- Hunter
UPDATE quest_template SET NextQuestIdChain=28759 WHERE Id=28767; -- Beating Them Back!
UPDATE quest_template SET NextQuestIdChain=26910, PrevQuestId=28767 WHERE Id=28759; -- Lions for Lambs
UPDATE quest_template SET NextQuestIdChain=26917, PrevQuestId=28759 WHERE Id=26910; -- Etched Letter
UPDATE quest_template SET NextQuestIdChain=28780, PrevQuestId=26910 WHERE Id=26917; -- The Hunter's Path
UPDATE quest_template SET NextQuestIdChain=28791, PrevQuestId=26917 WHERE Id=28780; -- Join the Battle
UPDATE quest_template SET NextQuestIdChain=28820, PrevQuestId=28780 WHERE Id=28791; -- They Sent Assassins
UPDATE quest_template SET NextQuestIdChain=26389, PrevQuestId=28791 WHERE Id=28820; -- The Rear is Clear
UPDATE quest_template SET RequiredClasses=4, RequiredRaces=1 WHERE Id IN(28767, 28759, 26910, 26917, 28780, 28791, 28820);

-- Priest
UPDATE quest_template SET NextQuestIdChain=28771 WHERE Id=28763; -- Beating Them Back!
UPDATE quest_template SET NextQuestIdChain=3103, PrevQuestId=28763 WHERE Id=28771; -- Lions for Lambs
UPDATE quest_template SET NextQuestIdChain=26919, PrevQuestId=28771 WHERE Id=3103; -- Hallowed Letter
UPDATE quest_template SET NextQuestIdChain=28786, PrevQuestId=3103 WHERE Id=26919; -- Learning the Word
UPDATE quest_template SET NextQuestIdChain=28796, PrevQuestId=26919 WHERE Id=28786; -- Join the Battle
UPDATE quest_template SET NextQuestIdChain=28822, PrevQuestId=28786 WHERE Id=28796; -- They Sent Assassins
UPDATE quest_template SET NextQuestIdChain=26389, PrevQuestId=28796 WHERE Id=28822; -- The Rear is Clear
UPDATE quest_template SET RequiredClasses=16, RequiredRaces=1 WHERE Id IN(28763, 28771, 3103, 26919, 28786, 28796, 28822);

-- Warlock
UPDATE quest_template SET NextQuestIdChain=28773 WHERE Id=28765; -- Beating Them Back!
UPDATE quest_template SET NextQuestIdChain=3105, PrevQuestId=28765 WHERE Id=28773; -- Lions for Lambs
UPDATE quest_template SET NextQuestIdChain=26914, PrevQuestId=28773 WHERE Id=3105; -- Tainted Letter
UPDATE quest_template SET NextQuestIdChain=28788, PrevQuestId=3105 WHERE Id=26914; -- Corruption
UPDATE quest_template SET NextQuestIdChain=28794, PrevQuestId=26914 WHERE Id=28788; -- Join the Battle
UPDATE quest_template SET NextQuestIdChain=28819, PrevQuestId=28788 WHERE Id=28794; -- They Sent Assassins
UPDATE quest_template SET NextQuestIdChain=26389, PrevQuestId=28794 WHERE Id=28819; -- The Rear is Clear
UPDATE quest_template SET RequiredClasses=256, RequiredRaces=1 WHERE Id IN(28765, 28773, 3105, 26914, 28788, 28794, 28819);

-- Warrior
UPDATE quest_template SET NextQuestIdChain=28774 WHERE Id=28766; -- Beating Them Back!
UPDATE quest_template SET NextQuestIdChain=3100, PrevQuestId=28766 WHERE Id=28774; -- Lions for Lambs
UPDATE quest_template SET NextQuestIdChain=26913, PrevQuestId=28774 WHERE Id=3100; -- Simple Letter
UPDATE quest_template SET NextQuestIdChain=28789, PrevQuestId=3100 WHERE Id=26913; -- Charging into Battle
UPDATE quest_template SET NextQuestIdChain=28793, PrevQuestId=26913 WHERE Id=28789; -- Join the Battle
UPDATE quest_template SET NextQuestIdChain=28818, PrevQuestId=28789 WHERE Id=28793; -- They Sent Assassins
UPDATE quest_template SET NextQuestIdChain=26389, PrevQuestId=28793 WHERE Id=28818; -- The Rear is Clear
UPDATE quest_template SET RequiredClasses=1, RequiredRaces=1 WHERE Id IN(28766, 28774, 3100, 26913, 28789, 28793, 28818);


INSERT INTO creature_questrelation(id, quest) VALUES
(197, 28772),
(197, 28767),
(197, 28763),
(197, 28765),
(197, 28766),
(197, 28764),
(197, 28759),
(197, 28771),
(197, 28773),
(197, 28774),
(197, 3102),
(197, 26910),
(197, 3103),
(197, 3105),
(197, 3100),
(911, 26913),
(911, 28789),
(459, 26914),
(459, 28788),
(375, 26919),
(375, 28786),
(43278, 26917),
(43278, 28780),
(915, 26915),
(915, 28787),
(823, 28793),
(823, 28794), 
(823, 28796),
(823, 28791),
(823, 28795),
(823, 28818),
(823, 28819),
(823, 28822),
(823, 28820),
(823, 28821);

INSERT INTO creature_involvedrelation(id, quest) VALUES
(197, 28772),
(197, 28767),
(197, 28763),
(197, 28765),
(197, 28766),
(197, 28764),
(197, 28759),
(197, 28771),
(197, 28773),
(197, 28774),
(915, 3102),
(43278, 26910),
(375, 3103),
(459, 3105),
(911, 3100),
(911, 26913),
(823, 28789),
(459, 26914),
(823, 28788),
(375, 26919),
(823, 28786),
(43278, 26917),
(823, 28780),
(915, 26915),
(823, 28787),
(823, 28793),
(823, 28794),
(823, 28796),
(823, 28791),
(823, 28795),
(197, 28818),
(197, 28819),
(197, 28822),
(197, 28820),
(197, 28821);

INSERT INTO creature_questrelation(id, quest) VALUES
(198, 28784),
(198, 26916),
(925, 28785),
(925, 26918),
(197, 28762),
(197, 28757),
(197, 28769),
(197, 3104),
(197, 3101),
(823, 28792),
(823, 28797),
(823, 28823);

INSERT INTO creature_involvedrelation(id, quest) VALUES
(823, 28784),
(198, 26916),
(823, 28785),
(925, 26918),
(197, 28762),
(197, 28757),
(197, 28769),
(198, 3104),
(925, 3101),
(823, 28792),
(823, 28797),
(197, 28823); 

DELETE FROM creature_questrelation WHERE id IN(49871, 49874);

UPDATE creature_template SET AIName='SmartAI', unit_flags=131072, faction_A=7, faction_H=7, unit_flags2=2048 WHERE entry=44548;
DELETE FROM `smart_scripts` WHERE `entryorguid`=-168266 AND `id`=0 AND `source_type`=0 LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES (-168266,0,0,0,8,0,100,0,100,0,0,0,33,44548,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Spell Hit get quest credit--Warrior");
UPDATE quest_template SET RequiredNpcOrGo1=44548 WHERE Id=26913;
