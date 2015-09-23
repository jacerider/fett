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

/**
 * Implements theme_field().
 */
function fett_field($vars) {
  $output = '';
  if (!$vars['label_hidden']) {
    $output .= '<div ' . $vars['title_attributes'] . '>' . $vars['label'] . (!empty($vars['no_colon']) ? '' : ':') . '&nbsp;</div>';
  }
  if(count($vars['items']) > 1){
    // $output .= '<div class="field-items"' . $vars['content_attributes'] . '>';
  }
  foreach ($vars['items'] as $item) {
    $output .= drupal_render($item);
  }
  if(count($vars['items']) > 1){
    // $output .= '</div>';
  }
  $output = '<div class="' . $vars['classes'] . '"' . $vars['attributes'] . '>' . $output . '</div>';
  return $output;
}

/**
 * Theme function for registration properties.
 *
 * Simple wrapper around theme_field that sets default values and ensures
 * properties render consistently with fields.
 */
function fett_registration_property_field($vars) {
  return fett_field($vars);
}

/**
 * Implements theme_menu_local_tasks().
 */
function fett_menu_local_tasks(&$variables) {
  $output = '';
  if (!empty($variables['primary'])) {
    $variables['primary']['#prefix'] = '<h2 class="element-invisible">' . t('Primary tabs') . '</h2>';
    $variables['primary']['#prefix'] .= '<ul class="primary-tabs button-group">';
    $variables['primary']['#suffix'] = '</ul>';
    $output .= drupal_render($variables['primary']);
  }
  if (!empty($variables['secondary'])) {
    $variables['secondary']['#prefix'] = '<h2 class="element-invisible">' . t('Secondary tabs') . '</h2>';
    $variables['secondary']['#prefix'] .= '<ul class="secondary-tabs button-group">';
    $variables['secondary']['#suffix'] = '</ul>';
    $output .= drupal_render($variables['secondary']);
  }
  if (!empty($output)) {
    $output = '<div class="l-tabs">' . $output . '</div>';
  }
  return $output;
}

/**
 * Implements theme_menu_local_task().
 */
function fett_menu_local_task(&$variables) {
  $link = $variables['element']['#link'];
  $link_text = $link ['title'];
  $li_class = (!empty($variables['element']['#active']) ? ' class="active"' : '');

  // Add section tab styling
  $link['localized_options']['attributes']['class'] = array('tiny', 'button', 'secondary');

  if (!empty($variables['element']['#active'])) {
    // Add text to indicate active tab for non-visual users.
    $active = '<span class="element-invisible">' . t('(active tab)') . '</span>';

    // If the link does not contain HTML already, check_plain() it now.
    // After we set 'html'=TRUE the link will not be sanitized by l().
    if (empty($link['localized_options']['html'])) {
      $link['title'] = check_plain($link['title']);
    }

    $link['localized_options']['attributes']['class'][] = 'disabled';
    $link['localized_options']['html'] = TRUE;
    $link_text = t('!local-task-title!active', array('!local-task-title' => $link_text, '!active' => $active));
  }

  $output = '';
  $output .= '<li' . $li_class . '>';
  $output .= fett_icon_link($link_text, $link['href'], $link['localized_options']);
  $output .= "</li>\n";

  return  $output;
}

/**
 * Implements theme_status_messages().
 */
function fett_status_messages($variables) {
  $display = $variables ['display'];
  $output = '';

  $status_heading = array(
    'status' => t('Status message'),
    'error' => t('Error message'),
    'warning' => t('Warning message'),
  );

  foreach (drupal_get_messages($display) as $type => $messages) {
    $classes = array('message');
    $output .= "<div class=\"alert $type\">\n";
    if (!empty($status_heading [$type])) {
      $output .= '<h2 class="element-invisible">' . $status_heading [$type] . "</h2>\n";
    }
    if (count($messages) > 1) {
      $output .= " <ul>\n";
      foreach ($messages as $message) {
        if(strpos($message, 'krumo') !== FALSE){
          $classes[] = 'has-krumo';
        }
        $output .= '  <li class="'.implode(' ', $classes).'">' . $message . "</li>\n";
      }
      $output .= " </ul>\n";
    }
    else {
      if(strpos(reset($messages), 'krumo') !== FALSE){
        $classes[] = 'has-krumo';
      }
      $output .= '<div class="'.implode(' ', $classes).'">' . reset($messages) . '</div>';
    }
    $output .= "</div>\n";
  }
  return $output;
}

/**
 * Implements theme_breadrumb().
 *
 * Print breadcrumbs as a list, with separators.
 */
function fett_breadcrumb($vars) {
  $breadcrumb = $vars['breadcrumb'];

  if (!empty($breadcrumb)) {
    // Provide a navigational heading to give context for breadcrumb links to
    // screen-reader users. Make the heading invisible with .element-invisible.
    $breadcrumbs = '<h2 class="element-invisible">' . t('You are here') . '</h2>';

    $breadcrumbs .= '<ul class="breadcrumbs">';

    foreach ($breadcrumb as $key => $value) {
      if(empty($value) || !strip_tags($value)) continue;
      $breadcrumbs .= '<li>' . $value . '</li>';
    }

    $title = strip_tags(drupal_get_title());
    if($title) $breadcrumbs .= '<li class="current"><a href="#">' . $title. '</a></li>';
    $breadcrumbs .= '</ul>';

    return $breadcrumbs;
  }
}

