-- phpMyAdmin SQL Dump
-- version 5.2.1
-- https://www.phpmyadmin.net/
--
-- Host: 127.0.0.1
-- Generation Time: Dec 28, 2024 at 07:08 AM
-- Server version: 10.4.32-MariaDB
-- PHP Version: 8.2.12

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
START TRANSACTION;
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- Database: `produksi_perikanan`
--

-- --------------------------------------------------------

--
-- Table structure for table `data_komoditas`
--

CREATE TABLE `data_komoditas` (
  `ID_Komoditas` varchar(10) NOT NULL,
  `Komoditas_Utama` varchar(50) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Dumping data for table `data_komoditas`
--

INSERT INTO `data_komoditas` (`ID_Komoditas`, `Komoditas_Utama`) VALUES
('K001', 'Cakalang'),
('K002', 'Tongkol'),
('K003', 'Tuna'),
('K004', 'Udang'),
('K005', 'Lainnya'),
('K006', 'Tangkapan Laut'),
('K007', 'Kepiting'),
('K008', 'Rajungan'),
('K009', 'Ikan Kakap'),
('K010', 'Ikan Tenggiri');

-- --------------------------------------------------------

--
-- Table structure for table `tabel_currency`
--

CREATE TABLE `tabel_currency` (
  `ID_Currency` varchar(5) NOT NULL,
  `Currency_Desc` varchar(50) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Dumping data for table `tabel_currency`
--

INSERT INTO `tabel_currency` (`ID_Currency`, `Currency_Desc`) VALUES
('AUD', 'Australian Dollar'),
('CAD', 'Canadian Dollar'),
('CHF', 'Franc'),
('CNY', 'Yuan'),
('EUR', 'Euro'),
('GBP', 'Pound Sterling'),
('IDR', 'Rp.'),
('JPY', 'Yen'),
('SGD', 'Singapore Dollar'),
('USD', 'US Dollar');

-- --------------------------------------------------------

--
-- Table structure for table `tabel_geografi`
--

CREATE TABLE `tabel_geografi` (
  `ID_Geografi` varchar(10) NOT NULL,
  `Geografi_Desc` varchar(50) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Dumping data for table `tabel_geografi`
--

INSERT INTO `tabel_geografi` (`ID_Geografi`, `Geografi_Desc`) VALUES
('G001', 'Laut'),
('G002', 'Samudra Pasifik'),
('G003', 'Samudra Atlantik'),
('G004', 'Samudra Hindia'),
('G005', 'Samudra Arktik'),
('G006', 'Samudra Antartika'),
('G007', 'Laut Jawa'),
('G008', 'Laut Banda'),
('G009', 'Laut Sulawesi'),
('G010', 'Selat Malaka');

-- --------------------------------------------------------

--
-- Table structure for table `tabel_produksi`
--

CREATE TABLE `tabel_produksi` (
  `ID_Produksi` varchar(10) NOT NULL,
  `ID_Provinsi` varchar(10) DEFAULT NULL,
  `ID_Komoditas` varchar(10) DEFAULT NULL,
  `ID_Geografi` varchar(10) DEFAULT NULL,
  `Jenis_Produksi` varchar(50) DEFAULT NULL,
  `Produksi_Perikanan` float DEFAULT NULL,
  `Unit_Desc` varchar(10) DEFAULT NULL,
  `Nilai_Produksi` bigint(20) DEFAULT NULL,
  `ID_Currency` varchar(10) DEFAULT NULL,
  `Tahun` int(11) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Dumping data for table `tabel_produksi`
--

INSERT INTO `tabel_produksi` (`ID_Produksi`, `ID_Provinsi`, `ID_Komoditas`, `ID_Geografi`, `Jenis_Produksi`, `Produksi_Perikanan`, `Unit_Desc`, `Nilai_Produksi`, `ID_Currency`, `Tahun`) VALUES
('AA1', 'P001', 'K001', 'G001', 'Perikanan', 39717, 'Ton', 1017842542, 'IDR', 2022),
('AA10', 'P002', 'K004', 'G001', 'Perikanan', 25485, 'Ton', 930560518, 'IDR', 2022),
('AA2', 'P001', 'K002', 'G001', 'Perikanan', 53428, 'Ton', 1194926571, 'IDR', 2022),
('AA3', 'P001', 'K003', 'G001', 'Perikanan', 23419, 'Ton', 883960133, 'IDR', 2022),
('AA4', 'P001', 'K004', 'G001', 'Perikanan', 4765, 'Ton', 289275626, 'IDR', 2022),
('AA5', 'P001', 'K005', 'G001', 'Perikanan', 189966, 'Ton', 5578646083, 'IDR', 2022),
('AA6', 'P001', 'K006', 'G001', 'Perikanan', 311295, 'Ton', 8964650955, 'IDR', 2022),
('AA7', 'P002', 'K001', 'G001', 'Perikanan', 10347, 'Ton', 199130621, 'IDR', 2022),
('AA8', 'P002', 'K002', 'G001', 'Perikanan', 24308, 'Ton', 716538946, 'IDR', 2022),
('AA9', 'P002', 'K003', 'G001', 'Perikanan', 2045, 'Ton', 74653731, 'IDR', 2022);

-- --------------------------------------------------------

--
-- Table structure for table `tabel_provinsi`
--

CREATE TABLE `tabel_provinsi` (
  `ID_Provinsi` varchar(10) NOT NULL,
  `Provinsi` varchar(50) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Dumping data for table `tabel_provinsi`
--

INSERT INTO `tabel_provinsi` (`ID_Provinsi`, `Provinsi`) VALUES
('P001', 'Aceh'),
('P002', 'Sumatera Utara'),
('P003', 'Sumatera Barat'),
('P004', 'Riau'),
('P005', 'Jambi'),
('P006', 'Sumatera Selatan'),
('P007', 'Bengkulu'),
('P008', 'Lampung'),
('P009', 'Kepulauan Bangka Belitung'),
('P010', 'Kepulauan Riau');

--
-- Indexes for dumped tables
--

--
-- Indexes for table `data_komoditas`
--
ALTER TABLE `data_komoditas`
  ADD PRIMARY KEY (`ID_Komoditas`);

--
-- Indexes for table `tabel_currency`
--
ALTER TABLE `tabel_currency`
  ADD PRIMARY KEY (`ID_Currency`);

--
-- Indexes for table `tabel_geografi`
--
ALTER TABLE `tabel_geografi`
  ADD PRIMARY KEY (`ID_Geografi`);

--
-- Indexes for table `tabel_produksi`
--
ALTER TABLE `tabel_produksi`
  ADD PRIMARY KEY (`ID_Produksi`),
  ADD KEY `FK_Komoditas` (`ID_Komoditas`),
  ADD KEY `FK_Geografi` (`ID_Geografi`),
  ADD KEY `idx_provinsi` (`ID_Provinsi`),
  ADD KEY `FK_Currency` (`ID_Currency`);

--
-- Indexes for table `tabel_provinsi`
--
ALTER TABLE `tabel_provinsi`
  ADD PRIMARY KEY (`ID_Provinsi`);

--
-- Constraints for dumped tables
--

--
-- Constraints for table `tabel_produksi`
--
ALTER TABLE `tabel_produksi`
  ADD CONSTRAINT `FK_Currency` FOREIGN KEY (`ID_Currency`) REFERENCES `tabel_currency` (`ID_Currency`),
  ADD CONSTRAINT `FK_Geografi` FOREIGN KEY (`ID_Geografi`) REFERENCES `tabel_geografi` (`ID_Geografi`),
  ADD CONSTRAINT `FK_Komoditas` FOREIGN KEY (`ID_Komoditas`) REFERENCES `data_komoditas` (`ID_Komoditas`),
  ADD CONSTRAINT `FK_Provinsi` FOREIGN KEY (`ID_Provinsi`) REFERENCES `tabel_provinsi` (`ID_Provinsi`);
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
