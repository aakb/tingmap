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
}

$conf = new Conf();

?>
