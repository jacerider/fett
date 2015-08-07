<?php

/**
 * @file
 * General CSS alters.
 */

/**
 * Implements hook_css_alter().
 */
function fett_css_alter(&$css) {
  global $theme_key;

  // Remove all core/contrib/module CSS
  if(fett_get_setting('css_exclude')){
    $css_data = fett_get_css_files($theme_key);

    $exceptions = array();
    foreach(array('core','contrib','library','user') as $group){
      $exceptions += drupal_map_assoc(fett_get_setting("css_exclude_enable_$group", $theme_key, array()));
    }

    // Get the theme setting and unset files
    foreach ($css_data as $key => $value) {
      $setting = preg_replace('/[^a-zA-Z0-9-]+/', '_', $key);
      if (isset($css[$key]) && !isset($exceptions[$setting])) {
        unset($css[$key]);
      }
    }
  }

  foreach ($css as $data => &$item) {
    // The CSS_SYSTEM aggregation group doesn't make any sense. Therefore, we are
    // pre-pending it to the CSS_DEFAULT group. This has the same effect as giving
    // it a separate (low-weighted) group but also allows it to be aggregated
    // together with the rest of the CSS.
    if ($item['group'] == CSS_SYSTEM) {
      $item['group'] = CSS_DEFAULT;
      $item['weight'] = $item['weight'] - 100;
    }
  }

  // Combine CSS files into one per type, this is not perfect
  if (fett_get_setting('css_onefile', $theme_key) === 1) {
    uasort($css, 'drupal_sort_css_js');
    $print = array();
    $weight = 0;
    foreach ($css as $name => $style) {
      // Leave  the conditional stylesheets untouched
      if (isset($css[$name]['browsers']['!IE'])) {
        $css[$name]['group'] = 0;
        $css[$name]['weight'] = $weight++;
        $css[$name]['every_page'] = TRUE;
      }
      if ($css[$name]['media'] == 'print') {
        $print[$name] = $css[$name];
        unset($css[$name]);
      }
    }
    $css = array_merge($css, $print);
  }

}
