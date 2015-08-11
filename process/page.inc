<?php

function _fett_process_page(&$vars){

  if($offcanvas = fett_offcanvas_get()){
    $path_fett = drupal_get_path('theme', 'fett');
    $vars['page']['content']['#attached']['css']["$path_fett/assets/scss/_offcanvas.scss"] = array(
      'weight' => -100,
      'group' => CSS_THEME,
    );
    $vars['page']['content']['#attached']['js'][] = "$path_fett/assets/js/fett.offcanvas.js";
    $vars['classes_array'][] = 'oc-wrapper';
    $vars['page_prefix']['offcanvas_block'] = array(
      '#markup' => render($offcanvas[0]),
      '#weight' => -1000
    );
    $vars['page_prefix']['offcanvas'] = array(
      '#markup' => '<div class="oc-push">' . render($offcanvas[1]) . '<div class="oc-content"><div class="oc-content-inner">',
      '#weight' => -999
    );
    $vars['page_suffix']['offcanvas'] = array(
      '#markup' => '</div></div></div>',
      '#weight' => 999
    );
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

  // Add Foundation CSS/SCSS
  foreach(fett_foundation_css() as $file => $options){
    $vars['page']['content']['#attached']['css'][$file] = $options;
  }

  // Add Foundation JS
  foreach(fett_foundation_js() as $file => $options){
    $vars['page']['content']['#attached']['js'][$file] = $options;
  }
}
