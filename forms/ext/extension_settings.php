<?php

/**
 * @file
 * Generate form elements for the Extension settings.
 */

// Submit handlers for the advanced settings.
include_once(drupal_get_path('theme', 'fett') . '/forms/ext/extension_settings_validate.php');
include_once(drupal_get_path('theme', 'fett') . '/forms/ext/extension_settings_submit.php');

$settings_extensions_form_open = theme_get_setting('settings.extensions_form_open', $theme);

$form['extensions'] = array(
  '#type' => 'details',
  '#title' => t('Extensions'),
  '#weight' => -201,
  '#open' => $settings_extensions_form_open,
  '#attributes' => array('class' => array('extension-settings', 'clearfix')),
);

// Enable extensions, the extension settings are hidden by default to ease the
// the UI clutter, this setting is also used as a global enable/disable for any
// extension in other logical operations.
$form['extensions']['extensions-enable-container'] = array(
  '#type' => 'container',
  '#attributes' => array('class' => array('subsystem-enabled-container', 'layouts-column-onequarter')),
);

$form['extensions']['extensions-enable-container']['settings_enable_extensions'] = array(
  '#type' => 'checkbox',
  '#title' => t('Enable'),
  '#default_value' => theme_get_setting('settings.enable_extensions', $theme),
);

$form['extensions']['extensions-enable-container']['settings_extensions_form_open'] = array(
  '#type' => 'checkbox',
  '#title' => t('Keep open'),
  '#default_value' => $settings_extensions_form_open,
  '#states' => array(
    'disabled' => array('input[name="settings_enable_extensions"]' => array('checked' => FALSE)),
  ),
);

$form['extensions']['extension_settings'] = array(
  '#type' => 'vertical_tabs',
  '#attributes' => array('class' => array('clearfix')),
  '#states' => array(
    'visible' => array(':input[name="settings_enable_extensions"]' => array('checked' => TRUE)),
  ),
);

// Extensions
$form['enable_extensions'] = array(
  '#type' => 'details',
  '#title' => t('Enable extensions'),
  '#group' => 'extension_settings',
);

$form['enable_extensions']['description'] = array(
  '#markup' => t('<p>Extensions are settings for configuring and styling your site. Enabled extensions appear in new vertical tabs.</p>'),
);

// Mobile Menu
$form['enable_extensions']['settings_enable_mobile_menu'] = array(
  '#type' => 'checkbox',
  '#title' => t('Mobile menu'),
  '#description' => t('Select responsive menu styles and breakpoints.'),
  '#default_value' => theme_get_setting('settings.enable_mobile_menu', $theme),
);

// Iconify
$form['enable_extensions']['settings_enable_iconify'] = array(
  '#type' => 'checkbox',
  '#title' => t('Iconify'),
  '#description' => t('Enable support for the Iconify module.'),
  '#default_value' => theme_get_setting('settings.enable_iconify', $theme),
);

// Legacy browsers
$form['enable_extensions']['settings_enable_legacy_browsers'] = array(
  '#type' => 'checkbox',
  '#title' => t('Legacy browsers'),
  '#description' => t('Settings to support crappy old browsers like IE8. Use with caution, do not enable this unless you really, really need it.'),
  '#default_value' => theme_get_setting('settings.enable_legacy_browsers', $theme),
);

// Extensions master toggle.
if (theme_get_setting('settings.enable_extensions', $theme) == 1) {

  $extensions_array = array(
    'mobile_menu',
    // 'fonts',
    // 'titles',
    // 'images',
    // 'touch_icons',
    // 'shortcodes',
    // 'mobile_blocks',
    // 'slideshows',
    // 'custom_css',
    // 'ckeditor',
    // 'markup_overrides',
    // 'devel',
    'iconify',
    'legacy_browsers',
  );

  // Get form values.
  $values = $form_state->getValues();

  foreach ($extensions_array as $extension) {
    $form_state_value = isset($values["settings_enable_$extension"]) ? $values["settings_enable_$extension"] : 0;
    $form_value = isset($form['enable_extensions']["settings_enable_$extension"]['#default_value']) ? $form['enable_extensions']["settings_enable_$extension"]['#default_value'] : 0;
    if (($form_state_value && $form_state_value === 1) || (!$form_state_value && $form_value === 1)) {
      include_once($fett_path . '/forms/ext/' . $extension . '.php');
    }
  }
}

// Submit button for advanced settings.
$form['extensions']['actions'] = array(
  '#type' => 'actions',
  '#attributes' => array('class' => array('submit--advanced-settings')),
);
$form['extensions']['actions']['submit'] = array(
  '#type' => 'submit',
  '#value' => t('Save extension settings'),
  '#validate'=> array('fett_validate_extension_settings'),
  '#submit'=> array('fett_submit_extension_settings'),
  '#attributes' => array('class' => array('button--primary')),
);
