UPDATE version SET core_version = "Winrunner Rev: 6036";

#update Teron HP & no taunt
UPDATE creature_template SET minhealth = 4956765, maxhealth =  4956765, flags_extra = 1 + 0x00010000 WHERE entry = 22871;
UPDATE creature_template SET minhealth = 60000, maxhealth =  60000, flags_extra = 0x00010000 WHERE entry = 23111;
