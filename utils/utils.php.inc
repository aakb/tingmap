<?php

include_once dirname(__FILE__).'/conf.php.inc';

class Utils {
  public static function getParam($param) {
    if ($_GET[$param] != '') {
      return $_GET[$param];
    }
    else if ($_POST[$param] != '') {
      return $_POST[$param];
    }
    else {
      throw new Exception('Parameter not found: '. $param);
    }
  }
}

?>
