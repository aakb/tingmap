<?php

// Load configuration
include_once dirname(__FILE__).'/utils/conf.php.inc';
global $conf;

// Load classes
include_once dirname(__FILE__).'/database/regions.php.inc';
include_once dirname(__FILE__).'/utils/layout.php.inc';
include_once dirname(__FILE__).'/utils/utils.php.inc';
include_once dirname(__FILE__).'/utils/kml.php.inc';

function placeholder($conf) {
  $layout = new Layout(LAYOUT_FRONT);
  echo $layout;
}

// Encode regions information
function encodeRegions($type) {
  global $conf;

  // Load regions from database
  $regions = new Regions();
  $current_regions = null;
  switch ($type) {
    case REGION_SELECTED:
      $current_regions = $regions->getAllSelectRegions();
      break;

    case REGION_INTERESTED:
      $current_regions = $regions->getAllInterestedRegions();
      break;

    case REGION_NOT_INTERESTED:
      $current_regions = $regions->getAllNotInterestedRegions();
      break;

    case REGION_NOT_SELECTED:
      $current_regions = $regions->getAllNonSelectedRegions();
      break;
  }

  // Load regions polygons and encode them
  foreach ($current_regions as $key => $region) {
    $kml = new kml($region['name'], $conf->getKmlPath() . $region[file]);
    $regions_polygons[] = $kml->getRegionPolygons();
    $data[$key] = array('name' => $region['name'],
            'color' => $region['color'],
            'population' => $region['population'],
            'region_polygons' => $regions_polygons);

    // Empty it, as it have been add to data array
    $regions_polygons = null;
  }

  return $data;
}

// Take action
try {$action = strtolower(Utils::getParam('action'));} catch (Exception $e) {};
switch ($action) {
  
  case 'loadselectedregions':
    echo json_encode(array('status' => "selected_regions", 'regions' => encodeRegions(REGION_SELECTED)));
    break;

  case 'loadnotselectedregions':
    echo json_encode(array('status' => "selected_regions", 'regions' => encodeRegions(REGION_NOT_SELECTED)));
    break;

  case 'loadpopulation':
    $regions = new Regions();
    echo json_encode(array('status' => "population", 'population' => $regions->getPopulation()));
    break;

  case 'loadinterestedregions':
    echo json_encode(array('status' => "selected_regions", 'regions' => encodeRegions(REGION_INTERESTED)));
    break;

  case 'loadnotinterestedregions':
    echo json_encode(array('status' => "selected_regions", 'regions' => encodeRegions(REGION_NOT_INTERESTED)));
    break;

  case 'embedded':
    $layout = new Layout(LAYOUT_EMBEDDED);
    echo $layout;
    break;

  default:
    echo placeholder($conf);
    break;
}

?>