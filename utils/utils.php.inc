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

  public static function getPage($content, $js) {
    global $conf;

    // Main page layout
    $page = '<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd">
             <html xmlns="http://www.w3.org/1999/xhtml">
             <head>
               <meta http-equiv="content-type" content="text/html; charset=utf-8"/>
               <link href="'. $conf->getWebroot() .'/css/style.css" rel="stylesheet" type="text/css" />
               <script type="text/javascript" src="'. $conf->getWebroot() .'/js/jquery-1.3.2.min.js"></script>
               '.$js.'
               <title>
                 TING udbredelseskort
               </title>
             </head>
             <body>
               '.$content.'
             </body>
             </html>';

    return $page;
  }
}

?>
