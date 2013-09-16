/* change some door autoclose timer 10485760 = 1 minute */
UPDATE gameobject_template set data2 = 10485760 where entry = 184164
OR entry = 183450
OR entry = 184276
OR entry = 176694;