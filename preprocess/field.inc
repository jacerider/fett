<?php

function _fett_preprocess_field(&$vars){
  $vars['title_attributes_array']['class'][] = 'field-label';

  // Edit classes for taxonomy term reference fields.
  if ($vars['field_type_css'] == 'taxonomy-term-reference') {
    $vars['content_attributes_array']['class'][] = 'comma-separated';
  }

  // Convenience vars.
  $name = $vars['element']['#field_name'];
  $bundle = $vars['element']['#bundle'];
  $mode = $vars['element']['#view_mode'];
  $classes = &$vars['classes_array'];
  $title_classes = &$vars['title_attributes_array']['class'];
  $content_classes = &$vars['content_attributes_array']['class'];
  $item_classes = array();

  // Global field classes.
  $classes[] = 'field-wrapper';
  $content_classes[] = 'field-items';
  $item_classes[] = 'field-item';

  // Add specific classes to targeted fields.
  if(isset($field)) {
    switch ($mode) {
      // All teasers.
      case 'teaser':
        switch ($field) {
          // Teaser read more links.
          case 'node_link':
            $item_classes[] = 'more-link';
            break;
          // Teaser descriptions.
          case 'body':
          case 'field_description':
            $item_classes[] = 'description';
            break;
        }
        break;
    }
  }

  // Apply odd or even classes along with our custom classes to each item.
  foreach ($vars['items'] as $delta => $item) {
    $item_classes[] = $delta % 2 ? 'odd' : 'even';
    $vars['item_attributes_array'][$delta]['class'] = $item_classes;
  }

  // Add class to a specific fields across content types.
  // switch ($vars['element']['#field_name']) {
  //   case 'body':
  //     $vars['classes_array'] = array('body');
  //     break;

  //   case 'field_summary':
  //     $vars['classes_array'][] = 'text-teaser';
  //     break;

  //   case 'field_link':
  //   case 'field_date':
  //     // Replace classes entirely, instead of adding extra.
  //     $vars['classes_array'] = array('text-content');
  //     break;

  //   case 'field_image':
  //     // Replace classes entirely, instead of adding extra.
  //     $vars['classes_array'] = array('image');
  //     break;

  //   default:
  //     break;
  // }
  // Add classes to body based on content type and view mode.
  if ($vars['element']['#field_name'] == 'body') {

    // Add classes to Foobar content type.
    if ($vars['element']['#bundle'] == 'foobar') {
      $vars['classes_array'][] = 'text-secondary';
    }

    // Add classes to other content types with view mode 'teaser';
    elseif ($vars['element']['#view_mode'] == 'teaser') {
      $vars['classes_array'][] = 'text-secondary';
    }

    // The rest is text-content.
    else {
      $vars['classes_array'][] = 'field';
    }
  }
}
