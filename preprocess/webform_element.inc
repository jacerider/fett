<?php

/**
 * @file
 * Preprocess theme_webform_element.
 */

function fett_preprocess_webform_element(&$vars){
  $element = &$vars['element'];
  $component = $element['#webform_component'];

  if($component['type'] == 'multifile'){
    drupal_add_js(drupal_get_path('theme','fett') . '/assets/js/fett.upload.multifile.js');
  }
}
