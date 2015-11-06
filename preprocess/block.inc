<?php

/**
 * @file
 * Preprocess theme_block.
 */

function fett_preprocess_block(&$vars){
  $block = $vars['block'];

  // Only add necessary classes.
  $vars['block_html_id'] = '';
  $vars['classes_array'] = array_filter($vars['classes_array'], function($class) {
    return $class == 'contextual-links-region';
  });
  $vars['classes_array'][] = 'block';
  if(isset($vars['elements']['#views_contextual_links_info']['views_ui']['view'])){
    $view = $vars['elements']['#views_contextual_links_info']['views_ui']['view'];
    $view_display_id = $vars['elements']['#views_contextual_links_info']['views_ui']['view_display_id'];
    $vars['classes_array'][] = drupal_html_class($view->name);
    $vars['classes_array'][] = drupal_html_class($view_display_id);
    if(!empty($view->use_ajax)){
      $vars['classes_array'][] = drupal_html_class('view-dom-id-' . $view->dom_id);
    }
  }
  else{
    $vars['classes_array'][] = drupal_html_class($block->module);
    $vars['classes_array'][] = drupal_html_class('id-' . $block->delta);
  }
}
