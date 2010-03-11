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
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `username` text NOT NULL,
  `password` text NOT NULL,
  `level` int(11) NOT NULL,
  `fullname` text NOT NULL,
  `last_login` int(11) NOT NULL,
  `active` tinyint(4) NOT NULL DEFAULT '0',
  PRIMARY KEY (`id`)
) ENGINE=MyISAM AUTO_INCREMENT=3 DEFAULT CHARSET=latin1;

#
# Dumping data for table 'account'
#

INSERT INTO account VALUES (1,'cableman','654e199892dc16043fb5b37ab12f049c',10,'Jesper Kristensen',1268256178,1);
INSERT INTO account VALUES (2,'bo','a8f2728a70ba97a9e29a0ee82947de19',10,'Bo Fristed',1261384929,1);

#
# Table structure for table 'regions'
#

# DROP TABLE IF EXISTS regions;
CREATE TABLE `regions` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `name` text NOT NULL,
  `file` text NOT NULL,
  `selected` tinyint(4) NOT NULL DEFAULT '0',
  `color` varchar(7) NOT NULL DEFAULT '#0000FF',
  `population` int(11) NOT NULL DEFAULT '0',
  PRIMARY KEY (`id`)
) ENGINE=MyISAM AUTO_INCREMENT=100 DEFAULT CHARSET=latin1;

#
# Dumping data for table 'regions'
#

