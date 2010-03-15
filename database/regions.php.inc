<?php

include_once dirname(__FILE__).'/authorize.php.inc';


class Regions {
  
  private $id = null;
  private $name = null;
  private $file = null;
  private $selected = null;
  private $color = null;
  private $population = null;
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

  public function name($val = null) {
    if ($val != null) {
      $this->name = $val;
    }
    else {
      return $this->name;
    }
  }

  public function file($val = null) {
    if ($val != null) {
      $this->file = $val;
    }
    else {
      return $this->file;
    }
  }

  public function selected($val = null) {
    if ($val != null) {
      $this->selected = $val;
    }
    else {
      return $this->selected;
    }
  }

  public function color($val = null) {
    if ($val != null) {
      $this->color = $val;
    }
    else {
      return $this->color;
    }
  }

  public function population($val = null) {
    if ($val != null) {
      $this->population = $val;
    }
    else {
      return $this->population;
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
      $this->color = $row['color'];
      $this->population = $row['population'];

      $this->loaded = true;
    }
    else {
      throw new Exception('Can\'t load unknown region! (line: '. __LINE__ .')');
    }
  }

  public function save() {
    if ($this->loaded) {
      $statement = 'UPDATE regions SET selected = :selected WHERE id = :id';
      $query = $this->connection->execute($statement, array('id' => $this->id, 'selected' => $this->selected));
    }
    else {
      throw new Exception('Can\'t save region that have not been loaded! (line: '. __LINE__ .')');
    }
  }

  public function updateColor() {
    if ($this->loaded) {
      $statement = 'UPDATE regions SET color = :color WHERE id = :id';
      $query = $this->connection->execute($statement, array('id' => $this->id, 'color' => $this->color));
    }
    else {
      throw new Exception('Can\'t save region that have not been loaded! (line: '. __LINE__ .')');
    }
  }

  public function getAllSelectRegions() {
    $statement = 'SELECT id,name,file,color,population FROM regions WHERE selected = 1';
    $query = $this->connection->execute($statement);

    $regions = array();
    while ($row = $query->fetch(PDO::FETCH_ASSOC)) {
      $regions[$row['id']] = array('name' => ucfirst($row['name']),
                                   'file' => $row['file'],
                                   'color' => $row['color'],
                                   'population' => $row['population']);
    }
    return $regions;
  }

  public function getAllNonSelectedRegions() {
    $statement = 'SELECT id,name,file,color,population FROM regions WHERE selected = 0';
    $query = $this->connection->execute($statement);

    $regions = array();
    while ($row = $query->fetch(PDO::FETCH_ASSOC)) {
      $regions[$row['id']] = array('name' => ucfirst($row['name']),
                                   'file' => $row['file'],
                                   'color' => $row['color'],
                                   'population' => $row['population']);
    }
    return $regions;
  }

  public function getAllRegions() {
    $statement = 'SELECT * FROM regions';
    $query = $this->connection->execute($statement);

    $regions = array();
    while ($row = $query->fetch(PDO::FETCH_ASSOC)) {
      $regions[$row['id']] = array('name' => ucfirst($row['name']),
                                   'file' => $row['file'],
                                   'checked' => $row['selected']);
    }

    return $regions;
  }

  public function deselectAllRegions() {
    $statement = 'UPDATE regions SET selected = 0';
    $query = $this->connection->execute($statement);
  }
}

?>