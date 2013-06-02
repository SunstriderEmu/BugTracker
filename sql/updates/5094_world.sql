/*  Removing GO_FLAG_INTERACT_COND flag */
update gameobject_template set flags = 0x20 where entry = 184275;