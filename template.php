<?php

$include = array(
  'tools',
  'css',
  'js',
  'foundation',
  'theme',
  'offcanvas',
  'megamenu',
);
_fett_includes($include, 'includes');

$preprocess = array(
  'field',
  'html',
  'page',
  'views_view',
  'views_view_unformatted'
);
_fett_includes($preprocess, 'preprocess');

$preprocess = array(
  'html',
  'html_tag',
  'page'
);
_fett_includes($preprocess, 'process');

// Load in theme defaults if needed.
_fett_defaults();

// Load in all core CSS. We do this here so that these files get loaded
// no matter how the request is processed.
_fett_add_core_css();

// /**
//  * Implements hook_preprocess().
//  */
// function fett_preprocess(&$vars, $hook) {
//   if($function = fett_include('preprocess', $hook)){
//     $function($vars);
//   }
// }

/**
 * Implements hook_process().
 */
// function fett_process(&$vars, $hook) {
//   if($function = fett_include('process', $hook)){
//     $function($vars);
//   }
// }

/**
 * Implements hook_preprocess_field()
 */
// function fett_preprocess_field(&$vars) {
//   $hook = 'field';
//   if($function = fett_include('preprocess', $hook, TRUE)){
//     $function($vars);
//   }
// }

/**
 * Implements hook_process_html_tag()
 *
 * Prunes HTML tags: http://sonspring.com/journal/html5-in-drupal-7#_pruning
 */
// function fett_process_html_tag(&$vars) {
//   $hook = 'html_tag';
//   if($function = fett_include('process', $hook, TRUE)){
//     $function($vars);
//   }
// }

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
function _fett_add_core_css(){
  // Load in Foundation CSS
  foreach(fett_foundation_css() as $file => $options){
    drupal_add_css($file, $options);
  }

  // Add core CSS files.
  if(module_exists('sonar')){
    $path_fett = drupal_get_path('theme', 'fett');
    foreach(array('mixins','core','contextual') as $scss){
      drupal_add_css("$path_fett/assets/scss/_$scss.scss", array(
        'group' => CSS_DEFAULT,
        'every_page' => TRUE,
      ));
    }
  }
}

/**
 * Include files found inside the include folder.
 */
function _fett_includes($files, $directory) {
  $tp = drupal_get_path('theme', 'fett');
  $file = '';
  $dir = dirname(__FILE__);

  // Check file path and '.inc' extension
  foreach($files as $file) {
    $file_path = $dir . "/$directory/" . $file . '.inc';
    require_once($file_path);
  }
}
