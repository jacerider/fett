<?php

/**
 * @file
 * Contains \Drupal\fett\Theme\ThemeInfo.
 */

namespace Drupal\fett\Theme;

/**
 * ThemeInfo declares methods used to return theme info
 * for use in themes, mainly the front end.
 */
class ThemeInfo {

  /**
   * The theme of the theme settings object.
   *
   * @var string
   */
  protected $theme;

  /**
   * The data of the theme settings object.
   *
   * @var array
   */
  protected $data;

  /**
   * Constructs a theme info object.
   *
   * @param string $theme
   */
  public function __construct($theme) {
    $this->theme = $theme;
    $this->data = \Drupal::service('theme_handler')->listInfo();
  }

  /**
   * Returns the theme of this theme info object.
   *
   * @return string
   *   The theme of this theme settings object.
   */
  public function getTheme() {
    return $this->theme;
  }

  /**
   * Returns either the whole info array for $this theme or just one key
   * if the $key parameter is set.
   *
   * @param string $key
   *   A string that maps to a key within the theme settings data.
   * @return mixed
   *   The info data that was requested.
   */
  public function getThemeInfo($key = '') {
    if (empty($key)) {
      return $this->data[$this->theme];
    }
    else {
      return isset($this->data[$this->theme]->$key) ? $this->data[$this->theme]->$key : NULL;
    }
  }

}
