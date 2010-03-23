<?php

include_once dirname(__FILE__).'/../utils/layout.php.inc';
include_once dirname(__FILE__).'/../utils/utils.php.inc';
include_once dirname(__FILE__).'/../utils/conf.php.inc';
include_once dirname(__FILE__).'/../database/information.php.inc';

function information_page($conf) {

  $content = '<h2>Extened information</h2>
              <p>Add more information to the regions.</p>';

  $layout = new Layout();
  $layout->add_JS_file('js/information.js');
  $layout->add_content($content);
  echo $layout;
}



try {$action = strtolower(Utils::getParam('action'));} catch (Exception $e) {};
switch ($action) {

  default:
    echo information_page($conf);
    break;
}

?>
