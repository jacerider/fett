<?php

/**
 * @file
 * Generate settings for the CSS exclude form.
 */
function fett_settings_css_exclude_form(&$form, $theme_name) {
  $select_toggle = '<br>' .
  l(t('select all'), '#', array('attributes' => array('class' => 'select-all'))) . ' | ' .
  l(t('select none'), '#', array('attributes' => array('class' => 'select-none'))) . '<br><br>';

  // Get the relevent CSS file data for building the form.
  $css_data = fett_get_css_files($theme_name);

  // regex pattern
  $pattern = '/[^a-zA-Z0-9-]+/';

  $form['exclude'] = array(
    '#type' => 'fieldset',
    '#title' => t('CSS Reset'),
    '#collapsible' => TRUE,
    '#collapsed'   => !fett_get_setting('css_exclude'),
  );

  $form['exclude']['css_exclude'] = array(
    '#type' => 'checkbox',
    '#title' => t("Prevent all core and contrib CSS for being loaded"),
    '#attributes' => array(
      'class' => array('enable-extension'),
    ),
    '#description' => t('Disable all CSS files included by core and contrib modules. You will be able to re-enable individual files.'),
    '#default_value' => fett_get_setting('css_exclude'),
  );

  $options = array();
  foreach ($css_data as $key => $value) {
    $setting = preg_replace($pattern, '_', $key);
    $title_parts = explode('/', $key);
    $title = array_pop($title_parts);
    $options[$value['type']][$setting] = t('<b>@title</b> <small>(@key)</small>', array('@title' => $title, '@key' => $key));
  }

  $form['exclude']['enable'] = array(
    '#type' => 'fieldset',
    '#title' => t('Allow CSS'),
    '#description' => t('Stylesheet names are cached, if some are not showing in this list you may need to <strong>clear the cache</strong>.<br><small>In for some reason (it happens) the CSS files you want to unset never show here you can explicitly declare them in your info file as "unset_css", see your sub-themes info file under "Stylesheets" for instructions.</small>'),
  );

  // Core
  if (!empty($options['unset_core'])) {
    $form['exclude']['enable']['core'] = array(
      '#type' => 'fieldset',
      '#title' => t('Core'),
      '#description' => t('Allow core module CSS') . $select_toggle,
      '#collapsible' => TRUE,
      '#collapsed'   => TRUE,
    );
    $form['exclude']['enable']['core']['css_exclude_enable_core'] = array(
      '#type' => 'checkboxes',
      '#options' => $options['unset_core'],
      '#default_value' => fett_get_setting('css_exclude_enable_core', NULL, array()),
      '#element_validate' => array('fett_settings_validate_cleanup'),
    );
  }

  // Contrib
  if (!empty($options['contrib'])) {
    $form['exclude']['enable']['contrib'] = array(
      '#type' => 'fieldset',
      '#title' => t('Contrib'),
      '#description' => t('Allow contrib module CSS') . '<br><small>' . t('Only modules contained within /contrib or /community are scanned for CSS files.') . '</small>' . $select_toggle,
      '#collapsible' => TRUE,
      '#collapsed'   => TRUE,
    );
    $form['exclude']['enable']['contrib']['css_exclude_enable_contrib'] = array(
      '#type' => 'checkboxes',
      '#options' => $options['contrib'],
      '#default_value' => fett_get_setting('css_exclude_enable_contrib', NULL, array()),
      '#element_validate' => array('fett_settings_validate_cleanup'),
    );
  }

  // Library
  if (!empty($options['library'])) {
    $form['exclude']['enable']['library'] = array(
      '#type' => 'fieldset',
      '#title' => t('Library'),
      '#description' => t('Allow library CSS') . $select_toggle,
      '#collapsible' => TRUE,
      '#collapsed'   => TRUE,
    );
    $form['exclude']['enable']['library']['css_exclude_enable_library'] = array(
      '#type' => 'checkboxes',
      '#options' => $options['library'],
      '#default_value' => fett_get_setting('css_exclude_enable_library', NULL, array()),
      '#element_validate' => array('fett_settings_validate_cleanup'),
    );
  }

  // User-defined
  if (!empty($options['user_defined'])) {
    $form['exclude']['enable']['user'] = array(
      '#type' => 'fieldset',
      '#title' => t('User-defined'),
      '#description' => t('User-defined CSS') . $select_toggle,
      '#collapsible' => TRUE,
      '#collapsed'   => TRUE,
    );
    $form['exclude']['enable']['library']['css_exclude_enable_user'] = array(
      '#type' => 'checkboxes',
      '#options' => $options['user_defined'],
      '#default_value' => fett_get_setting('css_exclude_enable_user', NULL, array()),
      '#element_validate' => array('fett_settings_validate_cleanup'),
    );
  }

}