INSERT INTO regions VALUES (1,'aabenrå','aabenraa.kml',1,'#0000FF',59978);
INSERT INTO regions VALUES (2,'aalborg','aalborg.kml',1,'#FF0000',197426);
INSERT INTO regions VALUES (3,'albertslund','albertslund.kml',0,'#0000FF',27730);
INSERT INTO regions VALUES (4,'allerød','alleroed.kml',0,'#0000FF',24089);
INSERT INTO regions VALUES (5,'assens','assens.kml',0,'#0000FF',42054);
INSERT INTO regions VALUES (6,'ballerup','ballerup.kml',0,'#0000FF',47652);
INSERT INTO regions VALUES (7,'billund','billund.kml',0,'#0000FF',26160);
INSERT INTO regions VALUES (8,'bornholm','bornholm.kml',0,'#0000FF',42154);
INSERT INTO regions VALUES (9,'brøndby','broendby.kml',0,'#0000FF',33795);
INSERT INTO regions VALUES (10,'brønderslev','broenderslev.kml',0,'#0000FF',35804);
INSERT INTO regions VALUES (11,'christiansø','christiansoe.kml',0,'#0000FF',101);
INSERT INTO regions VALUES (12,'dragø','dragoe.kml',0,'#0000FF',13564);
INSERT INTO regions VALUES (13,'egedal','egedal.kml',0,'#0000FF',41513);
INSERT INTO regions VALUES (14,'esbjerg','esbjerg.kml',0,'#0000FF',115114);
INSERT INTO regions VALUES (15,'fanø','fanoe.kml',0,'#0000FF',3219);
INSERT INTO regions VALUES (16,'favrskov','favrskov.kml',0,'#0000FF',46529);
INSERT INTO regions VALUES (17,'faxe','faxe.kml',0,'#0000FF',35306);
INSERT INTO regions VALUES (18,'fredensborg','fredensborg.kml',0,'#0000FF',39226);
INSERT INTO regions VALUES (19,'fredericia','fredericia.kml',1,'#000000',49849);
INSERT INTO regions VALUES (20,'frederiksberg','frederiksberg.kml',0,'#0000FF',96718);
INSERT INTO regions VALUES (21,'frederikshavn','frederikshavn.kml',0,'#0000FF',62007);
INSERT INTO regions VALUES (22,'frederikssund','frederikssund.kml',0,'#0000FF',44182);
INSERT INTO regions VALUES (23,'furesø','furesoe.kml',0,'#0000FF',38232);
INSERT INTO regions VALUES (24,'fåborg','faaborg.kml',0,'#0000FF',52085);
INSERT INTO regions VALUES (25,'gentofte','gentofte.kml',1,'#00ff52',71052);
INSERT INTO regions VALUES (26,'gladsaxe','gladsaxe.kml',0,'#0000FF',64102);
INSERT INTO regions VALUES (27,'glostrup','glostrup.kml',0,'#0000FF',21296);
INSERT INTO regions VALUES (28,'greve','greve.kml',0,'#0000FF',47826);
INSERT INTO regions VALUES (29,'gribskov','gribskov.kml',0,'#0000FF',40694);
INSERT INTO regions VALUES (30,'guldborgsund','guldborgsund.kml',0,'#0000FF',62912);
INSERT INTO regions VALUES (31,'haderslev','haderslev.kml',0,'#0000FF',56346);
INSERT INTO regions VALUES (32,'halsnæs','halsnaes.kml',0,'#0000FF',31077);
INSERT INTO regions VALUES (33,'hedensted','hedensted.kml',0,'#0000FF',45982);
INSERT INTO regions VALUES (34,'helsingør','helsingoer.kml',0,'#0000FF',61143);
INSERT INTO regions VALUES (35,'herlev','herlev.kml',0,'#0000FF',26556);
INSERT INTO regions VALUES (36,'herning','herning.kml',1,'#fdb912',85548);
INSERT INTO regions VALUES (37,'hillerød','hilleroed.kml',0,'#0000FF',47473);
INSERT INTO regions VALUES (38,'hjørring','hjoerring.kml',0,'#0000FF',66803);
INSERT INTO regions VALUES (39,'holbæk','holbaek.kml',0,'#0000FF',69550);
INSERT INTO regions VALUES (40,'holstebro','holstebro.kml',0,'#0000FF',57056);
INSERT INTO regions VALUES (41,'horsens','horsens.kml',0,'#0000FF',81957);
INSERT INTO regions VALUES (42,'hvidovre','hvidovre.kml',0,'#0000FF',49724);
INSERT INTO regions VALUES (43,'højetåstrup','hoejetaastrup.kml',0,'#0000FF',47664);
INSERT INTO regions VALUES (44,'hørsholm','hoersholm.kml',0,'#0000FF',24378);
INSERT INTO regions VALUES (45,'ikast','ikast.kml',0,'#0000FF',40312);
INSERT INTO regions VALUES (46,'ishøj','ishoej.kml',0,'#0000FF',20606);
INSERT INTO regions VALUES (47,'jammerbugt','jammerbugt.kml',0,'#0000FF',38927);
INSERT INTO regions VALUES (48,'kalundborg','kalundborg.kml',0,'#0000FF',49265);
INSERT INTO regions VALUES (49,'kerteminde','kerteminde.kml',0,'#0000FF',23770);
INSERT INTO regions VALUES (50,'kolding','kolding.kml',1,'#0000FF',89071);
INSERT INTO regions VALUES (51,'københavn','koebenhavn.kml',1,'#fa52d1',528208);
INSERT INTO regions VALUES (52,'køge','koege.kml',0,'#0000FF',57125);
INSERT INTO regions VALUES (53,'langeland','langeland.kml',0,'#0000FF',13510);
INSERT INTO regions VALUES (54,'lejre','lejre.kml',0,'#0000FF',26794);
INSERT INTO regions VALUES (55,'lemvig','lemvig.kml',0,'#0000FF',21790);
INSERT INTO regions VALUES (56,'lolland','lolland.kml',0,'#0000FF',46984);
INSERT INTO regions VALUES (57,'lyngby','lyngby.kml',0,'#0000FF',52237);
INSERT INTO regions VALUES (58,'læsø','laesoe.kml',0,'#0000FF',1969);
INSERT INTO regions VALUES (59,'mariagerfjord','mariagerfjord.kml',0,'#0000FF',42604);
INSERT INTO regions VALUES (60,'middelfart','middelfart.kml',0,'#0000FF',37661);
INSERT INTO regions VALUES (61,'morsø','morsoe.kml',0,'#0000FF',21833);
INSERT INTO regions VALUES (62,'norddjurs','norddjurs.kml',0,'#0000FF',38148);
INSERT INTO regions VALUES (63,'nordfyns','nordfyns.kml',0,'#0000FF',29638);
INSERT INTO regions VALUES (64,'nyborg','nyborg.kml',0,'#0000FF',31690);
INSERT INTO regions VALUES (65,'næstved','naestved.kml',0,'#0000FF',81112);
INSERT INTO regions VALUES (66,'odder','odder.kml',0,'#0000FF',21721);
INSERT INTO regions VALUES (67,'odense','odense.kml',1,'#0000FF',188777);
INSERT INTO regions VALUES (68,'odsherred','odsherred.kml',0,'#0000FF',33030);
INSERT INTO regions VALUES (69,'randers','randers.kml',0,'#0000FF',94750);
INSERT INTO regions VALUES (70,'rebild','rebild.kml',0,'#0000FF',28852);
INSERT INTO regions VALUES (71,'ringkøbing','ringkoebing.kml',0,'#0000FF',58439);
INSERT INTO regions VALUES (72,'ringsted','ringsted.kml',0,'#0000FF',32584);
INSERT INTO regions VALUES (73,'roskilde','roskilde.kml',0,'#0000FF',81947);
INSERT INTO regions VALUES (74,'rudersdal','rudersdal.kml',0,'#0000FF',54444);
INSERT INTO regions VALUES (75,'rødovre','roedovre.kml',0,'#0000FF',36233);
INSERT INTO regions VALUES (76,'samsø','samsoe.kml',0,'#0000FF',4010);
INSERT INTO regions VALUES (77,'svendborg','svendborg.kml',0,'#0000FF',58998);
INSERT INTO regions VALUES (78,'silkeborg','silkeborg.kml',0,'#0000FF',88481);
INSERT INTO regions VALUES (79,'skanderborg','skanderborg.kml',0,'#0000FF',57303);
INSERT INTO regions VALUES (80,'skive','skive.kml',0,'#0000FF',48137);
INSERT INTO regions VALUES (81,'slagelse','slagelse.kml',0,'#0000FF',77475);
INSERT INTO regions VALUES (82,'solrød','solroed.kml',0,'#0000FF',20882);
INSERT INTO regions VALUES (83,'sorø','soroe.kml',0,'#0000FF',29522);
INSERT INTO regions VALUES (84,'stevns','stevns.kml',0,'#0000FF',21931);
INSERT INTO regions VALUES (85,'struer','struer.kml',0,'#0000FF',22483);
INSERT INTO regions VALUES (86,'syddjurs','syddjurs.kml',0,'#0000FF',41392);
INSERT INTO regions VALUES (87,'sønderborg','soenderborg.kml',0,'#0000FF',76439);
INSERT INTO regions VALUES (88,'thisted','thisted.kml',0,'#0000FF',45297);
INSERT INTO regions VALUES (89,'tårnby','taarnby.kml',0,'#0000FF',40383);
INSERT INTO regions VALUES (90,'tønder','toender.kml',0,'#0000FF',39710);
INSERT INTO regions VALUES (91,'vallensbæk','vallensbaek.kml',0,'#0000FF',14045);
INSERT INTO regions VALUES (92,'varde','varde.kml',0,'#0000FF',50378);
INSERT INTO regions VALUES (93,'vejen','vejen.kml',1,'#ff00b7',42768);
INSERT INTO regions VALUES (94,'vejle','vejle.kml',0,'#0000FF',106383);
INSERT INTO regions VALUES (95,'vesthimmerlands','vesthimmerlands.kml',0,'#0000FF',38106);
INSERT INTO regions VALUES (96,'viborg','viborg.kml',0,'#0000FF',93310);
INSERT INTO regions VALUES (97,'vordingborg','vordingborg.kml',0,'#0000FF',46319);
INSERT INTO regions VALUES (98,'ærø','aeroe.kml',0,'#0000FF',6679);
INSERT INTO regions VALUES (99,'århus','aarhus.kml',1,'#00ff34',306650);

#
# Table structure for table 'session'
#

# DROP TABLE IF EXISTS session;
CREATE TABLE `session` (
  `id` text NOT NULL,
  `time` int(11) NOT NULL
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

#
# Dumping data for table 'session'
#


