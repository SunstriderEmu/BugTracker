-- MySQL dump 10.13  Distrib 5.5.31, for debian-linux-gnu (i686)
--
-- Host: localhost    Database: world
-- ------------------------------------------------------
-- Server version	5.5.31-0ubuntu0.13.04.1

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Table structure for table `player_factionchange_items`
--

DROP TABLE IF EXISTS `player_factionchange_items`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `player_factionchange_items` (
  `alliance_id` int(8) NOT NULL,
  `alliance_comment` text,
  `horde_id` int(8) NOT NULL,
  `horde_comment` text,
  PRIMARY KEY (`alliance_id`,`horde_id`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `player_factionchange_items`
--

LOCK TABLES `player_factionchange_items` WRITE;
/*!40000 ALTER TABLE `player_factionchange_items` DISABLE KEYS */;
INSERT INTO `player_factionchange_items` VALUES (28957,NULL,28931,NULL),(28955,NULL,28930,NULL),(28954,NULL,28929,NULL),(28947,NULL,28922,NULL),(28953,NULL,28928,NULL),(28944,NULL,28920,NULL),(28946,NULL,28921,NULL),(28950,NULL,28924,NULL),(28951,NULL,28925,NULL),(29153,NULL,29155,NULL),(28952,NULL,28926,NULL),(28956,NULL,29165,NULL),(28949,NULL,28923,NULL),(29166,NULL,29167,NULL),(28959,NULL,28935,NULL),(28945,NULL,28918,NULL),(29138,NULL,29137,NULL),(28942,NULL,28917,NULL),(28948,NULL,28919,NULL),(28943,NULL,28293,NULL),(29151,NULL,29152,NULL),(28960,NULL,28933,NULL),(25825,NULL,25823,NULL),(28708,NULL,28860,NULL),(28717,NULL,28869,NULL),(31625,NULL,316229,NULL),(28628,NULL,28821,NULL),(28716,NULL,28868,NULL),(28704,NULL,28856,NULL),(31620,NULL,31621,NULL),(28624,NULL,28817,NULL),(35464,NULL,35332,NULL),(35467,NULL,35337,NULL),(28625,NULL,28818,NULL),(28705,NULL,28857,NULL),(28715,NULL,28867,NULL),(31622,NULL,31626,NULL),(35466,NULL,35339,NULL),(28626,NULL,28819,NULL),(28706,NULL,28858,NULL),(28718,NULL,28870,NULL),(31623,NULL,31627,NULL),(28627,NULL,28820,NULL),(28707,NULL,28859,NULL),(28714,NULL,28866,NULL),(31624,NULL,31628,NULL),(35465,NULL,35343,NULL),(28623,NULL,28815,NULL),(28688,NULL,28840,NULL),(28723,NULL,28875,NULL),(31593,NULL,31588,NULL),(35469,NULL,35360,NULL),(28618,NULL,28811,NULL),(28684,NULL,28836,NULL),(28719,NULL,28871,NULL),(31589,NULL,31584,NULL),(35468,NULL,35366,NULL),(35471,NULL,35371,NULL),(28619,NULL,28812,NULL),(28685,NULL,28837,NULL),(28720,NULL,28872,NULL),(31590,NULL,31585,NULL),(28620,NULL,28813,NULL),(28686,NULL,28838,NULL),(28721,NULL,28873,NULL),(29142,NULL,29141,NULL),(31591,NULL,31586,NULL),(28622,NULL,28814,NULL),(28687,NULL,28839,NULL),(28722,NULL,28874,NULL),(29148,NULL,29147,NULL),(31592,NULL,31587,NULL),(35470,NULL,35364,NULL),(25605,NULL,25609,NULL),(25599,NULL,25600,NULL),(28613,NULL,28805,NULL),(28689,NULL,28841,NULL),(28694,NULL,28846,NULL),(31640,NULL,31646,NULL),(35472,NULL,35386,NULL),(28614,NULL,28806,NULL),(28690,NULL,28842,NULL),(28695,NULL,28847,NULL),(31641,NULL,31647,NULL),(35475,NULL,35377,NULL),(35473,NULL,35392,NULL),(28615,NULL,28807,NULL),(28691,NULL,28843,NULL),(28696,NULL,28848,NULL),(29136,NULL,29135,NULL),(31642,NULL,31648,NULL),(31643,NULL,31649,NULL),(25579,NULL,25575,NULL),(31444,NULL,31713,NULL),(28616,NULL,28808,NULL),(28692,NULL,28844,NULL),(28697,NULL,28849,NULL),(35474,NULL,35383,NULL),(31458,NULL,31689,NULL),(28617,NULL,28809,NULL),(28693,NULL,28845,NULL),(28698,NULL,28850,NULL),(31644,NULL,31650,NULL),(31431,NULL,31479,NULL),(28679,NULL,28831,NULL),(28699,NULL,28851,NULL),(28709,NULL,28861,NULL),(31630,NULL,31635,NULL),(28680,NULL,28832,NULL),(28700,NULL,28852,NULL),(28710,NULL,28862,NULL),(31631,NULL,31636,NULL),(35477,NULL,35413,NULL),(31428,NULL,31473,NULL),(28681,NULL,28833,NULL),(28701,NULL,28853,NULL),(28711,NULL,28863,NULL),(31632,NULL,31637,NULL),(35478,NULL,35409,NULL),(28724,NULL,28834,NULL),(28702,NULL,28854,NULL),(28712,'',28864,''),(31633,NULL,31638,NULL),(28683,NULL,28835,NULL),(28703,NULL,28855,NULL),(28713,NULL,28865,NULL),(31634,NULL,31639,NULL),(35476,NULL,35406,NULL),(25597,NULL,25602,NULL),(25803,NULL,25809,NULL),(25919,NULL,25914,NULL),(29146,NULL,29145,NULL),(29169,NULL,29168,NULL),(25804,NULL,25811,NULL),(25606,NULL,25607,NULL),(25921,NULL,25913,NULL),(25826,NULL,25824,NULL),(27833,'',27830,NULL),(27834,NULL,27832,NULL),(37864,NULL,37865,NULL),(28238,NULL,28239,NULL),(28234,NULL,28240,NULL),(28235,NULL,28241,NULL),(28236,NULL,28242,NULL),(28237,NULL,28242,NULL),(28237,NULL,28243,NULL),(30348,NULL,30343,NULL),(30350,NULL,30344,NULL),(30351,NULL,30345,NULL),(30349,NULL,30346,NULL),(25633,NULL,25628,NULL),(27921,NULL,2920,NULL),(27922,NULL,27924,NULL),(27927,NULL,27926,NULL),(25829,NULL,24551,NULL),(18864,NULL,29592,NULL),(29593,NULL,18845,NULL),(28379,NULL,28377,NULL),(28380,NULL,28378,NULL),(29140,NULL,29139,NULL),(25805,NULL,25810,NULL),(25618,NULL,25621,NULL),(28941,NULL,28938,NULL),(28940,NULL,28939,NULL),(29144,NULL,29143,NULL),(24520,NULL,24522,NULL),(24579,NULL,24581,NULL),(24007,NULL,24006,NULL),(24008,NULL,24009,NULL),(30443,NULL,22917,NULL),(25870,NULL,29232,NULL),(22905,NULL,24001,NULL),(23619,NULL,24002,NULL),(33150,NULL,33151,NULL),(22547,NULL,24003,NULL),(22531,NULL,24000,NULL),(24180,NULL,31358,NULL),(23142,NULL,31359,NULL),(29722,NULL,31362,NULL),(29214,NULL,25739,NULL),(29215,NULL,25740,NULL),(29213,NULL,25738,NULL),(29218,NULL,25743,NULL),(34175,NULL,34174,NULL),(34173,NULL,34172,NULL),(29217,NULL,25741,NULL),(29219,NULL,25742,NULL),(29719,NULL,31361,NULL),(30444,NULL,29664,NULL),(30622,NULL,30637,NULL),(23999,NULL,24004,NULL),(31774,NULL,31773,NULL),(25527,NULL,25477,NULL),(25528,NULL,25531,NULL),(25473,NULL,25532,NULL),(25529,NULL,25533,NULL),(25471,NULL,25476,NULL),(25472,NULL,25475,NULL),(25470,NULL,25474,NULL),(31830,NULL,31829,NULL),(29227,NULL,29102,NULL),(31832,'',31831,''),(29229,NULL,29104,NULL),(31834,NULL,31833,NULL),(29230,NULL,29105,NULL),(31836,NULL,31835,NULL),(29231,NULL,29103,NULL),(13086,'Rênes de sabre-de-givre de Berceau-de-l\'Hiver',0,NULL);
/*!40000 ALTER TABLE `player_factionchange_items` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2013-06-02 20:09:54
-- MySQL dump 10.13  Distrib 5.5.31, for debian-linux-gnu (i686)
--
-- Host: localhost    Database: world
-- ------------------------------------------------------
-- Server version	5.5.31-0ubuntu0.13.04.1

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;
-- MySQL dump 10.13  Distrib 5.5.31, for debian-linux-gnu (i686)
--
-- Host: localhost    Database: world
-- ------------------------------------------------------
-- Server version	5.5.31-0ubuntu0.13.04.1

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Table structure for table `player_factionchange_items_race_specific`
--

DROP TABLE IF EXISTS `player_factionchange_items_race_specific`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `player_factionchange_items_race_specific` (
  `race1` int(8) NOT NULL,
  `item1` int(8) NOT NULL,
  `race2` int(11) NOT NULL,
  `item2` int(11) NOT NULL
) ENGINE=MyISAM DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `player_factionchange_items_race_specific`
--

LOCK TABLES `player_factionchange_items_race_specific` WRITE;
/*!40000 ALTER TABLE `player_factionchange_items_race_specific` DISABLE KEYS */;
INSERT INTO `player_factionchange_items_race_specific` VALUES (2,5665,3,5872),(2,18797,3,18787),(2,1132,3,5864),(1,18776,2,18796),(1,5655,3,5872),(1,5656,3,5873),(1,18778,2,18798),(1,18777,2,18797),(1,2411,2,5665),(1,2414,2,1132),(1,5655,2,5665),(1,5656,2,5668),(1,2411,3,5872),(1,18777,3,18787),(1,18778,3,18786),(1,18776,3,18785),(1,5656,4,8632),(1,5655,4,8631),(1,2414,4,8629),(1,2411,4,8632),(1,18777,4,18902),(1,18778,4,18767),(1,18776,4,18766),(1,5656,5,13333),(1,5655,5,13332),(1,2414,5,13331),(1,2411,5,13333),(1,18778,5,18791),(1,18777,5,13334),(1,18776,5,18791),(1,5656,6,15290),(1,5655,6,15277),(1,2414,6,15290),(1,2411,6,15277),(1,18777,6,18795),(1,18778,6,18794),(1,18776,6,18793),(1,5656,7,13322),(1,5655,7,13321),(1,2414,7,8595),(1,2411,7,8563),(1,18777,7,18774),(1,18778,7,18773),(1,18776,7,18772),(1,5656,8,8592),(2,5668,3,5873),(1,5655,8,8591),(1,2414,8,8588),(1,2411,8,8588),(1,18777,8,18790),(1,18778,8,18789),(1,18776,8,18788),(1,5656,10,29222),(1,5655,10,29221),(1,2414,10,29220),(1,2411,10,28927),(1,18777,10,29224),(1,18778,10,29223),(1,18776,10,28936),(1,5656,11,29744),(1,5655,11,29743),(1,2414,11,28481),(1,2411,11,29744),(1,18777,11,29747),(1,18778,11,29746),(1,18776,11,29745),(1,2414,3,5864),(2,18798,3,18786),(2,18796,3,18785),(2,5668,4,8632),(2,5665,4,8631),(2,1132,4,8629),(2,18797,4,18902),(2,18798,4,18767),(2,18796,4,18766),(2,5668,5,13333),(2,5665,5,13332),(2,1132,5,13331),(2,18797,5,18791),(2,18798,5,13334),(2,18796,5,18791),(2,5668,6,15290),(2,5665,6,15277),(2,1132,6,15290),(2,18797,6,18795),(2,18798,6,18794),(2,18796,6,18793),(2,5668,7,13322),(2,5665,7,13321),(2,1132,7,8595),(2,1132,7,8563),(2,18797,7,18774),(2,18798,7,18773),(2,18796,7,18772),(2,5668,8,8592),(2,5665,8,8591),(2,1132,8,8588),(2,18797,8,18790),(2,18798,8,18789),(2,18796,8,18788),(2,5668,10,29222),(2,5665,10,29221),(2,1132,10,29220),(2,5665,10,28927),(2,18797,10,29224),(2,18798,10,29223),(2,18796,10,28936),(2,5668,11,29744),(2,5665,11,29743),(2,1132,11,28481),(2,18797,11,29747),(2,18798,11,29746),(2,18796,11,29745),(3,5873,4,8632),(3,5872,4,8631),(3,5864,4,8629),(3,18787,4,18902),(3,18786,4,18767),(3,18785,4,18766),(3,5873,5,13333),(3,5872,5,13332),(3,5864,5,13331),(3,18787,5,18791),(3,18786,5,13334),(3,18785,5,18791),(3,5873,6,15290),(3,5872,6,15277),(3,5864,6,15290),(3,18787,6,18795),(3,18786,6,18794),(3,18785,6,18793),(3,5873,7,13322),(3,5872,7,13321),(3,5864,7,8595),(3,5872,7,8563),(3,18787,7,18774),(3,18786,7,18773),(3,18785,7,18772),(3,5873,8,8592),(3,5872,8,8591),(3,5864,8,8588),(3,18787,8,18790),(3,18786,8,18789),(3,18785,8,18788),(3,5873,10,29222),(3,5872,10,29221),(3,5864,10,29220),(3,5864,10,28927),(3,18787,10,29224),(3,18786,10,29223),(3,18785,10,28936),(3,5873,11,29744),(3,5872,11,29743),(3,5864,11,28481),(3,18787,11,29747),(3,18786,11,29746),(3,18785,11,29745),(4,8632,5,13333),(4,8631,5,13332),(4,8629,5,13331),(4,18902,5,18791),(4,18767,5,13334),(4,18766,5,18791),(4,8632,6,15290),(4,8631,6,15277),(4,8629,6,15277),(4,18902,6,18795),(4,18767,6,18794),(4,18766,6,18793),(4,8632,7,13322),(4,8631,7,13321),(4,8629,7,8595),(4,8629,7,8563),(4,18902,7,18774),(4,18767,7,18773),(4,18766,7,18772),(4,8632,8,8592),(4,8631,8,8591),(4,8629,8,8588),(4,18902,8,18790),(4,18767,8,18789),(4,18766,8,18788),(4,8632,10,29222),(4,8631,10,29221),(4,8629,10,29220),(4,8631,10,28927),(4,18902,10,29224),(4,18767,10,29223),(4,18766,10,28936),(4,8632,11,29744),(4,8631,11,29743),(4,8629,11,28481),(4,18902,11,29747),(4,18767,11,29746),(4,18766,11,29745),(5,13333,6,15290),(5,13332,6,15277),(5,13331,6,15290),(5,13333,7,13322),(5,18791,6,18795),(5,13334,6,18794),(5,18791,6,18793),(5,13332,7,13321),(5,13331,7,8595),(5,13333,7,8563),(5,18791,7,18774),(5,13334,7,18773),(5,13334,7,18772),(5,13333,8,8592),(5,13332,8,8591),(5,13331,8,8588),(5,18791,8,18790),(5,13334,8,18788),(5,13334,8,18789),(5,13333,10,29222),(5,13332,10,29221),(5,13331,10,29220),(5,13333,10,28927),(5,18791,10,29224),(5,13334,10,29223),(5,18791,10,28936),(5,13333,11,29744),(5,13332,11,29743),(5,13331,11,28481),(5,18791,11,29747),(5,13334,11,29476),(5,18791,11,29745),(6,15290,7,13322),(6,15277,7,13321),(6,15290,7,8595),(6,15277,7,8563),(6,18795,7,18774),(6,18794,7,18773),(6,18793,7,18772),(6,15290,8,8592),(7,13322,8,8592),(7,13321,8,8591),(6,15277,8,8591),(6,15290,8,8588),(6,18795,8,18790),(6,18794,8,18789),(6,18793,8,18788),(6,15290,10,29222),(6,15277,10,29221),(6,15290,10,29220),(6,15277,10,28927),(6,18795,10,29224),(6,18794,10,29223),(6,18793,10,28936),(6,15290,11,29744),(6,15277,11,29743),(6,15277,11,28481),(6,18795,11,29747),(6,18794,11,29746),(6,18793,11,29745),(7,8595,8,8588),(7,8563,8,8588),(7,18774,8,18790),(7,18773,8,18789),(7,18772,8,18788),(7,13322,10,29222),(7,13321,10,29221),(7,8595,10,29220),(7,8563,10,28927),(7,18774,10,29224),(7,18773,10,29223),(7,18772,10,28936),(7,13322,11,29744),(7,13321,11,29743),(7,8595,11,28481),(7,8563,11,28481),(7,18774,11,29747),(7,18773,11,29746),(7,18772,11,29745),(8,8592,10,29222),(8,8591,10,29221),(8,8588,10,29220),(8,8592,10,28927),(8,18790,10,29224),(8,18789,10,29223),(8,18788,10,28936),(8,8592,11,29744),(8,8591,11,29743),(8,8588,11,28481),(8,18790,11,29747),(8,18789,11,29746),(8,18788,11,29745),(10,29222,11,29744),(10,29221,11,29743),(10,29220,11,28481),(10,28927,11,29743),(10,29224,11,29747),(10,29223,11,29746),(10,28936,11,29745);
/*!40000 ALTER TABLE `player_factionchange_items_race_specific` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2013-06-02 20:10:14
-- MySQL dump 10.13  Distrib 5.5.31, for debian-linux-gnu (i686)
--
-- Host: localhost    Database: world
-- ------------------------------------------------------
-- Server version	5.5.31-0ubuntu0.13.04.1

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Table structure for table `player_factionchange_quests`
--

DROP TABLE IF EXISTS `player_factionchange_quests`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `player_factionchange_quests` (
  `alliance_id` int(11) NOT NULL,
  `alliance_comment` varchar(100) NOT NULL,
  `horde_id` int(11) NOT NULL,
  `horde_comment` varchar(100) NOT NULL
) ENGINE=MyISAM DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `player_factionchange_quests`
--

LOCK TABLES `player_factionchange_quests` WRITE;
/*!40000 ALTER TABLE `player_factionchange_quests` DISABLE KEYS */;
INSERT INTO `player_factionchange_quests` VALUES (9994,'',9995,''),(9996,'',9997,''),(10005,'',10006,''),(10444,'',10448,''),(10446,'',10447,''),(10051,'',10052,''),(10002,'',10003,''),(10033,'',10034,''),(10035,'',10036,''),(10026,'',10027,''),(9961,'',9960,''),(10038,'',10039,''),(10040,'',10041,''),(10042,'',10043,''),(9986,'',9987,''),(10863,'',10862,''),(10007,'',10008,''),(9992,'',9993,''),(10012,'',10013,''),(9998,'',10000,''),(10007,'',10008,''),(10028,'',10201,''),(10796,'',10784,''),(10797,'',10749,''),(10798,'',10783,''),(10799,'',10715,''),(10800,'',10721,''),(10801,'',10785,''),(10802,'',10723,''),(10806,'',10742,''),(10803,'',10786,''),(10455,'',10486,''),(10675,'',10867,''),(10502,'',10505,''),(10504,'',10503,''),(11040,'',11036,''),(11042,'',11037,''),(10927,'',10928,''),(9955,'',9946,''),(9954,'',9945,''),(9924,'',9944,''),(9871,'',9873,''),(9982,'',9983,''),(10076,'',10074,''),(10113,'',10114,''),(9879,'',9868,''),(9869,'',9870,''),(9873,'',9863,''),(9938,'',9937,''),(9936,'',9935,''),(9940,'',9939,''),(9933,'',9934,''),(10476,'',10479,''),(9921,'',9906,''),(9922,'',9907,''),(10108,'',10107,''),(11044,'',11048,''),(10116,'',10117,''),(9791,'',9770,''),(9896,'',9898,''),(9827,'',9828,''),(9901,'',9899,''),(9902,'',9904,''),(9834,'',9845,''),(9839,'',9847,''),(9835,'',9846,''),(9833,'',9842,''),(10104,'',10105,''),(11045,'',11046,''),(10642,'',10624,''),(10643,'',10625,''),(10644,'',10633,''),(10572,'',10597,''),(10680,'',10681,''),(10612,'',10613,''),(10573,'',10599,''),(10585,'',10602,''),(10662,'',10663,''),(10606,'',10611,''),(10621,'',10623,''),(10744,'',10745,''),(10776,'',10769,''),(10648,'',10647,''),(10564,'',10598,''),(10562,'',10595,''),(10586,'',10603,''),(10772,'',10750,''),(10773,'',10751,''),(10774,'',10765,''),(10775,'',10768,''),(10661,'',10660,''),(10677,'',10672,''),(10678,'',10673,''),(6121,'',6126,''),(6122,'',6127,''),(6123,'',6128,''),(6124,'',6129,''),(6124,'',6129,''),(6125,'',6130,''),(3120,'',3094,''),(5923,'',5926,''),(5921,'',5922,''),(5929,'',5930,''),(5931,'',5932,''),(6001,'',6002,''),(26,'',27,''),(29,'',28,''),(272,'',30,''),(5061,'',31,''),(5924,'',5928,''),(5925,'',5927,''),(4970,'',0,''),(5201,'',0,''),(5981,'',0,''),(0,'',9130,''),(0,'',9133,''),(0,'',9134,''),(0,'',9135,''),(0,'',9138,''),(0,'',9139,''),(0,'',9140,''),(0,'',9147,''),(0,'',9148,''),(0,'',9149,''),(0,'',9150,''),(0,'',9151,''),(0,'',9152,''),(0,'',9155,''),(0,'',9156,''),(0,'',9157,''),(0,'',9160,''),(0,'',9163,''),(0,'',9164,''),(0,'',9166,''),(0,'',9166,''),(0,'',9167,''),(0,'',9169,''),(0,'',9170,''),(0,'',9171,''),(0,'',9172,''),(0,'',9172,''),(0,'',9173,''),(0,'',9174,''),(0,'',9175,''),(0,'',9176,''),(0,'',9192,''),(0,'',9193,''),(0,'',9207,''),(0,'',9216,''),(10119,'',9407,''),(0,'',9217,''),(10288,'',10120,''),(0,'',9218,''),(0,'',9219,''),(0,'',9220,''),(0,'',9275,''),(0,'',9281,''),(0,'',9315,''),(0,'',9327,''),(0,'',9329,''),(0,'',9758,''),(0,'',9877,''),(10050,'',10220,''),(9420,'',9381,''),(9383,'',10278,''),(10909,'',0,''),(10482,'',10450,''),(10396,'',10391,''),(9426,'',10389,''),(10093,'',9498,''),(0,'',9499,''),(10443,'',10442,''),(10291,'',10875,''),(10903,'',10388,''),(10346,'',10347,''),(10895,'',10792,''),(10146,'',10129,''),(10163,'',10162,''),(10106,'',10110,''),(13408,'',13409,'');
/*!40000 ALTER TABLE `player_factionchange_quests` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2013-06-02 20:10:21
-- MySQL dump 10.13  Distrib 5.5.31, for debian-linux-gnu (i686)
--
-- Host: localhost    Database: world
-- ------------------------------------------------------
-- Server version	5.5.31-0ubuntu0.13.04.1

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Table structure for table `player_factionchange_reputations`
--

DROP TABLE IF EXISTS `player_factionchange_reputations`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `player_factionchange_reputations` (
  `race_from` int(10) unsigned NOT NULL,
  `race_to` int(10) unsigned NOT NULL,
  `faction_from` int(10) unsigned NOT NULL,
  `faction_from_comment` varchar(100) NOT NULL DEFAULT '',
  `faction_to` int(10) unsigned NOT NULL,
  `faction_to_comment` varchar(100) NOT NULL DEFAULT '',
  PRIMARY KEY (`race_from`,`race_to`,`faction_from`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `player_factionchange_reputations`
--

LOCK TABLES `player_factionchange_reputations` WRITE;
/*!40000 ALTER TABLE `player_factionchange_reputations` DISABLE KEYS */;
INSERT INTO `player_factionchange_reputations` VALUES (1,2,47,'forgefer',68,'fossoyeuse'),(1,2,54,'gnomeregan',530,'sombrelance'),(1,2,69,'darnassus',81,'pitons du tonnerre'),(1,2,72,'hurlevent',76,'orgrimmar'),(1,2,930,'exodar',911,'elfes de sang'),(1,3,47,'forgefer',72,'hurlevent'),(1,3,72,'hurlevent',47,'forgefer'),(1,4,69,'darnassus',72,'hurlevent'),(1,4,72,'hurlevent',69,'darnassus'),(1,5,47,'forgefer',76,'orgrimmar'),(1,5,54,'gnomeregan',530,'sombrelance'),(1,5,69,'darnassus',81,'pitons du tonerre'),(1,5,72,'hurlevent',68,'fossoyeuse'),(1,5,930,'exodar',911,'lune d\'argent'),(1,6,47,'forgefer',68,'fossoyeuse'),(1,6,54,'gnomeregan',530,'sombrelance'),(1,6,69,'darnassus',76,'orgrimmar'),(1,6,72,'hurlevent',81,'pitons du tonerre'),(1,6,930,'exodar',911,'lune d\'argent'),(1,7,54,'gnomeregan',72,'hurlevent'),(1,7,72,'hurlevent',54,'gnomeregan'),(1,8,47,'forgefer',68,'forgefer'),(1,8,54,'gnomeregan',76,'orgrimmar'),(1,8,69,'darnassus',81,'pitons du tonnerre'),(1,8,72,'hurlevent',530,'sombrelance'),(1,8,930,'exodar',911,'lune d\'argent'),(1,10,47,'fogefer',68,'fossoyeuse'),(1,10,54,'gnormeregan',530,'sombrelance'),(1,10,69,'darnassus',81,'pitons du tonnerre'),(1,10,72,'hurlevent',911,'lune d\'argent'),(1,10,930,'exodar',76,'orgrimmar'),(1,11,72,'hurlevent',930,'exodar'),(1,11,930,'exodar',72,'hurlevent'),(2,1,47,'forgefer',68,'fossoyeuse'),(2,1,76,'orgrimmar',72,'hurlevent'),(2,1,81,'pitons du tonnerre',69,'darnassus'),(2,1,530,'sombrelance',54,'gnomeregan'),(2,1,911,'lune d\'argent',930,'exodar'),(2,3,68,'fossoyeuse',72,'hurlevent'),(2,3,76,'orgrimmar',47,'forgefer'),(2,3,81,'pitons du tonnerre',69,'darnassus'),(2,3,530,'sombrelance',54,'gnomeregan'),(2,3,911,'lune d\'argent',930,'exodar'),(2,4,68,'fossoyeuse',47,'forgefer'),(2,4,76,'orgrimmar',69,'darnassus'),(2,4,81,'pitons du tonnerre',72,'hurlevent'),(2,4,530,'sombrelance',54,'gnormeregan'),(2,4,911,'lune d\'argent',930,'exodar'),(2,5,68,'fossoyeuse',76,'orgrimmar'),(2,5,76,'orgrimmar',68,'fossoyeuse'),(2,6,76,'orgrimmar',81,'pitons du tonnerre'),(2,6,81,'pitons du tonnerre',76,'orgrimmar'),(2,7,68,'fossoyeuse',47,'forgefer'),(2,7,76,'orgrimmar',54,'gnomeregan'),(2,7,81,'pitons du tonnerre',69,'darnassus'),(2,7,530,'sombrelance',72,'hurlevent'),(2,7,911,'lune d\'argent',930,'exodar'),(2,8,76,'orgrimmar',530,'sombrelance'),(2,8,530,'sombrelance',76,'orgrimmar'),(2,10,76,'orgrimmar',911,'lune d\'argent'),(2,10,911,'lune d\'argent',76,'orgrimmar'),(2,11,47,'forgefer',68,'fossoyeuse'),(2,11,54,'gnomeregan',530,'sombrelance'),(2,11,69,'darnassus',81,'pitons du tonnere'),(2,11,76,'orgrimmar',930,'exodar'),(2,11,930,'lune d\'argent',72,'hurlevent'),(3,1,47,'forgefer',72,'hurlevent'),(3,1,72,'hurlevent',47,'forgefer'),(3,2,47,'forgefer',76,'orgrimmar'),(3,2,54,'gnomeregan',530,'sombrelance'),(3,2,69,'darnassus',81,'pitons du tonnerre'),(3,2,72,'hurlevent',68,'fossoyeuse'),(3,2,930,'exodar',911,'lune d\'argent'),(3,4,47,'forgefer',69,'darnassus'),(3,4,69,'darnassus',47,'forgefer'),(3,5,47,'fogefer',68,'fossoyeuse'),(3,5,54,'gnormeregan',530,'sombrelance'),(3,5,69,'darnassus',81,'pitons du tonnerre'),(3,5,72,'hurlevent',76,'orgrimmar'),(3,5,930,'exodar',911,'lune d\'argent'),(3,6,47,'forgefer',81,'pitons du tonnerre'),(3,6,54,'gnomeregan',530,'sombrelance'),(3,6,69,'darnassus',68,'fossoyeuse'),(3,6,72,'hurlevent',76,'orgrimmar'),(3,6,930,'lune d\'argent',911,'exodar'),(3,7,47,'forgefer',54,'gnomeregan'),(3,7,54,'gnomeregan',47,'forgefer'),(3,8,47,'forgefer',530,'sombrelance'),(3,8,54,'gnomeregan',68,'fossoyeuse'),(3,8,69,'darnassus',81,'pitons du tonnerre'),(3,8,72,'hurlevent',76,'orgrimmar'),(3,8,930,'exodar',911,'lune d\'argent'),(3,10,47,'forgefer',911,'lune d\'argent'),(3,10,54,'gnomeregan',530,'sombrelance'),(3,10,68,'fossoyeuse',930,'exodar'),(3,10,69,'darnassus',81,'pitons du tonnerre'),(3,10,72,'hurlevent',76,'orgrimmar'),(3,11,47,'forgefer',930,'exodar'),(3,11,930,'exodar',47,'forgefer'),(4,1,69,'darnassus',72,'hurlevent'),(4,1,72,'hurlevent',69,'darnassus'),(4,2,47,'forgefer',68,'fossoyeuse'),(4,2,54,'gnomeregan',530,'sombrelance'),(4,2,69,'darnassus',76,'orgrimmar'),(4,2,72,'hurlevent',81,'pitons du tonnerre'),(4,2,930,'exodar',911,'lune d\'argent'),(4,3,47,'forgefer',69,'darnassus'),(4,3,69,'darnassus',47,'forgefer'),(4,5,47,'forgefer',81,'pitons du tonnerre'),(4,5,54,'gnomeregan',530,'sombrelance'),(4,5,69,'darnassus',68,'fossoyeuse'),(4,5,72,'hurlevent',76,'orgrimmar'),(4,5,930,'exodar',911,'lune d\'argent'),(4,6,47,'forgefer',68,'fossoyeuse'),(4,6,54,'gnomeregan',530,'sombrelance'),(4,6,69,'darnassus',81,'pitons du tonnerre'),(4,6,72,'hurlevent',76,'orgrimmar'),(4,6,930,'exodar',911,'lune d\'argent'),(4,7,54,'gnomeregan',69,'darnassus'),(4,7,69,'darnassus',54,'gnomeregan'),(4,8,47,'forgefer',68,'fossoyeuse'),(4,8,54,'gnomeregan',81,'pitons du tonerre'),(4,8,69,'darnassus',530,'sombrelance'),(4,8,72,'hurlevent',76,'orgrimmar'),(4,8,930,'exodar',911,'lune d\'argent'),(4,10,47,'forgefer',68,'fossoyeuse'),(4,10,54,'gnomeregan',530,'sombrelance'),(4,10,69,'darnassus',911,'lune d\'argent'),(4,10,72,'hurlevent',76,'orgrimmar'),(4,10,930,'exodar',81,'pitons du tonerre'),(4,11,69,'darnassus',930,'exodar'),(4,11,930,'exodar',69,'darnassus'),(5,1,68,'fossoyeuse',72,'hurlevent'),(5,1,76,'orgrimmar',47,'forgefer'),(5,1,81,'pitons du tonerre',69,'darnassus'),(5,1,530,'sombrelance',54,'gnormeran'),(5,1,911,'lune d\'argent',930,'exodar'),(5,2,68,'fossoyeuse',76,''),(5,2,76,'orgrimmar',68,'fossoyeuse'),(5,3,68,'fossyeuse',47,'forgefer'),(5,3,76,'orgrimmar',72,'hurlevent'),(5,3,81,'pitons du tonnerre',69,'darnassus'),(5,3,530,'sombrelance',54,'gnomeregan'),(5,3,911,'lune d\'argent',930,'exodar'),(5,4,68,'fossoyeuse',69,'darnassus'),(5,4,76,'orgrimmar',72,'hurlevent'),(5,4,81,'pitons du tonnerre',47,'forgefer'),(5,4,530,'sombrelance',54,'gnomeregan'),(5,4,911,'lune d\'argent',930,'exodar'),(5,6,68,'fossoyeuse',81,'pitons du tonnerre'),(5,6,81,'pitons du tonnerre',68,'fossoyeuse'),(5,7,68,'fossoyeuse',54,'gnomeregan'),(5,7,76,'orgrimmar',72,'hurlevent'),(5,7,81,'pitons du tonerre',69,'darnassus'),(5,7,530,'sombrelance',47,'forgefer'),(5,7,911,'lune d\'argent',930,'exodar'),(5,8,68,'fossoyeuse',530,'sombrelance'),(5,8,530,'sombrelance',68,'fossoyeuse'),(5,10,68,'fossoyeuse',911,'lune d\'argent'),(5,10,911,'lune d\'argent',68,'fossoyeuse'),(6,1,68,'fossoyeuse',47,'forgefer'),(6,1,76,'orgrimmar',69,'darnassus'),(6,1,81,'pitons du tonnerre',72,'hurlevent'),(6,1,530,'sombrelance',54,'gnomeregan'),(6,1,911,'lune d\'argent',930,'exodar'),(6,2,76,'orgrimmar',81,'pitons du tonnerre'),(6,2,81,'pitons du tonnerre',76,'orgrimmar'),(6,3,68,'fossoyeuse',69,'darnassus'),(6,3,76,'orgrimmar',72,'hurlevent'),(6,3,81,'pitons du tonnerre',47,'forgefer'),(6,3,530,'sombrelance',54,'gnomeregan'),(6,3,911,'lune d\'argent',930,'exodar'),(6,4,68,'fossoyeuse',47,'forgefer'),(6,4,76,'orgrimmar',72,'hurlevent'),(6,4,81,'pitons du tonnerre',69,'darnassus'),(6,4,530,'sombrelance',54,'gnomeregan'),(6,4,911,'lune d\'argent',930,'exodar'),(6,5,68,'fossoyeuse',81,'pitons du tonnerre'),(6,5,81,'pitons du tonnerre',68,'fossoyeuse'),(6,7,68,'fossoyeuse',47,'forgefer'),(6,7,76,'orgrimmar',72,'hurlevent'),(6,7,81,'pitons du tonerre',54,'gnomeregan'),(6,7,530,'sombrelance',69,'darnassus'),(6,7,911,'lune d\'argent',930,'exodar'),(6,8,81,'pitons du tonnerre',530,'sombrelance'),(6,8,530,'sombrelance',81,'pitons du tonnerre'),(6,10,81,'pitons du tonnerre',911,'lune d\'argent'),(6,10,911,'lune d\'argent',81,'pitons du tonnerre'),(6,11,68,'fossoyeuse',47,'forgefer'),(6,11,76,'orgrimmar',72,'hurlevent'),(6,11,81,'pitons du tonnerre',930,'exodar'),(6,11,530,'sombrelance',54,'gnomeregan'),(6,11,911,'lune d\'argent',69,'darnassus'),(7,1,54,'gnomeregan',72,'hurlevent'),(7,1,72,'hurlevent',54,'gnomeregan'),(7,2,47,'forgefer',68,'fossoyeuse'),(7,2,54,'gnomeregan',76,'orgrimmar'),(7,2,69,'darnassus',81,'pitons du tonnerre'),(7,2,72,'hurlevent',530,'sombrelance'),(7,2,930,'exodar',911,'lune d\'argent'),(7,3,47,'forgefer',54,'gnomeregan'),(7,3,54,'gnomeregan',47,'forgefer'),(7,4,54,'gnomeregan',69,'darnassus'),(7,4,69,'darnassus',54,'gnomeregan'),(7,5,47,'forgefer',530,'sombrelance'),(7,5,54,'gnomeregan',68,'fossoyeuse'),(7,5,69,'darnassus',81,'pitons du tonerre'),(7,5,72,'hurlevent',76,'orgrimmar'),(7,5,930,'exodar',911,'lune d\'argent'),(7,6,47,'forgefer',68,'fossoyeuse'),(7,6,54,'gnomeregan',81,'pitons du tonerre'),(7,6,69,'darnassus',530,'sombrelance'),(7,6,72,'hurlevent',76,'orgrimmar'),(7,6,930,'exodar',911,'lune d\'argent'),(7,8,47,'forgefer',68,'fossoyeuse'),(7,8,54,'gnomeregan',530,'sombrelance'),(7,8,69,'darnassus',81,'pitons du tonerre'),(7,8,72,'hurlevent',76,'orgrimmar'),(7,8,930,'exodar',911,'lune d\'argent'),(7,10,47,'forgefer',68,'fossoyeuse'),(7,10,54,'gnomeregan',911,'lune d\'argent'),(7,10,69,'darnassus',81,'pitons du tonerre'),(7,10,72,'hurlevent',76,'orgrimmar'),(7,10,930,'exodar',530,'sombrelance'),(7,11,54,'gnomeregan',930,'exodar'),(7,11,930,'exodar',54,'gnomeregan'),(8,1,68,'fossoyeuse',47,'forgefer'),(8,1,76,'orgrimmar',54,'gnomeregan'),(8,1,81,'pitons du tonnerre',69,'darnassus'),(8,1,530,'sombrelance',72,'hurlevent'),(8,1,911,'lune d\'argent',930,'exodar'),(8,2,76,'orgrimmar',530,'sombrelance'),(8,2,530,'sombrelance',76,'orgrimmar'),(8,3,68,'fossoyeuse',54,'gnomeregan'),(8,3,76,'orgrimmar',72,'hurlevent'),(8,3,81,'pitons du tonnerre',69,'darnassus'),(8,3,530,'sombrelance',47,'forgefer'),(8,3,911,'lune d\'argent',930,'exodar'),(8,4,68,'fossoyeuse',47,'forgefer'),(8,4,76,'orgrimmar',72,'hurlevent'),(8,4,81,'pitons du tonerre',54,'gnomeregan'),(8,4,530,'sombrelance',69,'darnassus'),(8,4,911,'lune d\'argent',930,'exodar'),(8,5,68,'fossoyeuse',530,'sombrelance'),(8,5,530,'sombrelance',68,'fossoyeuse'),(8,6,81,'pitons du tonnerre',530,'sombrelance'),(8,6,530,'sombrelance',81,'pitons du tonnerre'),(8,7,68,'fossoyeuse',47,'forgefer'),(8,7,76,'orgrimmar',72,'hurlevent'),(8,7,81,'pitons du tonerre',69,'darnassus'),(8,7,530,'sombrelance',54,'gnomeregan'),(8,7,911,'lune d\'argent',930,'exodar'),(8,10,530,'sombrelance',911,'lune d\'argent'),(8,10,911,'lune d\'argent',530,'sombrelance'),(8,11,68,'fossoyeuse',47,'forgefer'),(8,11,76,'orgrimmar',72,'hurlevent'),(8,11,81,'pitons du tonnerre',69,'darnassus'),(8,11,530,'sombrelance',930,'exodar'),(8,11,911,'lune d\'argent',54,'gnomeregan'),(10,1,68,'fossoyeuse',47,'forgefer'),(10,1,76,'orgrimmar',930,'exodar'),(10,1,81,'pitons du tonnerre',69,'darnassus'),(10,1,530,'sombrelance',54,'gnomeregan'),(10,1,911,'lune d\'argent',72,'hurlevent'),(10,2,76,'orgrimmar',911,'lune d\'argent'),(10,2,911,'lune d\'argent',76,'orgrimmar'),(10,3,68,'fossoyeuse',930,'exodar'),(10,3,76,'orgrimmar',72,'hurlevent'),(10,3,81,'pitons du tonnerre',69,'darnassus'),(10,3,530,'sombrelance',54,'gnomeregan'),(10,3,911,'lune d\'argent',47,'forgefer'),(10,4,68,'fossoyeuse',47,'forgefer'),(10,4,76,'orgrimmar',72,'hurlevent'),(10,4,81,'pitons du tonerre',930,'exodar'),(10,4,530,'sombrelance',54,'gnomeregan'),(10,4,911,'lune d\'argent',69,'darnassus'),(10,5,68,'fossoyeuse',911,'lune d\'argent'),(10,5,911,'lune d\'argent',68,'fossoyeuse'),(10,6,81,'pitons du tonnerre',911,'lune d\'argent'),(10,6,911,'lune d\'argent',81,'pitons du tonnerre'),(10,7,68,'fossoyeuse',47,'forgefer'),(10,7,76,'orgrimmar',72,'hurlevent'),(10,7,81,'pitons du tonerre',69,'darnassus'),(10,7,530,'sombrelance',930,'exodar'),(10,7,911,'lune d\'argent',54,'gnomeregan'),(10,8,530,'sombrelance',911,'lune d\'argent'),(10,8,911,'lune d\'argent',530,'sombrelance'),(10,11,68,'fossoyeuse',47,'forgefer'),(10,11,76,'orgrimmar',72,'hurlevent'),(10,11,81,'pitons du tonerre',69,'darnassus'),(10,11,530,'sombrelance',54,'gnomeregan'),(10,11,911,'lune d\'argent',930,'exodar'),(11,1,72,'hurlevent',930,'exodar'),(11,1,930,'exodar',72,'hurlevent'),(11,2,47,'forgefer',68,'fossoyeuse'),(11,2,54,'gnomeregan',530,'sombrelance'),(11,2,69,'darnassus',81,'pitons du tonnerre'),(11,2,72,'hurlevent',911,'lune d\'argent'),(11,2,930,'exodar',76,'orgrimmar'),(11,3,47,'forgefer',930,'exodar'),(11,3,930,'exodar',47,'forgefer'),(11,4,69,'darnassus',930,'exodar'),(11,4,930,'exodar',69,'darnassus'),(11,6,47,'forgefer',68,'fossoyeuse'),(11,6,54,'gnomeregan',530,'sombrelance'),(11,6,69,'darnassus',911,'lune d\'argent'),(11,6,72,'hurlevent',76,'orgrimmar'),(11,6,930,'exodar',81,'pitons du tonnerre'),(11,7,54,'gnomeregan',930,'exodar'),(11,7,930,'exodar',54,'gnomeregan'),(11,8,47,'forgefer',68,'fossoyeuse'),(11,8,54,'gnomeregan',911,'lune d\'argent'),(11,8,69,'darnassus',81,'pitons du tonerre'),(11,8,72,'hurlevent',76,'orgrimmar'),(11,8,930,'exodar',530,'sombrelance'),(11,10,47,'forgefer',68,'fossoyeuse'),(11,10,54,'gnomeregan',530,'sombrelance'),(11,10,69,'darnassus',81,'pitons du tonerre'),(11,10,72,'hurlevent',76,'orgrimmar'),(11,10,930,'exodar',911,'lune d\'argent');
/*!40000 ALTER TABLE `player_factionchange_reputations` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2013-06-02 20:10:27
-- MySQL dump 10.13  Distrib 5.5.31, for debian-linux-gnu (i686)
--
-- Host: localhost    Database: world
-- ------------------------------------------------------
-- Server version	5.5.31-0ubuntu0.13.04.1

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Table structure for table `player_factionchange_reputations_generic`
--

DROP TABLE IF EXISTS `player_factionchange_reputations_generic`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `player_factionchange_reputations_generic` (
  `alliance_id` int(11) NOT NULL,
  `alliance_comment` varchar(50) CHARACTER SET utf8 NOT NULL,
  `horde_id` int(11) NOT NULL,
  `horde_comment` varchar(50) CHARACTER SET utf8 NOT NULL
) ENGINE=MyISAM DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `player_factionchange_reputations_generic`
--

LOCK TABLES `player_factionchange_reputations_generic` WRITE;
/*!40000 ALTER TABLE `player_factionchange_reputations_generic` DISABLE KEYS */;
INSERT INTO `player_factionchange_reputations_generic` VALUES (730,'Garde Foudrepique',729,'Clan Loup-de-givre'),(946,'Bastion de l\'Honneur',947,'Thrallmar'),(978,'Kurenaï',941,'Mag\'har'),(0,'pas de faction équivalente',922,'Tranquillien'),(509,'La Ligue d\'Arathor',510,'Les Profanateurs'),(890,'Sentinelles d’Aile-argent',889,'Voltigeurs Chanteguerre'),(589,'Éleveurs de sabres-d\'hiver',0,'pas de réputation équivalente');
/*!40000 ALTER TABLE `player_factionchange_reputations_generic` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2013-06-02 20:10:30
-- MySQL dump 10.13  Distrib 5.5.31, for debian-linux-gnu (i686)
--
-- Host: localhost    Database: world
-- ------------------------------------------------------
-- Server version	5.5.31-0ubuntu0.13.04.1

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Table structure for table `player_factionchange_spells`
--

DROP TABLE IF EXISTS `player_factionchange_spells`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `player_factionchange_spells` (
  `alliance_id` int(8) NOT NULL,
  `alliance_comment` text,
  `horde_id` int(8) NOT NULL,
  `horde_comment` text,
  PRIMARY KEY (`alliance_id`,`horde_id`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `player_factionchange_spells`
--

LOCK TABLES `player_factionchange_spells` WRITE;
/*!40000 ALTER TABLE `player_factionchange_spells` DISABLE KEYS */;
INSERT INTO `player_factionchange_spells` VALUES (10059,'portail hurlevent',11417,'portail orgrimmar'),(32266,'portail exodar',32267,'portail lune d\'argent'),(49360,'portail théramore',49361,'portail pierreche'),(11419,'portail darnassus',11420,'portail pitons du tonnerre'),(11416,'portail forgefer',11418,'portail fossoyeuse'),(3561,'téléportation hurlevent',3567,'téléportation orgrimmar'),(32271,'téléportation exodar',32272,'téléportation lune d\'argent'),(49359,'téléportation théramore',49358,'téléportation pierreche'),(3565,'téléportation darnassus',3566,'téléportation pitons du tonerre'),(3562,'téléportation forgefer',3563,'téléportation fossoyeuse'),(32182,'héroisme',2825,'furie sanguinaire'),(31801,'sceau de vengeance',31892,'sceau de sang');
/*!40000 ALTER TABLE `player_factionchange_spells` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2013-06-02 20:10:35
-- MySQL dump 10.13  Distrib 5.5.31, for debian-linux-gnu (i686)
--
-- Host: localhost    Database: world
-- ------------------------------------------------------
-- Server version	5.5.31-0ubuntu0.13.04.1

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Table structure for table `player_factionchange_spells_specific`
--

DROP TABLE IF EXISTS `player_factionchange_spells_specific`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `player_factionchange_spells_specific` (
  `race1` int(11) NOT NULL,
  `spell1` int(11) NOT NULL,
  `race2` int(11) NOT NULL,
  `spell2` int(11) NOT NULL,
  `comment` varchar(100) CHARACTER SET utf8 NOT NULL
) ENGINE=MyISAM DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `player_factionchange_spells_specific`
--

LOCK TABLES `player_factionchange_spells_specific` WRITE;
/*!40000 ALTER TABLE `player_factionchange_spells_specific` DISABLE KEYS */;
INSERT INTO `player_factionchange_spells_specific` VALUES (5,2652,1,0,'toucher de faiblesse rang 1'),(5,2652,2,0,'toucher de faiblesse rang 1'),(5,2652,3,0,'toucher de faiblesse rang 1'),(5,2652,4,0,'toucher de faiblesse rang 1'),(5,2652,6,0,'toucher de faiblesse rang 1'),(5,2652,7,0,'toucher de faiblesse rang 1'),(5,2652,8,0,'toucher de faiblesse rang 1'),(5,2652,11,0,'toucher de faiblesse rang 1'),(10,2652,1,0,'toucher de faiblesse rang 1'),(10,2652,2,0,'toucher de faiblesse rang 1'),(10,2652,3,0,'toucher de faiblesse rang 1'),(10,2652,4,0,'toucher de faiblesse rang 1'),(10,2652,6,0,'toucher de faiblesse rang 1'),(10,2652,7,0,'toucher de faiblesse rang 1'),(10,2652,8,0,'toucher de faiblesse rang 1'),(10,2652,11,0,'toucher de faiblesse rang 1'),(5,19261,1,0,'toucher de faiblesse rang 2'),(5,19261,2,0,'toucher de faiblesse rang 2'),(5,19261,3,0,'toucher de faiblesse rang 2'),(5,19261,4,0,'toucher de faiblesse rang 2'),(5,19261,6,0,'toucher de faiblesse rang 2'),(5,19261,7,0,'toucher de faiblesse rang 2'),(5,19261,8,0,'toucher de faiblesse rang 2'),(5,19261,11,0,'toucher de faiblesse rang 2'),(10,19261,1,0,'toucher de faiblesse rang 2'),(10,19261,2,0,'toucher de faiblesse rang 2'),(10,19261,3,0,'toucher de faiblesse rang 2'),(10,19261,4,0,'toucher de faiblesse rang 2'),(10,19261,6,0,'toucher de faiblesse rang 2'),(10,19261,7,0,'toucher de faiblesse rang 2'),(10,19261,8,0,'toucher de faiblesse rang 2'),(10,19261,11,0,'toucher de faiblesse rang 2'),(5,19262,1,0,'toucher de faiblesse rang 3'),(5,19262,2,0,'toucher de faiblesse rang 3'),(5,19262,3,0,'toucher de faiblesse rang 3'),(5,19262,4,0,'toucher de faiblesse rang 3'),(5,19262,6,0,'toucher de faiblesse rang 3'),(5,19262,7,0,'toucher de faiblesse rang 3'),(5,19262,8,0,'toucher de faiblesse rang 3'),(5,19262,11,0,'toucher de faiblesse rang 3'),(10,19262,1,0,'toucher de faiblesse rang 3'),(10,19262,2,0,'toucher de faiblesse rang 3'),(10,19262,3,0,'toucher de faiblesse rang 3'),(10,19262,4,0,'toucher de faiblesse rang 3'),(10,19262,6,0,'toucher de faiblesse rang 3'),(10,19262,7,0,'toucher de faiblesse rang 3'),(10,19262,8,0,'toucher de faiblesse rang 3'),(10,19262,11,0,'toucher de faiblesse rang 3'),(5,19264,1,0,'toucher de faiblesse rang 4'),(5,19264,2,0,'toucher de faiblesse rang 4'),(5,19264,3,0,'toucher de faiblesse rang 4'),(5,19264,4,0,'toucher de faiblesse rang 4'),(5,19264,6,0,'toucher de faiblesse rang 4'),(5,19264,7,0,'toucher de faiblesse rang 4'),(5,19264,8,0,'toucher de faiblesse rang 4'),(5,19264,11,0,'toucher de faiblesse rang 4'),(10,19264,1,0,'toucher de faiblesse rang 4'),(10,19264,2,0,'toucher de faiblesse rang 4'),(10,19264,3,0,'toucher de faiblesse rang 4'),(10,19264,4,0,'toucher de faiblesse rang 4'),(10,19264,6,0,'toucher de faiblesse rang 4'),(5,19265,1,0,'toucher de faiblesse rang 5'),(10,19264,7,0,'toucher de faiblesse rang 4'),(10,19264,8,0,'toucher de faiblesse rang 4'),(10,19264,11,0,'toucher de faiblesse rang 4'),(5,19265,2,0,'toucher de faiblesse rang 5'),(5,19265,3,0,'toucher de faiblesse rang 5'),(5,19265,4,0,'toucher de faiblesse rang 5'),(5,19265,6,0,'toucher de faiblesse rang 5'),(5,19265,7,0,'toucher de faiblesse rang 5'),(5,19265,8,0,'toucher de faiblesse rang 5'),(5,19265,11,0,'toucher de faiblesse rang 5'),(10,19265,1,0,'toucher de faiblesse rang 5'),(10,19265,2,0,'toucher de faiblesse rang 5'),(10,19265,3,0,'toucher de faiblesse rang 5'),(10,19265,4,0,'toucher de faiblesse rang 5'),(10,19265,6,0,'toucher de faiblesse rang 5'),(10,19265,7,0,'toucher de faiblesse rang 5'),(10,19265,8,0,'toucher de faiblesse rang 5'),(10,19265,11,0,'toucher de faiblesse rang 5'),(5,19266,1,0,'toucher de faiblesse rang 6'),(5,19266,2,0,'toucher de faiblesse rang 6'),(5,19266,3,0,'toucher de faiblesse rang 6'),(5,19266,4,0,'toucher de faiblesse rang 6'),(5,19266,6,0,'toucher de faiblesse rang 6'),(5,19266,7,0,'toucher de faiblesse rang 6'),(5,19266,8,0,'toucher de faiblesse rang 6'),(5,19266,11,0,'toucher de faiblesse rang 6'),(10,19266,2,0,'toucher de faiblesse rang 6'),(10,19266,1,0,'toucher de faiblesse rang 6'),(10,19266,3,0,'toucher de faiblesse rang 6'),(10,19266,4,0,'toucher de faiblesse rang 6'),(10,19266,6,0,'toucher de faiblesse rang 6'),(10,19266,7,0,'toucher de faiblesse rang 6'),(10,19266,8,0,'toucher de faiblesse rang 6'),(10,19266,11,0,'toucher de faiblesse rang 6'),(5,25461,1,0,'toucher de faiblesse rang 7'),(5,25461,2,0,'toucher de faiblesse rang 7'),(5,25461,3,0,'toucher de faiblesse rang 7'),(5,25461,4,0,'toucher de faiblesse rang 7'),(5,25461,6,0,'toucher de faiblesse rang 7'),(5,25461,7,0,'toucher de faiblesse rang 7'),(5,25461,8,0,'toucher de faiblesse rang 7'),(5,25461,11,0,'toucher de faiblesse rang 7'),(10,25461,1,0,'toucher de faiblesse rang 7'),(10,25461,2,0,'toucher de faiblesse rang 7'),(10,25461,3,0,'toucher de faiblesse rang 7'),(10,25461,4,0,'toucher de faiblesse rang 7'),(10,25461,6,0,'toucher de faiblesse rang 7'),(10,25461,7,0,'toucher de faiblesse rang 7'),(10,25461,8,0,'toucher de faiblesse rang 7'),(10,25461,11,0,'toucher de faiblesse rang 7');
/*!40000 ALTER TABLE `player_factionchange_spells_specific` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2013-06-02 20:10:38
-- MySQL dump 10.13  Distrib 5.5.31, for debian-linux-gnu (i686)
--
-- Host: localhost    Database: world
-- ------------------------------------------------------
-- Server version	5.5.31-0ubuntu0.13.04.1

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Table structure for table `player_factionchange_titles`
--

DROP TABLE IF EXISTS `player_factionchange_titles`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `player_factionchange_titles` (
  `alliance_id` int(8) NOT NULL,
  `alliance_comment` text,
  `horde_id` int(8) NOT NULL,
  `horde_comment` text,
  PRIMARY KEY (`alliance_id`,`horde_id`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `player_factionchange_titles`
--

LOCK TABLES `player_factionchange_titles` WRITE;
/*!40000 ALTER TABLE `player_factionchange_titles` DISABLE KEYS */;
INSERT INTO `player_factionchange_titles` VALUES (48,'Justicier',47,'Conquérant'),(1,'Soldat',15,'Eclaireur'),(2,'Caporal',16,'Grunt'),(3,'Sergent',17,'Sergent'),(4,'sergent-chef',18,'sergent-chef'),(5,'Sergent-major',19,'adjudant'),(6,'chevalier',20,'Garde de pierre'),(7,'chevalier lieutenant',21,'Garde sang'),(8,'chevalier capitaine',22,'légionnaire'),(9,'chevalier champion',23,'centurion'),(10,'lieutenant commandant',24,'champion'),(11,'commandant',25,'lieutenant général'),(12,'maréchal',26,'général'),(13,'grand maréchal',27,'seigneur de guerre'),(14,'connétable',28,'grand seigneur de guerre');
/*!40000 ALTER TABLE `player_factionchange_titles` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2013-06-02 20:10:42
