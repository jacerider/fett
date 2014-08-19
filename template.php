<?php

$files = array(
  'tools.inc',
  'form.inc',
  'js.inc',
  'css.inc',
  'foundation.inc',
  'theme.inc',
);

if(module_exists('ds')){
  $files[] = 'ds.inc';
}

function _fett_load($files) {
  $tp = drupal_get_path('theme', 'fett');
  $file = '';
  $dir = dirname(__FILE__);

  // Check file path and '.inc' extension
  foreach($files as $file) {
    $file_path = $dir . '/inc/' . $file;
    if (strpos($file,'.inc') > 0 && file_exists($file_path)) {
      require_once($file_path);
    }
  }
}

_fett_load($files);

// Add Foundation SCSS assets
// We do this here as styles defined in the .info file will always be loaded.
// We need our files to always be loaded.
fett_foundation_add_css();

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

  // Remove image toolbar in IE.
  $head_elements['ie_image_toolbar'] = array(
    '#type' => 'html_tag',
    '#tag' => 'meta',
    '#attributes' => array(
      'http-equiv' => 'ImageToolbar',
      'content' => 'false',
    ),
  );
}

/**
 * Implements hook_preprocess().
 */
function fett_preprocess(&$vars, $hook) {
  $dir = dirname(__FILE__);
  $hook_path = $dir . '/preprocess/' . $hook . '.inc';
  if(file_exists($hook_path)){
    require_once($hook_path);
    $hook_function = '_fett_preprocess_' . $hook;
    if(function_exists($hook_function)){
      $hook_function($vars);
    }
  }
}

/**
 * Implements template_preprocess_field().
 */
function fett_preprocess_field(&$vars) {
  fett_preprocess($vars, 'field');
}

/**
 * Implements hook_process_html_tag()
 *
 * Prunes HTML tags: http://sonspring.com/journal/html5-in-drupal-7#_pruning
 */
function fett_process_html_tag(&$vars) {
  if (theme_get_setting('fett_html_tags')) {
    $el = &$vars['element'];

    // Remove type="..." and CDATA prefix/suffix.
    unset($el['#attributes']['type'], $el['#value_prefix'], $el['#value_suffix']);

    // Remove media="all" but leave others unaffected.
    if (isset($el['#attributes']['media']) && $el['#attributes']['media'] === 'all') {
      unset($el['#attributes']['media']);
    }
  }
}

/**
 * Implements hook_theme_registry_alter().
 */
function fett_theme_registry_alter(&$theme_registry) {
  if(module_exists('ds')){
    _fett_ds_theme_registry_alter($theme_registry);
  }
}

/**
 * Implements hook_element_info_alter().
 */
function fett_element_info_alter(&$type) {
  if(isset($type['managed_file'])){
    $type['managed_file']['#attached']['js'][] = drupal_get_path('theme','fett') . '/assets/js/fett.upload.js';
  }
}
