<?php

class kml {

  private $name = null;
  private $file = null;

  private $coordinates = null;
  private $polygon = null;

  public function __construct($name, $file) {
    $this->name = $name;
    $this->file = $file;
  }

  public function load() {
    $xml = simplexml_load_file($this->file);
    $this->coordinates = split(' ', $xml->Document->Placemark->MultiGeometry->Polygon->outerBoundaryIs->LinearRing->coordinates[0]);
    $this->coordinates = array_map(array($this, 'clean_coordinates'), $this->coordinates);
  }

  private function clean_coordinates($coordinat) {
    return substr($coordinat, 0, -2);
  }

  public function getCoordinates() {
    return $this->coordinates;
  }
}

?>
