-- phpMyAdmin SQL Dump
-- version 3.4.9
-- http://www.phpmyadmin.net
--
-- Client: localhost
-- Généré le : Jeu 14 Mai 2020 à 13:41
-- Version du serveur: 5.5.20
-- Version de PHP: 5.3.9

SET SQL_MODE="NO_AUTO_VALUE_ON_ZERO";
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;

--
-- Base de données: `smart_finances`
--

-- --------------------------------------------------------

--
-- Structure de la table `administrateur`
--

CREATE TABLE IF NOT EXISTS `administrateur` (
  `ID` int(11) NOT NULL AUTO_INCREMENT,
  `Pseudo` varchar(100) NOT NULL,
  `MDP` varchar(50) NOT NULL,
  PRIMARY KEY (`ID`)
) ENGINE=InnoDB  DEFAULT CHARSET=latin1 AUTO_INCREMENT=6 ;

--
-- Contenu de la table `administrateur`
--

INSERT INTO `administrateur` (`ID`, `Pseudo`, `MDP`) VALUES
(1, 'gerard37', '123456789'),
(5, 'test', '123456789');

-- --------------------------------------------------------

--
-- Structure de la table `article`
--

CREATE TABLE IF NOT EXISTS `article` (
  `IDArticle` int(11) NOT NULL AUTO_INCREMENT,
  `Titre` varchar(50) NOT NULL,
  `Contenu` varchar(50) NOT NULL,
  `Description` longtext NOT NULL,
  `Solde` varchar(125) NOT NULL,
  `IDSC` int(11) NOT NULL,
  PRIMARY KEY (`IDArticle`),
  KEY `Article_SousChapitre_FK` (`IDSC`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1 AUTO_INCREMENT=1 ;

-- --------------------------------------------------------

--
-- Structure de la table `chapitre`
--

CREATE TABLE IF NOT EXISTS `chapitre` (
  `IDChap` int(11) NOT NULL AUTO_INCREMENT,
  `Titre` varchar(50) NOT NULL,
  `Contenu` varchar(255) NOT NULL,
  `Description` longtext NOT NULL,
  `Solde` varchar(125) NOT NULL,
  PRIMARY KEY (`IDChap`)
) ENGINE=InnoDB  DEFAULT CHARSET=latin1 AUTO_INCREMENT=7 ;

--
-- Contenu de la table `chapitre`
--

INSERT INTO `chapitre` (`IDChap`, `Titre`, `Contenu`, `Description`, `Solde`) VALUES
(6, 'Chapitre1', 'Test', 'Test', '100');

-- --------------------------------------------------------

--
-- Structure de la table `fournisseur`
--

CREATE TABLE IF NOT EXISTS `fournisseur` (
  `ID` int(11) NOT NULL AUTO_INCREMENT,
  `Gerant` varchar(50) NOT NULL,
  `RaisonSocial` varchar(255) NOT NULL,
  `Description` longtext NOT NULL,
  `Domaine` varchar(255) NOT NULL,
  `Creation` year(4) NOT NULL,
  `Popularite` varchar(255) NOT NULL,
  `Ville` varchar(125) NOT NULL,
  PRIMARY KEY (`ID`)
) ENGINE=InnoDB  DEFAULT CHARSET=latin1 AUTO_INCREMENT=2 ;

--
-- Contenu de la table `fournisseur`
--

INSERT INTO `fournisseur` (`ID`, `Gerant`, `RaisonSocial`, `Description`, `Domaine`, `Creation`, `Popularite`, `Ville`) VALUES
(1, 'Gerant', 'Raison sociale', 'Description', 'Nettoyage ', 2001, 'Popularité', 'Tours');

-- --------------------------------------------------------

--
-- Structure de la table `programme`
--

CREATE TABLE IF NOT EXISTS `programme` (
  `IDProg` int(11) NOT NULL AUTO_INCREMENT,
  `Titre` varchar(50) NOT NULL,
  `Contenu` varchar(255) NOT NULL,
  `Description` longtext NOT NULL,
  `Solde` varchar(255) NOT NULL,
  `IDArticle` int(11) NOT NULL,
  PRIMARY KEY (`IDProg`),
  KEY `Programme_Article_FK` (`IDArticle`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1 AUTO_INCREMENT=1 ;

-- --------------------------------------------------------

--
-- Structure de la table `souschapitre`
--

CREATE TABLE IF NOT EXISTS `souschapitre` (
  `IDSC` int(11) NOT NULL AUTO_INCREMENT,
  `Titre` varchar(50) NOT NULL,
  `Contenu` varchar(255) NOT NULL,
  `Description` longtext NOT NULL,
  `Solde` varchar(125) NOT NULL,
  `IDChap` int(11) NOT NULL,
  PRIMARY KEY (`IDSC`),
  KEY `SousChapitre_Chapitre_FK` (`IDChap`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1 AUTO_INCREMENT=1 ;

-- --------------------------------------------------------

--
-- Structure de la table `transaction`
--

CREATE TABLE IF NOT EXISTS `transaction` (
  `IDTransac` int(11) NOT NULL AUTO_INCREMENT,
  `Nature` varchar(50) NOT NULL,
  PRIMARY KEY (`IDTransac`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1 AUTO_INCREMENT=1 ;

--
-- Contraintes pour les tables exportées
--

--
-- Contraintes pour la table `article`
--
ALTER TABLE `article`
  ADD CONSTRAINT `Article_SousChapitre_FK` FOREIGN KEY (`IDSC`) REFERENCES `souschapitre` (`IDSC`);

--
-- Contraintes pour la table `programme`
--
ALTER TABLE `programme`
  ADD CONSTRAINT `Programme_Article_FK` FOREIGN KEY (`IDArticle`) REFERENCES `article` (`IDArticle`);

--
-- Contraintes pour la table `souschapitre`
--
ALTER TABLE `souschapitre`
  ADD CONSTRAINT `SousChapitre_Chapitre_FK` FOREIGN KEY (`IDChap`) REFERENCES `chapitre` (`IDChap`);

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
