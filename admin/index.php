<?php

include_once dirname(__FILE__).'/../database/authorize.php.inc';
include_once dirname(__FILE__).'/../utils/utils.php.inc';
include_once dirname(__FILE__).'/../utils/layout.php.inc';

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
  $content = '<div class="box roundCorners" style="width:400px">
                <h2>Login</h2>
                <form id="login" name="login" action="" method="post">
                  <label for="username">Bruger:</label>
                  <input id="username" name="username" type="text" style="width:200px" autocomplete="off"></input>
                  <br />
                  <label for="passwd">Adgangskode:</label>
                  <input id="passwd" name="passwd" type="password" style="width:200px" autocomplete="off"></input>
                  <br />
                  <div id="feedback">
                    <span id="icon"></span>
                    <span id="msg"></span>
                  </div>
                  <div class="button-wrapper">
                    <input class="button" id="loginBtn" type="button" value="Login"></input>
                  </div>
                </form>
              </div>';

  // Build the page
  $layout = new Layout();
  $layout->add_JS_file('js/login.js');
  $layout->add_content($content);
  $layout->addMenu(array());
  echo $layout;
}

?>