<?php

// Global Includes
_fett_include(_fett_theme_info('include_global', array()), 'includes');

// Variable Includes
_fett_include(_fett_theme_info('include_var', array()), 'includes', TRUE);

// Preprocess Includes
_fett_include(_fett_theme_info('include_preprocess', array()), 'preprocess');

// Process Includes
_fett_include(_fett_theme_info('include_process', array()), 'process');

// Load in theme defaults if needed.
_fett_defaults();

/*
 * Implements hook_preprocess_HOOK().
 */
function fett_preprocess_username(&$vars) {
  global $language;
  // Make sure this validates
  $vars['attributes_array']['lang'] = $vars['attributes_array']['xml:lang'];
}

/**
 * Implements hook_html_head_alter().
 */
function fett_html_head_alter(&$head_elements) {
  // HTML5 charset declaration.
  $head_elements['system_meta_content_type']['#attributes'] = array(
    'charset' => 'utf-8',
  );

  // Optimize mobile viewport.
  $head_elements['mobile_viewport'] = array(
    '#type' => 'html_tag',
    '#tag' => 'meta',
    '#attributes' => array(
      'name' => 'viewport',
      'content' => 'width=device-width, initial-scale=1.0',
    ),
  );
}

/**
 * Implements hook_library().
 */
function fett_library(){
  $path_fett = drupal_get_path('theme', 'fett');
  $libraries['fett.position'] = array(
    'title' => 'Position',
    'website' => 'https://github.com/jacerider/fett',
    'version' => '7.x-3.x-dev',
    'js' => array(
      "$path_fett/assets/js/fett.position.js" => array(
        'every_page' => TRUE,
        'group' => JS_LIBRARY,
        'weight' => 5,
      ),
    ),
  );
  $libraries['fett.fixed'] = array(
    'title' => 'Fixed Header',
    'website' => 'https://github.com/jacerider/fett',
    'version' => '7.x-3.x-dev',
    'js' => array(
      "$path_fett/assets/js/fett.fixed.js" => array(
        'every_page' => TRUE,
        'group' => JS_LIBRARY,
        'weight' => 10,
      ),
    ),
    'css' => array(
      "$path_fett/assets/scss/_fixed.scss" => array(
        'type' => 'file',
        'media' => 'screen',
        'every_page' => TRUE,
        'group' => CSS_DEFAULT,
      ),
    ),
    'dependencies' => array(
      array('fett', 'fett.position'),
    ),
  );
  $libraries['fett.tooltips'] = array(
    'title' => 'Tooltipster',
    'website' => 'http://iamceege.github.io/tooltipster/',
    'version' => '3.3.0',
    'js' => array(
      "$path_fett/libraries/tooltipster/js/jquery.tooltipster.min.js" => array(),
      "$path_fett/assets/js/fett.tooltip.js" => array(),
    ),
    'css' => array(
      "$path_fett/libraries/tooltipster/css/tooltipster.css" => array(
        'type' => 'file',
        'media' => 'screen',
        'group' => CSS_DEFAULT,
      ),
      "$path_fett/assets/scss/_tooltip.scss" => array(
        'type' => 'file',
        'media' => 'screen',
        'group' => CSS_DEFAULT,
      ),
    ),
  );
  $libraries['fett.form'] = array(
    'title' => 'Fett Form Utilities',
    'website' => 'https://github.com/jacerider/fett',
    'version' => '7.x-3.x-dev',
    'js' => array(
      "$path_fett/assets/js/fett.form.js" => array(),
    ),
    'css' => array(
      "$path_fett/assets/scss/_forms-fett.scss" => array(
        'type' => 'file',
        'media' => 'screen',
        'group' => CSS_DEFAULT,
      ),
    ),
  );
  return $libraries;
}

/**
 * Implements hook_element_info_alter().
 */
function fett_element_info_alter(&$type) {
  if(isset($type['managed_file'])){
    $type['managed_file']['#attached']['js'][] = drupal_get_path('theme','fett') . '/assets/js/fett.upload.js';
  }
}

/**
 * Implements hook_fawesome_icons().
 */
function fett_fawesome_icons(){
  return array(
    '^save' => array('icon' => 'save', 'attributes' => array('class' => array('primary'))),
  );
}

/**
 * Add CSS
 */
// function _fett_add_core_css(){
//   // Load in Foundation CSS
//   foreach(fett_foundation_css() as $file => $options){
//     drupal_add_css($file, $options);
//   }

//   // Add core CSS files.
//   if(module_exists('sonar')){
//     $path_fett = drupal_get_path('theme', 'fett');
//     foreach(array('mixins','core','contextual') as $scss){
//       drupal_add_css("$path_fett/assets/scss/_$scss.scss", array(
//         'group' => CSS_DEFAULT,
//         'every_page' => TRUE,
//       ));
//     }
//   }
// }

/**
 * Get Fett theme info.
 *
 * @param  $type
 *   The sub-type of info to retrieve.
 */
function _fett_theme_info($type = NULL, $default = NULL){
  global $theme_key;
  $themes = list_themes();
  $info = $themes['fett']->info;
  if($type){
    $info = isset($info[$type]) && !empty($info[$type]) ? $info[$type] : $default;
  }
  return $info;
}

/**
 * Get Fett trail theme info.
 *
 * @param  $type
 *   The sub-type of info to retrieve.
 */
function _fett_theme_info_all($type, $default = NULL){
  global $theme_key;
  $themes = _fett_theme_info_trail($theme_key);
  $info = array();
  foreach($themes as $theme_name => $theme){
    $info[$theme_name] = isset($theme['info'][$type]) && !empty($theme['info'][$type]) ? $theme['info'][$type] : $default;
  }
  return $info;
}

/**
 * Returns an array keyed by theme name.
 *
 * Return the all the info file data for a particular theme including base
 * themes. Parts of this function are shamelessly ripped from Drupal core's
 * _drupal_theme_initialize().
 *
 * @param $theme_name, usually the active theme.
 */
function _fett_theme_info_trail($theme_name) {
  $info_trail = &drupal_static(__FUNCTION__, array());
  if (empty($info_trail)) {
    $lt = list_themes();

    // First check for base themes and get info
    $base_theme = array();
    $ancestor = $theme_name;
    while ($ancestor && isset($lt[$ancestor]->base_theme)) {
      $ancestor = $lt[$ancestor]->base_theme;
      $base_theme[] = $lt[$ancestor];
    }
    foreach ($base_theme as $base) {
      $info_trail[$base->name]['info'] = $base->info;
    }

    // Now the active theme
    $info_trail[$theme_name]['info'] = $lt[$theme_name]->info;
  }

  return $info_trail;
}

/**
 * Include files found inside the include folder.
 */
function _fett_include($files, $directory, $is_setting = FALSE) {
  $tp = drupal_get_path('theme', 'fett');
  $file = '';
  $dir = dirname(__FILE__);

  if(!is_array($files)){
    $files = array($files);
  }

  // Check file path and '.inc' extension
  foreach($files as $file) {
    if($is_setting){
      if(!fett_get_setting($file)){
        continue;
      }
    }
    $file_path = $dir . "/$directory/" . $file . '.inc';
    require_once($file_path);
  }
}
