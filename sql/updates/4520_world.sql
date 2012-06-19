ALTER TABLE warden_data_result ADD COLUMN action tinyint unsigned not null default 0 after result;

-- WA_ACT_LOG for all checks
UPDATE warden_data_result SET action = 1;
