<?php

/**
 * Implements hook_js_alter().
 */
function fett_js_alter(&$js) {
  $path_fett = drupal_get_path('theme', 'fett');

  // Display warning if jQuery Update not present.
  if (!module_exists('jquery_update')) {
    // Use jQuery 1.10.2 if jQuery Update module is not installed.
    if (isset($js['misc/jquery.js'])) {
      $js['misc/jquery.js']['data'] = $path_fett . '/assets/js/jquery-1.10.2.min.js';
      $js['misc/jquery.js']['weight'] = -100;
    }
    else{
      drupal_set_message(t('Incorrect jQuery version detected. Zurb Foundation requires jQuery 1.10 or higher. Please install jQuery Update.'), 'error', FALSE);
    }
  }
  // If it is present, check for correct jQuery version.
  else {
    $jquery_version = variable_get('jquery_update_jquery_version', '1.5');

    if (!version_compare($jquery_version, '1.10', '>=')) {
      drupal_set_message(t('Incorrect jQuery version detected. Zurb Foundation requires jQuery 1.0 or higher. Please change your <a href="!settings">jQuery Update settings</a>.', array('!settings' => url('admin/config/development/jquery_update'))), 'error', FALSE);
    }
  }

  // Move all scripts to footer
  // Remove for now as this is breaking Drupal.ajax
  // if(theme_get_setting('fett_js_footer')) {
  //   foreach ($js as $file => $value) {
  //     $js[$file]['scope'] = 'footer';
  //   }
  // }

  // Aggregate all files into a single file
  if(theme_get_setting('fett_js_onefile')){
    uasort($js, 'drupal_sort_css_js');
    $i = 0;
    foreach ($js as $name => $script) {
      $js[$name]['weight'] = $i++;
      $js[$name]['group'] = JS_DEFAULT;
      $js[$name]['every_page'] = FALSE;
    }
  }
}
