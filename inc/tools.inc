<?php

/**
 * Add Font Awesome icons based on text.
 *
 * @param  boolean  $tooltip
 *   Hide text and place in tooltip
 * @param  boolean  $hide_title
 *   Hide title and just use icon
 */
function fett_icon_link(&$text, &$options = array(), $hide_title = FALSE, $tooltip = FALSE, $direction = 'bottom'){
  $original_text = $text;
  if($info = fett_icon($text, $hide_title, FALSE, $direction)){
    if($tooltip){
      fett_foundation_add_js('foundation.tooltip.js');
      $options['attributes']['data-tooltip'] = '';
      $options['attributes']['title'] = $original_text;
      $options['attributes']['class'][] = 'tip-' . $direction;
      $options['attributes']['data-options'] = 'disable_for_touch:true';
    }
    $options['html'] = TRUE;
    return $info;
  }
}

/**
 * Add Font Awesome icons based on text while also adding classes to the options.
 *
 * @param  boolean  $tooltip
 *   Hide text and place in tooltip
 * @param  boolean  $hide_title
 *   Hide title and just use icon
 */
function fett_icon_link_with_classes(&$text, &$options = array(), $hide_title = FALSE, $tooltip = FALSE, $direction = 'bottom'){
  if($info = fett_icon_link($text, $options, $hide_title, $tooltip, $direction)){
    if(isset($info['class'])){
      $options['attributes']['class'] = isset($options['attributes']['class']) ? $options['attributes']['class'] : array();
      $options['attributes']['class'] = array_merge($options['attributes']['class'], $info['class']);
    }
    $options['html'] = TRUE;
  }
}

/**
 * Add Font Awesome icons based on text.
 *
 * @param  boolean  $tooltip
 *   Hide text and place in tooltip
 * @param  boolean  $hide_title
 *   Hide title and just use icon
 */
function fett_icon_button(&$text, &$element){
  $original_text = $text;
  if($data = fett_icon($text)){
    if(isset($data['class'])){
      $element['#attributes']['class'] = isset($element['#attributes']['class']) ? $element['#attributes']['class'] : array();
      $element['#attributes']['class'] = array_merge($element['#attributes']['class'], $data['class']);
    }
  }
}

/**
 * Add Font Awesome icons based on text.
 *
 * @param  boolean  $tooltip
 *   Hide text and place in tooltip
 * @param  boolean  $hide_title
 *   Hide title and just use icon
 */
function fett_icon(&$text, $hide_title = FALSE, $tooltip = FALSE, $direction = 'bottom'){
  if(module_exists('fawesome')){
    $icons = fett_icons();
    $t = strtolower(t($text));
    $info = TRUE;
    // Check for simple match.
    $icon = isset($icons[$t]) ? $icons[$t] : FALSE;
    if(is_array($icon) && isset($icon['icon'])){
      $info = $icon;
      $icon = $icon['icon'];
    }
    if(!$icon){
      // Check for complex match
      foreach($icons as $key => $data){
        // Regex values should be defined as arrays.
        if(is_array($data) && !$icon){
          // Check for regex match
          if(preg_match('!' . $key . '!', strtolower($text))){
            $info = $data;
            if(isset($data['icon'])) $icon = $data['icon'];
          }
        }
      }
    }
    if($icon){
      $attributes['class'] = array('fa', 'fa-' . $icon);
      if($tooltip){
        $attributes['data-tooltip'] = '';
        $attributes['class'][] = 'has-tip';
        $attributes['class'][] = 'tip-' . $direction;
        $attributes['title'] = $text;
        $text = '';
      }
      elseif($hide_title){
        $text = '<span><span class="hide-for-medium-up">' . $text . '</span></span>';
      }
      $text = '<i ' . drupal_attributes($attributes) . '></i> ' . $text;
      return $info;
    }
  }
  return FALSE;
}

/**
 * Get Fett icons
 */
function fett_icons(){
  global $theme_key;
  $icons = &drupal_static(__FUNCTION__);
  if (!isset($icons)) {
    $cache_key = 'fett_icons_' . $theme_key;
    if ($cache = cache_get($cache_key)) {
      $icons = $cache->data;
    }
    else {
      $icons = array(
        'view'           => 'eye',
        'edit'           => 'edit',
        'devel'          => 'code',
        'log out'        => 'power-off',
        'my account'     => 'user',
        'home'           => 'home',
        'manage display' => 'desktop',
        'dashboard'      => 'dashboard',
        'create'         => 'plus-square',
        'menus'          => 'sitemap',
        'taxonomy'       => 'tag',
        'users'          => 'users',
        'translations'   => 'globe',
        'translate'      => 'globe',
        'settings'       => 'cog',
        'webform'        => 'th-list',
        'results'        => 'bar-chart-o',
        'order nodes'    => 'arrows',
        'order items'    => 'arrows',
        'delete'         => 'trash-o',
        'nodequeue'      => 'sort',
      );

      foreach(node_type_get_types() as $key => $value){
        $icons[strtolower($value->name)] = 'file-text';
      }

      // Allow others to add their own icons.
      drupal_alter('fett_icons', $icons);
      $icons = array_change_key_case($icons,  CASE_LOWER);

      cache_set($cache_key, $icons, 'cache');
    }
  }
  return $icons;
}

/**
 * Force use of default language.
 */
function fett_language_force(){
  static $current_language;
  if(!isset($current_language)){
    if(module_exists('admin_language') && variable_get('admin_language_translate_toolbar', 1)){
      global $language, $_admin_language;
      // save the current language and activate the administration language...
      $current_language = $language;
      $language = $_admin_language;
    }
  }
  else{
    if(module_exists('admin_language') && variable_get('admin_language_translate_toolbar', 1)){
      global $language, $_admin_language;
      // ...and restore the previous language
      $language = $current_language;
      unset($current_language);
    }
  }
}
