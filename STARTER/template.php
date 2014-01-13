<?php

/**
 * Implements template_preprocess_html().
 *
 */
//function STARTER_preprocess_html(&$vars) {
//}


/**
 * Implements template_preprocess_page
 *
 */
//function STARTER_preprocess_page(&$vars) {
//}


/**
 * Implements template_preprocess_node
 *
 */
//function STARTER_preprocess_node(&$vars) {
//}


/**
 * Implements hook_preprocess_block()
 */
//function STARTER_preprocess_block(&$vars) {
//}


//function STARTER_preprocess_views_view(&$vars) {
//}


/**
 * Implements template_preprocess_panels_pane().
 *
 */
//function STARTER_preprocess_panels_pane(&$vars) {
//}


/**
 * Implements template_preprocess_views_views_fields().
 *
 */
//function STARTER_preprocess_views_view_fields(&$vars) {
//}


/**
 * Implements theme_form_element_label()
 * Use foundation tooltips
 */
//function STARTER_form_element_label($vars) {
//}


/**
 * Implements hook_preprocess_button().
 */
//function STARTER_preprocess_button(&$vars) {
//}


/**
 * Implements hook_form_alter()
 * Example of using foundation sexy buttons
 */
//function STARTER_form_alter(&$form, &$form_state, $form_id) {
//  // Sexy submit buttons
//  if (!empty($form['actions']) && !empty($form['actions']['submit'])) {
//    $form['actions']['submit']['#attributes'] = array('class' => array('primary', 'button', 'radius'));
//  }
//}

// Sexy preview buttons
//function STARTER_form_comment_form_alter(&$form, &$form_state) {
//  $form['actions']['preview']['#attributes']['class'][] = array('class' => array('secondary', 'button', 'radius'));
//}


/**
 * Implements template_preprocess_panels_pane().
 */
// function zurb_foundation_preprocess_panels_pane(&$vars) {
// }


/**
* Implements template_preprocess_views_views_fields().
*/
// function THEMENAME_preprocess_views_view_fields(&$vars) {
// }


/**
 * Implements hook_css_alter().
 */
//function STARTER_css_alter(&$css) {
//  // Always remove base theme CSS.
//  $theme_path = drupal_get_path('theme', 'zurb_foundation');
//
//  foreach($css as $path => $values) {
//    if(strpos($path, $theme_path) === 0) {
//      unset($css[$path]);
//    }
//  }
//}


/**
 * Implements hook_js_alter().
 */
//function STARTER_js_alter(&$js) {
//  // Always remove base theme JS.
//  $theme_path = drupal_get_path('theme', 'zurb_foundation');
//
//  foreach($js as $path => $values) {
//    if(strpos($path, $theme_path) === 0) {
//      unset($js[$path]);
//    }
//  }
//}
