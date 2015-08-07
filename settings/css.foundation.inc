<?php

/**
 * @file
 * Generate settings for the CSS exclude form.
 */
function fett_settings_css_foundation_form(&$form, $theme_name) {
  $select_toggle = '<br>' .
  l(t('select all'), '#', array('attributes' => array('class' => 'select-all'))) . ' | ' .
  l(t('select none'), '#', array('attributes' => array('class' => 'select-none')));

  $form['foundation'] = array(
    '#type'        => 'fieldset',
    '#title'       => t('Foundation CSS Components'),
    '#description' => t('Enable/Disable Foundation Components') . $select_toggle,
    '#collapsible' => TRUE,
    '#collapsed'   => TRUE,
  );

  $form['foundation']['css_foundation'] = array(
    '#type'             => 'checkboxes',
    '#title'            => t('Files'),
    '#options'          => fett_foundation_css_components(),
    '#default_value'    => fett_get_setting('css_foundation', NULL, array()),
    '#element_validate' => array('fett_settings_validate_cleanup'),
  );

}
