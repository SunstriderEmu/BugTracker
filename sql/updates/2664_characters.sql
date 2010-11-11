ALTER TABLE characters
ADD COLUMN `equipmentCache` longtext AFTER exploredZones,
ADD COLUMN `ammoId` int(10) UNSIGNED NOT NULL default '0' AFTER equipmentCache,
ADD COLUMN `knownTitles` longtext AFTER ammoId;

UPDATE characters SET
equipmentCache = SUBSTRING(data, length(SUBSTRING_INDEX(data, ' ', 344))+2, length(SUBSTRING_INDEX(data, ' ', 647+1))- length(SUBSTRING_INDEX(data, ' ', 344)) - 1),
ammoId = SUBSTRING(data, length(SUBSTRING_INDEX(data, ' ', 1487))+2, length(SUBSTRING_INDEX(data, ' ', 1487+1))- length(SUBSTRING_INDEX(data, ' ', 1487)) - 1),
knownTitles = SUBSTRING(data, length(SUBSTRING_INDEX(data, ' ', 924))+2, length(SUBSTRING_INDEX(data, ' ', 925+1))- length(SUBSTRING_INDEX(data, ' ', 924)) - 1);
