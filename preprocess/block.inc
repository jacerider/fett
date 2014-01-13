<?php

function _fett_preprocess_block(&$vars){
  // Convenience variable for block headers.
  $title_class = &$vars['title_attributes_array']['class'];

  // Generic block header class.
  $title_class[] = 'block-title';

  // In the header region visually hide block titles.
  if ($vars['block']->region == 'header') {
    $title_class[] = 'element-invisible';
  }

  // Add a unique class for each block for styling.
  $vars['classes_array'][] = $vars['block_html_id'];

  // Add classes based on region.
  switch ($vars['elements']['#block']->region) {
    // Clear blocks in this region
    case 'sidebar_first':
      $vars['classes_array'][] = 'clearfix';
      break;
    // Add a striping class & clear blocks in this region
    case 'sidebar_second':
      $vars['classes_array'][] = 'block-' . $vars['zebra'];
      $vars['classes_array'][] = 'clearfix';
      break;

    case 'header':
      $vars['classes_array'][] = 'header';
      break;

    default;
  }
}
