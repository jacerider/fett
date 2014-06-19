<?php

/**
 * Add Font Awesome icons based on text.
 *
 * @param  boolean  $tooltip
 *   Hide text and place in tooltip
 * @param  boolean  $hide_title
 *   Hide title and just use icon
 */
function fett_icon_link(&$text, &$options, $hide_title, $tooltip = FALSE, $direction = 'bottom'){
  $original_text = $text;
  if(fett_icon($text, $hide_title, FALSE, $direction)){
    if($tooltip){
      $options['attributes']['data-tooltip'] = '';
      $options['attributes']['title'] = $original_text;
      $options['attributes']['class'][] = 'tip-' . $direction;
      $options['attributes']['data-options'] = 'disable_for_touch:true';
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
    $t = strtolower($text);
    $info = TRUE;
    // Check for simple match.
    $icon = isset($icons[$t]) ? $icons[$t] : FALSE;
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
  $icons = &drupal_static(__FUNCTION__);
  if (!isset($icons)) {
    $icons = array(
      t('view')           => 'eye',
      t('edit')           => 'edit',
      t('devel')          => 'code',
      t('log out')        => 'power-off',
      t('my account')     => 'user',
      t('home')           => 'home',
      t('manage display') => 'desktop',
      t('dashboard')      => 'dashboard',
      t('create')         => 'plus-square',
      t('menus')          => 'sitemap',
      t('taxonomy')       => 'tag',
      t('users')          => 'users',
      t('translations')   => 'globe',
      t('translate')      => 'globe',
      t('settings')       => 'cog',
      t('webform')        => 'th-list',
      t('results')        => 'bar-chart-o',
      t('order nodes')    => 'arrows',
      t('order items')    => 'arrows',
      t('delete')         => 'trash-o',
    );

    // Allow others to add their own icons.
    drupal_alter('fett_icons', $icons);
    $icons = array_change_key_case($icons,  CASE_LOWER);
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
