<?php

/**
 * Implements hook_form_alter().
 */
function fett_form_alter(&$form, &$form_state, $form_id){
  $alters = &drupal_static(__FUNCTION__, array());
  if(empty($alters)){
    $alters = array_flip(_fett_theme_info('form_alter', array()));
  }
  if(isset($alters[$form_id])){
    _fett_include($form_id, 'form');
    $function = "form_{$form_id}_alter";
    $function($form, $form_state);
  }
}

/**
 * Implements theme_form_element().
 */
function fett_form_element($vars) {
  $element = &$vars['element'];

  // This function is invoked as theme wrapper, but the rendered form element
  // may not necessarily have been processed by form_builder().
  $element += array(
    '#title_display' => 'before',
  );

  // Add element #id for #type 'item'.
  if (isset($element['#markup']) && !empty($element['#id'])) {
    $attributes['id'] = $element['#id'];
  }
  // Add element's #type and #name as class to aid with JS/CSS selectors.
  $attributes['class'] = array('form-item');
  if (!empty($element['#type'])) {
    $attributes['class'][] = strtr($element['#type'], '_', '-');
  }
  if (!empty($element['#field_name'])) {
    $attributes['class'][] = strtr($element['#field_name'], '_', '-');
  }
  if (!empty($element['#delta'])) {
    $attributes['class'][] = 'item-' . $element['#delta'];
  }
  // Add a class for disabled elements to facilitate cross-browser styling.
  if (!empty($element['#attributes']['disabled'])) {
    $attributes['class'][] = 'form-disabled';
  }
  $output = '<div' . drupal_attributes($attributes) . '>' . "\n";

  // If #title is not set, we don't display any label or required marker.
  if (!isset($element['#title'])) {
    $element['#title_display'] = 'none';
  }
  $prefix = isset($element['#field_prefix']) ? '<span class="field-prefix">' . $element['#field_prefix'] . '</span> ' : '';
  $suffix = isset($element['#field_suffix']) ? ' <span class="field-suffix">' . $element['#field_suffix'] . '</span>' : '';

  switch ($element['#title_display']) {
    case 'before':
    case 'invisible':
      $output .= ' ' . theme('form_element_label', $vars);
      $output .= ' ' . $prefix . $element['#children'] . $suffix . "\n";
      break;

    case 'after':
      $output .= ' ' . $prefix . $element['#children'] . $suffix;
      $output .= ' ' . theme('form_element_label', $vars) . "\n";
      break;

    case 'none':
    case 'attribute':
      // Output no label and no required marker, only the children.
      $output .= ' ' . $prefix . $element['#children'] . $suffix . "\n";
      break;
  }

  if (!empty($element['#description'])) {
    $output .= '<div class="description">' . $element['#description'] . "</div>\n";
  }

  $output .= "</div>\n";

  return $output;
}

/**
 * Implements theme_form_element_label().
 */
function fett_form_element_label($vars) {
  $element = $vars['element'];

  // If title and required marker are both empty, output no label.
  if ((!isset($element['#title']) || $element['#title'] === '') && empty($element['#required'])) {
    return '';
  }

  // If the element is required, a required marker is appended to the label.
  $required = !empty($element['#required']) ? theme('form_required_marker', array('element' => $element)) : '';

  $title = filter_xss_admin($element['#title']);

  // if (fett_get_setting('tooltip_form') && !empty($element['#description'])) {
  //   $tip_id = strtr($element['#name'], array(' ' => '-', '_' => '-', '[' => '-', ']' => '')) . '-help';
  //   fett_tooltip_add('#' . $tip_id, $element['#description'], array('maxWidth' => 400, 'position' => 'right'));
  //   $title .= ' <i id="'.$tip_id.'" class="fa fa-info-circle help">' . "</i>\n";
  // }

  $attributes = array();
  // Style the label as class option to display inline with the element.
  if ($element['#title_display'] == 'after') {
    $attributes['class'] = 'option';
  }
  // Show label only to screen readers to avoid disruption in visual flows.
  elseif ($element['#title_display'] == 'invisible') {
    $attributes['class'] = 'element-invisible';
  }

  if (!empty($element['#id'])) {
    $attributes['for'] = $element['#id'];
  }

  // The leading whitespace helps visually separate fields from inline labels.
  return ' <label' . drupal_attributes($attributes) . '>' . t('!title !required', array('!title' => $title, '!required' => $required)) . "</label>\n";
}

/**
 * Returns HTML to wrap child elements in a container.
 *
 * Used for grouped form items. Can also be used as a #theme_wrapper for any
 * renderable element, to surround it with a <div> and add attributes such as
 * classes or an HTML id.
 *
 * @param $variables
 *   An associative array containing:
 *   - element: An associative array containing the properties of the element.
 *     Properties used: #id, #attributes, #children.
 *
 * @ingroup themeable
 */
// function fett_container($variables) {
//   $element = $variables['element'];
//   // Ensure #attributes is set.
//   $element += array('#attributes' => array());

//   // Special handling for form elements.
//   if (isset($element['#array_parents'])) {
//     // Assign an html ID.
//     if (!isset($element['#attributes']['id'])) {
//       $element['#attributes']['id'] = $element['#id'];
//     }
//     $element['#attributes'] = array();
//     // Add the 'form-wrapper' class.
//     $element['#attributes']['class'][] = 'form';
//     $element['#attributes']['class'][] = 'wrapper';
//   }

//   return '<div' . drupal_attributes($element['#attributes']) . '>' . $element['#children'] . '</div>';
// }

/**
 * Returns HTML for a button form element.
 */
function fett_button($vars) {
  $element = $vars['element'];
  $label = $element['#value'];
  element_set_attributes($element, array('id', 'name', 'value', 'type'));

  $element['#attributes']['class'][] = 'form-' . $element['#button_type'];
  $element['#attributes']['class'][] = 'button';
  if (!empty($element['#attributes']['disabled'])) {
    $element['#attributes']['class'][] = 'form-button-disabled';
  }

  // Prepare input whitelist - added to ensure ajax functions don't break
  $whitelist = _fett_element_whitelist();

  // Upload progress skip.
  if(isset($element['#ajax']['progress']['type']) && $element['#ajax']['progress']['type'] === 'bar'){
    $whitelist[] = $element['#id'];
  }

  if (isset($element['#id']) && in_array($element['#id'], $whitelist)) {
    return '<input' . drupal_attributes($element['#attributes']) . ">\n"; // This line break adds inherent margin between multiple buttons
  }
  else {
    return '<button' . drupal_attributes($element['#attributes']) . '>'. $label ."</button>\n"; // This line break adds inherent margin between multiple buttons
  }
}

/**
 * Returns an array containing ids of any whitelisted drupal elements
 */
function _fett_element_whitelist() {
/**
 * Why whitelist an element?
 * The reason is to provide a list of elements we wish to exclude
 * from certain modifications made by the Fett theme which
 * break core functionality - e.g. ajax.
 */
  $whitelist = array(
    'edit-refresh',
    'edit-pass-pass1',
    'edit-pass-pass2',
    'panels-ipe-cancel',
    'panels-ipe-customize-page',
    'panels-ipe-save',
    'panelizer-save-default',
    'panelizer-ipe-revert',
  );

  // Allow other modules and themes to alter return value.
  drupal_alter('fett_element_whitelist', $whitelist);

  return $whitelist;
}
