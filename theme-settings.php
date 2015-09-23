<?php

function fett_form_system_theme_settings_alter(&$form, &$form_state, $form_id = NULL) {
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
  $form_state['theme_name'] = $theme_name;

  if(module_exists('sonar')){
    $bg = drupal_get_path('theme', $theme_name) . '/assets/images/settings.png';
    $lines = $path_fett . '/assets/images/settings-lines.png';
    if(!file_exists($bg)){
      $bg = $path_fett . '/assets/images/settings.png';
    }
    sonar_add_var('fett-settings-bg-image', "'" . url($bg) . "'");
    sonar_add_var('fett-settings-bg-lines', "'" . url($lines) . "'");
    $form['#attached']['css'][$path_fett . '/assets/scss/_settings.scss'] = array('every_page' => FALSE);
  }

  $title = 'Fe&#8224;&#8224;';
  if($theme_name !== 'fett'){
    $themes = list_themes();
    $theme = $themes[$theme_name];
    $title = $theme->info['name'] . ' <small><em>a student of</em> '.$title.' <em>'.$themes['fett']->info['version'].'</em></small>';
  }

  $form['#id'] = 'fett-settings-wrapper';

  $form['fett'] = array(
    '#type'   => 'vertical_tabs',
    '#weight' => -10,
    '#prefix' => '
      <div id="fett-settings-header">
        <canvas id="starfield" style="background-color:#000000"></canvas>
        <div class="bg"></div>
        <div class="shine"></div>
        <div class="image"></div>
        <div class="lines"></div>
      </div>
      <div id="fett-settings">
      <h1>' . $title . '</h1>',
    '#suffix' => '</div>',
  );

  //////////////////////////////////////////////////////////////////////////////
  // Status
  //////////////////////////////////////////////////////////////////////////////

  $form['fett']['fett_status'] = array(
    '#type' => 'fieldset',
    '#title' => t('Status'),
    '#description' => t('This bounty is worth more when all requirements and recommendations are met.'),
    '#weight' => -100,
  );

  $form['fett']['fett_status']['status'] = array(
    '#type' => 'item',
    '#markup' => fett_form_system_status()
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

  // $form['fett']['tooltip'] = array(
  //   '#type' => 'fieldset',
  //   '#title' => t('Tooltip'),
  // );

  // require_once($path_fett . '/settings/tooltip.inc');
  // fett_settings_tooltip_form($form['fett']['tooltip'], $theme_name);


  //////////////////////////////////////////////////////////////////////////////
  // Favicons
  //////////////////////////////////////////////////////////////////////////////

  $form['fett']['favicons'] = array(
    '#type' => 'fieldset',
    '#title' => t('Favicons'),
  );

  require_once($path_fett . '/settings/favicons.inc');
  fett_settings_favicons_form($form['fett']['favicons'], $form_state, $theme_name);


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
 * Validation for removing values that should not be saved.
 */
function fett_settings_validate_remove($element, &$form_state, $form) {
  // File field support included.
  unset($form_state['values'][str_replace(array('files[', ']'), '', $element['#name'])]);
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

function fett_form_system_status(){
  global $theme_key;
  include_once DRUPAL_ROOT . '/includes/install.inc';

  $output = array();

  $info = drupal_parse_info_file(drupal_get_path('theme', 'fett') . '/fett.info');
  if($info){
    $output[] = fett_form_system_status_item('<i class="fa fa-crosshairs"></i> Version', $info['version']);
  }

  if(module_exists('sonar')){
    if(sonar_is_enabled()){
      $status = 'Enabled';
      $output[] = fett_form_system_status_item('SASS Support (Sonar)', $status, NULL, REQUIREMENT_OK);
    }
    else{
      $output[] = fett_form_system_status_item('SASS Support (Sonar)', 'Disabled', t('The Sonar module is installed but it is not set to compile SASS. !url', array('!url' => l('Configure', 'admin/config/system/sonar'))), REQUIREMENT_WARNING);
    }
  }
  else{
    $output[] = fett_form_system_status_item('SASS Support (Sonar)', 'Disabled', t('!sonar is <strong>not</strong> enabled. Sonar adds SASS support to Fett and is essential for unleashing the awesomeness of Fett.', array('!sonar' => l('Sonar', 'https://github.com/JaceRider/Sonar'))), REQUIREMENT_WARNING);
  }

  if(module_exists('fawesome')){
    $output[] = fett_form_system_status_item('Font Awesome (FAwesome)', 'Enabled', NULL, REQUIREMENT_OK);
  }
  else{
    $output[] = fett_form_system_status_item('Font Awesome (FAwesome)', 'Disabled', t('!fa is a simple module that adds SASS powered Font Awesome to your site. Although it is not required, it does add awesomeness to Fett.', array('!fa' => l('FAwesome', 'https://github.com/JaceRider/Fawesome'))), REQUIREMENT_WARNING);
  }

  if(module_exists('jquery_update')){
    $version = variable_get('jquery_update_jquery_version');
    if($version == '1.10'){
      $output[] = fett_form_system_status_item('jQuery Update', 'Enabled', NULL, REQUIREMENT_OK);
    }
    else{
      $output[] = fett_form_system_status_item('jQuery Update', 'Incorrect', t('The jQuery Update module is not configured to use jQuery 1.10. !url', array('!url' => l('Configure', 'admin/config/development/jquery_update'))), REQUIREMENT_WARNING);
    }
  }
  else{
    $output[] = fett_form_system_status_item('jQuery Update', 'Disabled', t('!jq module is required as Foundation 5 needs jQuery 10.2. Make sure to download the dev version of this module.', array('!jq' => l('jQuery Update', 'https://drupal.org/project/jquery_update'))), REQUIREMENT_WARNING);
  }

  // Add Modernizr
  $output[] = fett_form_system_status_item('Modernizr', 'Enabled <small>(CDN)</small>', '', REQUIREMENT_OK);

  return theme('status_report', array(
    'requirements' => $output,
  ));
}

function fett_form_system_status_item($title, $value, $description = NULL, $severity = REQUIREMENT_INFO, $weight = 0){
  return array(
    'title' => '<strong>' . t($title) . '</strong>',
    'value' => t($value),
    'description' => '<small>' . t($description) . '</small>',
    'severity' => $severity,
    'weight' => $weight,
  );
}
