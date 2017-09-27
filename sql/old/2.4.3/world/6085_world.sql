/*
SQLyog Community v9.63 
MySQL - 5.5.32-MariaDB : Database - wrworld
*********************************************************************
*/

/*!40101 SET NAMES utf8 */;

/*!40101 SET SQL_MODE=''*/;

/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;
/*Table structure for table `game_event_fireworks` */

DROP TABLE IF EXISTS `game_event_fireworks`;

CREATE TABLE `game_event_fireworks` (
  `groupid` smallint(5) unsigned NOT NULL,
  `time` int(10) unsigned NOT NULL DEFAULT '0',
  `spellorgob` int(11) NOT NULL DEFAULT '0',
  `size` float NOT NULL DEFAULT '1',
  `posX` tinyint(3) unsigned NOT NULL DEFAULT '0',
  `posY` tinyint(3) unsigned NOT NULL DEFAULT '0',
  `ori` float NOT NULL DEFAULT '0',
  `morphX` float NOT NULL DEFAULT '0',
  `morphY` float NOT NULL DEFAULT '0',
  PRIMARY KEY (`groupid`,`time`,`spellorgob`,`size`,`posX`,`posY`,`ori`,`morphX`,`morphY`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

/*Data for the table `game_event_fireworks` */

insert  into `game_event_fireworks`(`groupid`,`time`,`spellorgob`,`size`,`posX`,`posY`,`ori`,`morphX`,`morphY`) values (0,1000,180851,2,0,0,0,0,0),(0,1000,180854,2,5,5,0,0,0),(0,1000,180855,2,10,10,0,0,0),(0,1000,180857,2,5,10,0,0,0),(0,1000,180858,2,10,5,0,0,0),(0,1000,180860,2,3,3,0,0,0),(0,1000,180861,2,5,0,0,0,0),(0,1000,180861,3,0,5,0,0,0),(0,4000,180860,4,10,10,0,0,0),(0,4000,180863,2,0,0,0,0,0),(0,4000,180864,3,5,5,0,0,0),(0,8000,180860,5,5,5,0,0.3,0),(0,12000,180860,6,5,5,0,0,0.3),(0,16000,180860,5,5,5,0,0.3,0.3),(0,20000,180860,4,5,5,0,0.8,0.1),(1,1000,180851,1,0,10,0,0,0),(1,1150,180851,1.5,3,10,0,0,0),(1,1300,180851,2,6,10,0,0,0),(1,1800,180854,1,6,10,0,0,0),(1,1950,180854,1.5,3,10,0,0,0),(1,2100,180854,2,0,10,0,0,0),(1,2600,180855,1.5,0,10,0,0,0),(1,2600,180855,1.5,3,10,0,0,0),(1,2600,180855,1.5,6,10,0,0,0),(1,3500,180855,5,5,20,0,0,0),(1,3900,180855,5,5,15,0,0.2,0.2),(1,4300,180855,5,5,10,0,0.4,0.4),(1,5000,180858,2,0,10,0,0,0),(1,5000,180858,2,15,10,0,0,0),(1,5150,180858,1.8,3,10,0,0,0),(1,5150,180858,1.8,12,10,0,0,0),(1,5300,180858,1.6,6,10,0,0,0),(1,5300,180858,1.6,9,10,0,0,0),(1,5450,180857,1.4,6,10,0,0,0),(1,5450,180857,1.4,9,10,0,0,0),(1,5600,180857,1.2,3,10,0,0,0),(1,5600,180857,1.2,12,10,0,0,0),(1,5750,180857,1,0,10,0,0,0),(1,5750,180857,1,15,10,0,0,0),(1,6000,180857,5,8,10,0,0.4,0.4),(1,8000,11540,3,5,5,0,0,0),(1,8000,11540,3,5,5,0.5,0,0),(1,8000,11540,3,5,5,1,0,0),(1,8000,11540,3,5,5,1.5,0,0),(1,8000,11540,3,5,5,2,0,0),(1,8000,11540,3,5,5,2.5,0,0),(1,8000,11540,3,5,5,3,0,0),(1,8000,11540,3,5,5,3.5,0,0),(1,8000,11540,3,5,5,4,0,0),(1,8000,11540,3,5,5,4.5,0,0),(1,8000,11540,3,5,5,5,0,0),(1,8000,11540,3,5,5,5.5,0,0),(1,8000,11540,3,5,5,6,0,0),(2,1000,180860,2,5,5,0,0,0);

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;
