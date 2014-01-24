<?php

define('REGION_SELECTED', 'region_selected');
define('REGION_NOT_SELECTED', 'region_not_selected');
define('REGION_INTERESTED', 'region_interested');
define('REGION_NOT_INTERESTED', 'region_not_interested');

class Conf {

  // Database configuration
  private $database = 'tingmap';
  private $server   = 'localhost';
  private $user     = 'drupaladmin ';
  private $passwd   = 'gagger94buv';

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

  // Define region settings
  private $region_interested_color = '#0000FF';
  private $region_not_interested_color = '#FF0000';

  public function getRegionInterestedColor() {
    return $this->region_interested_color;
  }

  public function getRegionNotInterestedColor() {
    return $this->region_not_interested_color;
  }
  // End region settings

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
