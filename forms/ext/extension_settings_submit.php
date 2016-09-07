<?php

/**
 * @file
 * Process extension settings submits.
 */

use Drupal\Core\PhpStorage\PhpStorageFactory;
use Drupal\Core\Url;
use Drupal\fett\Theme\ThemeSettingsConfig;

/**
 * Form submit handler for the Extension settings.
 * @param $form
 * @param $form_state
 */
function fett_submit_extension_settings(&$form, \Drupal\Core\Form\FormStateInterface &$form_state) {
  $build_info = $form_state->getBuildInfo();
  $values = $form_state->getValues();
  $theme = $build_info['args'][0];
  $fett_path = drupal_get_path('theme', 'fett');
  $subtheme_path = drupal_get_path('theme', $theme);

  // Don't let this timeout easily.
  set_time_limit(60);

  if ($values['settings_enable_extensions'] === 1) {

  }

  // Flush caches. I really, really tried to avoid this, but if you know a better
  // way of always clearing twig, CSS and the registry?
  // drupal_flush_all_caches();

  // Manage settings and configuration.
  // Must get mutable config otherwise bad things happen.
  $config = \Drupal::configFactory()->getEditable($theme . '.settings');
  $convertToConfig = new ThemeSettingsConfig();
  $convertToConfig->settingsExtensionsConvertToConfig($values, $config);

  drupal_set_message(t('Extensions configuration saved.'), 'status');
}
