<?php

/**
 * @file
 * Contains \Drupal\fett\Theme\ThemeSettingsConfig.
 */

namespace Drupal\fett\Theme;

use Drupal\Core\Config\Config;
use Drupal\Component\Utility\Unicode;

class ThemeSettingsConfig {

  /**
 * Set config for theme Extension settings.
 * @param array $values
 * @param \Drupal\Core\Config\Config $config
 */
  public function settingsExtensionsConvertToConfig(array $values, Config $config) {
    foreach ($values as $key => $value) {
      if (substr($key, 0, 9) == 'settings_') {
        $config_key = Unicode::substr($key, 9);
        $config->set('settings.' . $config_key, $value);
      }
    }
    $config->save();
  }

  /**
   * Set config for theme Layout settings.
   * @param array $values
   * @param \Drupal\Core\Config\Config $config
   */
  public function settingsLayoutConvertToConfig(array $values, Config $config) {
    foreach ($values as $key => $value) {
      if (substr($key, 0, 9) == 'settings_') {
        $config_key = Unicode::substr($key, 9);
        $config->set('settings.' . $config_key, $value);
      }
      // Delete suggestions config settings. Do not remove all the suggestions
      // setting because later on if the suggestion is recreated there will be
      // settings for it already which is kind of nice for the user should they
      // accidentally delete a suggestion.
      if (substr($key, 0, 18) == 'delete_suggestion_') {
        $delete_suggestion_key = 'settings.suggestion_' . Unicode::substr($key, 18);
        if ($value == 1) {
          $config->clear($delete_suggestion_key, $value);
        }
      }
    }
    $config->save();
  }
}
