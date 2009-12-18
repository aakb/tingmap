<?php

// Load configuration
include_once dirname(__FILE__).'/utils/conf.php.inc';
global $conf;

// Load classes
include_once dirname(__FILE__).'/database/regions.php.inc';
include_once dirname(__FILE__).'/utils/utils.php.inc';
include_once dirname(__FILE__).'/utils/kml.php.inc';

function placeholder($conf) {
  $content = '<div id="ting_gmap" style="background-color:#eee;width:600px;height:650px;"></div>';
  $js = '<script type="text/javascript" src="http://www.google.com/jsapi?key='. $conf->gkey() .'"></script>
         <script type="text/javascript" src="'. $conf->getWebroot() .'/js/tingmap.js"></script>';

  return Utils::getPage($content, $js);
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
      $coordinates[basename($region['file'], '.kml')] = $kml->getCoordinates();
    }

    //print_r($coordinates);

    echo json_encode(array('status' => 1, 'coordinates' => $coordinates));
    break;

  default:
    echo placeholder($conf);
    break;
}

?>