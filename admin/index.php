<?php

include_once dirname(__FILE__).'/../database/authorize.php.inc';
include_once dirname(__FILE__).'/../utils/utils.php.inc';

include_once dirname(__FILE__).'/../utils/conf.php.inc';
global $conf;

/* Check if user is aurhorizes */
$auth = new Authorize();
if ($auth->isAuthorized()) {
  echo '<META HTTP-EQUIV="refresh" content="0.001; URL=' . $conf->getAdminPage() . '">';
  exit;
}

/* Try to login */
$username = null;
$passwd   = null;
try {
  $username = Utils::getParam('username');
  $passwd   = Utils::getParam('passwd');

  try {
    $auth->Login($username, $passwd);
    echo json_encode(array('status'  => 'granted',
                           'message' => 'Logged ind, vent...',
                           'url' => $conf->getAdminPage()));
  }
  catch (Exception $e) {
    /* Access not granted */
    echo json_encode(array('status'  => 'denied',
                           'message' => $e->getMessage()));
  }
}
catch (Exception $e) {

  // Display login form
  $content = '<div class="spacer">&nbsp;</div>
              <div class="box">
                <h2 class="alignCenter">Log ind</h2>
                <form name="login" id="login" action="" method="post">
                  <div id="field">
                    <label for="username">Bruger:</label>
                    <input id="username" name="username" type="text" style="width:200px" autocomplete="off" />
                  </div>
                  <div id="field">
                    <label for="passwd">Adgangskode:<label>
                    <input id="passwd" name="passwd" type="password" style="width:200px" autocomplete="off" />
                  </div>
                  <div id="feedback"><span>&nbsp;</span></div>
                  <div id="buttons">
                    <input class="button" id="loginBtn" type="button" value="Login" />
                  </div>
                </form>
              </div>
            <div class="spacer">&nbsp;</div>';

  echo Utils::getPage($content, '<script type="text/javascript" src="'. $conf->getWebroot() .'/js/login.js"></script>');
}

?>