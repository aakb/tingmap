<?php

// Load configuration
include_once dirname(__FILE__).'/utils/conf.php.inc';
global $conf;

// Load classes
include_once dirname(__FILE__).'/database/regions.php.inc';
include_once dirname(__FILE__).'/utils/utils.php.inc';
include_once dirname(__FILE__).'/utils/kml.php.inc';

function placeholder($conf) {
  $content = '<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd">
             <html xmlns="http://www.w3.org/1999/xhtml">
             <head>
               <meta http-equiv="content-type" content="text/html; charset=utf-8"/>
               <script type="text/javascript" src="http://www.google.com/jsapi?key='. $conf->gkey() .'"></script>
               <script type="text/javascript" src="'. $conf->getWebroot() .'/js/tingmap.js"></script>
               <script type="text/javascript" src="'. $conf->getWebroot() .'/js/jquery-1.3.2.min.js"></script>
               <link href="'. $conf->getWebroot() .'/css/style.css" rel="stylesheet" type="text/css"></link>
               <title>
                 TING udbredelseskort
               </title>
             </head>
             <body>
               <div id="content">
                 <div id="ting_gmap" style="background-color:#eee;width:600px;height:650px;"></div>
                 <div id="population">
                   <table border="1">
                     <tr id="pop-total"><td>Dansker</td><td class="num"></td><td class="pro"></td></tr>
                     <tr id="pop-selected"><td>Har T!NG</td><td class="num"></td><td class="pro"></td></tr>
                     <tr id="pop-interested"><td>Interesseret i T!NG</td><td class="num"></td><td class="pro"></td></tr>
                     <tr id="pop-not-interested"><td>Ikke interesseret i T!NG</td><td class="num"></td><td class="pro"></td></tr>
                   </table>
                 </div>
               </div>
             </body>
             </html>';

  echo $content;
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

  default:
    echo placeholder($conf);
    break;
}

?>