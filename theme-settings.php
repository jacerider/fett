<?php

/**
 * @file
 * Custom theme settings.
 */

use Drupal\Component\Utility\Html;
use Drupal\Core\Form\FormStateInterface;
use Drupal\fett\Theme\ThemeInfo;

/**
 * Implementation of hook_form_system_theme_settings_alter()
 *
 * @param $form
 *   Nested array of form elements that comprise the form.
 * @param $form_state
 *   A keyed array containing the current state of the form.
 */
function fett_form_system_theme_settings_alter(&$form, FormStateInterface $form_state, $form_id = NULL) {
  // Work-around for a core bug affecting admin themes. See issue #943212.
  if (isset($form_id)) {
    return;
  }

  // Set the theme name.
  $build_info = $form_state->getBuildInfo();

  $active_theme = \Drupal::theme()->getActiveTheme();
  $theme = $active_theme->getName();
  $theme_extension = $active_theme->getExtension();

  // Instantiate our Theme info object.
  $themeInfo = new ThemeInfo($theme);
  $getThemeInfo = $themeInfo->getThemeInfo('info');

  // Get this themes config settings
  $config = \Drupal::config($theme . '.settings')->get('settings');

  // Common paths.
  $fett_path  = drupal_get_path('theme', 'fett');
  $subtheme_path = drupal_get_path('theme', $theme);

  // Get the active themes regions so we can use this in
  // various other places.
  $theme_regions = system_region_list($theme, $show = REGIONS_VISIBLE);

  // Active themes active blocks
  // $block_module = \Drupal::moduleHandler()->moduleExists('breakpoint');
  // if ($block_module == TRUE) {
  //   $theme_blocks = \Drupal::entityTypeManager()->getStorage('block')->loadByProperties(['theme' => $theme]);
  // }
  // else {
  //   $theme_blocks = NULL;
  // }

  // Check for breakpoints module and set a warning and a flag to disable much
  // of the theme settings if its not available.
  $breakpoints_module = \Drupal::moduleHandler()->moduleExists('breakpoint');

  if ($breakpoints_module == TRUE) {
    $breakpoint_groups = \Drupal::service('breakpoint.manager')->getGroups();
    $breakpoints = array();

    // Set breakpoint options, we use these in layout and other extensions like
    // Responsive menus.
    foreach ($breakpoint_groups as $group_key => $group_values) {
      $breakpoints[$group_key] = \Drupal::service('breakpoint.manager')->getBreakpointsByGroup($group_key);
    }

    foreach($breakpoints as $group => $breakpoint_values)  {
      if ($breakpoint_values !== array()) {
        $breakpoint_options[$group] = $group;
      }
    }
  }
  else {
    drupal_set_message(t('This theme requires the <b>Breakpoint module</b> to be installed. Go to the <a href="@extendpage" target="_blank">Modules</a> page and install Breakpoint. You cannot set the layout or use this themes custom settings until Breakpoint is installed.', array('@extendpage' => base_path() . 'admin/modules')), 'error');
  }

  // Set a class on the form for the current admin theme, note if this is set to
  // "Default theme" the result is always 0.
  $system_theme_config = \Drupal::config('system.theme');
  $admin_theme = $system_theme_config->get('admin');
  if (!empty($admin_theme)) {
    $admin_theme_class = 'admin-theme--' . Html::cleanCssIdentifier($admin_theme);
    $form['#attributes'] = array('class' => array($admin_theme_class));
  }

  // Fett Core
  if ($theme == 'fett') {
    drupal_set_message(t('Fett has no configuration and cannot be used as a front end theme - it is a base them only. Use <b>drush fett</b> to generate or clone a theme to get started.'), 'error');

    // Hide form items.
    $form['theme_settings']['#attributes']['class'] = array('visually-hidden');
    $form['logo']['#attributes']['class'] = array('visually-hidden');
    $form['favicon']['#attributes']['class'] = array('visually-hidden');
    $form['actions']['#attributes']['class'] = array('visually-hidden');
  }

  // Fett Subtheme
  if (isset($getThemeInfo['subtheme type']) && $getThemeInfo['subtheme type'] === 'fett_subtheme') {

    // Extension settings.
    require_once($fett_path . '/forms/ext/extension_settings.php');

    // Basic settings - move into details wrapper and collapse.
    $form['basic_settings'] = array(
      '#type' => 'details',
      '#title' => t('Basic Settings'),
      '#open' => FALSE,
    );

    $form['theme_settings']['#open'] = FALSE;
    $form['theme_settings']['#group'] = 'basic_settings';
    $form['logo']['#open'] = FALSE;
    $form['logo']['#group'] = 'basic_settings';
    $form['favicon']['#open'] = FALSE;
    $form['favicon']['#group'] = 'basic_settings';

    // Buttons don't work with #group, move it the hard way.
    $form['basic_settings']['actions']['#type'] = 'actions';
    $form['basic_settings']['actions']['submit']['#type'] = 'submit';
    $form['basic_settings']['actions']['submit']['#value'] = t('Save basic settings');
    $form['basic_settings']['actions']['submit']['#button_type'] = 'primary';
    unset($form['actions']);
  }
}
