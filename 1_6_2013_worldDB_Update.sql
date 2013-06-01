INSERT INTO spell_linked_spell(spell_trigger, spell_effect, TYPE, COMMENT) VALUES
(11366, -48108, 2 'Pyroblast Remove Hot Streak State'),
(34428, -32216, 2, 'Victory Rush remove Victorius state');

-- Try to fix Pyroblast Damage

UPDATE spell_bonus_data SET direct_bonus=2.15, dot_bonus=1.05 WHERE entry=11366;
