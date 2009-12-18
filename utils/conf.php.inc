<?php

class Conf {

  // Database configuration
  private $database = 'ting_map';
  private $server   = 'localhost';
  private $user     = 'root';
  private $passwd   = 'Hr1Rod';

  public function getDB() {
    return $this->database;
  }

  public function getServer() {
    return $this->server;
  }

  public function getUser() {
    return $this->user;
  }

  public function getPassword() {
    return $this->passwd;
  }
  // End database configuration

  // File paths
  private $kml_path = '/kml/';
  public function getKmlPath() {
    return $this->kml_path;
  }
  // End file paths

  // Cookie settings
  private $cookiename = 'ding_ting_map';
  public function getCookieName() {
    return $this->cookiename;
  }
  // End cookie settings

  // Google map settings
  private $gkey = 'ABQIAAAA9R5q17pqStwXYr5_fGwbshSFlJqI8A_ukbJ8NDNja8qdLzJOsxRNd-9GEiAZNWhR5c7j5G-fyr0e6g';
  public function gkey() {
    return $this->gkey;
  }

  private $gmap_center = '56.016808, 10.431763'; // Denmark centring at zoom 7
  public function gmap_center() {
    return $this->gmap_center;
  }

  // End google map settings

  // Define the system locations
  private $webroot = null;
  public function getWebroot() {
    if ($this->webroot == null) {
      $path = substr(dirname(__FILE__), 0, strlen(dirname(__FILE__)) - 5);
      $this->webroot = substr($path, strlen($_SERVER['DOCUMENT_ROOT']));

      // Correction of webroot
      if ($this->webroot == '/') {
        $this->webroot = '';
      }
    }
    return $this->webroot;
  }
  // End define the system locations
}

$conf = new Conf();

?>
