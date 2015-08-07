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
}

/**
 * Implements template_preprocess_page().
 *
 * @see _fett_preprocess_page()
 */
function _fett_megamenu_preprocess_page(&$vars){
  if(!empty($vars['main_menu']) && fett_get_setting('megamenu')){
    $path_fett = drupal_get_path('theme', 'fett');
    $vars['page']['content']['#attached']['css'][] = "$path_fett/assets/scss/_megamenu.scss";
    $source = variable_get('menu_main_links_source', 'main-menu');
    $vars['main_nav'] = menu_tree_output(menu_tree_all_data($source, null, 3));
    fett_megamenu_alter_link_theme($vars['main_nav']);

    $links = menu_tree_output(menu_tree_all_data($source, null, 3));
    unset($links['#theme_wrappers']);
    fett_megamenu_alter_link_theme($links);
    $vars['main_nav'] = array(
      '#theme' => 'fett_megamenu',
      '#tree' => $links,
      '#attributes' => array(
        'id' => 'main-nav',
        'class' => array('megamenu'),
      ),
    );
  }
}

function fett_megamenu_alter_link_theme(&$links, $depth = 0){
  $depth++;
  if(isset($links['#theme_wrappers'])){
    $links['#theme_wrappers'][0] = 'menu_tree__megamenu_' . $depth;
    $links['#wrapper_attributes']['class'][] = 'menu_tree__megamenu_' . $depth;
  }
  foreach (element_children($links) as $key) {
    $link = &$links[$key];
    if(is_array($link) && isset($link['#theme'])){
      $link['#theme'] = 'menu_link__megamenu_' . $depth;
      if(!empty($link['#below'])){
        fett_megamenu_alter_link_theme($link['#below'], $depth);
      }
    }
  }
}

function fett_fett_megamenu($vars){
  return '<h2 class="element-invisible">Main menu</h2><nav ' . drupal_attributes($vars['attributes']) . '><ul class="mm-1">' . drupal_render($vars['tree']) . '</ul></nav>';
}

function fett_menu_tree__megamenu_2($vars) {
  return '<ul class="mm-2">' . $vars ['tree'] . '</ul>';
}

function fett_menu_link__megamenu_1($vars) {
  $element = $vars ['element'];
  $sub_menu = '';

  if ($element['#below']) {
    $sub_menu = drupal_render($element['#below']);
  }
  unset($element['#attributes']['class']);
  $output = l($element['#title'], $element['#href'], $element['#localized_options']);
  return '<li' . drupal_attributes($element['#attributes']) . '>' . $output . $sub_menu . "</li>\n";
}

function fett_menu_link__megamenu_2($vars) {
  $element = $vars ['element'];
  $sub_menu = '';

  if ($element['#below']) {
    $sub_menu = drupal_render($element['#below']);
  }
  unset($element['#attributes']['class']);
  $output = l($element['#title'], $element['#href'], $element['#localized_options']);
  return '<li' . drupal_attributes($element['#attributes']) . '>' . $output . $sub_menu . "</li>\n";
}
