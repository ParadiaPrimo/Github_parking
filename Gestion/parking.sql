-- phpMyAdmin SQL Dump
-- version 4.6.4
-- https://www.phpmyadmin.net/
--
-- Client :  127.0.0.1
-- Généré le :  Lun 15 Janvier 2018 à 15:11
-- Version du serveur :  5.7.14
-- Version de PHP :  5.6.25

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- Base de données :  `parking`
--

-- --------------------------------------------------------

--
-- Structure de la table `cb`
--

CREATE TABLE `cb` (
  `id_cb` int(11) NOT NULL,
  `id_proprio` int(11) NOT NULL,
  `code_bancaire` char(16) NOT NULL,
  `crypto` char(3) NOT NULL,
  `date_expi` char(10) DEFAULT NULL
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

--
-- Contenu de la table `cb`
--

INSERT INTO `cb` (`id_cb`, `id_proprio`, `code_bancaire`, `crypto`, `date_expi`) VALUES
(1, 1, '1111222233334444', '222', '2021-05-12'),
(12, 2, '1234123412341234', '525', '2020-12-01');

-- --------------------------------------------------------

--
-- Structure de la table `proprietaire`
--

CREATE TABLE `proprietaire` (
  `id_proprio` int(11) NOT NULL,
  `nom` varchar(50) NOT NULL,
  `prenom` varchar(80) NOT NULL,
  `password` varchar(100) NOT NULL,
  `mail` varchar(50) NOT NULL,
  `abonnement` int(11) NOT NULL DEFAULT '0'
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

--
-- Contenu de la table `proprietaire`
--

INSERT INTO `proprietaire` (`id_proprio`, `nom`, `prenom`, `password`, `mail`, `abonnement`) VALUES
(1, 'Ky', 'Stephane', 'plop', 'sky050577@gmail.com', 2),
(2, 'sdddf', 'psdlfpl', 'dpfl', 'sdfsdf', 0),
(0, 'dummy', 'dummy', '', '', -1),
(5, 'plop', 'plop', 'plop@nani.fr', 'plop', 0),
(6, '0', 'hgfds', 'ffffff', 'dfdfdf', 0);

-- --------------------------------------------------------

--
-- Structure de la table `reservation`
--

CREATE TABLE `reservation` (
  `id_reservation` int(11) NOT NULL,
  `id_voiture` int(11) NOT NULL,
  `date_prevue_start` char(20) NOT NULL,
  `date_prevue_end` char(20) NOT NULL,
  `date_true_start` char(20) DEFAULT NULL,
  `date_true_end` char(20) DEFAULT NULL,
  `lavage_int` int(11) NOT NULL DEFAULT '0',
  `lavage_ext` int(11) NOT NULL DEFAULT '0',
  `lavage_total` int(11) NOT NULL DEFAULT '0',
  `essence` int(11) NOT NULL DEFAULT '0',
  `actif` int(11) NOT NULL DEFAULT '0',
  `fini` int(11) NOT NULL DEFAULT '0',
  `paye` int(11) NOT NULL DEFAULT '0'
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

--
-- Contenu de la table `reservation`
--

INSERT INTO `reservation` (`id_reservation`, `id_voiture`, `date_prevue_start`, `date_prevue_end`, `date_true_start`, `date_true_end`, `lavage_int`, `lavage_ext`, `lavage_total`, `essence`, `actif`, `fini`, `paye`) VALUES
(1, 4, '2017-12-31 00:00:00', '2018-01-02 00:00:00', '2018-01-01 05:00:00', '2018-01-02 04:19:35', 0, 0, 0, 16, 1, 1, 1),
(4, 1, '2018-01-15 00:00:00', '2018-01-18 00:00:00', '2018-01-15 15:21:41', '2018-01-15 16:06:46', 0, 1, 0, 60, 1, 1, 1);

-- --------------------------------------------------------

--
-- Structure de la table `voiture`
--

CREATE TABLE `voiture` (
  `id_voiture` int(11) NOT NULL,
  `id_proprio` int(11) NOT NULL,
  `plaque_immatriculation` varchar(15) NOT NULL,
  `etat` int(11) NOT NULL DEFAULT '0'
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

--
-- Contenu de la table `voiture`
--

INSERT INTO `voiture` (`id_voiture`, `id_proprio`, `plaque_immatriculation`, `etat`) VALUES
(1, 1, 'EL 110 AM', 0),
(2, 1, '65 CKL 77', 0),
(3, 1, 'EL 220 EM', 0),
(4, 1, 'BATMOBILE!', 0);

--
-- Index pour les tables exportées
--

--
-- Index pour la table `cb`
--
ALTER TABLE `cb`
  ADD PRIMARY KEY (`id_cb`),
  ADD UNIQUE KEY `id_proprio` (`id_proprio`);

--
-- Index pour la table `proprietaire`
--
ALTER TABLE `proprietaire`
  ADD PRIMARY KEY (`id_proprio`);

--
-- Index pour la table `reservation`
--
ALTER TABLE `reservation`
  ADD PRIMARY KEY (`id_reservation`);

--
-- Index pour la table `voiture`
--
ALTER TABLE `voiture`
  ADD PRIMARY KEY (`id_voiture`);

--
-- AUTO_INCREMENT pour les tables exportées
--

--
-- AUTO_INCREMENT pour la table `cb`
--
ALTER TABLE `cb`
  MODIFY `id_cb` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=13;
--
-- AUTO_INCREMENT pour la table `proprietaire`
--
ALTER TABLE `proprietaire`
  MODIFY `id_proprio` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=7;
--
-- AUTO_INCREMENT pour la table `reservation`
--
ALTER TABLE `reservation`
  MODIFY `id_reservation` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=5;
--
-- AUTO_INCREMENT pour la table `voiture`
--
ALTER TABLE `voiture`
  MODIFY `id_voiture` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=5;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
