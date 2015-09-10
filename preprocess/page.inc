<?php

/**
 * @file
 * Preprocess theme_page.
 */

function fett_preprocess_page(&$vars){
  global $language, $theme_key;
  $path_fett = drupal_get_path('theme', 'fett');

  // Add path to current theme.
  $vars['theme_path'] = drupal_get_path('theme', $theme_key);

  // Add Fett core javascript
  $vars['page']['content']['#attached']['js'][$path_fett . '/assets/js/fett.core.js'] = array(
    'every_page' => TRUE,
    // 'weight' => 1, // After drupal.js which is 0
    'group' => JS_LIBRARY,
  );
  // Modernizr
  $vars['page']['content']['#attached']['js']['//cdnjs.cloudflare.com/ajax/libs/modernizr/2.7.1/modernizr.min.js'] = array(
    'data' => '//cdnjs.cloudflare.com/ajax/libs/modernizr/2.7.1/modernizr.min.js',
    'type' => 'external',
    'every_page' => TRUE,
    'weight' => -100,
    'group' => JS_LIBRARY,
  );
  // Fastclick
  $vars['page']['content']['#attached']['js'][$path_fett . '/libraries/fastclick/fastclick.js'] = array(
    'every_page' => TRUE,
    'weight' => -99, // After drupal.js which is 0
    'group' => JS_LIBRARY,
  );

  // Primary Navigation
  if(!empty($vars['main_menu'])){
    $vars['main_nav'] = array(
      '#theme' => 'links__system_main_menu',
      '#links' => $vars['main_menu'],
      '#is_nav' => TRUE,
      '#attributes' => array(
        'id' => 'main-nav',
      ),
      '#heading' => array(
        'text' => t('Main menu'),
        'level' => 'h2',
        'class' => array('element-invisible'),
      ),
    );
  }

  // Secondary Navigation
  if(!empty($vars['secondary_menu'])){
    $vars['secondary_nav'] = array(
      '#theme' => 'links__system_secondary_menu',
      '#links' => $vars['secondary_menu'],
      '#attributes' => array(
        'id' => 'secondary-nav',
      ),
      '#heading' => array(
        'text' => t('Secondary menu'),
        'level' => 'h2',
        'class' => array('element-invisible'),
      ),
    );
  }

  // Logo
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

  // Linked logo
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

  $vars['copyright'] = date('Y') . ' ' . check_plain($vars['site_name']) . '. ' . t('All rights reserved.');

  if($vars['is_front']){
    $vars['breadcrumb'] = '';
  }

  // Mega-menu
  if(fett_get_setting('megamenu')){
    fett_megamenu_preprocess_page($vars);
  }

  // Off-canvas
  fett_offcanvas_preprocess_page($vars);

  // Content area Foundation classes.
  $has_first = !empty($vars['page']['sidebar_first']);
  $has_second = !empty($vars['page']['sidebar_second']);

  $vars['sidebar_first_classes_array'] = isset($vars['page']['sidebar_first']['#attributes']['class']) ? $vars['page']['sidebar_first']['#attributes']['class'] : array();
  $vars['sidebar_second_classes_array'] = isset($vars['page']['sidebar_second']['#attributes']['class']) ? $vars['page']['sidebar_second']['#attributes']['class'] : array();

  $vars['content_classes_array'][] = 'columns';
  $vars['sidebar_first_classes_array'][] = 'columns';
  $vars['sidebar_second_classes_array'][] = 'columns';

  $content_large = fett_get_setting('content_class_large', NULL, 12);
  $sidebar_large = fett_get_setting('sidebar_class_large', NULL, 3);

  if($has_first && $has_second){
    $content_large = 12;
    $content_large -= $sidebar_large * 2;
    $vars['content_classes_array'][] = 'large-' . $content_large;
    $vars['content_classes_array'][] = 'large-push-' . $sidebar_large;
    $vars['sidebar_first_classes_array'][] = 'large-' . $sidebar_large;
    $vars['sidebar_first_classes_array'][] = 'large-pull-' . $content_large;
    $vars['sidebar_second_classes_array'][] = 'large-' . $sidebar_large;
  }
  elseif($has_first){
    $content_large = 12;
    $content_large -= $sidebar_large;
    $vars['content_classes_array'][] = 'large-' . $content_large;
    $vars['content_classes_array'][] = 'large-push-' . $sidebar_large;
    $vars['sidebar_first_classes_array'][] = 'large-' . $sidebar_large;
    $vars['sidebar_first_classes_array'][] = 'large-pull-' . $content_large;
  }
  elseif($has_second){
    $vars['content_classes_array'][] = 'large-' . $content_large;
    $vars['sidebar_second_classes_array'][] = 'large-' . $sidebar_large;
  }
  else{
    $vars['content_classes_array'][] = 'large-' . $content_large;
    $vars['content_classes_array'][] = 'large-centered';
  }
}
