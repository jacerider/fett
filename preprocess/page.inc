<?php

function _fett_preprocess_page(&$vars){
  global $language;
  $path_fett = drupal_get_path('theme', 'fett');

  // Add some core CSS files.
  if(module_exists('sonar')){
    foreach(array('core','mixins') as $scss){
      $vars['page']['content']['#attached']['css']["$path_fett/assets/scss/_$scss.scss"] = array(
        'weight' => -100,
        'group' => CSS_THEME,
      );
    }
  }

  // Add Fett core javascript
  $vars['page']['content']['#attached']['js'][$path_fett . '/assets/js/fett.core.js'] = array(
    'every_page' => TRUE,
    'weight' => 1, // After drupal.js which is 0
    'group' => JS_LIBRARY,
  );
  $vars['page']['content']['#attached']['js'][] = array(
    'data' => '//cdnjs.cloudflare.com/ajax/libs/modernizr/2.7.1/modernizr.min.js',
    'type' => 'external',
    'every_page' => TRUE,
    'weight' => -100,
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
        'class' => array('nav-inline'),
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
        'class' => array('nav-inline'),
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

  // Mega-menu
  _fett_megamenu_preprocess_page($vars);

  // Off-canvas
  _fett_offcanvas_preprocess_page($vars);

  // Content area Foundation classes.
  $has_first = !empty($vars['page']['sidebar_first']);
  $has_second = !empty($vars['page']['sidebar_second']);

  $vars['content_classes_array'][] = 'columns';
  $vars['sidebar_first_classes_array'][] = 'columns';
  $vars['sidebar_second_classes_array'][] = 'columns';

  if($has_first && $has_second){
    $vars['content_classes_array'][] = 'large-6';
    $vars['content_classes_array'][] = 'large-push-3';
    $vars['sidebar_first_classes_array'][] = 'large-3';
    $vars['sidebar_first_classes_array'][] = 'large-pull-6';
    $vars['sidebar_second_classes_array'][] = 'large-3';
  }
  elseif($has_first){
    $vars['content_classes_array'][] = 'large-9';
    $vars['content_classes_array'][] = 'large-push-3';
    $vars['sidebar_first_classes_array'][] = 'large-3';
    $vars['sidebar_first_classes_array'][] = 'large-pull-9';
  }
  elseif($has_second){
    $vars['content_classes_array'][] = 'large-9';
    $vars['sidebar_second_classes_array'][] = 'large-3';
  }
  else{
    $vars['content_classes_array'][] = 'large-12';
  }
}
