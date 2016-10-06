<?php

use Drupal\Core\Menu\MenuTreeParameters;
use Drupal\Core\Template\Attribute;
use Drupal\block\Entity\Block;

/**
 * Implements hook_theme().
 */
function fett_mobile_menu_theme($module_path) {
  return [
    'fett_mobile_menu' => [
      'variables' => [
        'menu' => NULL,
        'header' => NULL,
        'footer' => NULL,
      ],
      'path' => $module_path . '/templates/menu',
    ]
  ];
}

/**
 * Implements hook_preprocess_page().
 */
function fett_mobile_menu_preprocess_page(&$vars, $config) {

  // Process extension settings.
  if (isset($config['enable_extensions']) && $config['enable_extensions'] === 1) {
    if (isset($config['enable_mobile_menu']) && $config['enable_mobile_menu'] === 1 && $config['mobile_menu'] !== 'bummer') {
      $menu_name = $config['mobile_menu'];
      $menu_tree = \Drupal::menuTree();
      $active_trail = \Drupal::service('menu.active_trail')->getActiveTrailIds($menu_name);
      $parameters = new MenuTreeParameters();
      $parameters->setActiveTrail($active_trail)->onlyEnabledLinks();
      $tree = $menu_tree->load($menu_name, $parameters);

      // If a secondary menu has been selected.
      if (!empty($config['mobile_menu_secondary'])) {
        $menu_name_secondary = $config['mobile_menu_secondary'];
        if (empty(array_filter($active_trail))) {
          $active_trail = \Drupal::service('menu.active_trail')->getActiveTrailIds($menu_name_secondary);
        }
        $parameters = new MenuTreeParameters();
        $parameters->setActiveTrail($active_trail)->onlyEnabledLinks();
        $tree += $menu_tree->load($menu_name_secondary, $parameters);
      }

      $manipulators = array(
        array('callable' => 'menu.default_tree_manipulators:checkAccess'),
        array('callable' => 'menu.default_tree_manipulators:generateIndexAndSort'),
      );
      $mobile_menu = $menu_tree->build($menu_tree->transform($tree, $manipulators));

      if (!empty($config['mobile_menu_secondary'])) {
        $mobile_menu['#cache']['tags'][] = 'config:system.menu.' . $config['mobile_menu_secondary'];
        $items = [];
        // Make sure all secondary menu items are appended to list.
        foreach ($mobile_menu['#items'] as $key => $item) {
          if ($item['original_link']->getMenuName() == $config['mobile_menu_secondary']) {
            $items[$key] = $item;
            unset($mobile_menu['#items'][$key]);
          }
        }
        $mobile_menu['#items'] += $items;
      }

      $mobile_menu['#attached']['library'][] = 'fett/fett.mobile_menu';
      $mobile_menu['#theme'] = 'menu__mobile_menu';
      $mobile_menu['#attributes']['class'][] = 'mobile-menu';
      $mobile_menu['#attributes']['data-depth'] = count(array_filter($active_trail)) - 1;
      $link_attributes['class'][] = $config['mobile_menu_breakpoint'];

      $output = [
        '#theme' => 'fett_mobile_menu',
      ];
      $output['#menu'] = $mobile_menu;

      if (!empty($config['mobile_block_header'])) {
        if ($block = Block::load($config['mobile_block_header'])) {
          $output['#header'] = \Drupal::entityManager()->getViewBuilder('block')->view($block);
        }
      }

      if (!empty($config['mobile_block_footer'])) {
        if ($block = Block::load($config['mobile_block_footer'])) {
          $output['#footer'] = \Drupal::entityManager()->getViewBuilder('block')->view($block);
        }
      }

      fett_offcanvas_add($output, [
        'link_text' => $config['mobile_menu_link_text'],
        'position' => $config['mobile_menu_position'],
        'link_attributes' => $link_attributes,
      ]);
    }
  }
}

/**
 * Implements hook_preprocess_block().
 */
function fett_mobile_menu_preprocess_block(&$vars, $config) {
  if (isset($config['enable_extensions']) && $config['enable_extensions'] === 1) {
    if (isset($config['enable_mobile_menu']) && $config['enable_mobile_menu'] === 1 && $config['mobile_menu'] !== 'bummer') {
      if ($config['mobile_menu_breakpoint'] && $vars['base_plugin_id'] == 'system_menu_block' && $vars['derivative_plugin_id'] == $config['mobile_menu']) {
        $breakpoint = $config['mobile_menu_breakpoint'];
        if (strpos($breakpoint, 'hide') !== FALSE) {
          $breakpoint = str_replace('hide', 'show', $breakpoint);
        } else {
          $breakpoint = str_replace('show', 'hide', $breakpoint);
        }
        $vars['attributes']['class'][] = $breakpoint;
      }
    }
  }
}

/**
 * Implements hook_preprocess_menu__mobile_menu().
 */
function fett_preprocess_menu__mobile_menu(&$vars) {
  fett_mobile_menu_append_parent($vars['items']);
}

/**
 * Appends the parent menu item as a child so that it is accessible.
 */
function fett_mobile_menu_append_parent(&$items) {
  foreach ($items as $key => $item) {
    if (!empty($item['below']) && $item['url']->toString()) {
      $parent = $item;
      $parent['below'] = [];
      $parent['is_expanded'] = FALSE;
      $parent['in_active_trail'] = FALSE;
      $parent['attributes'] = new Attribute();
      $items[$key]['below'] = [$key => $parent] + $items[$key]['below'];
      fett_mobile_menu_append_parent($items[$key]['below']);
    }
  }
}
