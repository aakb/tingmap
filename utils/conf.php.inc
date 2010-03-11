<?php

class Conf {

  // Database configuration
  private $database = 'tingmap_etek_dk';
  private $server   = 'localhost';
  private $user     = 'tingmap_etek_dk';
  private $passwd   = '0Gbm5H6s8v5Q84';

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
    return dirname(__FILE__) . '/..' . $this->kml_path;
  }
  // End file paths

  // Google map settings
  private $gkey = 'ABQIAAAA9R5q17pqStwXYr5_fGwbshQdsGoDhOO5dDXgBJZflgvLfp46ZxTNIa0B3Rd_pPY_bXR1pEjzpOJ1Tw';
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

  private $admin_page = '/admin/regions.php';
  public function getAdminPage() {
    return $this->getWebroot() . $this->admin_page;
  }
  // End define the system locations

  // Cookie config
  private $cookie_name   = 'tingmap';
  private $cookie_expire = 30; // Mins
  public function getCookieName() {
    return $this->cookie_name;
  }

  public function getCookieExpire() {
    return $this->cookie_expire * 60; // Secs
  }
  // End cookie config
}

$conf = new Conf();

?>
