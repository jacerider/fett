<?php

function _fett_preprocess_quickbar(&$vars){
  global $user;

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

  if($return = quickbar_available()){
    // We need to fetch the links ourselves because we need the entire tree.
    $links = menu_tree_output(menu_tree_all_data($return['menu']));
    $links_right = array();
    foreach (element_properties($links) as $key) {
      $links_right[$key] = $links[$key];
    }
    if(@is_array($settings['menu'])){
      foreach($settings['menu'] as $menu_id => $position){
        $mlid = str_replace('mlid_','',$menu_id);
        if($position == 'right' && isset($links[$mlid])){
          $links_right[$mlid] = $links[$mlid];
          unset($links[$mlid]);
        }
      }
    }

    if(!empty($links)){
      $output = _fett_links($links, TRUE, TRUE);
      $attr = array();
      $attr['class'][] = 'left';
      $vars['tree_0']['admin'] = '<ul' . drupal_attributes($attr) . '>' . $output . '</ul>';
    }

    if(!empty($links_right)){
      if (!empty($settings['show_username'])) {
        $username_prefix = isset($settings['show_username_prefix']) ? $settings['show_username_prefix'] : '<i class="fa fa-user"></i> ';
        $username_suffix = isset($settings['show_username_suffix']) ? $settings['show_username_suffix'] : '!';
        $links_right['user'] = array(
          '#theme' => 'menu_link__menu_quickbar_editor',
          '#title' => $username_prefix . $user->name,
          '#href' => 'user/' . $user->uid,
          '#attributes' => array(),
          '#localized_options' => array('html' => TRUE),
        );
      }
      $output = _fett_links($links_right, TRUE, TRUE);
      $attr = array();
      $attr['class'][] = 'right';
      $vars['tree_0']['right'] = '<ul' . drupal_attributes($attr) . '>' . $output . '</ul>';
    }
  }

  // Use default language close
  fett_language_force();

}
