<?php

include_once dirname(__FILE__).'/../database/authorize.php.inc';
include_once dirname(__FILE__).'/../database/regions.php.inc';
include_once dirname(__FILE__).'/../utils/layout.php.inc';

include_once dirname(__FILE__).'/../utils/utils.php.inc';

include_once dirname(__FILE__).'/../utils/conf.php.inc';
global $conf;

// Check login
$auth = new Authorize();
if (!$auth->isAuthorized()) {
  echo '<META HTTP-EQUIV="refresh" content="0.001; URL=index.php">';
  exit;
}


function configuration_page($conf) {
  // Load all regions desription
  $regions = new Regions();
  $region_list = $regions->getAllRegions();

  // Wrap regions into checkboxes
  $cell_count = 0;
  $row_count = 0;
  $regions_out = '<table class="listing">';
  foreach ($region_list as $id => $region) {
    if ($cell_count == 0) {
      $row_count++;
      $class = 'odd';
      if (($row_count % 2) == 0) {
        $class = 'even';        
      }
      $regions_out .= '<tr class="'.$class.'">';
    }

    // Cell
    $regions_out .= '<td><input type="checkbox" name="'.$id.'" '.(($region['checked']) ? 'checked="yes"' : '' ).'>'.ucfirst($region['name']).'</input></td>';

    $cell_count++;
    if ($cell_count == 6) {
      $regions_out .= '</tr>';
      $cell_count = 0;
    }
  }
  $regions_out .= '</table>';
  
  // Form wrapper
  $content = '<h2>Regions</h2>
              <p>Select the regions that should be displayed on the Google map.</p>
              <form id="conf_region" name="conf_region" action="" method="post">
                <input type="hidden" name="action" id="action" value="updateregions" />
                ' . $regions_out . '
                <div id="feedback">
                  <span id="icon"></span>
                  <span id="msg"></span>
                </div>
                
                <div class="buttons">
                  <input class="button" id="saveBtn" type="button" value="Save" />
                </div>
              </form>';

  $layout = new Layout();
  $layout->add_JS_file('js/config.js');
  $layout->add_content($content);
  echo $layout;
}

try {$action = strtolower(Utils::getParam('action'));} catch (Exception $e) {};
switch ($action) {
  case 'updateregions':
    // Deselect all regions
    $region = new Regions();
    $region->deselectAllRegions();

    // Set selected regions
    foreach ($_POST as $id => $state) {
      if (is_numeric($id)) {
        $region->id($id);
        $region->load();
        if ($state == 'on') {
          $region->selected(1);
        }
        else {
          $region->selected(0);
        }
        $region->save();
      }
    }
    echo json_encode(array('status' => 1,
                           'msg' => 'Regions saved'));

    break;

  default:
    echo configuration_page($conf);
    break;
}

?>
