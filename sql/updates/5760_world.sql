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

/*Table structure for table `instance_template_addon` */

DROP TABLE IF EXISTS `instance_template_addon`;

CREATE TABLE `instance_template_addon` (
  `map` int(11) DEFAULT NULL,
  `forceHeroicEnabled` tinyint(1) DEFAULT '0',
  KEY `map` (`map`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

/*Data for the table `instance_template_addon` */

/*insert  into `instance_template_addon`(`map`,`forceHeroicEnabled`) values (36,1);*/

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;
