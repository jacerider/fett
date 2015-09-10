<?php

function fett_form_system_theme_settings_alter(&$form, $form_state, $form_id = NULL) {
  if (isset($form_id)) return;

  // Variables
  $path_fett = drupal_get_path('theme', 'fett');
  $sonar_enabled = module_exists('sonar');
  $theme_name = $form_state['build_info']['args'][0];
  $configured = variable_get("theme_{$theme_name}_settings", FALSE);
  $css_mode = variable_get('preprocess_css', '') == 1 ? TRUE : FALSE;
  $js_mode = variable_get('preprocess_js', '') == 1 ? TRUE : FALSE;

  // Includes
  include_once './' . $path_fett . '/includes/foundation.inc';
  include_once './' . $path_fett . '/includes/tools.inc';
  include_once './' . $path_fett . '/includes/share.inc';
  $form['#attached']['js'][] = $path_fett .'/assets/js/fett.theme.settings.js';

  // Set defaults if necessary
  _fett_defaults();

  $title = 'Fe&#8224;&#8224;';
  if($theme_name !== 'fett'){
    $themes = list_themes();
    $theme = $themes[$theme_name];
    $title = $theme->name . ' <small><em>a lowly clone of</em> '.$title.'</small>';
  }

  $form['fett'] = array(
    '#type'   => 'vertical_tabs',
    '#weight' => -10,
    '#prefix' => '<h1>' . $title . '</h1>',
  );


  //////////////////////////////////////////////////////////////////////////////
  // CSS
  //////////////////////////////////////////////////////////////////////////////

  $form['fett']['css'] = array(
      '#type'        => 'fieldset',
      '#title'       => t('CSS'),
  );

  // Aggregation overrides, see http://drupal.org/node/1115026
  if ($css_mode == FALSE) {
    $css_mode_message = t('CSS aggregation is OFF. This settings will have no effect until CSS aggregation is turned ON.');
  }
  else {
    $css_mode_message = t('CSS aggregation is ON. This settings will take effect.');
  }
  // Combine CSS
  $form['fett']['css']['css_onefile'] = array(
    '#type' => 'checkbox',
    '#title'  => t('Combine CSS Files'),
    '#description' => t('In Fett you will normally get three media type CSS files after this is enabled and CSS aggregation is turned on - all, screen and only screen. If you are using a print stylesheet this will be seperate also. Browser specific stylesheets for Internet Explorer are ignored.<br><small>!css_mode_message</small>', array('!css_mode_message' => $css_mode_message)),
    '#default_value' => fett_get_setting('css_onefile'),
  );

  require_once($path_fett . '/settings/css.foundation.inc');
  fett_settings_css_foundation_form($form['fett']['css'], $theme_name);

  require_once($path_fett . '/settings/css.exclude.inc');
  fett_settings_css_exclude_form($form['fett']['css'], $theme_name);

  //////////////////////////////////////////////////////////////////////////////
  // JS
  //////////////////////////////////////////////////////////////////////////////

  $form['fett']['js'] = array(
    '#type' => 'fieldset',
    '#title' => t('Javascript'),
  );

  if ($js_mode == FALSE) {
    $js_mode_message = t('JavaScript aggregation is OFF. This settings will have no effect until JavaScript aggregation is turned ON.');
  }
  else {
    $js_mode_message = t('JavaScript aggregation is ON. This settings will take effect.');
  }
  // Combine JS
  $form['fett']['js']['js_onefile'] = array(
    '#type' => 'checkbox',
    '#title'  => t('Combine JS Files'),
    '#description' => t('This will force all aggregated JavaScript files into one file.<br><small>!js_mode_message</small>', array('!js_mode_message' => $js_mode_message)),
    '#default_value' => fett_get_setting('js_onefile'),
  );

  require_once($path_fett . '/settings/js.foundation.inc');
  fett_settings_js_foundation_form($form['fett']['js'], $theme_name);


  //////////////////////////////////////////////////////////////////////////////
  // Off-canvas
  //////////////////////////////////////////////////////////////////////////////

  $form['fett']['offcanvas'] = array(
    '#type' => 'fieldset',
    '#title' => t('Off-canvas'),
  );

  require_once($path_fett . '/settings/offcanvas.inc');
  fett_settings_offcanvas_form($form['fett']['offcanvas'], $theme_name);


  //////////////////////////////////////////////////////////////////////////////
  // Social Sharing Buttons.
  //////////////////////////////////////////////////////////////////////////////

  $form['fett']['share'] = array(
    '#type' => 'fieldset',
    '#title' => t('Social Sharing Buttons'),
  );

  require_once($path_fett . '/settings/share.inc');
  fett_settings_share_form($form['fett']['share'], $theme_name);


  //////////////////////////////////////////////////////////////////////////////
  // Megamenu
  //////////////////////////////////////////////////////////////////////////////

  $form['fett']['megamenu'] = array(
    '#type' => 'fieldset',
    '#title' => t('Mega Menu'),
  );

  require_once($path_fett . '/settings/megamenu.inc');
  fett_settings_megamenu_form($form['fett']['megamenu'], $theme_name);


  //////////////////////////////////////////////////////////////////////////////
  // Tooltips
  //////////////////////////////////////////////////////////////////////////////

  $form['fett']['tooltip'] = array(
    '#type' => 'fieldset',
    '#title' => t('Tooltip'),
  );

  require_once($path_fett . '/settings/tooltip.inc');
  fett_settings_tooltip_form($form['fett']['tooltip'], $theme_name);


  //////////////////////////////////////////////////////////////////////////////
  // Tools
  //////////////////////////////////////////////////////////////////////////////

  $form['fett']['tools'] = array(
    '#type' => 'fieldset',
    '#title' => t('Tools'),
  );

  $form['fett']['tools']['header_fixed'] = array(
    '#type' => 'checkbox',
    '#title' => t('Enable Fixed Header'),
    '#default_value' => fett_get_setting('header_fixed'),
    '#description' => t('Will fix the header to the top of the page when scrolling.'),
  );

  $form['fett']['tools']['html_tags'] = array(
    '#type' => 'checkbox',
    '#title' => t('Prune HTML Tags'),
    '#default_value' => fett_get_setting('html_tags'),
    '#description' => t('Prunes your <code>style</code>, <code>link</code>, and <code>script</code> tags as <a href="!link" target="_blank"> suggested by Nathan Smith</a>.', array('!link' => 'http://sonspring.com/journal/html5-in-drupal-7#_pruning')),
  );

  if(module_exists('fawesome')){
    $form['fett']['tools']['icon_hide_labels'] = array(
      '#type' => 'select',
      '#title' => t('Hide labels on links with icons'),
      '#empty_option' => t('Always show'),
      '#options' => array(
        'for-medium-up' => t('Hide for medium up'),
        'for-large-up' => t('Hide for large up'),
      ),
      '#description' => t('Font Awesome icons are automatically added to various links in this theme. When checked, and an icon has been added, the link label will be hidden and placed into a tooltip.'),
      '#default_value' => fett_get_setting('icon_hide_labels'),
    );
  }

  $options = array(1,2,3,4,5,6,7,8,9,10,11,12);
  $form['fett']['tools']['content_class_large'] = array(
    '#type' => 'select',
    '#title' => t('Content size without sidebars'),
    '#options' => drupal_map_assoc($options),
    '#default_value' => fett_get_setting('content_class_large', NULL, 12),
    '#description' => t('The Foundation large size of the main content area when no sidebars exist.'),
  );

  $options = array(1,2,3,4,5,6,7,8,9,10,11,12);
  $form['fett']['tools']['sidebar_class_large'] = array(
    '#type' => 'select',
    '#title' => t('Sidebar size'),
    '#options' => drupal_map_assoc($options),
    '#default_value' => fett_get_setting('sidebar_class_large', NULL, 3),
    '#description' => t('The Foundation large size of the sidebars.'),
  );


  //////////////////////////////////////////////////////////////////////////////
  // General
  //////////////////////////////////////////////////////////////////////////////

  $form['fett']['fett_general'] = array(
    '#type' => 'fieldset',
    '#title' => t('General'),
  );

  if(isset($form['theme_settings'])){
    $form['fett']['fett_general']['theme_settings'] = $form['theme_settings'];
    $form['fett']['fett_general']['logo'] = $form['logo'];
    $form['fett']['fett_general']['favicon'] = $form['favicon'];
    unset($form['theme_settings']);
    unset($form['logo']);
    unset($form['favicon']);
  }

  $form['#submit'][] = 'fett_settings_submit';
}

function fett_settings_submit($form, &$form_state){
  drupal_theme_rebuild();
}

/**
 * Validation best assigned to checkboxes. It will remove all empty values from
 * the saved array.
 */
function fett_settings_validate_cleanup($element, &$form_state, $form) {
  if(isset($form_state['values'][$element['#name']]) && is_array($form_state['values'][$element['#name']])){
    $form_state['values'][$element['#name']] = array_values(array_filter($form_state['values'][$element['#name']]));
    if(empty($form_state['values'][$element['#name']])){
      unset($form_state['values'][$element['#name']]);
    }
  }
}

/**
 * Validation best assigned to a checkbox. If value of checkbox is FALSE then
 * all children started with the checkbox key will be removed.
 */
function fett_settings_validate_cleanup_children($element, &$form_state, $form) {
  if(empty($form_state['values'][$element['#name']])){
    foreach($form_state['values'] as $key => $value){
      $result = preg_match('#^' . $element['#name'] . '#i', $key);
      if($result != 0){
        unset($form_state['values'][$key]);
      }
    }
  }
}
