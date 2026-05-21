SET @ENTRY := 52;

UPDATE `quest_template`
SET `LogDescription` = 'Kill 8 Prowlers or Gray Forest Wolves and 5 Young Forest Bears, and then return to Guard Thomas at the east Elynn bridge.'
WHERE `ID` = @ENTRY;
