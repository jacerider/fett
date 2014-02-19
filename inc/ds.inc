<?php

/**
 * Implements hook_theme_registry_alter().
 */
function _fett_ds_theme_registry_alter(&$theme_registry) {
  // Add our own preprocess function to entities so we can add default classes
  // to our custom Display Suite layouts.
  $entity_info = entity_get_info();
  foreach ($entity_info as $entity => $info) {
    if (isset($entity_info[$entity]['fieldable']) && $entity_info[$entity]['fieldable']) {

      // User uses user_profile for theming.
      if ($entity == 'user') $entity = 'user_profile';

      // Only add preprocess functions if entity exposes theme function.
      if (isset($theme_registry[$entity])) {
        $theme_registry[$entity]['preprocess functions'][] = 'fett_entity_vars';
      }
    }
  }

  // Support for File Entity.
  if (isset($theme_registry['file_entity'])) {
    $theme_registry['file_entity']['preprocess functions'][] = 'fett_entity_vars';
  }

  // Support for Entity API.
  if (isset($theme_registry['entity'])) {
    $theme_registry['entity']['preprocess functions'][] = 'fett_entity_vars';
  }
}

/**
 * Add default classes to Display Suite regions if none are set.
 *
 * This approach was taken from Display Suite.
 *
 * @see fett_theme_registry_alter()
 */
