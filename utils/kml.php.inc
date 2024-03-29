<?php

include_once dirname(__FILE__).'/PolylineEncoder.php';

class kml {

  private $name = null;
  private $file = null;

  private $region_polygons = null;

  public function __construct($name, $file) {
    $this->name = $name;
    $this->file = $file;
    $this->load();
  }

  private function load() {
    $xml = simplexml_load_file($this->file);
    $polygons = $xml->Document->Placemark->MultiGeometry->Polygon;
    foreach ($polygons as $polygon) {
      $points = split(' ', $polygon->outerBoundaryIs->LinearRing->coordinates[0]);
      array_pop($points); // Remove empty laste element
      $points = array_map(array($this, 'clean_coordinates'), $points);
      
      // Encode polygons
      $encoder = new PolylineEncoder($points);
      $this->region_polygons[] = $encoder->dpEncode();
    }
  }

  private function clean_coordinates($coordinat) {
    $coordinat = trim(substr($coordinat, 0, -2));
    list ($long, $lat) = split(',', $coordinat);
    return array($lat, $long);
  }

  public function getRegionPolygons() {
    return $this->region_polygons;
  }
}

?>
