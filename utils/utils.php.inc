<?php

class Utils {
  public static function getParam($param) {
    if ($_GET[$param] != '') {
      return $_GET[$param];
    }
    else if ($_POST[$param] != '') {
      return $_POST[$param];
    }
    else {
      return false;
    }
  }
}

?>