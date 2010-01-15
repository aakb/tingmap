<?php

include_once dirname(__FILE__).'/../utils/layout.php.inc';
include_once dirname(__FILE__).'/../utils/utils.php.inc';
include_once dirname(__FILE__).'/../utils/conf.php.inc';

include_once dirname(__FILE__).'/../database/regions.php.inc';

function colors_page($conf) {

  $regions = new Regions();
  $selected_regions = $regions->getAllSelectRegions();

  $content = '<h2>Colors</h2>
             <p>Select the colors for the selected regions.</p>';

  $content .= '<dl id="color-selections">';
  foreach ($selected_regions as $key => $region) {
    $content .= '<dt class="color-name">'.$region['name'].'</dt>
                    <dd id="preview-color-'.$key.'">
                      <div class="preview-color"></div><input id="region_'.$key.'" type="hidden" value="'.$region['color'].'"></input>
                    </dd>';
  }
  $content .= '</dl>';

  $layout = new Layout();
  $layout->add_JS_file('js/colors.js');
  $layout->add_content($content);
  echo $layout;
}



try {$action = strtolower(Utils::getParam('action'));} catch (Exception $e) {};
switch ($action) {
  
  case 'updatecolor':
    

    break;

  default:
    echo colors_page($conf);
    break;
}

?>
