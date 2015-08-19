<?php

/**
 * @file
 * Preprocess theme_views_view_unformatted.
 */

function fett_preprocess_views_view_unformatted(&$vars){
  $view = $vars['view'];
  $vars['wrap_content'] = !empty($vars['title']);

  foreach($vars['classes_array'] as &$classes){
    $classes = '';
    if(!empty($view->style_options['row_class'])){
      $vars['wrap_content'] = TRUE;
      $classes = drupal_clean_css_identifier($view->style_options['row_class']);
    }
  }
}
