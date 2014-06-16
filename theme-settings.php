<?php

function fett_form_system_theme_settings_alter(&$form, $form_state, $form_id = NULL) {
  if (isset($form_id)) return;

  // Variables
  $path_fett = drupal_get_path('theme', 'fett');
  $sonar_enabled = module_exists('sonar');
  $current_theme = arg(3);

  // Includes
  include_once './' . $path_fett . '/inc/foundation.inc';
  drupal_add_js($path_fett .'/assets/js/themeSettings.js');

  if($sonar_enabled){
    drupal_add_css($path_fett . '/assets/scss/themeSettings.scss');

  }

  $select_toggle = '<br>' .
  l(t('select all'), '#', array('attributes' => array('class' => 'select-all'))) . ' | ' .
  l(t('select none'), '#', array('attributes' => array('class' => 'select-none')));

  $form['fett'] = array(
    '#type'   => 'vertical_tabs',
    '#weight' => -10,
    '#prefix' => '<h1>F e &#8224; &#8224;</h1><small>' . l('View Style Guide', '<front>', array('query' => array('styleguide' => 1))) . '</small>',
  );

  //////////////////////////////////////////////////////////////////////////////
  // Status
  //////////////////////////////////////////////////////////////////////////////

  $form['fett']['fett_status'] = array(
    '#type' => 'fieldset',
    '#title' => t('Status'),
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

 $description = t('This is the _settings.scss file that ships with Foundation and it used for changing the many variables that Foundation uses.');
 $disabled = FALSE;
 $filepath = drupal_get_path('theme', $current_theme) . '/assets/scss/libraries';
 if(!file_exists($filepath . '/_settings.scss')){
  $description .= ' ' . t('The Foundation _settings.scss file must be placed in !filepath.', array('!filepath' => $filepath));
  $disabled = TRUE;
 }
 $form['fett']['css']['fett_foundation_settings'] = array(
    '#type'          => 'checkbox',
    '#title'         => t('Use Foundation settings SCSS file'),
    '#description'   => $description,
    '#default_value' => theme_get_setting('fett_foundation_settings'),
    '#disabled' => $disabled,
 );

 $form['fett']['css']['fett_css_onefile'] = array(
    '#type'          => 'checkbox',
    '#title'         => t('Aggregate all CSS into a single file'),
    '#description'   => t('This will decrese HTTP requests.'),
    '#default_value' => theme_get_setting('fett_css_onefile')
 );

  $form['fett']['css']['foundation'] = array(
    '#type'        => 'fieldset',
    '#title'       => t('Foundation SCSS Components'),
    '#description' => $sonar_enabled ? t('Enable/Disable Foundation SCSS Components') . $select_toggle : '',
    '#collapsible' => TRUE,
    '#collapsed'   => TRUE,
  );

  if($sonar_enabled){
    $form['fett']['css']['foundation']['fett_foundation_scss'] = array(
      '#type'          => 'checkboxes',
      '#title'         => t('Files'),
      '#options'       => fett_foundation_get_scss(),
      '#default_value' => theme_get_setting('fett_foundation_scss') ? theme_get_setting('fett_foundation_scss') : array(),
    );
  }
  else{
    $form['fett']['css']['foundation']['fett_foundation_scss'] = array(
      '#type'   => 'item',
      '#markup' => '<div class="messages warning">' . t('In order to use inidividual Foundation SCSS components, <a href="!url">Sonar</a> is needed.', array('!url'=>'https://github.com/JaceRider/Sonar')) . '</div>',
    );
  }


  //////////////////////////////////////////////////////////////////////////////
  // JS
  //////////////////////////////////////////////////////////////////////////////

  $form['fett']['js'] = array(
    '#type' => 'fieldset',
    '#title' => t('Javascript'),
  );

  $form['fett']['js']['fett_js_footer'] = array(
    '#type'          => 'checkbox',
    '#title'         => t('Place all Javascript into the footer') ,
    '#description'   => t('This can help improve page loading speed.'),
    '#default_value' => theme_get_setting('fett_js_footer')
  );

  $form['fett']['js']['fett_js_onefile'] = array(
    '#type'          => 'checkbox',
    '#title'         => t('Aggregate all Javascript into a single file'),
    '#description'   => t('This will decrese HTTP requests.'),
    '#default_value' => theme_get_setting('fett_js_onefile')
  );

  $form['fett']['js']['foundation'] = array(
    '#type'        => 'fieldset',
    '#title'       => t('Foundation Components'),
    '#description' => t('Enable/Disable Foundation JavaScript Components') . $select_toggle,
    '#collapsible' => TRUE,
    '#collapsed'   => TRUE,
  );

  $form['fett']['js']['foundation']['fett_foundation_js'] = array(
    '#type'          => 'checkboxes',
    '#title'         => t('Files'),
    '#options'       => fett_foundation_get_js(),
    '#default_value' => theme_get_setting('fett_foundation_js') ? theme_get_setting('fett_foundation_js') : array(),
  );


  //////////////////////////////////////////////////////////////////////////////
  // Tools
  //////////////////////////////////////////////////////////////////////////////

  $form['fett']['fett_tools'] = array(
    '#type' => 'fieldset',
    '#title' => t('Tools'),
  );

  $form['fett']['fett_tools']['fett_messages_modal'] = array(
    '#type' => 'checkbox',
    '#title' => t('Display status messages in a modal'),
    '#description' => t('Check this to display Drupal status messages in a Zurb Foundation reveal modal.'),
    '#default_value' => theme_get_setting('fett_messages_modal'),
  );

  $form['fett']['fett_tools']['fett_html_tags'] = array(
    '#type' => 'checkbox',
    '#title' => t('Prune HTML Tags'),
    '#default_value' => theme_get_setting('fett_html_tags'),
    '#description' => t('Prunes your <code>style</code>, <code>link</code>, and <code>script</code> tags as <a href="!link" target="_blank"> suggested by Nathan Smith</a>.', array('!link' => 'http://sonspring.com/journal/html5-in-drupal-7#_pruning')),
  );

  /*
   * Foundation Top Bar.
   */
  $form['fett']['fett_tools']['topbar'] = array(
    '#type' => 'fieldset',
    '#title' => t('Foundation Top Bar'),
    '#description' => t('The Foundation Top Bar gives you a great way to display a complex navigation bar on small or large screens.'),
  );

  $form['fett']['fett_tools']['topbar']['fett_top_bar_enable'] = array(
    '#type' => 'select',
    '#title' => t('Enable'),
    '#description' => t('If enabled, the site name and main menu will appear in a bar along the top of the page.'),
    '#options' => array(
      0 => t('Never'),
      1 => t('Always'),
      2 => t('Mobile only'),
    ),
    '#default_value' => theme_get_setting('fett_top_bar_enable'),
  );

  // Group the rest of the settings in a container to be able to quickly hide
  // them if the Top Bar isn't being used.
  $form['fett']['fett_tools']['topbar']['container'] = array(
    '#type' => 'container',
    '#states' => array(
      'visible' => array(
        'select[name="fett_top_bar_enable"]' => array('!value' => '0'),
      ),
    ),
  );

  $form['fett']['fett_tools']['topbar']['container']['fett_top_bar_grid'] = array(
    '#type' => 'checkbox',
    '#title' => t('Contain to grid'),
    '#description' => t('Check this for your top bar to be set to your grid width.'),
    '#default_value' => theme_get_setting('fett_top_bar_grid'),
  );

  if(module_exists('fawesome')){
    $form['fett']['fett_tools']['topbar']['container']['fett_top_bar_fawesome'] = array(
      '#type' => 'checkbox',
      '#title' => t('Use Font Awesome icons'),
      '#description' => t('This will add icons for commonly used menu items such as "Log Out", "Home" and "My Account".'),
      '#default_value' => theme_get_setting('fett_top_bar_fawesome'),
    );
  }

  $form['fett']['fett_tools']['topbar']['container']['fett_top_bar_sticky'] = array(
    '#type' => 'checkbox',
    '#title' => t('Sticky'),
    '#description' => t('Check this for your top bar to stick to the top of the screen when the user scrolls down. If you\'re using the Admin Menu module and have it set to \'Keep menu at top of page\', you\'ll need to check this option to maintain compatibility.'),
    '#default_value' => theme_get_setting('fett_top_bar_sticky'),
  );

  $form['fett']['fett_tools']['topbar']['container']['fett_top_bar_scrolltop'] = array(
    '#type' => 'checkbox',
    '#title' => t('Scroll to top on click'),
    '#description' => t('Jump to top when sticky nav menu toggle is clicked.'),
    '#default_value' => theme_get_setting('fett_top_bar_scrolltop'),
    '#states' => array(
      'visible' => array(
        'input[name="fett_top_bar_sticky"]' => array('checked' => TRUE),
      ),
    ),
  );

  $form['fett']['fett_tools']['topbar']['container']['fett_top_bar_is_hover'] = array(
    '#type' => 'checkbox',
    '#title' => t('Hover to expand menu'),
    '#description' => t('Set this to false to require the user to click to expand the dropdown menu.'),
    '#default_value' => theme_get_setting('fett_top_bar_is_hover'),
  );

  // Menu settings.
  $form['fett']['fett_tools']['topbar']['container']['menu'] = array(
    '#type' => 'fieldset',
    '#title' => t('Dropdown Menu'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );

  $form['fett']['fett_tools']['topbar']['container']['menu']['fett_top_bar_menu_text'] = array(
    '#type' => 'textfield',
    '#title' => t('Menu text'),
    '#description' => t('Specify text to go beside the mobile menu icon or leave blank for none.'),
    '#default_value' => theme_get_setting('fett_top_bar_menu_text'),
  );

  $form['fett']['fett_tools']['topbar']['container']['menu']['fett_top_bar_custom_back_text'] = array(
    '#type' => 'checkbox',
    '#title' => t('Enable custom back text'),
    '#description' => t('This is the text that appears to navigate back one level in the dropdown menu. Set this to false and it will pull the top level link name as the back text.'),
    '#default_value' => theme_get_setting('fett_top_bar_custom_back_text'),
  );

  $form['fett']['fett_tools']['topbar']['container']['menu']['fett_top_bar_back_text'] = array(
    '#type' => 'textfield',
    '#title' => t('Custom back text'),
    '#description' => t('Define what you want your custom back text to be.'),
    '#default_value' => theme_get_setting('fett_top_bar_back_text'),
    '#states' => array(
      'visible' => array(
        'input[name="fett_top_bar_custom_back_text"]' => array('checked' => TRUE),
      ),
    ),
  );

  /*
   * Tooltips.
   */
  $form['fett']['fett_tools']['tooltips'] = array(
    '#type' => 'fieldset',
    '#title' => t('Tooltips'),
    '#collapsible' => TRUE,
  );

  $form['fett']['fett_tools']['tooltips']['fett_tooltip_enable'] = array(
    '#type' => 'checkbox',
    '#title' => t('Display form element descriptions in a tooltip'),
    '#default_value' => theme_get_setting('fett_tooltip_enable'),
  );

  $form['fett']['fett_tools']['tooltips']['fett_tooltip_position'] = array(
    '#type' => 'select',
    '#title' => t('Tooltip position'),
    '#options' => array(
      'tip-top' => t('Top'),
      'tip-bottom' => t('Bottom'),
      'tip-right' => t('Right'),
      'tip-left' => t('Left'),
    ),
    '#default_value' => theme_get_setting('fett_tooltip_position'),
    '#states' => array(
      'visible' => array(
        'input[name="fett_tooltip_enable"]' => array('checked' => TRUE),
      ),
    ),
  );

  $form['fett']['fett_tools']['tooltips']['fett_tooltip_mode'] = array(
    '#type' => 'select',
    '#title' => t('Display mode'),
    '#description' => t('You can either display the tooltip on the form element itself or on a "More information?" link below the element.'),
    '#options' => array(
      'element' => t('On the form element'),
      'text' => t('Below element on "More information?" text'),
    ),
    '#default_value' => theme_get_setting('fett_tooltip_mode'),
    '#states' => array(
      'visible' => array(
        'input[name="fett_tooltip_enable"]' => array('checked' => TRUE),
      ),
    ),
  );

  $form['fett']['fett_tools']['tooltips']['fett_tooltip_text'] = array(
    '#type' => 'textfield',
    '#title' => t('More information text'),
    '#description' => t('Customize the tooltip trigger text.'),
    '#default_value' => theme_get_setting('fett_tooltip_text'),
    '#states' => array(
      'visible' => array(
        'input[name="fett_tooltip_enable"]' => array('checked' => TRUE),
        'select[name="fett_tooltip_mode"]' => array('value' => 'text'),
      ),
    ),
  );

  $form['fett']['fett_tools']['tooltips']['fett_tooltip_touch'] = array(
    '#type' => 'checkbox',
    '#title' => t('Disable for touch devices'),
    '#description' => t('If you don\'t want tooltips to interfere with a touch event, you can disable them for those devices.'),
    '#default_value' => theme_get_setting('fett_tooltip_touch'),
    '#states' => array(
      'visible' => array(
        'input[name="fett_tooltip_enable"]' => array('checked' => TRUE),
      ),
    ),
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


  //////////////////////////////////////////////////////////////////////////////
  // Icon status
  //////////////////////////////////////////////////////////////////////////////

  $form['fett']['fett_icons'] = array(
    '#type' => 'fieldset',
    '#title' => t('Logo and Icons'),
  );

  $form['fett']['fett_icons']['status'] = array(
    '#type' => 'item',
    '#markup' => fett_form_icon_status($current_theme)
  );

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
  $override = drupal_get_path('theme', $theme_key).'/assets/js/modernizr.min.js';
  if(file_exists($override)){
    $output[] = fett_form_system_status_item('Modernizr', 'Enabled <small>(Local)</small>', NULL, REQUIREMENT_OK);
  }
  else{
    $output[] = fett_form_system_status_item('Modernizr', 'Enabled <small>(Remote)</small>', t('To override, place custom modernizr.min.js file so that it\'s filepath is @filepath.', array('@filepath' => $override)), REQUIREMENT_OK);
  }

  return theme('status_report', array(
    'requirements' => $output,
  ));
}

function fett_form_icon_status($current_theme){
  global $base_url;
  $path = drupal_get_path('theme', $current_theme);
  $path_fett = drupal_get_path('theme', 'fett');

  $output = array();
  $output[] = fett_form_system_status_item('<i class="fa fa-desktop"></i> Site Logo', theme('image', array('path' => $base_url .'/'. $path . '/logo.png')), NULL, REQUIREMENT_OK);
  $output[] = fett_form_system_status_item('<i class="fa fa-mobile"></i> iPad Retina Touch Icon (144x144)', theme('image', array('path' => $base_url .'/'. $path . '/assets/images/apple-touch-icon-144x144.png')), NULL, REQUIREMENT_OK);
  $output[] = fett_form_system_status_item('<i class="fa fa-mobile"></i> iPhone Retina Touch Icon (114x114)', theme('image', array('path' => $base_url .'/'. $path . '/assets/images/apple-touch-icon-114x114.png')), NULL, REQUIREMENT_OK);
  $output[] = fett_form_system_status_item('<i class="fa fa-mobile"></i> iPad Non-Retina Icon (72x72)', theme('image', array('path' => $base_url .'/'. $path . '/assets/images/apple-touch-icon-72x72.png')), NULL, REQUIREMENT_OK);
  $output[] = fett_form_system_status_item('<i class="fa fa-mobile"></i> iPad Non-Retina Icon (57x57)', theme('image', array('path' => $base_url .'/'. $path . '/assets/images/apple-touch-icon.png')), NULL, REQUIREMENT_OK);

  return theme('status_report', array(
    'requirements' => $output,
  ));

}

function fett_form_system_status_item($title, $value, $description = NULL, $severity = REQUIREMENT_INFO, $weight = 0){
  return array(
    'title' => t($title),
    'value' => t($value),
    'description' => t($description),
    'severity' => $severity,
    'weight' => $weight,
  );
}
