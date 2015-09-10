<?php

/**
 * @file
 * Generate settings for the megamenu.
 */
function fett_settings_megamenu_form(&$form, $theme_name) {

  $form['megamenu'] = array(
    '#type' => 'checkbox',
    '#title' => t('Enable Mega Menu'),
    '#attributes' => array(
      'class' => array('enable-extension'),
    ),
    '#default_value' => fett_get_setting('megamenu'),
    '#description' => t('The main menu will be converted into mega-menu/dropdown ready markup.'),
    '#element_validate' => array('fett_settings_validate_cleanup_children'),
  );

  if(module_exists('fawesome')){
    $form['megamenu_icon'] = array(
      '#type' => 'checkbox',
      '#title' => t('Use icons for full menu'),
      '#default_value' => fett_get_setting('megamenu_icon'),
      '#description' => t('Font Awesome icons will be added to links in the full menu.'),
    );
    $form['megamenu_icon_oc'] = array(
      '#type' => 'checkbox',
      '#title' => t('Use icons for off-canvas menu'),
      '#default_value' => fett_get_setting('megamenu_icon_oc'),
      '#description' => t('Font Awesome icons will be added to links in the off-canvas menu'),
    );
  }

}
