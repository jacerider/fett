<?php

/**
 * Implements hook_theme().
 *
 * @see fett_theme()
 */
function _fett_theme_megamenu(&$theme){
  $theme['fett_megamenu'] = array(
    'variables' => array(
      'tree' => '',
      'attributes' => array(),
    ),
  );
  $theme['fett_megamenu_offcanvas'] = array(
    'variables' => array(
      'tree' => '',
      'attributes' => array(),
    ),
  );
}

/**
 * Implements template_preprocess_page().
 *
 * @see fett_preprocess_page()
 */
function fett_megamenu_preprocess_page(&$vars){
  if(!empty($vars['main_menu'])){
    $path_fett = drupal_get_path('theme', 'fett');
    $vars['page']['content']['#attached']['css']["$path_fett/assets/scss/_megamenu.scss"] = array(
      'group' => CSS_DEFAULT,
      'every_page' => TRUE,
    );
    $vars['page']['content']['#attached']['js']["$path_fett/assets/js/fett.megamenu.js"] = array(
      'group' => JS_LIBRARY,
      'every_page' => TRUE,
    );
    $source = variable_get('menu_main_links_source', 'main-menu');
    $tree = menu_tree_all_data($source, null, fett_get_setting('megamenu_depth', null, 3));
    _fett_menu_tree_add_active_path($tree);
    $links = menu_tree_output($tree);
    unset($links['#theme_wrappers']);
    $vars['main_nav'] = array(
      '#theme' => 'fett_megamenu',
      '#tree' => $links,
      '#megamenu' => TRUE,
      '#attributes' => array(
        'id' => 'main-nav',
        'class' => array('megamenu'),
      ),
    );
  }
}

/**
 * Rewrite link themes.
 */
function fett_megamenu_alter_link_theme(&$links, $theme = 'megamenu', $depth = 0){
  $depth++;
  if(isset($links['#theme_wrappers'])){
    $links['#theme_wrappers'][0] = 'menu_tree__' . $theme . '_' . $depth;
  }
  $icons_enabled = fett_get_setting('megamenu_icon') || fett_get_setting('megamenu_icon_oc');
  $icons = array();
  foreach (element_children($links) as $key) {
    $link = &$links[$key];
    if($icons_enabled){
      // Icons provided by fawesome_menu.
      if(!empty($link['#localized_options']['fawesome'])){
        $icons[$key] = $link['#localized_options']['fawesome'];
      }
      // Fawesome module text match.
      elseif($icon = fawesome_match($link['#title'])){
        $icons[$key] = $icon['icon'];
      }
    }
    if(is_array($link) && isset($link['#theme'])){
      $link['#theme'] = 'menu_link__' . $theme . '_' . $depth;
      if(!empty($link['#below'])){
        fett_megamenu_alter_link_theme($link['#below'], $theme, $depth);
      }
    }
  }
  if(!empty($icons)){
    foreach (element_children($links) as $key) {
      $link = &$links[$key];
      $link['#icon'] = isset($icons[$key]) ? $icons[$key] : '_default';
    }
  }
}

////////////////////////////////////////////////////////////////////////////////
/// Main Menu
////////////////////////////////////////////////////////////////////////////////

/**
 * Implements hook_process_fett_megamenu().
 */
function fett_process_fett_megamenu(&$vars){
  // Overwrite child theme callbacks added by menu_tree_output().
  fett_megamenu_alter_link_theme($vars['tree']);
}

/**
 * Returns themed menu output.
 */
function fett_fett_megamenu($vars){
  return '<h2 class="element-invisible">Main menu</h2><nav ' . drupal_attributes($vars['attributes']) . '><ul class="mm-1">' . drupal_render($vars['tree']) . '</ul></nav>';
}

/**
 * Second level link wrapper.
 */
function fett_menu_tree__megamenu_2($vars) {
  return '<ul class="mm-2">' . $vars['tree'] . '</ul>';
}

/**
 * Second level link wrapper.
 */
