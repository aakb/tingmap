<?php

// Load configuration
include_once dirname(__FILE__).'/utils/conf.php.inc';
global $conf;

// Load classes
include_once dirname(__FILE__).'/database/regions.php.inc';
include_once dirname(__FILE__).'/utils/utils.php.inc';
include_once dirname(__FILE__).'/utils/kml.php.inc';

function placeholder($conf) {
  $out = '<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd">
          <html xmlns="http://www.w3.org/1999/xhtml">
          <head>
            <meta http-equiv="content-type" content="text/html; charset=utf-8"/>
            <title>
              TING udbredelseskort
            </title>
            <script type="text/javascript" src="'. $conf->getWebroot() .'/js/jquery-1.3.2.min.js"></script>
            <script type="text/javascript" src="http://www.google.com/jsapi?key='. $conf->gkey() .'"></script>
            <script type="text/javascript" src="'. $conf->getWebroot() .'/js/tingmap.js"></script>
          </head>
          <body>
            <div id="ting_gmap" style="background-color:#eee;width:600px;height:650px;"></div>
          </body>
        </html>';
  return $out;
}

// Take action
$action = strtolower(Utils::getParam('action'));
switch ($action) {
  
  case 'loadcoordinates':
    // Get select regions
    $regions = new Regions();
    $selected_regions = $regions->getAllSelectRegions();

    foreach ($selected_regions as $key => $region) {
      $coordinates = new kml($region['name'], $conf->getKmlPath() . $region[file]);
      print_r($coordinates->getCoordinates());
      echo '<br/><br/><br/><br/>';
    }

    //echo json_encode(array('status' => 1, 'regions' => $regions));
    break;

  default:
    echo placeholder($conf);
    break;
}

?>