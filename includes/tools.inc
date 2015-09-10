<?php

/**
 * @file
 * Provides frequently used functions that get theme info, settings and
 * other data.
 */

/**
 * Will add Font Awesome icons to any defined text.
 */
function fett_icon_text($text){
  if(function_exists('fawesome_text')){
    $text = fawesome_text($text, $attributes);
  }
  return $text;
}

/**
 * Will convert a link to use Font Awesome icon if icon defined for link text.
 *
 * @see  l
 */
function fett_icon_link($text, $path, array $options = array()){
  if(function_exists('fawesome_text') && $icon = fawesome_match($text)){
    $options['html'] = TRUE;
    if($visibility = fett_get_setting('icon_hide_labels')){
      $cache = &drupal_static(__FUNCTION__, 0);
      $options['attributes']['class'][] = 'tip-' . $cache;
      fett_tooltip_add('.' . 'tip-' . $cache, $text, array('maxWidth' => 400, 'touchDevices' => FALSE, 'delay' => 100));
      $text = '<i class="fa fa-' . $icon['icon'] . '"></i> <span class="hide-' . $visibility . '"> ' . $text . '</span>';
      $cache++;
    }
    else{
      $text = '<i class="fa fa-' . $icon['icon'] . '"></i> ' . $text;
    }
  }
  return l($text, $path, $options);
}

/**
 * Retrieve a setting for the current theme or for a given theme.
 *
 * Fett's stripped down optimized version of theme_get_setting().
 * Why? Because it wayfasterbetter, emphasis on the faster which is really the
 * only valid reason to do something as stupid as this, and it is faster,
 * considerably faster. Doing this wiped 100ms off page generation time.
 *
 * @param $setting_name
 * @param null $theme
 * @see http://api.drupal.org/api/drupal/includes!theme.inc/function/theme_get_setting/7
 */
function fett_get_setting($setting_name, $theme = NULL, $default = NULL) {
  $cache = &drupal_static(__FUNCTION__, array());

  // If no key is given, use the current theme if we can determine it.
  if (!isset($theme)) {
    $theme = !empty($GLOBALS['theme_key']) ? $GLOBALS['theme_key'] : '';
  }

  if (empty($cache[$theme])) {

    // Get the values for the theme-specific settings from the .info files
    if ($theme) {
      global $conf;
      $themes = list_themes();
      $theme_object = $themes[$theme];

      // Create a list which includes the current theme and all its base themes.
      if (isset($theme_object->base_themes)) {
        $theme_keys = array_keys($theme_object->base_themes);
        $theme_keys[] = $theme;
      }
      else {
        $theme_keys = array($theme);
      }

      foreach ($theme_keys as $theme_key) {
        if (!empty($themes[$theme_key]->info['settings'])) {
          $cache[$theme] = $themes[$theme_key]->info['settings'];
        }
      }

      // Get the saved theme-specific settings from the database.
      $cache[$theme] = array_merge($cache[$theme], variable_get('theme_' . $theme . '_settings', array()));
    }
  }

  return isset($cache[$theme][$setting_name]) ? $cache[$theme][$setting_name] : $default;
}

/**
 * Overwrite a theme setting.
 *
 * @param $setting_name
 * @param null $theme
 */
function fett_set_setting($setting_name, $value, $theme = NULL, $default = NULL) {

  // If no key is given, use the current theme if we can determine it.
  if (!isset($theme)) {
    $theme = !empty($GLOBALS['theme_key']) ? $GLOBALS['theme_key'] : '';
  }

  $setting = fett_get_setting($setting_name, $theme, $default);
  $cache = &drupal_static('fett_get_setting', array());
  $cache[$theme][$setting_name] = $value;
}

/**
 * Load Fett theme defaults when necessary.
 *
 * We do this as a function because Foundation changes their components
 * regularly and this allows us to dymaically set the defaults based on the
 * currently existing files.
 */
