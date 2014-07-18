<?php

function _fett_preprocess_quickbar(&$vars){
  global $user, $theme_key;

  $vars['title'] = '';
  if(drupal_valid_path('admin')){
    $path = 'admin';
  }
  else{
    $path = '<front>';
  }
  $vars['title'] = l(theme('image', array('path'=>drupal_get_path('theme', $theme_key) . '/assets/images/quickbar.png')), $path, array('html'=>TRUE));

  // Use default language
  fett_language_force();

  $role_weights = variable_get('quickbar_role_weights', '');
  $settings = array();

  if (is_array($role_weights)) {
    // Sort roles
    asort($role_weights);

    // Get the user roles
    $roles = user_roles();

    // Get some variables we might use
    $use_machine_names = variable_get('quickbar_use_machine_names', 0);
    if ($use_machine_names) {
      $machine_roles = _quickbar_role_machine_names($roles);
    }

    // Loop through the roles looking for a role that matches the current users
    // role and also has a menu associated with it.
    foreach($role_weights as $rid => $weight) {
      $user_role_index = ($use_machine_names) ? array_search($machine_roles[$rid], $roles) : $rid;
      if (!empty($user->roles[$user_role_index]) && $settings = variable_get('quickbar_extras_settings_' . $rid, array())) {
        break;
      }
    }
  }


  if(!empty($vars['tree'])){
    $tree = $vars['tree'];
    if(!empty($tree[0]['admin'])){
      $links = array();
      foreach($tree[0]['admin'] as $key => $link){
        $below = array();
        if(isset($tree[1][$link['href']])){
          foreach($tree[1][$link['href']] as $child_key => $child){
            $below[] = array(
              '#theme' => 'menu_link__menu_quickbar_editor',
              '#title' => strip_tags($child['title']),
              '#href' => $child['href'],
              '#attributes' => array(),
              '#localized_options' => array('html' => TRUE),
            );
          }
        }
        $links[$key] = array(
          '#theme' => 'menu_link__menu_quickbar_editor',
          '#title' => strip_tags($link['title']),
          '#href' => $link['href'],
          '#attributes' => array(),
          '#localized_options' => array('html' => TRUE),
          '#below' => $below,
        );
      }
      $output = _fett_links($links, TRUE, TRUE, TRUE);
      $attr = array();
      $attr['class'][] = 'left';
      $vars['tree_0']['admin'] = '<ul' . drupal_attributes($attr) . '>' . $output . '</ul>';
    }
    if(!empty($tree[0]['right'])){
      $links = array();
      foreach($tree[0]['right'] as $key => $link){
        if($key == 'username'){
          $links['username'] = array(
            '#theme' => 'menu_link__menu_quickbar_editor',
            '#title' => '<i class="fa fa-user"></i> ' . strip_tags($link['title']),
            '#href' => 'user/' . $user->uid,
            '#attributes' => array(),
            '#localized_options' => array('html' => TRUE),
          );
        }
        else{
          $links[$key] = array(
            '#theme' => 'menu_link__menu_quickbar_editor',
            '#title' => strip_tags($link['title']),
            '#href' => $link['href'],
            '#attributes' => array(),
            '#localized_options' => array('html' => TRUE),
          );
        }
      }
      $output = _fett_links($links, TRUE, TRUE, TRUE);
      $attr = array();
      $attr['class'][] = 'right';
      $vars['tree_0']['right'] = '<ul' . drupal_attributes($attr) . '>' . $output . '</ul>';
    }
  }

  // Use default language close
  fett_language_force();
}
