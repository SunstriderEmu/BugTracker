UPDATE creature c 
 JOIN creature_template ct ON c.id = ct.entry AND c.modelid = ct.modelid1
SET c.modelid = 0;