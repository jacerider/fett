<?php

/**
 * @file
 * Preprocess theme_field.
 */

function fett_preprocess_field(&$vars){
  $vars['no_colon'] = false;
  $vars['content_wrap'] = false;
  $vars['content_wrap_element'] = 'div';
  $vars['content_attributes_array']['class'][] = 'items';

  $vars['classes_array'] = array();
  $vars['classes_array'][] = 'field';
  if(isset($vars['element']['#field_name'])){
    $vars['classes_array'][] = drupal_html_class(str_replace('field_', '', $vars['element']['#field_name']));
    if(isset($vars['element']['#label_display']) && $vars['element']['#label_display'] == 'inline'){
      $vars['classes_array'][] = 'inline';
    }
  }
  $vars['title_attributes_array']['class'][] = 'title';
}

/**
 * Registration module field support.
 */
function fett_preprocess_registration_property_field(&$vars){
  fett_preprocess_field($vars);
  $vars['classes'] = empty($vars['classes_array']) ? '' : implode(' ', $vars['classes_array']);
  $vars['title_attributes'] = empty($vars['title_attributes_array']) ? '' : drupal_attributes($vars['title_attributes_array']);
}
