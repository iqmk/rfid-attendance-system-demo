-- phpMyAdmin SQL Dump
-- version 5.2.1
-- https://www.phpmyadmin.net/
--
-- Host: localhost
-- Generation Time: Mar 27, 2025 at 05:46 PM
-- Wersja serwera: 11.5.2-MariaDB
-- Wersja PHP: 8.3.12

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
START TRANSACTION;
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- Database: `ewidencja_obecnosci`
--

-- --------------------------------------------------------

--
-- Struktura tabeli dla tabeli `obecnosci`
--

CREATE TABLE `obecnosci` (
  `obecnosc_id` int(10) UNSIGNED NOT NULL,
  `uzytkownik_id` int(10) UNSIGNED NOT NULL,
  `data` datetime NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;

--
-- Dumping data for table `obecnosci`
--

INSERT INTO `obecnosci` (`obecnosc_id`, `uzytkownik_id`, `data`) VALUES
(3, 2, '2024-11-28 14:39:22'),
(4, 1, '2024-11-28 14:53:50'),
(7, 4, '2024-12-08 14:39:44'),
(5911, 4, '2024-12-09 15:40:21'),
(5915, 3, '2024-12-09 15:44:53'),
(5917, 2, '2024-12-09 16:17:27'),
(5918, 3, '2024-12-13 10:52:41'),
(5920, 1, '2024-12-13 11:51:02'),
(5932, 2, '2025-02-11 19:25:30'),
(5933, 5, '2025-02-11 19:27:24'),
(5934, 1, '2025-02-11 19:28:37');

-- --------------------------------------------------------

--
-- Struktura tabeli dla tabeli `przedmioty`
--

CREATE TABLE `przedmioty` (
  `przedmiot_id` int(10) UNSIGNED NOT NULL,
  `nazwa` tinytext NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;

--
-- Dumping data for table `przedmioty`
--

INSERT INTO `przedmioty` (`przedmiot_id`, `nazwa`) VALUES
(1, 'Fizyka'),
(2, 'Programowanie'),
(3, 'Podstawy metod probabilistycznych'),
(4, 'Systemy wbudowane'),
(5, 'Zarządzanie Projektami Informatycznymi'),
(6, 'Podstawy Baz Danych'),
(7, 'Eksploracja danych');

-- --------------------------------------------------------

--
-- Struktura tabeli dla tabeli `uzytkownicy`
--

CREATE TABLE `uzytkownicy` (
  `uzytkownik_id` int(10) UNSIGNED NOT NULL,
  `imie` tinytext NOT NULL,
  `nazwisko` tinytext NOT NULL,
  `numer_ewidencyjny` tinytext NOT NULL,
  `haslo` char(65) NOT NULL,
  `status` tinyint(1) NOT NULL,
  `tag_id` bigint(20) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;

--
-- Dumping data for table `uzytkownicy`
--

INSERT INTO `uzytkownicy` (`uzytkownik_id`, `imie`, `nazwisko`, `numer_ewidencyjny`, `haslo`, `status`, `tag_id`) VALUES
(1, 'Jakub', 'Nowak', 's001', 'test', 1, 6913018),
(2, 'Jan', 'Kowalski', 's002', 'test', 1, 6540311),
(3, 'Katarzyna', 'Sikora', 's003', 'haslo123', 1, 3026450),
(4, 'Renata', 'Baran', 's004', 'kolejneFajneHaslo123', 1, 3095023),
(5, 'Marcin', 'Dąbrowski', 's005', '12345test', 1, 6537786),
(9, 'Laura', 'Król', 'p001', 'testt', 0, NULL),
(10, 'Leon', 'Kamiński', 'p002', 'leo_123', 0, NULL);

-- --------------------------------------------------------

--
-- Struktura tabeli dla tabeli `zajecia`
--

CREATE TABLE `zajecia` (
  `zajecie_id` int(10) UNSIGNED NOT NULL,
  `przedmiot_id` int(10) UNSIGNED NOT NULL,
  `data` datetime NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;

--
-- Dumping data for table `zajecia`
--

INSERT INTO `zajecia` (`zajecie_id`, `przedmiot_id`, `data`) VALUES
(1, 1, '2024-11-28 08:00:00'),
(2, 2, '2024-11-28 09:40:00'),
(3, 3, '2024-12-01 08:00:00'),
(4, 1, '2024-11-28 14:40:00'),
(5, 4, '2024-12-08 13:00:00'),
(6, 4, '2024-12-08 14:40:00'),
(7, 3, '2024-12-10 13:00:00'),
(10, 3, '2024-12-13 11:50:00');

--
-- Indeksy dla zrzutów tabel
--

--
-- Indeksy dla tabeli `obecnosci`
--
ALTER TABLE `obecnosci`
  ADD PRIMARY KEY (`obecnosc_id`),
  ADD KEY `uzytkownik_id` (`uzytkownik_id`);

--
-- Indeksy dla tabeli `przedmioty`
--
ALTER TABLE `przedmioty`
  ADD PRIMARY KEY (`przedmiot_id`);

--
-- Indeksy dla tabeli `uzytkownicy`
--
ALTER TABLE `uzytkownicy`
  ADD PRIMARY KEY (`uzytkownik_id`),
  ADD UNIQUE KEY `tag_id` (`tag_id`),
  ADD UNIQUE KEY `login` (`numer_ewidencyjny`) USING HASH;

--
-- Indeksy dla tabeli `zajecia`
--
ALTER TABLE `zajecia`
  ADD PRIMARY KEY (`zajecie_id`),
  ADD KEY `przedmiot_id` (`przedmiot_id`);

--
-- AUTO_INCREMENT for dumped tables
--

--
-- AUTO_INCREMENT for table `obecnosci`
--
ALTER TABLE `obecnosci`
  MODIFY `obecnosc_id` int(10) UNSIGNED NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=5935;

--
-- AUTO_INCREMENT for table `przedmioty`
--
ALTER TABLE `przedmioty`
  MODIFY `przedmiot_id` int(10) UNSIGNED NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=8;

--
-- AUTO_INCREMENT for table `uzytkownicy`
--
ALTER TABLE `uzytkownicy`
  MODIFY `uzytkownik_id` int(10) UNSIGNED NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=11;

--
-- AUTO_INCREMENT for table `zajecia`
--
ALTER TABLE `zajecia`
  MODIFY `zajecie_id` int(10) UNSIGNED NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=11;

--
-- Constraints for dumped tables
--

--
-- Constraints for table `obecnosci`
--
ALTER TABLE `obecnosci`
  ADD CONSTRAINT `obecnosci_ibfk_1` FOREIGN KEY (`uzytkownik_id`) REFERENCES `uzytkownicy` (`uzytkownik_id`);

--
-- Constraints for table `zajecia`
--
ALTER TABLE `zajecia`
  ADD CONSTRAINT `zajecia_ibfk_1` FOREIGN KEY (`przedmiot_id`) REFERENCES `przedmioty` (`przedmiot_id`);
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
