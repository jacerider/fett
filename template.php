<?php

$include = array(
  'tools.inc',
  'css.inc',
  'js.inc',
  'foundation.inc',
  'theme.inc',
  'offcanvas.inc',
  'megamenu.inc',
);
_fett_includes($include);
_fett_defaults();

/**
 * Implements hook_preprocess().
 */
function fett_preprocess(&$vars, $hook) {
  if($function = fett_include('preprocess', $hook)){
    $function($vars);
  }
}

/**
 * Implements hook_process().
 */
function fett_process(&$vars, $hook) {
  if($function = fett_include('process', $hook)){
    $function($vars);
  }
}

/**
 * Implements hook_process_html_tag()
 *
 * Prunes HTML tags: http://sonspring.com/journal/html5-in-drupal-7#_pruning
 */
function fett_process_html_tag(&$vars) {
  $hook = 'html_tag';
  if($function = fett_include('process', $hook)){
    $function($vars);
  }
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
 * Load an include.
 */
function fett_include($type, $hook){
  $hooks = &drupal_static(__FUNCTION__);
  $key = "{$type}_{$hook}";
  if(!isset($hooks[$key])){
    $hooks[$key] = FALSE;
    $dir = dirname(__FILE__);
    $hook_path = "$dir/$type/$hook.inc";
    if(file_exists($hook_path)){
      require_once $hook_path;
    }
  }
  $hook_function = "_fett_{$type}_{$hook}";
  if(function_exists($hook_function)){
    $hooks[$key] = $hook_function;
  }
  return $hooks[$key];
}

/**
 * Include files found inside the include folder.
 */
function _fett_includes($files) {
  $tp = drupal_get_path('theme', 'fett');
  $file = '';
  $dir = dirname(__FILE__);

  // Check file path and '.inc' extension
  foreach($files as $file) {
    $file_path = $dir . '/includes/' . $file;
    require_once($file_path);
  }
}
