<?php

/**
 * @file
 * Generate settings for tooltip icons.
 */
function fett_settings_tooltip_form(&$form, $theme_name) {

  $form['tooltip_form'] = array(
    '#type' => 'checkbox',
    '#title' => t('Tooltip Forms'),
    '#default_value' => fett_get_setting('tooltip_form'),
    '#description' => t('Use tooltips for form descriptions.'),
    '#states' => array(
      'visible' => array(
        'input[name="tooltip"]' => array('checked' => TRUE),
      ),
    ),
  );

}
