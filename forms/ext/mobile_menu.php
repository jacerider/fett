<?php

/**
 * @file
 * Generate form elements for the Mobile Menu settings.
 */

use \Drupal\block\Entity\Block;
use Drupal\Component\Utility\Unicode;

// Menu options
$entity_manager = \Drupal::entityManager();
$menus = $entity_manager->getStorage('menu')->loadMultiple();
if (!empty($menus)) {
  foreach ($menus as $menu) {
    $menu_options[$menu->id()] = $menu->label();
  }
}
else {
  $menu_options['bummer'] = '-- no menus are available --';
}

// Breakpoint options
$mobile_menu_breakpoint_group = theme_get_setting('settings.mobile_menu_breakpoint_group', $theme);
$mobile_menu_breakpoints = $breakpoints[$mobile_menu_breakpoint_group];
$rmb_group_options = array();
foreach ($mobile_menu_breakpoints as $rmb_key => $rmb_value) {
  $rmb_group_options['show-for-' . $rmb_value->getLabel()] = 'Show for ' . $rmb_value->getLabel() . ' screen or larger';
  $rmb_group_options['hide-for-' . $rmb_value->getLabel()] = 'Hide for ' . $rmb_value->getLabel() . ' screen or larger';
}

$form['mobile_menu'] = array(
  '#type' => 'details',
  '#title' => t('Mobile Menu'),
  '#group' => 'extension_settings',
  '#description' => t('<h3>Mobile Menu</h3><p>Select a menu and breakpoint group, then a specific breakpoint for the mobile style. You can configure one default style and optionally a mobile style.</p><p>It is recommended to follow a mobile first approach where the <i>mobile style</i> is the one you typically associate with <i>desktop view</i>, and the <i>default style</i> is for small screens such as mobile touch devices.</p>'),
);

$form['mobile_menu']['default_settings'] = array(
  '#type' => 'fieldset',
  '#attributes' => array('class' => array('clearfix')),
);

// Menu
$form['mobile_menu']['default_settings']['settings_mobile_menu'] = array(
  '#type' => 'select',
  '#title' => t('Menu'),
  '#options' => $menu_options,
  '#default_value' => theme_get_setting('settings.mobile_menu', $theme),
);

// Link text
$form['mobile_menu']['default_settings']['settings_mobile_menu_link_text'] = array(
  '#type' => 'textfield',
  '#title' => t('Link Text'),
  '#default_value' => theme_get_setting('settings.mobile_menu_link_text', $theme),
  '#description' => t('The text to be placed within the link that will trigger the offcanvas element.'),
);

// Link text
$form['mobile_menu']['default_settings']['settings_mobile_menu_position'] = array(
  '#type' => 'select',
  '#title' => t('Offcanvas Position'),
  '#options' => ['left' => t('Left'), 'right' => t('Right')],
  '#default_value' => theme_get_setting('settings.mobile_menu_position', $theme),
);

// Breakpoints group
$form['mobile_menu']['default_settings']['settings_mobile_menu_breakpoint_group'] = array(
  '#type' => 'select',
  '#title' => t('Breakpoint group'),
  '#options' => $breakpoint_options,
  '#default_value' => $mobile_menu_breakpoint_group,
);

// Breakpoint
$form['mobile_menu']['default_settings']['settings_mobile_menu_breakpoint'] = array(
  '#type' => 'select',
  '#title' => t('Breakpoint'),
  '#options' => $rmb_group_options,
  '#default_value' => theme_get_setting('settings.mobile_menu_breakpoint', $theme),
  '#states' => array(
    'enabled' => array('select[name="settings_mobile_menu_breakpoint_group"]' => array('value' => $mobile_menu_breakpoint_group)),
  ),
);

// Change message
$form['mobile_menu']['default_settings']['mobile_menu_breakpoint_group_haschanged'] = array(
  '#type' => 'container',
  '#markup' => t('<em>Save the extension settings to change the breakpoint group and update breakpoint options.</em>'),
  '#attributes' => array('class' => array('warning', 'messages', 'messages--warning')),
  '#states' => array(
    'invisible' => array('select[name="settings_mobile_menu_breakpoint_group"]' => array('value' => $mobile_menu_breakpoint_group)),
  ),
);
