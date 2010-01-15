<?php

include_once dirname(__FILE__).'/../utils/layout.php.inc';
include_once dirname(__FILE__).'/../utils/utils.php.inc';
include_once dirname(__FILE__).'/../utils/conf.php.inc';


function colors_page($conf) {

  $layout = new Layout();
  $layout->add_JS_file('js/points.js');
  $layout->add_content($content);
  echo $layout;
}



try {$action = strtolower(Utils::getParam('action'));} catch (Exception $e) {};
switch ($action) {

  case 'updatepoint':


    break;

  default:
    echo colors_page($conf);
    break;
}

?>
