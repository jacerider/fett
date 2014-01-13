<?php

/**
 * Implements hook_css_alter()
 */
function fett_css_alter(&$css) {
  // Remove defaults.css file.
  unset($css[drupal_get_path('module', 'system') . '/system.menus.css']);

  // Aggregate all CSS into one file.
  if(theme_get_setting('fett_css_onefile')){

    $theme = drupal_get_path('theme', 'fett');
    foreach ($css as $path => $value) {
      if ($css[$path]['media'] == 'all') {
        $css[$path]['media'] = 'screen';
      }
    }

    // grab the css and punch it into one file
    // credits to metaltoad http://www.metaltoad.com/blog/drupal-7-taking-control-css-and-js-aggregation
    uasort($css, 'drupal_sort_css_js');
    $i = 0;
    foreach ($css as $name => $style) {
      $css[$name]['weight'] = $i++;
      $css[$name]['group'] = CSS_DEFAULT;
      $css[$name]['every_page'] = FALSE;
    }
  }
}