function _fett_defaults($theme = NULL){
  global $conf;

  // If no key is given, use the current theme if we can determine it.
  if (!isset($theme)) {
    $theme = !empty($GLOBALS['theme_key']) ? $GLOBALS['theme_key'] : '';
  }

  if(!isset($conf["theme_{$theme}_settings"])){
    $settings_path = "admin/appearance/settings/$theme";
    if(current_path() !== $settings_path){
      drupal_set_message(t('You have not yet customized your theme settings. <a href="@url">Visit the settings page.</a>', array('@url' => $settings_path)), 'warning');
    }
    // Include all Foundation CSS/SCSS files by default.
    $components = fett_foundation_css_components();
    foreach(array('orbit','joyride','magellan','pricing-tables','range-slider','reveal','offcanvas','accordion','alert-boxes','panels','progress-bar','side-nav','sub-nav','top-bar','switches','thumbs','icon-bar') as $key){
      unset($components[$key]);
    }
    $conf["theme_{$theme}_settings"]['css_foundation'] = array_keys($components);

    // Include no Foundation JS files by default.
    $conf["theme_{$theme}_settings"]['js_foundation'] = array();
  }
}

/**
 * Return lists of CSS files to unset.
 *
 * This returns a very small amount of data (< 10kb), but is very expensive
 * to get which is why its cached in the database. Without caching the theme
 * settings page takes at least 8 seconds to load if the Unset CSS extension
 * is enabled, and thats no fun.
 *
 * @param $theme_name, usually the active theme.
 */
function fett_get_css_files($theme_name) {
  $styles = &drupal_static(__FUNCTION__, array());
  if (empty($styles)) {
    if ($cache = cache_get('fett_get_css_files')) {
      $styles = $cache->data;
    }
    else {

      // Contrib module
      $module_data = system_rebuild_module_data();
      foreach ($module_data as $module => $data) {
        if ($data->status) {
          if (!empty($data->info['stylesheets'])) {
            foreach ($data->info['stylesheets'] as $media => $content) {
              foreach ($content as $file) {
                $styles[$file] = array(
                  'type' => 'contrib',
                  'source' => $module,
                );
              }
            }
          }
          else{
            if(strpos($data->filename, '/contrib/') !== FALSE || strpos($data->filename, '/community/') !== FALSE){
              $module_path = pathinfo($data->filename, PATHINFO_DIRNAME);
              $module_files = file_scan_directory($module_path, '/.*\.css$/');
              foreach ($module_files as $path => $file) {
                $styles[$file->uri] = array(
                  'type' => 'contrib',
                  'source' => $module,
                );
              }
            }
          }
        }
      }

      // Libraries
      if (module_exists('libraries')) {
        $libraries = libraries_get_libraries();
        $extension = 'css';
        foreach ($libraries as $lib) {
          $files = file_scan_directory($lib, '/\.' . $extension . '$/', array('recurse' => TRUE));
          $libraries[$lib] = $files;
        }
        foreach ($libraries as $lib_key => $library) {
          if (is_array($library) && !empty($library)) {
            foreach ($library as $lib_file) {
              $styles[$lib_file->uri] = array(
                'type' => 'library',
                'source' => $lib_file->uri,
              );
            }
          }
        }
      }

      // Theme info defined files
      include_once DRUPAL_ROOT . '/' . drupal_get_path('theme', 'fett') . '/template.php';
      $info_data = _fett_theme_info_trail($theme_name);
      foreach ($info_data as $provider => $theme_info) {
        foreach ($theme_info as $this_info => $info) {
          if ($this_info == 'info') {
            // Fett defined
            if (isset($info['unset_core'])) {
              foreach ($info['unset_core'] as $module_path => $description) {
                $styles[$module_path] = array(
                  'type' => 'unset_core',
                  'source' => $description,
                );
              }
            }
            // Active theme defined explicit excludes
            if (isset($info['unset_css'])) {
              foreach ($info['unset_css'] as $module_path => $description) {
                $styles[$module_path] = array(
                  'type' => 'user_defined',
                  'source' => $description,
                );
              }
            }
            // Active theme and ancestors, never show in admin
            foreach ($info['stylesheets'] as $media => $stylesheets) {
              foreach ($stylesheets as $file => $path) {
                $styles[$path] = array(
                  'type' => 'theme',
                  'source' => $provider,
                );
              }
            }
          }
        }
      }

      cache_set('fett_get_css_files', $styles, 'cache');
    }
  }

  return $styles;
}
