<?php

class kml {

  private $name = null;
  private $file = null;

  private $coordinates = null;
  private $polygon = null;

  public function __construct($name, $file) {
    $this->name = $name;
    $this->file = $file;
    $this->load();
  }

  private function load() {
    $xml = simplexml_load_file($this->file);
    $polygons = $xml->Document->Placemark->MultiGeometry->Polygon;
    foreach ($polygons as $polygon) {
      $this->coordinates[] = array_map(array($this, 'clean_coordinates'), split(' ', $polygon->outerBoundaryIs->LinearRing->coordinates[0]));
    }
  }

  private function clean_coordinates($coordinat) {
    return trim(substr($coordinat, 0, -2));
  }

  public function getCoordinates() {
    return $this->coordinates;
  }
}

?>
