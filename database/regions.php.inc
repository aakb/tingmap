<?php

include_once dirname(__FILE__).'/authorize.php.inc';


class Regions {
  
  private $id = null;
  private $name = null;
  private $file = null;
  private $selected = null;
  private $loaded = false;
  
  private $connection = null;

  // Construct and Destruct
  public function __construct() {
    $this->connection = PDOMysql::getInstance();
  }

  public function __destruct() {
    $this->connection = null;
  }

  public function id($val = null) {
    if ($val != null) {
      $this->id = $val;
    }
    else {
      return $this->id;
    }
  }

  public function name($val) {
    if ($val != null) {
      $this->name = $val;
    }
    else {
      return $this->name;
    }
  }

  public function file($val) {
    if ($val != null) {
      $this->file = $val;
    }
    else {
      return $this->file;
    }
  }

  public function selected($val) {
    if ($val != null) {
      $this->selected = $val;
    }
    else {
      return $this->selected;
    }
  }

  public function load() {
    if ($this->id != null) {
      $statement = 'SELECT * FROM regions WHERE id = :id';
      $query = $this->connection->execute($statement, array('id' => $this->id));

      // Fetch and insert data into this ovject
      $row = $query->fetch(PDO::FETCH_ASSOC);

      $this->name = $row['name'];
      $this->file = $row['file'];
      $this->selected = $row['selected'];

      $this->loaded;
    }
    else {
      throw new Exception('Can\'t load unknown region! (line: '. __LINE__ .')');
    }
  }

  public function save() {
    if ($this->loaded) {
      $statement = 'UPDATE regions SET selected = :selected WHERE id = :id';
      $query = $this->connection->execute($statement, array('selected', $this->selected));
    }
    else {
      throw new Exception('Can\'t save region that have not been loaded! (line: '. __LINE__ .')');
    }
  }

  public function getAllSelectRegions() {
    $statement = 'SELECT * FROM regions WHERE selected = 1';
    $query = $this->connection->execute($statement);

    $regions = array();
    while ($row = $query->fetch(PDO::FETCH_ASSOC)) {
      $regions[$row['id']] = array('name' => $row['name'], 'file' => $row['file']);
    }

    return $regions;
  }
}

?>