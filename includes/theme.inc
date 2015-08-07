<?php

/**
 * Implements hook_theme().
 */
function fett_theme($existing, $type, $theme, $path) {
  $path_fett = drupal_get_path('theme', 'fett');
  $theme = array();

  // Include offcanvas themes. These should always be included as there is an
  // API for adding these whenever needed.
  require_once($path_fett . '/includes/offcanvas.inc');
  _fett_theme_offcanvas($theme);

  if(fett_get_setting('megamenu')){
    require_once($path_fett . '/includes/megamenu.inc');
    _fett_theme_megamenu($theme);
  }

  return $theme;
}

/**
 * Implements theme_links().
 *
 * @see theme_links();
 */
function fett_links($vars) {
  $links = $vars['links'];
  $attributes = $vars['attributes'];
  $heading = $vars['heading'];
  $is_nav = !empty($vars['is_nav']);
  global $language_url;
  $output = '';

  if (count($links) > 0) {
    // Treat the heading first if it is present to prepend it to the
    // list of links.
    if (!empty($heading)) {
      if (is_string($heading)) {
        // Prepare the array that will be used when the passed heading
        // is a string.
        $heading = array(
          'text' => $heading,
          // Set the default level of the heading.
          'level' => 'h2',
        );
      }
      $output .= '<' . $heading ['level'];
      if (!empty($heading ['class'])) {
        $output .= drupal_attributes(array('class' => $heading ['class']));
      }
      $output .= '>' . check_plain($heading ['text']) . '</' . $heading ['level'] . '>';
    }

    if($is_nav){
      $output .= '<nav' . drupal_attributes($attributes) . '>';
      $output .= '<ul>';
    }
    else{
      $output .= '<ul' . drupal_attributes($attributes) . '>';
    }

    $num_links = count($links);
    $i = 1;

    foreach ($links as $key => $link) {
      $class = array($key);
      if (isset($link ['href']) && ($link ['href'] == $_GET ['q'] || ($link ['href'] == '<front>' && drupal_is_front_page()))
         && (empty($link ['language']) || $link ['language']->language == $language_url->language)) {
        $class [] = 'active';
      }
      $output .= '<li>';

      if (isset($link ['href'])) {
        // Pass in $link as $options, they share the same keys.
        $output .= l($link ['title'], $link ['href'], $link);
      }
      elseif (!empty($link ['title'])) {
        // Some links are actually not links, but we wrap these in <span> for adding title and class attributes.
        if (empty($link ['html'])) {
          $link ['title'] = check_plain($link ['title']);
        }
        $span_attributes = '';
        if (isset($link ['attributes'])) {
          $span_attributes = drupal_attributes($link ['attributes']);
        }
        $output .= '<span' . $span_attributes . '>' . $link ['title'] . '</span>';
      }

      $i++;
      $output .= "</li>\n";
    }

    $output .= '</ul>';
    if($is_nav){
      $output .= '</nav>';
    }
  }

  return $output;
}

/**
 * Implements theme_links() override just for main menu.
 *
 * @see theme_links();
 */
function fett_links__system_main_menu($vars) {
  $vars['is_nav'] = TRUE;
  return fett_links($vars);
}

/**
 * Implements theme_links() override just for secondary menu.
 *
 * @see theme_links();
 */
function fett_links__system_secondary_menu($vars) {
  $vars['is_nav'] = TRUE;
  return fett_links($vars);
}
