<?php

/**
 * Include Foundation CSS/SCSS components
 */
function fett_foundation_add_css(){
  global $theme_key;
  $sonar_enabled = module_exists('sonar');
  $scss = theme_get_setting('fett_foundation_scss');
  $options = array(
    'every_page' => TRUE,
    'weight' => -1000
  );

  drupal_add_css();

  if(@is_array($scss) && $sonar_enabled){
    $fett_path = drupal_get_path('theme', 'fett');
    $current_path = drupal_get_path('theme', $theme_key);
    $path = $fett_path . '/assets/foundation/scss';
    $override = $current_path . '/assets/scss/override';

    // Add normalize no matter what
    drupal_add_css($path . '/normalize.scss', $options);

    if(theme_get_setting('fett_foundation_settings')){
      // Add custom Foundation SCSS settings file.
      drupal_add_css($fett_path . '/assets/foundation/scss/foundation/_functions.scss', $options);
      drupal_add_css($current_path . '/assets/scss/libraries/_settings.scss', $options);
    }

    $path .= '/foundation/components';

    foreach($scss as $s){
      if(empty($s)) continue;
      $use_path = $path;
      // Allow local overriding of Foundation files
      if(file_exists($override.'/_'.$s.'.scss')){
        $use_path = $override;
      }
      drupal_add_css($use_path.'/_'.$s.'.scss', $options);
    }

    // Add theme css no matter what
    drupal_add_css($fett_path . '/assets/scss/theme.scss', $options);
  }
  // We have not selected any SCSS components to include OR Sonar is not
  // enabled. In this case we just use default compiled Foundation.
  else{
    $path = drupal_get_path('theme', 'fett').'/assets/foundation/css';

    // Add normalize no matter what
    drupal_add_css($path . '/normalize.css', $options);

    drupal_add_css($path . '/foundation.min.css', $options);
  }
}

/**
 * Modules and other themes can call this function to supress all Foundation
 * javascript from loading.
 */
function fett_foundation_js_suppress($set = TRUE) {
  static $suppress = FALSE;
  // drupal_add_js() must only be invoked once.
  if (!empty($set) && $suppress === FALSE) {
    $suppress = TRUE;
  }
  return $suppress;
}

/**
 * Include Foundation SCSS components
 *
 * @param  $js
 *   Can be a string or an array of strings. Should be called without this
 *   variable to return all js files.
 *   IE: array('foundation.reveal.js','foundation.topbar.js')
 */
function fett_foundation_add_js($js = NULL){
  $js_files = &drupal_static(__FUNCTION__);
  if(!fett_foundation_js_suppress(FALSE)){
    if($js){
      // Set a js file for loading later.
      if(!is_array($js)){
        $js = array($js);
      }
      $js_files = isset($js_files) ? $js_files : array();
      $js_files += drupal_map_assoc($js);
    }
    else{
      $js = isset($js_files) ? $js_files : array();
      // Load in all set Foundation js files.
      $js += theme_get_setting('fett_foundation_js');
      if(@is_array($js)){
        $path_fett = drupal_get_path('theme', 'fett');
        $path = drupal_get_path('theme', 'fett').'/assets/foundation/js/foundation';
        $options = array(
          'every_page' => TRUE,
          'scope' => 'footer'
        );
        drupal_add_js($path.'/foundation.js', $options + array('weight' => -1));
        foreach($js as $s){
          if(!empty($s)){
            drupal_add_js($path.'/'.$s, $options);
          }
        }
        // Initialize Foundation
        drupal_add_js('(function ($, Drupal, window, document, undefined) { $(document).foundation(); })(jQuery, Drupal, this, this.document);',
          array('type' => 'inline', 'scope' => 'footer', 'weight' => 1000)
        );
      }
    }
  }
}

/**
 * Returns a list of Foundation SCSS components
 */
function fett_foundation_get_scss($options = FALSE) {
  $file = file_get_contents(dirname(dirname(__FILE__)) . '/assets/foundation/scss/foundation.scss');
  preg_match_all("/components\/(.*)?\"/",$file,$matches, PREG_PATTERN_ORDER);
  $names = array();
  if(!empty($matches[1]) && is_array($matches[1])){
    foreach($matches[1] as $match){
      $names[$match] = ucwords(str_replace('-',' ',$match));
    }
  }
  return $names;
}

/**
 * Returns a list of Foundation javascript components
 */
function fett_foundation_get_js($options = FALSE) {
  $base = dirname(dirname(__FILE__)) . '/assets/foundation/js/foundation';
  $files = array_diff(scandir($base), array('.', '..'));
  $names = array();
  if(is_array($files)){
    $key = array_search('foundation.js', $files);
    unset($files[$key]);
    foreach($files as $file){
      $names[$file] = ucwords(preg_replace('/(foundation\.)?(.*)(\.js)/', '$2', $file));
    }
  }
  return $names;
}
