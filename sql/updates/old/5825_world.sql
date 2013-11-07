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
/*Table structure for table `player_factionchange_spells_priest_specific` */

DROP TABLE IF EXISTS `player_factionchange_spells_priest_specific`;

CREATE TABLE `player_factionchange_spells_priest_specific` (
  `race1` int(11) NOT NULL,
  `spell1` int(11) NOT NULL,
  `race2` int(11) NOT NULL,
  `spell2` int(11) NOT NULL,
  `comment` varchar(100) CHARACTER SET utf8 NOT NULL
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

/*Data for the table `player_factionchange_spells_priest_specific` */

insert  into `player_factionchange_spells_priest_specific`(`race1`,`spell1`,`race2`,`spell2`,`comment`) values (0,32676,0,0,'Consume Magic (BE)'),(0,2944,0,0,'Devouring Plague (UD)'),(0,9035,0,0,'Hex of Weakness (Troll)'),(0,28377,0,0,'(Thumsoul set this, dunno why)'),(0,18137,0,0,'Shadow Guard (Troll)'),(0,2652,0,0,'Touch of Weakness (Undead & BE)'),(0,2651,0,0,'Elune\'s Grace (Night Elf)'),(0,10797,0,0,'Starshards (Night Elf)'),(0,44047,0,0,'Chastise (Dwarf)'),(0,2943,0,0,'(Thumsoul set this, dunno why)'),(0,13896,0,0,'Feedback (Human)'),(0,13908,0,0,'Desperate Prayer (Human & Dwarf)');

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;
