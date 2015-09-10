<?php

/**
 * @file
 * Preprocess theme_page.
 */

function fett_preprocess_node(&$vars){
  $node = $vars['node'];

  // Social sharing buttons
  if(fett_get_setting('share')){
    fett_share_preprocess_node($vars);
  }

  // Add view mode as a default suggestion.
  $vars['theme_hook_suggestions'][] = 'node__' . $vars['view_mode'];

  // Only add necessary classes.
  $vars['classes_array'] = array_filter($vars['classes_array'], function($class) {
    return $class == 'contextual-links-region';
  });
  $vars['classes_array'][] = 'node';
  $vars['classes_array'][] = $node->type;
  $vars['classes_array'][] = $vars['view_mode'];

  // Better submitted by information.
  if (variable_get('node_submitted_' . $node->type, TRUE)) {
    $vars['submitted'] = t('By !username on !datetime', array('!username' => $vars['name'], '!datetime' => format_date($node->created, 'short')));
  }
}
