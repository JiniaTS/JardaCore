--Extinguishing Hope Elwynn Forest

DELETE FROM conditions WHERE SourceTypeOrReferenceId=13 AND SourceEntry=80208;
INSERT INTO conditions(SourceTypeOrReferenceId, SourceEntry, ConditionTypeOrReference, ConditionValue1, ConditionValue2, comment)
VALUES (13, 80208, 19, 42940, 2, 'Water Spray'); -- Spray Water requires target Trigger 42940

SET @ENTRY:=42940;
SET @SOURCE:=0;
DELETE FROM smart_scripts WHERE entryorguid=@ENTRY AND source_type=@SOURCE;
UPDATE creature_template SET AIName='SmartAI' WHERE entry=@ENTRY;
INSERT INTO smart_scripts(entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, target_type, comment) VALUES
(@ENTRY, @SOURCE, 0, 0, 25, 0, 100, 0, 0, 0, 0, 22, 1, 0, 0, 1, 'On Reset Set Phase 1'),
(@ENTRY, @SOURCE, 1, 0, 23, 1, 100, 80175, 0, 0, 0, 11, 80175, 0, 0, 1, 'On Phase One Set Visual Fire');