function fett_entity_vars(&$vars) {
  // Only alter entities that have been rendered by Display Suite.
  if (isset($vars['rendered_by_ds'])) {
    // If Display Suite rendered this, it's safe to assume we have the arguments
    // necessary to grab the layout.
    $layout = ds_get_layout($vars['elements']['#entity_type'], $vars['elements']['#bundle'], $vars['elements']['#view_mode']);

    // Each layout has different regions, only set default classes if none of
    // them have custom classes.
    switch ($layout['layout']) {
      case 'fett_1col':
        if (empty($vars['ds_content_classes'])) {
          $vars['ds_content_classes'] = ' large-12 columns';
          // $vars['classes_array'][] = 'row';
        }
        break;
      case 'fett_2col':
        if (empty($vars['left_classes']) && empty($vars['right_classes'])) {
          $vars['left_classes'] = ' large-6 columns';
          $vars['right_classes'] = ' large-6 columns';
          // $vars['classes_array'][] = 'row';
        }
        break;
      case 'fett_2col_push':
        if (empty($vars['left_classes']) && empty($vars['right_classes'])) {
          if(!empty($vars['left']) && !empty($vars['right'])){
            $vars['left_classes'] = ' large-8 columns';
            $vars['right_classes'] = ' large-4 columns';
          }
          elseif(!empty($vars['left']) ){
            $vars['left_classes'] = ' large-12 columns';
          }
          elseif(!empty($vars['right']) ){
            $vars['right_classes'] = ' large-12 columns';
          }
          // $vars['classes_array'][] = 'row';
        }
        break;
      case 'fett_2col_stacked':
        if (
          empty($vars['header_classes']) && empty($vars['left_classes'])
          && empty($vars['right_classes']) && empty($vars['footer_classes'])
        ) {
          $vars['header_classes'] = ' large-12 columns';
          $vars['left_classes'] = ' large-6 columns';
          $vars['right_classes'] = ' large-6 columns';
          $vars['footer_classes'] = ' large-12 columns';
          // $vars['classes_array'][] = 'row';
        }
        break;
      case 'fett_2col_bricks':
        if (empty($vars['top_classes']) && empty($vars['above_left_classes'])
          && empty($vars['above_right_classes']) && empty($vars['middle_classes'])
          && empty($vars['below_left_classes']) && empty($vars['below_right_classes'])
          && empty($vars['bottom_classes'])
        ) {
          $vars['top_classes'] = ' large-12 columns';
          $vars['above_left_classes'] = ' large-6 columns';
          $vars['above_right_classes'] = ' large-6 columns';
          $vars['middle_classes'] = ' large-12 columns';
          $vars['below_left_classes'] = ' large-6 columns';
          $vars['below_right_classes'] = ' large-6 columns';
          $vars['bottom_classes'] = ' large-12 columns';
          // $vars['classes_array'][] = 'row';
        }
        break;
      case 'fett_3col':
        if (empty($vars['left_classes']) && empty($vars['middle_classes'])
          && empty($vars['right_classes'])
        ) {
          $vars['left_classes'] = ' large-4 columns';
          $vars['middle_classes'] = ' large-4 columns';
          $vars['right_classes'] = ' large-4 columns';
          // $vars['classes_array'][] = 'row';
        }
        break;
      case 'fett_3col_stacked':
        if (
          empty($vars['header_classes']) && empty($vars['left_classes'])
          && empty($vars['middle_classes']) && empty($vars['right_classes'])
          && empty($vars['footer_classes'])
        ) {
          $vars['header_classes'] = ' large-12 columns';
          $vars['left_classes'] = ' large-4 columns';
          $vars['middle_classes'] = ' large-4 columns';
          $vars['right_classes'] = ' large-4 columns';
          $vars['footer_classes'] = ' large-12 columns';
          // $vars['classes_array'][] = 'row';
        }
        break;
      case 'fett_3col_bricks':
        if (empty($vars['top_classes']) && empty($vars['above_left_classes'])
          && empty($vars['above_middle_classes']) && empty($vars['above_right_classes'])
          && empty($vars['middle_classes']) && empty($vars['below_left_classes'])
          && empty($vars['below_middle_classes']) && empty($vars['below_right_classes'])
          && empty($vars['bottom_classes'])
        ) {
          $vars['top_classes'] = ' large-12 columns';
          $vars['above_left_classes'] = ' large-4 columns';
          $vars['above_middle_classes'] = ' large-4 columns';
          $vars['above_right_classes'] = ' large-4 columns';
          $vars['middle_classes'] = ' large-12 columns';
          $vars['below_left_classes'] = ' large-4 columns';
          $vars['below_middle_classes'] = ' large-4 columns';
          $vars['below_right_classes'] = ' large-4 columns';
          $vars['bottom_classes'] = ' large-12 columns';
          // $vars['classes_array'][] = 'row';
        }
        break;
      case 'fett_3row':
        if (empty($vars['header_classes']) && empty($vars['ds_content_classes'])
          && empty($vars['footer_classes'])
        ) {
          $vars['header_classes'] = ' large-12 columns';
          $vars['ds_content_classes'] = ' large-12 columns';
          $vars['footer_classes'] = ' large-12 columns';
          // $vars['classes_array'][] = 'row';
        }
        break;
      case 'fett_4col':
        if (empty($vars['first_classes']) && empty($vars['second_classes'])
          && empty($vars['third_classes']) && empty($vars['fourth_classes'])
        ) {
          $vars['first_classes'] = ' large-3 columns';
          $vars['second_classes'] = ' large-3 columns';
          $vars['third_classes'] = ' large-3 columns';
          $vars['fourth_classes'] = ' large-3 columns';
          // $vars['classes_array'][] = 'row';
        }
        break;
      case 'fett_4col_stacked':
        if (
          empty($vars['header_classes']) && empty($vars['first_classes'])
          && empty($vars['second_classes']) && empty($vars['third_classes'])
          && empty($vars['fourth_classes']) && empty($vars['footer_classes'])
        ) {
          $vars['header_classes'] = ' large-12 columns';
          $vars['first_classes'] = ' large-3 columns';
          $vars['second_classes'] = ' large-3 columns';
          $vars['third_classes'] = ' large-3 columns';
          $vars['fourth_classes'] = ' large-3 columns';
          $vars['footer_classes'] = ' large-12 columns';
          // $vars['classes_array'][] = 'row';
        }
        break;
      case 'fett_4col_bricks':
        if (empty($vars['top_classes']) && empty($vars['above_first_classes'])
          && empty($vars['above_second_classes']) && empty($vars['above_third_classes'])
          && empty($vars['above_fourth_classes']) && empty($vars['middle_classes'])
          && empty($vars['below_first_classes']) && empty($vars['below_second_classes'])
          && empty($vars['below_third_classes']) && empty($vars['below_fourth_classes'])
          && empty($vars['bottom_classes'])
        ) {
          $vars['top_classes'] = ' large-12 columns';
          $vars['above_first_classes'] = ' large-3 columns';
          $vars['above_second_classes'] = ' large-3 columns';
          $vars['above_third_classes'] = ' large-3 columns';
          $vars['above_fourth_classes'] = ' large-3 columns';
          $vars['middle_classes'] = ' large-12 columns';
          $vars['below_first_classes'] = ' large-3 columns';
          $vars['below_second_classes'] = ' large-3 columns';
          $vars['below_third_classes'] = ' large-3 columns';
          $vars['below_fourth_classes'] = ' large-3 columns';
          $vars['bottom_classes'] = ' large-12 columns';
          // $vars['classes_array'][] = 'row';
        }
        break;
    }
  }
}
