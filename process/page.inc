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

  // Empty out tabs if none exist
  if(empty($vars['tabs']['#primary']) && empty($vars['tabs']['#secondary'])){
    $vars['tabs'] = '';
  }
}
