<?php

/**
 * @file
 * Generate settings for the off-canvas sidebars.
 */
function fett_settings_offcanvas_form(&$form, $theme_name) {
  $effects = array(
    1 => 'Slide in on top',
    2 => 'Reveal',
    3 => 'Push',
    4 => 'Slide along',
    5 => 'Reverse slide out',
    6 => 'Rotate pusher',
    7 => '3D rotate in',
    8 => '3D rotate out',
    9 => 'Scale down pusher',
    10 => 'Scale Up',
    11 => 'Scale &amp; rotate pusher',
    12 => 'Open door',
    13 => 'Fall down',
    14 => 'Delayed 3D Rotate',
  );
  $sizes = array(
    'for-medium-up' => t('Small'),
    'for-large-up' => t('Medium'),
    'always' => t('Always'),
  );

  $sidebars = array('main_nav' => t('Main Nav'), 'sidebar_first' => t('First Sidebar'),'sidebar_second' => t('Second Sidebar'));
  foreach($sidebars as $key => $name){
    $form[$key] = array(
      '#type'        => 'fieldset',
      '#title'       => $name,
      '#collapsible' => TRUE,
      '#collapsed'   => !fett_get_setting('offcanvas_' .$key),
    );

    $form[$key]['offcanvas_' . $key] = array(
      '#type' => 'select',
      '#empty_option' => t('None'),
      '#options' => $sizes,
      '#title' => t('Use off-canvas sidebars'),
      '#description' => t('Sidebars will be placed in off-canvas areas when viewing on the selected media-query size.'),
      '#default_value' => fett_get_setting('offcanvas_' . $key),
    );

    $form[$key]['offcanvas_' . $key . '_title'] = array(
      '#type' => 'textfield',
      '#title' => t('Title'),
      '#default_value' => fett_get_setting('offcanvas_' . $key . '_title', NULL, '<i class="fa fa-bars"></i> ' . t('In this section')),
      '#description' => t('The title to use for the off-canvas link. Basic HTML (strong, span, em, i) is allowed.'),
      '#states' => array(
        'visible' => array(
          'select[name="offcanvas_' . $key . '"]' => array('!value' => ''),
        ),
      ),
    );

    $form[$key]['offcanvas_' . $key . '_effect'] = array(
      '#type' => 'select',
      '#title' => t('Effect'),
      '#options' => $effects,
      '#default_value' => fett_get_setting('offcanvas_' . $key . '_effect'),
      '#states' => array(
        'visible' => array(
          'select[name="offcanvas_' . $key . '"]' => array('!value' => ''),
        ),
      ),
    );

    $form[$key]['offcanvas_' . $key . '_direction'] = array(
      '#type' => 'select',
      '#title' => t('Effect Direction'),
      '#options' => array('left' => t('Left'), 'right' => t('Right')),
      '#default_value' => fett_get_setting('offcanvas_' . $key . '_direction'),
      '#states' => array(
        'visible' => array(
          'select[name="offcanvas_' . $key . '"]' => array('!value' => ''),
        ),
      ),
    );
  }

}
