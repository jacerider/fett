<?php

/**
 * @file
 * Preprocess theme_html.
 */

function fett_preprocess_html(&$vars){
  global $theme_key, $language;
  $path = drupal_get_path('theme', $theme_key);
  $path_fett = drupal_get_path('theme', 'fett');

  // Clean up body classes.
  foreach($vars['classes_array'] as $key => &$name){
    if($name == 'page-node-'){
      unset($vars['classes_array'][$key]);
    }
    if($name == 'page-node'){
      unset($vars['classes_array'][$key]);
    }
    elseif(strpos($name, 'page-node-') !== FALSE){
      unset($vars['classes_array'][$key]);
    }
    elseif(strpos($name, 'node-type-') !== FALSE){
      $name = str_replace('node-type','page',$name);
      // unset($vars['classes_array'][$key]);
    }
  }

  // Use a proper attributes array for the html attributes.
  // You can add more attributes to the html elment, for example in a sub-theme you can do this:
  // $vars['html_attributes_array']['xmlns:og'][] = 'http://opengraphprotocol.org/schema/';
  $vars['html_attributes_array']['lang'][] = $language->language;
  $vars['html_attributes_array']['dir'][] = $language->dir;

  // Convert RDF Namespaces into structured data using drupal_attributes.
  $vars['rdf_namespaces'] = array();
  if (function_exists('rdf_get_namespaces')) {
    foreach (rdf_get_namespaces() as $prefix => $uri) {
      $prefixes[] = $prefix . ': ' . $uri;
    }
    $vars['rdf_namespaces_array']['prefix'] = implode(' ', $prefixes);
  }

  // Prevent tags from entering into head title
  $vars['head_title'] = strip_tags(htmlspecialchars_decode($vars['head_title']));

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
  $script .= '<script type="text/javascript" src="' . url($path_fett . '/libraries/rem/rem.min.js', array('absolute' => TRUE)) . '"></script>' . "\n";
  $script .= '<![endif]-->' . "\n";
  $vars['page']['page_bottom']['remjs'] = array(
    '#markup' => $script,
  );

  // Add Foundation CSS/SCSS
  foreach(fett_foundation_css() as $file => $options){
    // $element['#attached']['css'][$file] = $options;
    drupal_add_css($file, $options);
  }
  // Add Foundation JS
  foreach(fett_foundation_js() as $file => $options){
    $element['#attached']['js'][$file] = $options;
    drupal_add_js($file, $options);
  }
  // Add core CSS files.
  if(module_exists('sonar')){
    // Add Fett and children SCSS files to page.
    if($theme_key !== 'fett'){
      $theme_path = drupal_get_path('theme', $theme_key);
      $options = array(
        'every_page' => TRUE,
        'group' => CSS_SYSTEM,
        'weight' => -100,
      );
      drupal_add_css("$theme_path/assets/scss/libraries/_variables.scss", $options);
      drupal_add_css("$theme_path/assets/scss/libraries/_mixins.scss", $options);
    }
    foreach(_fett_theme_info_all('scss', array()) as $theme_key_id => $scss){
      $theme_path = drupal_get_path('theme', $theme_key_id);
      $options = array(
        'group' => $theme_key_id == 'fett' ? CSS_DEFAULT : CSS_THEME,
        'every_page' => TRUE,
        'weight' => -10,
      );
      foreach($scss as $file){
        drupal_add_css("$theme_path/$file", $options);
      }
    }
    // Add Fett module-dependant SCSS files to page.
    foreach(_fett_theme_info('scss_module', array()) as $module => $scss){
      if(module_exists($module)){
        $options = array(
          'group' => CSS_DEFAULT,
          'every_page' => TRUE,
          'weight' => -5,
        );
        drupal_add_css("$path_fett/$scss", $options);
      }
    }
  }
  // Fixed header.
  if(fett_get_setting('header_fixed')){
    drupal_add_library('fett','fett.fixed', true);
    drupal_add_js(array('fettFixed' =>
      array(
        'scroll' => fett_get_setting('header_scroll_up'),
      ),
    ), 'setting');
  }

  // Tooltips
  fett_tooltip_process();
}
