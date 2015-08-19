<?php

/**
 * @file
 * Preprocess theme_field.
 */

function fett_preprocess_field(&$vars){
  $vars['classes_array'] = array();
  $vars['classes_array'][] = 'field';
  $vars['classes_array'][] = drupal_clean_css_identifier(str_replace('field_', '', $vars['element']['#field_name']));
}
