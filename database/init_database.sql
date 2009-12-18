# MySQL Navigator Xport
# Database: ting_map
# root@localhost

# CREATE DATABASE ting_map;
# USE ting_map;

#
# Table structure for table 'account'
#

# DROP TABLE IF EXISTS account;
CREATE TABLE `account` (
  `id` int(11) NOT NULL auto_increment,
  `username` text NOT NULL,
  `password` text NOT NULL,
  `level` int(11) NOT NULL,
  `fullname` text NOT NULL,
  `last_login` int(11) NOT NULL,
  `active` tinyint(4) NOT NULL default '0',
  PRIMARY KEY  (`id`)
) ENGINE=MyISAM AUTO_INCREMENT=2 DEFAULT CHARSET=latin1;

#
# Table structure for table 'regions'
#

# DROP TABLE IF EXISTS regions;
CREATE TABLE `regions` (
  `id` int(11) NOT NULL auto_increment,
  `name` text NOT NULL,
  `file` text NOT NULL,
  `selected` tinyint(4) NOT NULL default '0',
  PRIMARY KEY  (`id`)
) ENGINE=MyISAM AUTO_INCREMENT=100 DEFAULT CHARSET=latin1;

#
# Table structure for table 'session'
#

# DROP TABLE IF EXISTS session;
CREATE TABLE `session` (
  `id` text NOT NULL,
  `time` int(11) NOT NULL
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

