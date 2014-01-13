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
      // $options['attributes']['class'][] = 'has-tip';
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
function fett_icon(&$text, $hide_title, $tooltip = FALSE, $direction = 'bottom'){
  if(module_exists('fawesome')){
    $t = strtolower($text);
    $icons = array(
      'view' => 'eye',
      'edit' => 'edit',
      'devel' => 'code',
      'log out' => 'power-off',
      'my account' => 'user',
      'home' => 'home',
      'manage display' => 'desktop',
    );

    // Allow others to add their own icons.
    drupal_alter('fett_icons', $icons);

    $icon = isset($icons[$t]) ? $icons[$t] : FALSE;

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
      else{
        $text = ' ' . $text;
      }
      $text = '<i ' . drupal_attributes($attributes) . '></i> ' . $text;
      return TRUE;
    }
  }
  return FALSE;
}
