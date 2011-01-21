<?php

include_once 'conf.php.inc';

define('LAYOUT_FRONT', 'layout_front');
define('LAYOUT_BACK', 'layout_back');
define('LAYOUT_EMBEDDED', 'layout_embedded');

class Layout {

  private $css = array('css/style.css');
  private $js = array('js/curvycorners.js', 'js/jquery-1.3.2.min.js', 'js/utils.js');
  private $content = '';
  private $menu = null;
  private $type = null;
  private $conf = null;

  public function __construct($type) {
    global $conf;
    $this->conf = $conf;
    $this->type = $type;
    
    $this->menu = array('Regions' => $this->conf->getWebroot().'/admin/regions.php',
                        'Colors' => $this->conf->getWebroot().'/admin/colors.php',
                        'Information' => $this->conf->getWebroot().'/admin/information.php',
                        'Logout' => $this->conf->getWebroot().'/admin/logout.php');
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

  public function addMenu(array $menu) {
    $this->menu = $menu;
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

  private function renderMenu() {
    $output = '<div id="menu">';
    if ($this->menu != null) {
      $output .= '<ul>';
      foreach ($this->menu as $text => $link) {
        $output .= '<li><a href="'.$link.'">'.$text.'</a></li>';
      }
      $output .= '</ul>';
    }
    $output .= "</div>";
    return $output;
  }

  private function build() {
    switch ($this->type) {

      case LAYOUT_BACK:
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
                   <div id="page">
                      '.$this->renderMenu().'
                    <div id="content">
                      '.$this->content.'
                    </div>
                   </div>
                 </body>
                 </html>';
         break;
      
      case LAYOUT_FRONT:
        $page = '<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd">
                 <html xmlns="http://www.w3.org/1999/xhtml">
                 <head>
                   <meta http-equiv="content-type" content="text/html; charset=utf-8"/>
                   <script type="text/javascript" src="http://www.google.com/jsapi?key='. $this->conf->gkey() .'"></script>
                   <script type="text/javascript" src="'. $this->conf->getWebroot() .'/js/tingmap.js"></script>
                   <script type="text/javascript" src="'. $this->conf->getWebroot() .'/js/jquery-1.3.2.min.js"></script>
                   <link href="'. $this->conf->getWebroot() .'/css/reset.css" rel="stylesheet" type="text/css"></link>
                   <link href="'. $this->conf->getWebroot() .'/css/front.css" rel="stylesheet" type="text/css"></link>
                   <title>
                     T!NG udbredelseskort
                   </title>
                 </head>
                 <body class="black">
                   <div id="menu">
                     <div id="menu-inner">
                       <ul>
                         <li class="active"><a href="/">Kort</a></li>
                         <li><a href="">T!NG Concept</a></li>
                         <li><a href="https://'.$_SERVER['SERVER_NAME'].'/admin">Login</a></li>
                       </ul>
                     </div>
                   </div>
                   <div id="wrapper" class="clearfix">
                     <div id="wrapper-inner">
                       <div id="ting_gmap" style="background-color:#eee;width:600px;height:650px;"></div>
                       <div id="population">
                         <table border="1">
                           <tr id="pop-total"><td class="none">Indbyggere</td><td class="num none"></td><td class="pro none"></td></tr>
                           <tr id="pop-selected"><td>T!NG partnere</td><td class="num"></td><td class="pro bold"></td></tr>
                           <tr id="pop-interested"><td>Interesserede</td><td class="num"></td><td class="pro"></td></tr>
                           <tr id="pop-not-interested"><td>Potentielle</td><td class="num"></td><td class="pro"></td></tr>
                         </table>
                       </div>
                     </div>
                   </div>
                   <div id="footer">
                     <div id="footer-inner">
                     </div>
                   </div>
                 </body>
                 </html>';
        break;

      case LAYOUT_EMBEDDED:
        $page = '<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd">
                 <html xmlns="http://www.w3.org/1999/xhtml" class="embedded">
                 <head>
                   <meta http-equiv="content-type" content="text/html; charset=utf-8"/>
                   <script type="text/javascript" src="http://www.google.com/jsapi?key='. $this->conf->gkey() .'"></script>
                   <script type="text/javascript" src="'. $this->conf->getWebroot() .'/js/tingmap.js"></script>
                   <script type="text/javascript" src="'. $this->conf->getWebroot() .'/js/jquery-1.3.2.min.js"></script>
                   <link href="'. $this->conf->getWebroot() .'/css/reset.css" rel="stylesheet" type="text/css"></link>
                   <link href="'. $this->conf->getWebroot() .'/css/front.css" rel="stylesheet" type="text/css"></link>
                   <title>
                     T!NG udbredelseskort
                   </title>
                 </head>
                 <body>
                   <div id="wrapper" class="clearfix">
                     <div id="wrapper-inner">
                       <div id="ting_gmap" style="background-color:#eee;width:600px;height:650px;"></div>
                       <div id="population">
                         <table border="1">
                           <tr id="pop-total"><td class="none">Indbyggere</td><td class="num none"></td><td class="pro none"></td></tr>
                           <tr id="pop-selected"><td>T!NG partnere</td><td class="num"></td><td class="pro bold"></td></tr>
                           <tr id="pop-interested"><td>Interesserede</td><td class="num"></td><td class="pro"></td></tr>
                           <tr id="pop-not-interested"><td>Potentielle</td><td class="num"></td><td class="pro"></td></tr>
                         </table>
                       </div>
                     </div>
                   </div>
                 </body>
                 </html>';
        break;
    }
    return $page;
  }
}

?>
