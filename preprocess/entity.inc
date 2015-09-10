<?php

/**
 * @file
 * Preprocess theme_page.
 */

function fett_preprocess_entity(&$vars){
  $entity = $vars[$vars['entity_type']];

  // Only add necessary classes.
  if($vars['entity_type'] !== 'asset'){
    $vars['classes_array'] = array_filter($vars['classes_array'], function($class) {
      return $class == 'contextual-links-region';
    });
    $vars['classes_array'][] = 'entity';
    $vars['classes_array'][] = $vars['entity_type'];
    $vars['classes_array'][] = $vars['view_mode'];
  }
}