function fett_menu_tree__megamenu_3($vars) {
  return '<ul class="mm-3">' . $vars['tree'] . '</ul>';
}

/**
 * 1st Level Links
 */
function fett_menu_link__megamenu_1($vars) {
  global $language_url;
  $element = $vars['element'];
  $sub_menu = '';
  $element += array(
    '#attributes' => array(),
    '#localized_options' => array(),
    '#classes_array' => array(),
  );
  if(!empty($element['#attributes']['class'])){
    $element['#attributes']['class'] = array_filter($element['#attributes']['class'], function($class) {
      return $class == 'active-trail' || $class == 'active';
    });
  }else{
    $element['#attributes']['class'] = array();
  }
  $element['#attributes']['class'] += $element['#classes_array'];
  if (!empty($element['#below'])) {
    $sub_menu = drupal_render($element['#below']);
    $element['#attributes']['class'][] = 'drop';
  }
  // Append active class.
  if (($element['#href'] == $_GET['q'] || ($element['#href'] == '<front>' && drupal_is_front_page())) &&
    (empty($element['#localized_options']['language']) || $element['#localized_options']['language']->language == $language_url->language)) {
    $element['#attributes']['class'][] = 'active';
  }
  if(!empty($element['#icon']) && fett_get_setting('megamenu_icon')){
    $icon = $element['#icon'] == '_default' ? '' : $element['#icon'];
    if($icon){
      $element['#title'] = '<i class="fa fa-' . $icon . '"></i> <span>' . $element['#title'] . '</span>';
      $element['#localized_options']['html'] = TRUE;
      $element['#localized_options']['attributes']['class'][] = 'has-icon';
    }
  }
  $output = l($element['#title'], $element['#href'], $element['#localized_options']);
  return '<li' . drupal_attributes($element['#attributes']) . '>' . $output . $sub_menu . "</li>\n";
}

/**
 * 2nd Level Links
 */
function fett_menu_link__megamenu_2($vars) {
  $element = $vars['element'];
  $sub_menu = '';
  $element['#attributes']['class'] = array_filter($element['#attributes']['class'], function($class) {
    return $class == 'active-trail' || $class == 'active';
  });
  if ($element['#below']) {
    $sub_menu = drupal_render($element['#below']);
  }
  if(!empty($element['#icon']) && fett_get_setting('megamenu_icon')){
    $icon = $element['#icon'] == '_default' ? 'circle-thin' : $element['#icon'];
    $element['#title'] = '<i class="fa fa-' . $icon . '"></i> ' . $element['#title'];
    $element['#localized_options']['html'] = TRUE;
  }
  $output = l($element['#title'], $element['#href'], $element['#localized_options']);
  return '<li' . drupal_attributes($element['#attributes']) . '>' . $output . $sub_menu . "</li>\n";
}

////////////////////////////////////////////////////////////////////////////////
/// Offcanvas Menu
////////////////////////////////////////////////////////////////////////////////

/**
 * Implements fett_offcanvas_main_nav_alter().
 *
 * @see  fett_offcanvas_element().
 */
function fett_fett_offcanvas_main_nav_alter(&$content, &$effect, &$direction){
  $content['#attributes']['id'] .= '-offcanvas';
  $content['#attributes']['class'][] = 'mp-menu';
  $content['#theme'] = 'fett_megamenu_offcanvas';
  // Overwrite child theme callbacks added by menu_tree_output().
  fett_megamenu_alter_link_theme($content['#tree'], 'megamenu_offcanvas');
}

function fett_offcanvas_parent_storage($title = NULL){
  static $cache;
  if($title){
    $cache = $title;
  }
  return $cache;
}

// /**
//  * Offcanvas Menu
//  */
// function fett_process_fett_megamenu_offcanvas(&$vars){
//   $vars['attributes']['id'] .= '-offcanvas';
//   $vars['attributes']['class'][] = 'mp-menu';
//   // Overwrite child theme callbacks added by menu_tree_output().
//   fett_megamenu_alter_link_theme($vars['tree'], 'megamenu_offcanvas');
// }

