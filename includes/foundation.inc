<?php

/**
 * Return an array containing all available Foundation CSS/SCSS files.
 *
 * @return [array]
 *   An array of display friendly labels keyed by their file id.
 */
function fett_foundation_css_components(){
  $files = array();
  if(module_exists('sonar')){
    $file = file_get_contents(dirname(dirname(__FILE__)) . '/libraries/foundation/scss/foundation.scss');
    preg_match_all("/components\/(.*)?';/",$file,$matches, PREG_PATTERN_ORDER);
    if(!empty($matches[1])){
      foreach($matches[1] as $name){
        $files[$name] = ucwords(str_replace('-',' ',$name));
      }
    }
  }
  else{
    $files['normalize'] = 'Normalize';
    $files['foundation.min'] = 'Foundation';
  }
  return $files;
}

/**
 * Return an array containing all active Foundation CSS/SCSS files.
 *
 * @param $name
 *   (optional) The name of the Foundation SCSS component to add. Ignored if
 *   Sonar is not enabled.
 *
 * @return [array]
 *   An array of file paths to the active Foundation CSS/SCSS files.
 */
function fett_foundation_css($name = NULL){
  global $theme_key;
  $files = &drupal_static(__FUNCTION__);
  $path_fett = drupal_get_path('theme', 'fett');

  // Get theme-enabled css files. Only do this the first time this function is
  // called as the results are cached.
  $components = !isset($files) ? fett_get_setting('css_foundation', NULL, array()) : array();

  if(isset($name) && module_exists('sonar')){
    $components[] = $name;
  }
  // if(!empty($components)){
    $options = array(
      'every_page' => TRUE,
      'group' => CSS_DEFAULT,
      'weight' => -100,
    );
    $options_init = array(
      'group' => CSS_SYSTEM,
    );
    if(module_exists('sonar')){
      $files["$path_fett/libraries/foundation/scss/normalize.scss"] = $options_init + $options;
      $files["$path_fett/libraries/foundation/scss/foundation/_functions.scss"] = $options_init + $options;
      if($theme_key !== 'fett'){
        $theme_info = _fett_theme_info_trail($theme_key);
        foreach($theme_info as $theme_tree_key => $theme_tree_info){
          if($theme_tree_key !== 'fett'){
            // Add theme-specific Foundation settings override file.
            $path_current = drupal_get_path('theme', $theme_tree_key);
            // Load Foundation settings file AFTER scripts with a -100 weight.
            // (_variables & _mixins when in a child theme)
            $files["$path_current/assets/scss/libraries/_foundation.scss"] = array('weight' => -99) + $options_init + $options;
          }
        }
      }
      // We want global to load in CSS_SYSTEM so it loads with all libraries but we want it to load at the very end.
      $files["$path_fett/libraries/foundation/scss/foundation/components/_global.scss"] = array('weight' => -98) + $options_init + $options;
      foreach($components as $name){
        $files["$path_fett/libraries/foundation/scss/foundation/components/_$name.scss"] = $options;
      }
    }
    else{
      foreach($components as $name){
        $files["$path_fett/libraries/foundation/css/$name.css"] = $options;
      }
    }
  // }
  return $files ? $files : array();
}

/**
 * Return all valid Foundation JS files.
 *
 * @return [array]
 *   An array of display friendly labels keyed by their file id.
 */
function fett_foundation_js_components(){
  $files = array();
  $base = dirname(dirname(__FILE__)) . '/libraries/foundation/js/foundation';
  $match = array_diff(scandir($base), array('.', '..'));
  foreach($match as $file){
    if($file !== 'foundation.js'){
      $name = preg_replace('/(foundation\.)?(.*)(\.js)/', '$2', $file);
      $files[$name] = ucwords($name);
    }
  }
  return $files;
}

/**
 * Return an array containing all active Foundation JS files.
 *
 * @param $name
 *   (optional) The name of the Foundation SCSS component to add. Ignored if
 *   Sonar is not enabled.
 *
 * @return [array]
 *   An array of file paths to the active Foundation JS files.
 */
function fett_foundation_js($name = NULL){
  $files = &drupal_static(__FUNCTION__);
  $path_fett = drupal_get_path('theme', 'fett');

  // Get theme-enabled css files. Only do this the first time this function is
  // called as the results are cached.
  $components = !isset($files) ? fett_get_setting('js_foundation') : array();

  if(isset($name)){
    $components[] = $name;
  }

  if(!empty($components)){
    $options = array(
      'every_page' => TRUE,
      'scope'      => 'footer'
    );
    $files["$path_fett/libraries/foundation/js/foundation/foundation.js"] = $options;
    foreach($components as $name){
      $files["$path_fett/libraries/foundation/js/foundation/foundation.$name.js"] = $options;
    }
    $files['inline'] = $options + array(
      'type'   => 'inline',
      'data'   => '(function ($, Drupal, window, document, undefined) { $(document).foundation(); })(jQuery, Drupal, this, this.document);',
      'weight' => 1000,
    );
  }
  return $files ? $files : array();
}

function fett_sonar_var(){
  // We need these variables to load just BEFORE _global.scss.
  return array(
    'include-html-classes' => array(
      'value' => FALSE,
      'every_page' => FALSE,
      'group' => CSS_SYSTEM,
      'weight' => 901,
    ),
    'include-html-global-classes' => array(
      'value' => FALSE,
      'every_page' => FALSE,
      'group' => CSS_SYSTEM,
      'weight' => 901,
    ),
    'include-js-meta-styles' => array(
      'value' => FALSE,
      'every_page' => FALSE,
      'group' => CSS_SYSTEM,
      'weight' => 901,
    ),
  );
}
