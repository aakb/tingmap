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
                   <h2>Ting population</h2>
                 </div>
               </div>
             </body>
             </html>';

  echo $content;
}

// Take action
try {$action = strtolower(Utils::getParam('action'));} catch (Exception $e) {};
switch ($action) {
  
  case 'loadcoordinates':
    // Get select regions and coordinates
    $regions = new Regions();
    $selected_regions = $regions->getAllSelectRegions();

    foreach ($selected_regions as $key => $region) {
      $kml = new kml($region['name'], $conf->getKmlPath() . $region[file]);
      $regions_polygons[] = $kml->getRegionPolygons();
      $data[$key] = array('name' => $region['name'],
                          'color' => $region['color'],
                          'population' => $region['population'],
                          'region_polygons' => $regions_polygons);

      // Empty it, as it have been add to data array
      $regions_polygons = null; 
    }
    
    echo json_encode(array('status' => 1, 'regions' => $data));
    break;

  default:
    echo placeholder($conf);
    break;
}

?>