function fett_fett_megamenu_offcanvas($vars){
  $icon = 'chevron-right';
  return '<nav ' . drupal_attributes($vars['attributes']) . '><div class="mp-level mp-level-open mp-level-base"><div class="mp-back-icon"><i class="fa fa-' . $icon . '"></i></div><h2>Site Navigation</h2><ul class="mm-1">' . drupal_render($vars['tree']) . '</ul></div></nav>';
}

function fett_menu_tree__megamenu_offcanvas_2($vars) {
  $parent = fett_offcanvas_parent_storage();
  $icon = !empty($parent['#icon']) ? $parent['#icon'] : 'chevron-right';
  return '<div class="mp-level"><div class="mp-back-icon"><i class="fa fa-' . $icon . '"></i></div><h2>'. $parent['#title'] .'</h2><a class="mp-back" href="#">back</a><ul class="mm-2">' . $vars['tree'] . '</ul></div>';
}

function fett_menu_tree__megamenu_offcanvas_3($vars) {
  $parent = fett_offcanvas_parent_storage();
  $icon = !empty($parent['#icon']) ? $parent['#icon'] : 'chevron-right';
  return '<div class="mp-level"><div class="mp-back-icon"><i class="fa fa-' . $icon . '"></i></div><h2>'. $parent['#title'] .'</h2><a class="mp-back" href="#">back</a><ul class="mm-3">' . $vars['tree'] . '</ul></div>';
}

/**
 * 1st Level Links
 */
function fett_menu_link__megamenu_offcanvas_1($vars) {
  $element = $vars['element'];
  $sub_menu = '';
  unset($element['#attributes']['class']);
  if($element['#below']) {
    fett_offcanvas_parent_storage($element);
    $sub_menu = drupal_render($element['#below']);
    $element['#attributes']['class'][] = 'mp-nest';
  }
  if(!empty($element['#icon']) && fett_get_setting('megamenu_icon_oc')){
    $icon = $element['#icon'] == '_default' ? 'circle-thin' : $element['#icon'];
    $element['#title'] = '<i class="fa fa-' . $icon . '"></i> ' . $element['#title'];
    $element['#localized_options']['html'] = TRUE;
  }
  $output = l($element['#title'], $element['#href'], $element['#localized_options']);
  return '<li' . drupal_attributes($element['#attributes']) . '>' . $output . $sub_menu . "</li>\n";
}

/**
 * 2nd Level Links
 */
function fett_menu_link__megamenu_offcanvas_2($vars) {
  return fett_menu_link__megamenu_offcanvas_1($vars);
}

/**
 * Add the active trail indicators into the tree.
 *
 * The data returned by menu_tree_page_data() has link['in_active_trail'] set to
 * TRUE for each menu item in the active trail. The data returned from
 * menu_tree_all_data() does not contain the active trail indicators. This is a
 * helper function that adds it back in.
 *
 * @param array $tree
 *   The menu tree.
 */
function _fett_menu_tree_add_active_path(array &$tree) {
  // Grab any menu item to find the menu_name for this tree.
  $menu_item = current($tree);
  $tree_with_trail = menu_tree_page_data($menu_item['link']['menu_name']);

  // To traverse the original tree down the active trail, we use a pointer.
  $subtree_pointer =& $tree;

  // Find each key in the active trail.
  while ($tree_with_trail) {
    foreach ($tree_with_trail as $key => &$value) {
      if ($tree_with_trail[$key]['link']['in_active_trail'] && isset($subtree_pointer[$key])) {
        // Set the active trail info in the original tree.
        $subtree_pointer[$key]['link']['in_active_trail'] = TRUE;
        // Continue in the subtree, if it exists.
        $tree_with_trail =& $tree_with_trail[$key]['below'];
        $subtree_pointer =& $subtree_pointer[$key]['below'];
        break;
      }
      else {
        unset($tree_with_trail[$key]);
      }
    }
  }
}
