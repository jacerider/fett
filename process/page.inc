<?php

function fett_process_page(&$vars){

  // Offcanvas elements need to be processed during page processing so
  // additional elements can be added.
  if($offcanvas = fett_offcanvas_get()){
    $path_fett = drupal_get_path('theme', 'fett');
    $vars['page']['content']['#attached']['css']["$path_fett/assets/scss/_offcanvas.scss"] = array(
      'group' => CSS_DEFAULT,
    );
    $vars['page']['content']['#attached']['js']["$path_fett/assets/js/fett.offcanvas.js"] = array(
      'group' => JS_LIBRARY,
      'every_page' => TRUE,
    );
    $vars['classes_array'][] = 'oc-wrapper';
    $vars['page_prefix']['offcanvas_block'] = array(
      '#markup' => render($offcanvas[0]),
      '#weight' => -1000
    );
    // .window is used by fett.position.js and is the main scrollable
    // element.
    $vars['page_prefix']['offcanvas'] = array(
      '#markup' => '<div class="oc-push">' . render($offcanvas[1]) . '<div class="oc-content window"><div class="oc-content-inner">',
      '#weight' => -999
    );
    $vars['page_suffix']['offcanvas'] = array(
      '#markup' => '</div></div></div>',
      '#weight' => 999
    );
  }
  else{
    // .window is used by fett.position.js and is the main scrollable
    // element.
    $vars['classes_array'][] = 'window';
  }

  // Page prefix and suffix.
  $vars['page_prefix'] = empty($vars['page_prefix']) ? '' : $vars['page_prefix'];
  $vars['page_suffix'] = empty($vars['page_suffix']) ? '' : $vars['page_suffix'];

  // Page classes
  $vars['classes'] = empty($vars['classes_array']) ? '' : implode(' ', $vars['classes_array']);

  // Navigation
  $vars['main_nav'] = empty($vars['main_nav']) ? '' : $vars['main_nav'];
  $vars['secondary_nav'] = empty($vars['secondary_nav']) ? '' : $vars['secondary_nav'];

  // Flatten classes arrays
  $vars['content_classes'] = empty($vars['content_classes_array']) ? '' : implode(' ', $vars['content_classes_array']);
  $vars['sidebar_first_classes'] = empty($vars['sidebar_first_classes_array']) ? '' : implode(' ', $vars['sidebar_first_classes_array']);
  $vars['sidebar_second_classes'] = empty($vars['sidebar_second_classes_array']) ? '' : implode(' ', $vars['sidebar_second_classes_array']);

  // Run just before rendering
  $vars['page']['content']['#pre_render'][] = 'fett_process_page_pre_render';
  // Run just after rendering
  $vars['page']['content']['#post_render'][] = 'fett_process_page_post_render';

  // Empty out tabs if none exist
  if(empty($vars['tabs']['#primary']) && empty($vars['tabs']['#secondary'])){
    $vars['tabs'] = '';
  }
}

function fett_process_page_pre_render(&$element){
  global $theme_key;
  $path_fett = drupal_get_path('theme', 'fett');

  // Add Foundation CSS/SCSS
  foreach(fett_foundation_css() as $file => $options){
    $element['#attached']['css'][$file] = $options;
  }
  // Add Foundation JS
  foreach(fett_foundation_js() as $file => $options){
    $element['#attached']['js'][$file] = $options;
  }
  // Add core CSS files.
  if(module_exists('sonar')){
    // Add Fett and children SCSS files to page.
    if($theme_key !== 'fett'){
      $theme_path = drupal_get_path('theme', $theme_key);
      $element['#attached']['css']["$theme_path/assets/scss/libraries/_variables.scss"] = array(
        'every_page' => TRUE,
        'group' => CSS_SYSTEM,
        'weight' => -100,
      );
      $element['#attached']['css']["$theme_path/assets/scss/libraries/_mixins.scss"] = array(
        'every_page' => TRUE,
        'group' => CSS_SYSTEM,
        'weight' => -100,
      );
    }
    foreach(_fett_theme_info_all('scss', array()) as $theme_key_id => $scss){
      $theme_path = drupal_get_path('theme', $theme_key_id);
      foreach($scss as $file){
        $element['#attached']['css']["$theme_path/$file"] = array(
          'group' => $theme_key_id == 'fett' ? CSS_DEFAULT : CSS_THEME,
          'every_page' => TRUE,
          'weight' => -10,
        );
      }
    }
    // Add Fett module-dependant SCSS files to page.
    foreach(_fett_theme_info('scss_module', array()) as $module => $scss){
      if(module_exists($module)){
        $element['#attached']['css']["$path_fett/$scss"] = array(
          'group' => CSS_DEFAULT,
          'every_page' => TRUE,
          'weight' => -5,
        );
      }
    }
  }
  // Fixed header.
  if(fett_get_setting('header_fixed')){
    $element['#attached']['library'][] = array('fett','fett.fixed');
  }

  return $element;
}

function fett_process_page_post_render(&$element){
  return $element;
}
