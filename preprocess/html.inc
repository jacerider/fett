<?php

function _fett_preprocess_html(&$vars){
  global $base_url;
  global $theme_key;
  $path = drupal_get_path('theme', $theme_key);
  $path_fett = drupal_get_path('theme', 'fett');

  $vars['extra'] = '';

  // Add Modernizr
  $override = drupal_get_path('theme', $theme_key).'/assets/js/modernizr.min.js';
  if(file_exists($override)){
    drupal_add_js($override, array('every_page' => TRUE, 'group' => JS_LIBRARY));
  }
  else{
    // drupal_add_js('//cdnjs.cloudflare.com/ajax/libs/modernizr/2.7.1/modernizr.min.js', array('type' => 'external', 'every_page' => TRUE, 'group' => JS_LIBRARY));
    $script = "\n";
    $script .= '<script type="text/javascript" src="//cdnjs.cloudflare.com/ajax/libs/modernizr/2.7.1/modernizr.min.js"></script>' . "\n";
    $vars['extra'] .= $script;
  }

  // Add Foundation JS assets
  fett_foundation_add_js();

  // Touch icons
  $appletouchicon = '<link rel="apple-touch-icon" sizes="144x144" href="' . $base_url .'/'. $path . '/assets/images/apple-touch-icon-144x144.png">';
  //For iPhone with high-resolution Retina display
  $appletouchicon .= '<link rel="apple-touch-icon" sizes="114x114" href="' . $base_url .'/'. $path . '/assets/images/apple-touch-icon-114x114.png">'. "\n";
  //For first- and second-generation iPad:
  $appletouchicon .= '<link rel="apple-touch-icon" sizes="72x72" href="' . $base_url .'/'.  $path . '/assets/images/apple-touch-icon-72x72.png">' . "\n";
  //For non-Retina iPhone, iPod Touch, and Android 2.1+ devices
  $appletouchicon .= '<link rel="apple-touch-icon" href="' . $base_url .'/'.  $path . '/assets/images/apple-touch-icon.png">' . "\n";
  $vars['extra'] .= $appletouchicon;

  // nwmatcher
  $script = "\n";
  $script .= '<!--[if lt IE 9]>' . "\n";
  $script .= '<script type="text/javascript" src="//s3.amazonaws.com/nwapi/nwmatcher/nwmatcher-1.2.5-min.js"></script>' . "\n";
  $script .= '<![endif]-->' . "\n";
  $vars['page']['page_bottom']['nwmatcher'] = array(
    '#markup' => $script,
  );

  // selectiviizr
  $script = "\n";
  $script .= '<!--[if (gte IE 6)&(lte IE 8)]>' . "\n";
  $script .= '<script type="text/javascript" src="//cdnjs.cloudflare.com/ajax/libs/selectivizr/1.0.2/selectivizr-min.js"></script>' . "\n";
  $script .= '<![endif]-->' . "\n";
  $vars['page']['page_bottom']['selectivizr'] = array(
    '#markup' => $script,
  );

  // respondjs
  $script = "\n";
  $script .= '<!--[if lt IE 9]>' . "\n";
  $script .= '<script type="text/javascript" src="//cdnjs.cloudflare.com/ajax/libs/respond.js/1.1.0/respond.min.js"></script>' . "\n";
  $script .= '<![endif]-->' . "\n";
  $vars['page']['page_bottom']['respondjs'] = array(
    '#markup' => $script,
  );

  // rem.js
  $script = "\n";
  $script .= '<!--[if lt IE 9]>' . "\n";
  $script .= '<script type="text/javascript" src="' . url($path_fett . '/assets/js/rem.min.js') . '"></script>' . "\n";
  $script .= '<![endif]-->' . "\n";
  $vars['page']['page_bottom']['remjs'] = array(
    '#markup' => $script,
  );
}
