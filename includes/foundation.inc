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
    $file = file_get_contents(dirname(dirname(__FILE__)) . '/assets/foundation/scss/foundation.scss');
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
  $components = !isset($files) ? fett_get_setting('css_foundation') : array();

  if(isset($name) && module_exists('sonar')){
    $components[] = $name;
  }
  if(!empty($components)){
    $options = array(
      'every_page' => TRUE,
      'weight' => -1000
    );
    if(module_exists('sonar')){
      $files["$path_fett/assets/foundation/scss/normalize.scss"] = $options;
      if($theme_key !== 'fett'){
        // Add theme-specific Foundation settings override file.
        $path_current = drupal_get_path('theme', $theme_key);
        $files["$path_fett/assets/foundation/scss/foundation/_functions.scss"] = $options;
        $files["$path_current/assets/scss/libraries/_settings.scss"] = $options;
      }
      foreach($components as $name){
        $files["$path_fett/assets/foundation/scss/foundation/components/_$name.scss"] = $options;
      }
    }
    else{
      foreach($components as $name){
        $files["$path_fett/assets/foundation/css/$name.css"] = $options;
      }
    }
  }
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
  $base = dirname(dirname(__FILE__)) . '/assets/foundation/js/foundation';
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
    $files["$path_fett/assets/foundation/js/foundation/foundation.js"] = $options;
    foreach($components as $name){
      $files["$path_fett/assets/foundation/js/foundation/foundation.$name.js"] = $options;
    }
    $files['inline'] = $options + array(
      'type'   => 'inline',
      'data'   => '(function ($, Drupal, window, document, undefined) { $(document).foundation(); })(jQuery, Drupal, this, this.document);',
      'weight' => 1000,
    );
  }
  return $files ? $files : array();
}
