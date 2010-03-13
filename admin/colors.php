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

  $content .= '<div class="left">';
  $content .= '<dl id="color-selections">';
  foreach ($selected_regions as $key => $region) {
    $content .= '<dt class="color-name">'.$region['name'].'</dt>
                    <dd id="preview-color-'.$key.'">
                      <div class="preview-color"></div>
                      <input class="region-color" type="hidden" value="'.$region['color'].'"></input>
                      <input class="region-name" type="hidden" value="'.$region['name'].'"></input>
                      <input class="region-id" type="hidden" value="'.$key.'"></input>
                    </dd>';
  }
  $content .= '</dl>';
  $content .= '</div>';
  $content .= '<div id="color-box-selection" class="right box roundCorners">';
  $content .= '  <h2>Color selector</h2>';
  $content .= '  <p>Select a color an click "Save" or click on another rigion to auto save.</p>';
  $content .= '  <div class="center  clearfix">';
  $content .= '    <p id="region-name"></p>';
  $content .= '    <div id="color-picker"></div>';
  $content .= '    <input name="color-hex" id="color-hex" type="text" value="#" size="6"></input>';
  $content .= '    <input name="region-color" id="region-color" type="hidden" value="#"></input>';
  $content .= '    <input name="region-id" id="region-id" type="hidden" value="#"></input>';
  $content .= '    <div class="button-wrapper">';
  $content .= '      <input type="button" id="color-save" value="Save"></input>';
  $content .= '    </div>';
  $content .= '  </div>';
  $content .= '</div>';

  $layout = new Layout();
  $layout->add_CSS_file('css/farbtastic.css');
  $layout->add_CSS_file('css/jquery.jgrowl.css');
  $layout->add_JS_file('js/colors.js');
  $layout->add_JS_file('js/farbtastic.js');
  $layout->add_JS_file('js/jquery.jgrowl_minimized.js');
  $layout->add_content($content);
  echo $layout;
}



try {$action = strtolower(Utils::getParam('action'));} catch (Exception $e) {};
switch ($action) {
  
  case 'updatecolor':
    $region = new Regions();
    $region->id(Utils::getParam('id'));
    $region->load();
    $region->color(Utils::getParam('color'));
    $region->updateColor();
    echo json_encode(array('msg' => 'Color for \''. $region->name() .'\' have been saved'));
    break;

  default:
    echo colors_page($conf);
    break;
}

?>
