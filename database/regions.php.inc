<?php

include_once dirname(__FILE__).'/authorize.php.inc';


class Regions {
  
  private $id = null;
  private $name = null;
  private $file = null;
  private $selected = null;

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
      $statment = 'SELECT * FROM regions WHERE id = '. $this->id;
      
    }
    else {
      throw new Exception('Can\'t load unknown kommune! (line: '. __LINE__ .')');
    }
  }

  public function save() {
    
  }

  public function getAllSelectRegions() {
    
  }
}

?>