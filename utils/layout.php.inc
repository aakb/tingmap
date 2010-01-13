<?php

include_once 'conf.php.inc';

class Layout {

  private $css = array('css/style.css');
  private $js = array('js/jquery-1.3.2.min.js');
  private $content = '';

  private $conf = null;

  public function __construct() {
    global $conf;
    $this->conf = $conf;    
  }

  public function __toString() {
    return $this->build();
  }

  public function add_JS_file($file) {
    $this->js[] = $file;
  }

  public function add_CSS_file($file) {
    $this->css[] = $file;
  }

  public function add_content($content) {
    $this->content = $content;
  }

  private function wrap_array_in_element($format, $array) {
    $str = '';
    foreach ($array as $value) {
      $str .= sprintf($format, $value);
    }
    return $str;
  }

  private function build() {
    // Main page layout
    $page = '<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd">
             <html xmlns="http://www.w3.org/1999/xhtml">
             <head>
               <meta http-equiv="content-type" content="text/html; charset=utf-8"/>
               '. $this->wrap_array_in_element('<link href="'. $this->conf->getWebroot() .'/%s" rel="stylesheet" type="text/css"></link>', $this->css) .'
               '. $this->wrap_array_in_element('<script type="text/javascript" src="'. $this->conf->getWebroot() .'/%s"></script>', $this->js) .'
               <title>
                 TING udbredelseskort
               </title>
             </head>
             <body>
               <div id="content">
                 '.$this->content.'
               </div>
             </body>
             </html>';

    return $page;
  }
}

?>
