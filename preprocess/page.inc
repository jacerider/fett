<?php

function _fett_preprocess_page(&$vars){
  global $user;
  $path_fett = drupal_get_path('theme', 'fett');

  if ($user->uid == 1 && isset($_GET['styleguide']) ){
    $vars['theme_hook_suggestions'][] = 'page__styleguide';
  }

  // Convenience vars
  if (!empty($vars['page']['sidebar_first'])){
    $left = $vars['page']['sidebar_first'];
  }

  if (!empty($vars['page']['sidebar_second'])) {
    $right = $vars['page']['sidebar_second'];
  }

  // Dynamic sidebars
  if (!empty($left) && !empty($right)) {
    $vars['main_grid'] = 'large-6 large-push-3';
    $vars['sidebar_first_grid'] = 'large-3 large-pull-6';
    $vars['sidebar_sec_grid'] = 'large-3';
  } elseif (empty($left) && !empty($right)) {
    $vars['main_grid'] = 'large-9';
    $vars['sidebar_first_grid'] = '';
    $vars['sidebar_sec_grid'] = 'large-3';
  } elseif (!empty($left) && empty($right)) {
    $vars['main_grid'] = 'large-9 large-push-3';
    $vars['sidebar_first_grid'] = 'large-3 large-pull-9';
    $vars['sidebar_sec_grid'] = '';
  } else {
    $vars['main_grid'] = 'large-12';
    $vars['sidebar_first_grid'] = '';
    $vars['sidebar_sec_grid'] = '';
  }

  // Messages in modal.
  $vars['fett_messages_modal'] = !fett_foundation_js_suppress(FALSE) ? theme_get_setting('fett_messages_modal') : 0;

  $vars['logo_img'] = '';
  if (!empty($vars['logo'])) {
    $vars['logo_img'] = theme('image', array(
      'path'  => $vars['logo'],
      'alt'   => strip_tags($vars['site_name']) . ' ' . t('logo'),
      'title' => strip_tags($vars['site_name']) . ' ' . t('Home'),
      'attributes' => array(
        'class' => array('logo'),
      ),
    ));
  }

  $vars['linked_logo']  = '';
  if (!empty($vars['logo_img'])) {
    $vars['linked_logo'] = l($vars['logo_img'], '<front>', array(
      'attributes' => array(
        'rel'   => 'home',
        'title' => strip_tags($vars['site_name']) . ' ' . t('Home'),
        'id'    => 'page-logo',
      ),
      'html' => TRUE,
    ));
  }

  $vars['linked_site_name'] = '';
  if (!empty($vars['site_name'])) {
    $vars['linked_site_name'] = l($vars['site_name'], '<front>', array(
      'attributes' => array(
        'rel'   => 'home',
        'title' => strip_tags($vars['site_name']) . ' ' . t('Home'),
      ),
    ));
  }

  // Menus for alternative header.
  $vars['alt_main_menu'] = '';
  if (!empty($vars['main_menu'])) {
    $vars['alt_main_menu'] = theme('links__system_main_menu', array(
      'links' => $vars['main_menu'],
      'attributes' => array(
        'id' => 'main-menu-links',
        'class' => array('links', 'inline-list', 'clearfix'),
      ),
      'heading' => array(
        'text' => t('Main menu'),
        'level' => 'h2',
        'class' => array('element-invisible'),
      ),
    ));
  }

  $vars['alt_secondary_menu'] = '';
  if (!empty($vars['secondary_menu'])) {
    $vars['alt_secondary_menu'] = theme('links__system_secondary_menu', array(
      'links' => $vars['secondary_menu'],
      'attributes' => array(
        'id' => 'secondary-menu-links',
        'class' => array('links', 'clearfix'),
      ),
      'heading' => array(
        'text' => t('Secondary menu'),
        'level' => 'h2',
        'class' => array('element-invisible'),
      ),
    ));
  }

  // Top bar menus.
  $vars['top_bar_main_menu'] = '';
  if (!empty($vars['main_menu'])) {
    $vars['top_bar_main_menu'] = theme('links__topbar_main_menu', array(
      'links' => $vars['main_menu'],
      'attributes' => array(
        'id' => 'main-menu',
        'class' => array('main-nav'),
      ),
      'heading' => array(
        'text' => t('Main menu'),
        'level' => 'h2',
        'class' => array('element-invisible'),
      ),
    ));
  }

  $vars['top_bar_secondary_menu'] = '';
  if (!empty($vars['secondary_menu'])) {
    $vars['top_bar_secondary_menu'] = theme('links__topbar_secondary_menu', array(
      'links' => $vars['secondary_menu'],
      'attributes' => array(
        'id'    => 'secondary-menu',
        'class' => array('secondary', 'link-list'),
      ),
      'heading' => array(
        'text' => t('Secondary menu'),
        'level' => 'h2',
        'class' => array('element-invisible'),
      ),
    ));
  }

  // Top bar.
  $vars['top_bar'] = '';
  if ($top_bar = theme_get_setting('fett_top_bar_enable')) {
    $top_bar_classes = array();

    if (theme_get_setting('fett_top_bar_grid')) {
      $top_bar_classes[] = 'contain-to-grid';
    }

    if (theme_get_setting('fett_top_bar_sticky')) {
      $top_bar_classes[] = 'sticky';
    }

    if ($top_bar == 2) {
      $top_bar_classes[] = 'show-for-small';
    }

    $vars['top_bar_classes'] = implode(' ', $top_bar_classes);
    $vars['top_bar_menu_text'] = theme_get_setting('fett_top_bar_menu_text');

    $top_bar_options = array();

    if (!theme_get_setting('fett_top_bar_custom_back_text')) {
      $top_bar_options[] = 'custom_back_text:false';
    }

    if ($back_text = theme_get_setting('fett_top_bar_back_text')) {
      if ($back_text !== 'Back') {
        $top_bar_options[] = "back_text:'{$back_text}'";
      }
    }

    if (!theme_get_setting('fett_top_bar_is_hover')) {
      $top_bar_options[] = 'is_hover:false';
    }

    if (!theme_get_setting('fett_top_bar_scrolltop')) {
      $top_bar_options[] = 'scrolltop:false';
    }

    $vars['top_bar_options'] = ' data-options="' . implode('; ', $top_bar_options) . '"';

    $vars['top_bar'] = theme('fett_top_bar', array(
      'top_bar_classes' => $vars['top_bar_classes'],
      'top_bar_options' => $vars['top_bar_options'],
      'top_bar_menu_text' => $vars['top_bar_menu_text'],
      'linked_site_name' => $vars['linked_site_name'],
      'top_bar_main_menu' => $vars['top_bar_main_menu'],
      'top_bar_secondary_menu' => $vars['top_bar_secondary_menu']
    ));
  }

  // Alternative header.
  // This is what will show up if the top bar is disabled or enabled only for
  // mobile.
  if ($vars['alt_header'] = ($top_bar != 1)) {
    // Hide alt header on mobile if using top bar in mobile.
    $vars['alt_header_classes'] = $top_bar == 2 ? ' hide-for-small' : '';
  }
}
