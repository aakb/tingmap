<?php

include_once dirname(__FILE__).'/../database/authorize.php.inc';
include_once dirname(__FILE__).'/../utils/utils.php.inc';

include_once dirname(__FILE__).'/../utils/conf.php.inc';
global $conf;

// Check login
$auth = new Authorize();
if (!$auth->isAuthorized()) {
  echo '<META HTTP-EQUIV="refresh" content="0.001; URL=index.php">';
  exit;
}



try {$action = strtolower(Utils::getParam('action'));} catch (Exception $e) {};
switch ($action) {
  case 'updateregions':
    
    break;

  default:
    
    break;
}

?>
