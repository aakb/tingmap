<?php

include_once dirname(__FILE__) .'/../database/authorize.php.inc';

$auth = new Authorize();
$auth->Logout();
echo '<META HTTP-EQUIV="refresh" content="0.001; URL=index.php">';

?>