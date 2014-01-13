<?php

function _fett_preprocess_node(&$vars){

  // Add node--node_type--view_mode.tpl.php suggestions.
  $vars['theme_hook_suggestions'][] = 'node__' . $vars['type'] . '__' . $vars['view_mode'];

  // Add node--view_mode.tpl.php suggestions.
  $vars['theme_hook_suggestions'][] = 'node__' . $vars['view_mode'];

  // Add a class for the view mode.
  if (!$vars['teaser']) {
    $vars['classes_array'][] = 'view-mode-' . $vars['view_mode'];
  }

  $vars['title_attributes_array']['class'][] = 'node-title';
}
