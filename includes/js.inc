<?php

/**
 * @file
 * General Javascript alters.
 */

/**
 * Implements hook_js_alter().
 */
function fett_js_alter(&$javascript) {
  global $theme_key;

  // Combine JS files into one per type, this is a bit mad and
  // we probably shouldn't encourage such things :)
  if (fett_get_setting('js_onefile', $theme_key) === 1) {
    uasort($javascript, 'drupal_sort_css_js');
    $weight = 0;
    foreach ($javascript as $name => $script) {
      $javascript[$name]['group'] = -100;
      $javascript[$name]['weight'] = ++$weight;
      $javascript[$name]['every_page'] = 1;
    }
  }

}
