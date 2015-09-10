<?php

/**
 * @file
 * Generate settings for share icons.
 */
function fett_settings_share_form(&$form, $theme_name) {

  $form['share'] = array(
    '#type' => 'checkbox',
    '#title' => t('Enable share sharing buttons within nodes.'),
    '#default_value' => fett_get_setting('share'),
    '#description' => t('This will add share <a href="!link" target="_blank">share sharing buttons</a> to the node output array.', array('!link' => 'https://github.com/kni-labs/share')),
    '#element_validate' => array('fett_settings_validate_cleanup_children'),
  );

  $options = array();
  foreach(node_type_get_types() as $type){
    $options[$type->type] = $type->name;
  }
  $form['share_node_bundles'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Enabled Content Types'),
    '#default_value' => fett_get_setting('share_node_bundles', NULL, array()),
    '#options' => $options,
    '#element_validate' => array('fett_settings_validate_cleanup'),
    '#states' => array(
      'visible' => array(
        'input[name="share"]' => array('checked' => TRUE),
      ),
    ),
  );

  $options = fett_share_services();
  $form['share_services'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Enabled Services'),
    '#default_value' => fett_get_setting('share_services', NULL, array()),
    '#options' => $options,
    '#element_validate' => array('fett_settings_validate_cleanup'),
    '#states' => array(
      'visible' => array(
        'input[name="share"]' => array('checked' => TRUE),
      ),
    ),
  );

}
