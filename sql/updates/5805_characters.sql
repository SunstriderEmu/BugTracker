ALTER TABLE `item_instance`
    MODIFY `container_guid` BIGINT(12),
    MODIFY `creator` BIGINT(12),
    MODIFY `gift_creator` BIGINT(12);
	
ALTER TABLE `characters`
    MODIFY `extra_flags` SMALLINT(4);