#shadow priest
SET @CLASS := 5;
SET @COMMAND := "additemset 658;additem 28134 1;additem 34792 1;additem 27462 1;additem 27795 1;additem 27451 1;additem 27784 1;additem 28227 1;additem 28223 1;additem 27683 1;additem 27937 1;additem 28187 1;additem 25939 1";
SET @STUFF := 0;
REPLACE INTO recups_data VALUES (@CLASS,0,2,@COMMAND,0,@STUFF,0);

#warlock
SET @CLASS := 9;
SET @COMMAND := "additemset 644;additem 28134 1;additem 34792 1;additem 27462 1;additem 27795 1;additem 27902 1;additem 27784 1;additem 28227 1;additem 28223 1;additem 27683 1;additem 27543 1;additem 28187 1;additem 25939 1";
SET @STUFF := 0;
REPLACE INTO recups_data VALUES (@CLASS,0,2,@COMMAND,0,@STUFF,0);

#Mage
SET @CLASS := 8;
SET @COMMAND := "additemset 647;additem 28134 1;additem 34792 1;additem 27462 1;additem 27795 1;additem 27902 1;additem 27784 1;additem 28227 1;additem 28223 1;additem 28418 1;additem 27905 1;additem 28187 1;additem 25939 1";
SET @STUFF := 0;
REPLACE INTO recups_data VALUES (@CLASS,0,2,@COMMAND,0,@STUFF,0);
