<?php

/**
 * @file
 * Generate settings for Iconify.
 */

$form['iconify'] = array(
  '#type' => 'details',
  '#title' => t('Iconify'),
  '#group' => 'extension_settings',
);

$form['iconify']['settings_iconify_tasks'] = array(
  '#type' => 'checkbox',
  '#title' => t('Iconify Tasks'),
  '#default_value' => theme_get_setting('settings.iconify_tasks', $theme),
);

$form['iconify']['settings_iconify_tasks_icon_only'] = array(
  '#type' => 'checkbox',
  '#title' => t('Only show icon'),
  '#default_value' => theme_get_setting('settings.iconify_tasks_icon_only', $theme),
  '#states' => array(
    'visible' => array(':input[name="settings_iconify_tasks"]' => array('checked' => TRUE)),
  ),
);
