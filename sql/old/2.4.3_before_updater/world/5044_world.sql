DELETE FROM `command` WHERE `name` = 'updatetitle';
INSERT INTO `command` (`name`, `security`, `help`) VALUES ('updatetitle', 0, 'Syntax: .updatetitle\nFor update title');
