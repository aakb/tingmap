<?php

include_once dirname(__FILE__).'/authorize.php.inc';
include_once dirname(__FILE__).'/../utils/conf.php.inc';

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
    $statement = 'SELECT id,name,file,color FROM regions WHERE selected = 1';
    $query = $this->connection->execute($statement);

    $regions = array();
    while ($row = $query->fetch(PDO::FETCH_ASSOC)) {
      $regions[$row['id']] = array('name' => ucfirst($row['name']),
                                   'file' => $row['file'],
                                   'color' => $row['color']);
    }
    return $regions;
  }

  public function getAllInterestedRegions() {
    global $conf;

    $statement = 'SELECT id,name,file,color FROM regions WHERE interested = 1';
    $query = $this->connection->execute($statement);

    $regions = array();
    while ($row = $query->fetch(PDO::FETCH_ASSOC)) {
      $regions[$row['id']] = array('name' => ucfirst($row['name']),
                                   'file' => $row['file'],
                                   'color' => $conf->getRegionInterestedColor());
    }
    return $regions;
  }

  public function getAllNotInterestedRegions() {
    global $conf;

    $statement = 'SELECT id,name,file,color FROM regions WHERE not_interested = 1';
    $query = $this->connection->execute($statement);

    $regions = array();
    while ($row = $query->fetch(PDO::FETCH_ASSOC)) {
      $regions[$row['id']] = array('name' => ucfirst($row['name']),
                                   'file' => $row['file'],
                                   'color' => $conf->getRegionNotInterestedColor());
    }
    return $regions;
  }

  public function getAllNonSelectedRegions() {
    $statement = 'SELECT id,name,file,color FROM regions WHERE selected = 0';
    $query = $this->connection->execute($statement);

    $regions = array();
    while ($row = $query->fetch(PDO::FETCH_ASSOC)) {
      $regions[$row['id']] = array('name' => ucfirst($row['name']),
                                   'file' => $row['file'],
                                   'color' => $row['color']);
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

  public function getPopulation($all = false) {
    // Load total population
    $data = array();
    $statement = 'SELECT sum(population) AS total FROM regions';
    $query = $this->connection->execute($statement);
    $row = $query->fetch(PDO::FETCH_ASSOC);
    $data['total'] = $row['total'];
    $query->closeCursor();
    unset($query); // to avoid 2050 error

    // Load pop in selected regions
    $data['selected'] = 0;
    $statement = 'SELECT population FROM regions WHERE selected = 1';
    $query = $this->connection->execute($statement);
    while ($row = $query->fetch(PDO::FETCH_ASSOC)) {
      $data['selected'] += $row['population'];
    }
    $query->closeCursor();
    unset($query); // to avoid 2050 error

    // Load interested pop
    $data['interested'] = 0;
    $statement = 'SELECT population FROM regions WHERE interested = 1';
    $query = $this->connection->execute($statement);
    while ($row = $query->fetch(PDO::FETCH_ASSOC)) {
      $data['interested'] += $row['population'];
    }
    $query->closeCursor();
    unset($query); // to avoid 2050 error

    // Load not interested pop
    $data['not-interested'] = 0;
    $statement = 'SELECT population FROM regions WHERE not_interested = 1';
    $query = $this->connection->execute($statement);
    while ($row = $query->fetch(PDO::FETCH_ASSOC)) {
      $data['not-interested'] += $row['population'];
    }
    $query->closeCursor();
    unset($query); // to avoid 2050 error

    return $data;
  }
}

?>