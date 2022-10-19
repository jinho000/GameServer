CREATE DATABASE  IF NOT EXISTS `userver2` /*!40100 DEFAULT CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci */ /*!80016 DEFAULT ENCRYPTION='N' */;
USE `userver2`;
-- MySQL dump 10.13  Distrib 8.0.28, for Win64 (x86_64)
--
-- Host: localhost    Database: userver2
-- ------------------------------------------------------
-- Server version	8.0.28

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!50503 SET NAMES utf8 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Table structure for table `chartting`
--

DROP TABLE IF EXISTS `chartting`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `chartting` (
  `idx` int NOT NULL AUTO_INCREMENT,
  `UserIndex` int NOT NULL DEFAULT '-1',
  `NickName` varchar(45) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL,
  `Message` varchar(45) CHARACTER SET utf8 COLLATE utf8_general_ci DEFAULT NULL,
  `Time` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP,
  PRIMARY KEY (`idx`)
) ENGINE=InnoDB AUTO_INCREMENT=114 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `chartting`
--

LOCK TABLES `chartting` WRITE;
/*!40000 ALTER TABLE `chartting` DISABLE KEYS */;
INSERT INTO `chartting` VALUES (2,1,'deff','abcd','2022-04-08 12:49:30'),(3,1,'deff','abcd','2022-04-08 12:56:49'),(4,1,'deff','abcd','2022-04-08 12:59:52'),(5,1,'deff','abd','2022-04-08 13:07:32'),(6,1,'deff','sdfsefsf','2022-04-08 13:07:33'),(7,1,'deff','sdfsfsdf','2022-04-08 13:07:34'),(8,1,'deff','sdfsdfsdfsdf','2022-04-08 13:07:35'),(9,1,'deff','asdfasfdasdf','2022-04-08 13:07:36'),(10,1,'deff','asdfasdfadf','2022-04-08 13:07:37'),(11,1,'deff','sdfsdfsdf','2022-04-08 13:07:38'),(12,1,'deff','sdfsdfsf','2022-04-08 13:07:41'),(13,1,'deff','afaff','2022-04-08 13:07:45'),(14,1,'deff','sadfasdf','2022-04-08 13:07:48'),(15,1,'deff','sdfsdf','2022-04-08 13:07:49'),(16,1,'deff','sdfsf','2022-04-08 13:07:49'),(17,1,'deff','sdfsfd','2022-04-08 13:07:50'),(18,1,'deff','sdfsdfs','2022-04-08 13:07:50'),(19,1,'deff','sdfsdfsdf','2022-04-08 13:07:51'),(20,1,'deff','sdfsdfsdf','2022-04-08 13:07:52'),(21,1,'deff','sdfsdfsdfds','2022-04-08 13:07:53'),(22,1,'deff','fsdfsdfs','2022-04-08 13:07:54'),(23,1,'deff','sdfsdfsdf','2022-04-08 13:07:54'),(24,1,'deff','abvcd','2022-04-08 13:09:57'),(25,1,'deff','asdfsdf','2022-04-08 13:10:00'),(26,1,'deff','sfdf','2022-04-08 13:10:01'),(27,1,'deff','sfsf','2022-04-08 13:10:01'),(28,1,'deff','asdfsdf','2022-04-08 13:10:02'),(29,1,'deff','sgadsgag','2022-04-08 13:10:03'),(30,1,'deff','asefgse','2022-04-08 13:10:04'),(31,1,'deff','asfasdf','2022-04-08 13:10:05'),(32,1,'deff','한글','2022-04-08 13:10:07'),(33,1,'deff','ㄴㄹㄴㅇㄹ','2022-04-08 13:10:08'),(34,1,'deff','ㄴㅇㄹㄴㅇㄹ','2022-04-08 13:10:09'),(35,1,'deff','ㅁㄴㅇㄹㄴㅇㄹ','2022-04-08 13:10:09'),(36,1,'deff','ㄴㅇㄹㄴㅇㄹ','2022-04-08 13:10:17'),(37,1,'deff','ㄴㅇㄹㅇㄹ','2022-04-08 13:10:18'),(38,1,'deff','ㄴㄹㄴㄷㄹ','2022-04-08 13:10:19'),(39,1,'deff','ㅁㄴㅇㅎㄹㄴㅇㄹ','2022-04-08 13:10:20'),(40,1,'deff','ㅁㅇㄻㅎㅇㅀ','2022-04-08 13:10:21'),(41,1,'deff','ㅁㅇㅀㅀ','2022-04-08 13:10:22'),(42,1,'deff','ㅇㅀㅇㅀ','2022-04-08 13:10:23'),(43,1,'deff','ㅇㅀㅇㅀ','2022-04-08 13:10:24'),(44,1,'deff','ㅀㅇㅀㅇㅀ','2022-04-08 13:10:25'),(45,1,'deff','ㅁㅇㅎㅀㅀ','2022-04-08 13:10:26'),(46,1,'deff','ㅁㅇㅀㅇㅀㅀ','2022-04-08 13:10:27'),(47,1,'deff','ㅁㅇㅎㄹㅇㅀ','2022-04-08 13:10:28'),(48,1,'deff','ㅁㄴㅇㅀㄴㅇㄹ','2022-04-08 13:10:29'),(49,1,'deff','ㅇㅀㅇㅀㅇㅀ','2022-04-08 13:10:30'),(50,1,'deff','ㅀㅇㅀㅇㅀ','2022-04-08 13:10:31'),(51,1,'deff','ㅁㄴㅇㅎㅎㄴㅇㅎ','2022-04-08 13:10:32'),(52,1,'deff','ㅁㄴㅇㄹㄴㅇㄹ','2022-04-08 13:10:33'),(53,1,'deff','ㄴㄹㄴㄹㄹ','2022-04-08 13:10:34'),(54,1,'deff','ㅎㅇㅎㅇㅎ','2022-04-08 13:10:35'),(55,1,'deff','ㅀㄱㄱㅎ','2022-04-08 13:10:36'),(56,1,'deff','ㅁㅇㅎㅎㅇㅀ','2022-04-08 13:10:37'),(57,1,'deff','ㅁㄴㄹㅇㄴㄹㄴㅇㄹ','2022-04-08 13:10:38'),(58,1,'deff','ㄴㅇㄹㄴㅇㄹㄴㄹㄷㄹ','2022-04-08 13:10:39'),(59,1,'deff','ㄴㅇㄹㄴㅇㄹㄴㅇㄹ','2022-04-08 13:10:40'),(60,1,'deff','ㄴㄹㄴㅇㄹㄴㄹ','2022-04-08 13:10:41'),(61,1,'deff','ㄴㄹㄴㄹㄹ','2022-04-08 13:10:42'),(62,1,'deff','abcd','2022-04-08 13:13:10'),(63,1,'deff','gsdf','2022-04-08 13:14:19'),(64,10,'테스트1','테스트','2022-04-27 07:53:27'),(65,10,'테스트1','ffff','2022-04-27 07:53:41'),(66,10,'테스트1','eeeeee','2022-04-27 07:53:44'),(67,1,'deff','한글','2022-05-03 10:11:49'),(68,1,'sdfef','ggsd','2022-05-03 10:13:10'),(69,1,'sdfsef','sdff','2022-05-03 10:14:00'),(70,1,'sdfsef','sdfsdfsf','2022-05-03 10:14:02'),(71,1,'sdfsef','sdfsdf','2022-05-03 10:14:06'),(72,1,'sdfsef','sdfsdfsf','2022-05-03 10:14:08'),(73,1,'sdfsef','sdfsdfsdf','2022-05-03 10:14:10'),(74,1,'sdfsef','한글 ','2022-05-03 10:14:16'),(75,1,'sdfsef','ㅁㅁ','2022-05-03 10:14:27'),(76,1,'sdfsef','ㅎㄴㄱ','2022-05-03 10:14:30'),(77,1,'sdfsef','ㅇㄴㄹㅇㄹ','2022-05-03 10:14:32'),(78,1,'sdfsef','한글 인코딩','2022-05-03 10:14:35'),(79,1,'sdfsef','한글ㄹ','2022-05-03 10:14:38'),(80,1,'sdfsef','한글ㄹㅇ이','2022-05-03 10:14:41'),(81,1,'sdfsef','한글 인코딩','2022-05-03 10:14:44'),(82,10,'테스트1','한글','2022-05-03 10:39:08'),(83,10,'테스트1','ggg','2022-05-03 10:40:22'),(84,10,'테스트1','sdfsdf','2022-05-03 10:40:27'),(85,10,'테스트1','ggg','2022-05-03 10:40:28'),(86,10,'테스트1','한글','2022-05-03 10:40:31'),(87,10,'테스트1','ㄴㅇㄹㄴㅇㄹ','2022-05-03 10:40:32'),(88,10,'테스트1','ㄴㅇㄹㄴㅇㄹ','2022-05-03 10:40:35'),(89,10,'테스트1','ㄴㄹㄷㄹㅇㄹ','2022-05-03 10:40:38'),(90,1,'deff','gksrmfmfm','2022-05-03 10:40:41'),(91,1,'deff','sdfsdf','2022-05-03 10:40:45'),(92,1,'deff','abdd','2022-05-03 10:51:38'),(93,1,'deff','sdfsdfsdf','2022-05-03 10:51:41'),(94,1,'deff','채팅','2022-05-03 10:54:49'),(95,1,'deff','채팅ㅇㅇ','2022-05-03 10:54:53'),(96,1,'deff','abcddd','2022-05-03 10:54:57'),(97,2,'eeefe','채팅잉이잉이','2022-05-03 10:55:03'),(98,2,'eeefe','ㅊㅊㅊㅊㅊ','2022-05-03 10:55:06'),(99,10,'테스트1','ㄴㅇㄹㄴㅇㄹ','2022-05-03 10:55:15'),(100,10,'테스트1','abddddd','2022-05-03 10:55:18'),(101,10,'테스트1','sdfsdfsdfsdf','2022-05-03 10:55:20'),(102,10,'테스트1','채팅','2022-05-03 10:55:23'),(103,1,'deff','sdfasdfsdf','2022-05-15 06:14:14'),(104,1,'deff','sdfsdfsdf','2022-05-15 06:14:18'),(105,1,'deff','asd','2022-05-22 11:50:53'),(106,9,'sefe','asasd','2022-05-22 11:50:57'),(107,9,'sefe','한글','2022-05-22 11:50:59'),(108,1,'deff','dflksdre;dsfldarjg','2022-05-24 07:23:31'),(109,4,'asdfee','한글 ','2022-05-24 07:23:39'),(110,1,'deff','asdfsadfsdf]','2022-05-24 12:01:52'),(111,1,'deff','채팅','2022-05-24 12:01:54'),(112,1,'deff','ㅎㄴㅇㄹㄴㅇㄹ','2022-05-24 12:01:56'),(113,9,'sefe','jklasdfjkl;asdf','2022-05-27 03:56:55');
/*!40000 ALTER TABLE `chartting` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2022-05-27 16:50:04
