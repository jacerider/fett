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
 * @see _fett_preprocess_page()
 */
function _fett_megamenu_preprocess_page(&$vars){
  if(!empty($vars['main_menu']) && fett_get_setting('megamenu')){
    $path_fett = drupal_get_path('theme', 'fett');
    $vars['page']['content']['#attached']['css']["$path_fett/assets/scss/_megamenu.scss"] = array(
      'weight' => -100,
      'group' => CSS_THEME,
    );
    $vars['page']['content']['#attached']['js'][] = "$path_fett/assets/js/fett.megamenu.temp.2.js";
    $vars['page']['content']['#attached']['js'][] = "$path_fett/assets/js/fett.megamenu.temp.js";
    $vars['page']['content']['#attached']['js'][] = "$path_fett/assets/js/fett.megamenu.js";
    $source = variable_get('menu_main_links_source', 'main-menu');
    $links = menu_tree_output(menu_tree_all_data($source, null, 3));
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
  foreach (element_children($links) as $key) {
    $link = &$links[$key];
    if(is_array($link) && isset($link['#theme'])){
      $link['#theme'] = 'menu_link__' . $theme . '_' . $depth;
      if(!empty($link['#below'])){
        fett_megamenu_alter_link_theme($link['#below'], $theme, $depth);
      }
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
  return '<ul class="mm-2">' . $vars ['tree'] . '</ul>';
}

/**
 * Second level link wrapper.
 */
function fett_menu_tree__megamenu_3($vars) {
  return '<ul class="mm-3">' . $vars ['tree'] . '</ul>';
}

/**
 * 1st Level Links
 */
function fett_menu_link__megamenu_1($vars) {
  $element = $vars ['element'];
  $sub_menu = '';
  unset($element['#attributes']['class']);
  if ($element['#below']) {
    $sub_menu = drupal_render($element['#below']);
    $element['#attributes']['class'][] = 'drop';
  }
  $output = l($element['#title'], $element['#href'], $element['#localized_options']);
  return '<li' . drupal_attributes($element['#attributes']) . '>' . $output . $sub_menu . "</li>\n";
}

/**
 * 2nd Level Links
 */
function fett_menu_link__megamenu_2($vars) {
  $element = $vars ['element'];
  $sub_menu = '';
  unset($element['#attributes']['class']);
  if ($element['#below']) {
    $sub_menu = drupal_render($element['#below']);
  }
  $output = l($element['#title'], $element['#href'], $element['#localized_options']);
  return '<li' . drupal_attributes($element['#attributes']) . '>' . $output . $sub_menu . "</li>\n";
}

/**
 * Offcanvas Menu
 */
function fett_process_fett_megamenu_offcanvas(&$vars){
  $vars['attributes']['id'] .= '-offcanvas';
  $vars['attributes']['class'][] = 'mp-menu';
  // Overwrite child theme callbacks added by menu_tree_output().
  fett_megamenu_alter_link_theme($vars['tree'], 'megamenu_offcanvas');
}

function fett_fett_megamenu_offcanvas($vars){
  return '<nav ' . drupal_attributes($vars['attributes']) . '><div class="mp-level mp-level-open"><h2 class="icon icon-world">All Categories</h2><ul class="mm-1">' . drupal_render($vars['tree']) . '</ul></div></nav>';
}

function fett_menu_tree__megamenu_offcanvas_2($vars) {
  return '<div class="mp-level"><h2 class="icon icon-display">Devices</h2><ul class="mm-2">' . $vars ['tree'] . '</ul></div>';
}

function fett_menu_tree__megamenu_offcanvas_3($vars) {
  return '<div class="mp-level"><h2 class="icon icon-display">Devices</h2><ul class="mm-3">' . $vars ['tree'] . '</ul></div>';
}

/**
 * 1st Level Links
 */
function fett_menu_link__megamenu_offcanvas_1($vars) {
  $element = $vars ['element'];
  $sub_menu = '';
  unset($element['#attributes']['class']);
  if ($element['#below']) {
    $sub_menu = drupal_render($element['#below']);
  }
  $output = l($element['#title'], $element['#href'], $element['#localized_options']);
  return '<li' . drupal_attributes($element['#attributes']) . '>' . $output . $sub_menu . "</li>\n";
}

/**
 * 2nd Level Links
 */
function fett_menu_link__megamenu_offcanvas_2($vars) {
  $element = $vars ['element'];
  $sub_menu = '';
  unset($element['#attributes']['class']);
  if ($element['#below']) {
    $sub_menu = drupal_render($element['#below']);
  }
  $output = l($element['#title'], $element['#href'], $element['#localized_options']);
  return '<li' . drupal_attributes($element['#attributes']) . '>' . $output . $sub_menu . "</li>\n";
}
