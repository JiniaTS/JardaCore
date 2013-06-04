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

DELETE FROM creature_questrelation WHERE id IN(197, 198, 823, 925);
DELETE FROM creature_involvedrelation WHERE id IN(197, 198, 823, 925);

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

