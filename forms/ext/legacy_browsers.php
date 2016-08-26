<?php

/**
 * @file
 * Generate settings for Legacy Browsers.
 */

$form['legacy-browsers'] = array(
  '#type' => 'details',
  '#title' => t('Legacy Browsers'),
  '#group' => 'extension_settings',
);

// Support legacy browsers
//----------------------------------------------------------------------
$form['legacy-browsers']['legacy-browser-polyfills'] = array(
  '#type' => 'container',
  '#markup' => t('<p>By checking this setting poly-fills will be loaded for IE8 and below:</p>
    <dl>
      <dt><b>html5shiv.js:</b></dt><dd>To support HTML5 elements.</dd>
      <dt><b>Respond.js:</b></dt><dd>To support media queries.</dd>
      <dt><b>Selectivrz + YUI3*:</b></dt><dd>To support CSS3.</dd>
    </dl>
    <p>* Selectivrz runs better on YUI3 and Drupal uses jQuery 2 which does not support IE8.</p><p>Without this setting IE8 will display in one column and some styling will fail. The advice is to NOT turn this on, it loads a lot of JavaScript for IE8 and below, it may be better to simply allow those browsers to fail a bit, rather than throwing a huge chunk of JS at them.</p>'),
);

// Show page suggestions.
$form['legacy-browsers']['legacy-browser-polyfills']['settings_legacy_browser_polyfills'] = array(
  '#type' => 'checkbox',
  '#title' => t('Loads poly-fills to support IE8'),
  '#default_value' => theme_get_setting('settings.legacy_browser_polyfills', $theme),
);
