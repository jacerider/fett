<?php

/**
 * @file
 * Validate form values.
 * @param $form
 * @param $form_state
 */
function fett_validate_extension_settings(&$form, \Drupal\Core\Form\FormStateInterface &$form_state) {
  $build_info = $form_state->getBuildInfo();
  $values = $form_state->getValues();
  $theme = $build_info['args'][0];

  // TODO shocking lack of validation here, ops :)
}