/**
 * Implements theme_feed_icon().
 */
function fett_feed_icon($variables) {
  $text = t('Subscribe to !feed-title', array('!feed-title' => $variables ['title']));
  fett_tooltip_add('.feed-link', $text);
  return l('<i class="fa fa-feed feed-link"></i>', $variables ['url'], array('html' => TRUE, 'attributes' => array('class' => array('feed-icon'), 'alt' => $text)));
  if ($image = theme('image', array('path' => 'misc/feed.png', 'width' => 16, 'height' => 16, 'alt' => $text))) {
    return l($image, $variables ['url'], array('html' => TRUE, 'attributes' => array('class' => array('feed-icon'), 'title' => $text)));
  }
}

/**
 * Implements theme_pager().
 */
function fett_pager($vars) {
  $tags = $vars['tags'];
  $element = $vars['element'];
  $parameters = $vars['parameters'];
  $quantity = $vars['quantity'];
  global $pager_page_array, $pager_total;

  // Calculate various markers within this pager piece:
  // Middle is used to "center" pages around the current page.
  $pager_middle = ceil($quantity / 2);
  // Current is the page we are currently paged to.
  $pager_current = $pager_page_array[$element] + 1;
  // First is the first page listed by this pager piece (re-quantify).
  $pager_first = $pager_current - $pager_middle + 1;
  // Last is the last page listed by this pager piece (re-quantify)
  $pager_last = $pager_current + $quantity - $pager_middle;
  // Max is the maximum page number.
  $pager_max = $pager_total[$element];
  // End of marker calculations.

  // Prepare for generation loop.
  $i = $pager_first;
  if ($pager_last > $pager_max) {
    // Adjust "center" if at end of query.
    $i = $i + ($pager_max - $pager_last);
    $pager_last = $pager_max;
  }
  if ($i <= 0) {
    // Adjust "center" if at start of query.
    $pager_last = $pager_last + (1 - $i);
    $i = 1;
  }
  // End of generation loop preparation.

  $li_first = theme('pager_first', array('text' => (isset($tags[0]) ? $tags[0] : t('« first')), 'element' => $element, 'parameters' => $parameters));
  $li_previous = theme('pager_previous', array('text' => (isset($tags[1]) ? $tags[1] : t('‹ previous')), 'element' => $element, 'interval' => 1, 'parameters' => $parameters));
  $li_next = theme('pager_next', array('text' => (isset($tags[3]) ? $tags[3] : t('next ›')), 'element' => $element, 'interval' => 1, 'parameters' => $parameters));
  $li_last = theme('pager_last', array('text' => (isset($tags[4]) ? $tags[4] : t('last »')), 'element' => $element, 'parameters' => $parameters));

  if ($pager_total[$element] > 1) {
    if ($li_first) {
      $items[] = array(
        'class' => array('arrow'),
        'data' => $li_first,
      );
    }
    if ($li_previous) {
      $items[] = array(
        'class' => array('arrow'),
        'data' => $li_previous,
      );
    }

    // When there is more than one page, create the pager list.
    if ($i != $pager_max) {
      if ($i > 1) {
        $items[] = array(
          'class' => array('unavailable'),
          'data' => '<a href="">&hellip;</a>',
        );
      }
      // Now generate the actual pager piece.
      for (; $i <= $pager_last && $i <= $pager_max; $i++) {
        if ($i < $pager_current) {
          $items[] = array(
            'data' => theme('pager_previous', array('text' => $i, 'element' => $element, 'interval' => ($pager_current - $i), 'parameters' => $parameters)),
          );
        }
        if ($i == $pager_current) {
          $items[] = array(
            'class' => array('current'),
            'data' => '<a href="">' . $i . '</a>',
          );
        }
        if ($i > $pager_current) {
          $items[] = array(
            'data' => theme('pager_next', array('text' => $i, 'element' => $element, 'interval' => ($i - $pager_current), 'parameters' => $parameters)),
          );
        }
      }
      if ($i < $pager_max) {
        $items[] = array(
          'class' => array('unavailable'),
          'data' => '<a href="">&hellip;</a>',
        );
      }
    }
    // End generation.
    if ($li_next) {
      $items[] = array(
        'class' => array('arrow'),
        'data' => $li_next,
      );
    }
    if ($li_last) {
      $items[] = array(
        'class' => array('arrow'),
        'data' => $li_last,
      );
    }

    $pager_links = array(
      '#theme' => 'item_list',
      '#items' => $items,
      '#attributes' => array('class' => array('pagination', 'pager')),
    );

    if (theme_get_setting('fett_pager_center')) {
      $pager_links['#prefix'] = '<div class="pagination-centered">';
      $pager_links['#suffix'] = '</div>';
    }

    $pager_links = drupal_render($pager_links);

    return '<h2 class="element-invisible">' . t('Pages') . '</h2>' . $pager_links;
  }
}
