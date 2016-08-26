<?php

use Drupal\Core\Menu\MenuTreeParameters;
use Drupal\Core\Template\Attribute;

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
      $manipulators = array(
        array('callable' => 'menu.default_tree_manipulators:checkAccess'),
        array('callable' => 'menu.default_tree_manipulators:generateIndexAndSort'),
      );
      $mobile_menu = $menu_tree->build($menu_tree->transform($tree, $manipulators));
      $mobile_menu['#attached']['library'][] = 'fett/fett.mobile_menu';
      $mobile_menu['#theme'] = 'menu__mobile_menu';
      $mobile_menu['#attributes']['class'][] = 'mobile-menu';
      $mobile_menu['#attributes']['data-depth'] = count(array_filter($active_trail)) - 1;
      $link_attributes['class'][] = $config['mobile_menu_breakpoint'];
      fett_offcanvas_add($mobile_menu, [
        'link_text' => $config['mobile_menu_link_text'],
        'position' => $config['mobile_menu_position'],
        'link_attributes' => $link_attributes,
      ]);
    }
  }
}

function fett_preprocess_menu__mobile_menu(&$vars) {
  fett_mobile_menu_append_parent($vars['items']);
  // dsm($vars['items']);
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
