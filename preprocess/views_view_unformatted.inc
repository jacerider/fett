<?php

/**
 * @file
 * Preprocess theme_views_view_unformatted.
 */

function fett_preprocess_views_view_unformatted(&$vars){
  $view = $vars['view'];
  $vars['wrap_content'] = FALSE;

  foreach($vars['classes_array'] as &$classes){
    $classes = '';
    if(!empty($view->style_options['row_class'])){
      $vars['wrap_content'] = TRUE;
      $classes = drupal_html_class($view->style_options['row_class']);
    }
  }
}
