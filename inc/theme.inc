<?php

/**
 * Implements hook_theme().
 */
function fett_theme() {
  $path_fett = drupal_get_path('theme', 'fett');
  $return = array();

  $return['fett_top_bar'] = array(
    'variables' => array(
      'top_bar_classes' => NULL,
      'top_bar_options' => NULL,
      'top_bar_menu_text' => NULL,
      'linked_site_name' => NULL,
      'top_bar_main_menu' => NULL,
      'top_bar_secondary_menu' => NULL
    ),
    'template' => 'fett-top-bar',
    'path' => $path_fett . '/templates',
  );

  $return['fett_menu_link'] = array(
    'variables' => array('link' => NULL),
    'function' => 'theme_fett_menu_link',
  );
  return $return;
}

/**
 * Implements theme_menu_local_tasks().
 */
function fett_menu_local_tasks(&$variables) {
  $output = '';

  if (!empty($variables['primary'])) {
    $variables['primary']['#prefix'] = '<h2 class="element-invisible">' . t('Primary tabs') . '</h2>';
    $variables['primary']['#prefix'] .= '<ul class="button-group">';
    $variables['primary']['#suffix'] = '</ul>';
    $output .= drupal_render($variables['primary']);
  }
  if (!empty($variables['secondary'])) {
    $variables['secondary']['#prefix'] = '<h2 class="element-invisible">' . t('Secondary tabs') . '</h2>';
    $variables['secondary']['#prefix'] .= '<ul class="button-group">';
    $variables['secondary']['#suffix'] = '</ul>';
    $output .= drupal_render($variables['secondary']);
  }

  return $output;
}

/**
 * Implements theme_menu_local_task().
 */
function fett_menu_local_task(&$variables) {
  $link = $variables['element']['#link'];
  $li_class = (!empty($variables['element']['#active']) ? ' class="active"' : '');

  // Add section tab styling
  $link['localized_options']['attributes']['class'] = array('tiny', 'button', 'secondary');

  // Add Font Awesome Icon
  fett_icon_link($link['title'], $link['localized_options'], TRUE, TRUE);
  $link_text = $link['title'];

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
    $link_text = t('!local-task-title!active', array('!local-task-title' => $link['title'], '!active' => $active));
  }

  $output = '';
  $output .= '<li' . $li_class . '>';
  $output .= l($link_text, $link['href'], $link['localized_options']);
  $output .= "</li>\n";
  return  $output;
}

/**
 * Implements theme_field().
 */
function fett_field($vars) {
  $output = '';

  // Render the label, if it's not hidden.
  if (!$vars['label_hidden']) {
    $output .= '<div ' . $vars['title_attributes'] . '>' . $vars['label'] . ':&nbsp;</div>';
  }

  // Edit module requires some extra wrappers to work.
  if (module_exists('edit')) {
    $output .= '<div class="field-items"' . $vars['content_attributes'] . '>';
    foreach ($vars['items'] as $delta => $item) {
      $classes = 'field-item ' . ($delta % 2 ? 'odd' : 'even');
      $output .= '<div class="' . $classes . '"' . $vars['item_attributes'][$delta] . '>' . drupal_render($item) . '</div>';
    }
    $output .= '</div>';
  }
  else {
    $output .= '<div class="field-items"' . $vars['content_attributes'] . '>';
    foreach ($vars['items'] as $item) {
      $output .= drupal_render($item);
    }
    $output .= '</div>';
  }

  // Render the top-level DIV.
  $output = '<div class="' . $vars['classes'] . '"' . $vars['attributes'] . '>' . $output . '</div>';

  return $output;
}

/**
 * Override drupal core messages with foundation alert-box messages.
 * Customize the colors within the _settings.scss file.
 *
 * http://foundation.zurb.com/docs/elements.php#panelEx
 */
function fett_status_messages($variables) {
  $display = $variables['display'];
  $fett_messages_modal = !fett_foundation_js_suppress(FALSE) ? theme_get_setting('fett_messages_modal') : 0;
  $output = '';

  $status_heading = array(
    'error' => t('Error message'),
    'status' => t('Status message'),
    'warning' => t('Warning message'),
  );

  $status_mapping = array(
    'error' => 'alert',
    'status' => 'success',
    'warning' => 'warning'
  );

  foreach (drupal_get_messages($display) as $type => $messages) {
    if (isset($status_mapping[$type])) {
      $output .= "<div data-alert class=\"alert-box $status_mapping[$type]\">\n";
    }
    else {
      $output .= "<div data-alert class=\"alert-box\">\n";
    }

    if (!empty($status_heading[$type])) {
      $output .= '<h2 class="element-invisible">' . $status_heading[$type] . "</h2>\n";
    }

    if(!$fett_messages_modal){
      $output .= '<a href="#" class="close">&times;</a>';
    }

    if (count($messages) > 1) {
      $output .= " <ul class=\"no-bullet\">\n";
      foreach ($messages as $message) {
        $output .= '  <li>' . $message . "</li>\n";
      }
      $output .= " </ul>\n";
    }
    else {
      if(module_exists('fawesome')){
        $messages[0] = '<i class="fa fa-exclamation-triangle pull-left"></i> ' . $messages[0];
      }
      $output .= $messages[0];
    }

    $output .= "</div>\n";
  }

  if ($output != '' && $fett_messages_modal) {
    fett_foundation_add_js('foundation.reveal.js');
    drupal_add_js(drupal_get_path('theme', 'fett') . '/assets/js/themeMessages.js', array('every_page' => TRUE));

    $output = '<div id="status-messages" class="reveal-modal" role="alertdialog" data-reveal>'. $output;
    $output .= '<a class="close-reveal-modal">&#215;</a>';
    $output .= "</div>";
  }

  return $output;
}

/**
 * Theme the form element, add the error, when one occured.
 */
function fett_ife_form_element($variables) {
  $output = '';
  $output = $variables['element']['#children'];

  if (isset($variables['element']['#id'])) {
    $error = ife_errors('get', $variables['element']['#id']);

    if (!empty($error)) {
      if(module_exists('fawesome')){
        $error = '<i class="fa fa-exclamation-circle"></i> ' . $error;
      }
      $output .= '<div data-alert class="alert-box warning messages-inline">' . $error . '<a href="#" class="close">&times;</a></div>';
    }
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
    $breadcrumbs .= '<li class="current"><a href="#">' . $title. '</a></li>';
    $breadcrumbs .= '</ul>';

    return $breadcrumbs;
  }
}

/**
 * Replace Drupal pagers with Foundation pagers.
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

/**
 * Implements theme_links() targeting the main menu specifically.
 * Formats links for Top Bar http://foundation.zurb.com/docs/components/top-bar.html
 */
function fett_links__topbar_main_menu($vars) {
  // We need to fetch the links ourselves because we need the entire tree.
  $links = menu_tree_output(menu_tree_all_data(variable_get('menu_main_links_source', 'main-menu')));
  $output = _fett_links($links, TRUE);
  $vars['attributes']['class'][] = 'left';

  return '<ul' . drupal_attributes($vars['attributes']) . '>' . $output . '</ul>';
}

/**
 * Implements theme_links() targeting the secondary menu specifically.
 * Formats links for Top Bar http://foundation.zurb.com/docs/components/top-bar.html
 */
function fett_links__topbar_secondary_menu($vars) {
  // We need to fetch the links ourselves because we need the entire tree.
  $links = menu_tree_output(menu_tree_all_data(variable_get('menu_secondary_links_source', 'user-menu')));
  $output = _fett_links($links, TRUE);
  $vars['attributes']['class'][] = 'right';

  return '<ul' . drupal_attributes($vars['attributes']) . '>' . $output . '</ul>';
}

/**
 * Helper function to output a Drupal menu as a Foundation Top Bar.
 *
 * @param array
 *   An array of menu links.
 *
 * @return string
 *   A rendered list of links, with no <ul> or <ol> wrapper.
 *
 * @see fett_links__system_main_menu()
 * @see fett_links__system_secondary_menu()
 */
function _fett_links($links, $use_icon = FALSE, $use_tip = FALSE, $force_icon = FALSE) {
  $output = '';
  foreach (element_children($links) as $key) {
    if((theme_get_setting('fett_top_bar_fawesome') && $use_icon) || ($force_icon && $use_icon)){
      $tip = empty($links[$key]['#below']) ? $use_tip : FALSE;
      fett_icon_link($links[$key]['#title'], $links[$key]['#localized_options'], TRUE, $tip);
    }
    $output .= _fett_render_link($links[$key]);
  }

  return $output;
}

/**
 * Helper function to recursively render sub-menus.
 *
 * @param array
 *   An array of menu links.
 *
 * @return string
 *   A rendered list of links, with no <ul> or <ol> wrapper.
 *
 * @see _fett_links()
 */
function _fett_render_link($link) {
  $output = '';

  // This is a duplicate link that won't get the dropdown class and will only
  // show up in small-screen.
  $small_link = $link;

  if (!empty($link['#below'])) {
    $link['#attributes']['class'][] = 'has-dropdown';
  }

  if(!empty($link['#original_link']['mlid'])){
    $link['#attributes']['class'][] = 'mlid-' . $link['#original_link']['mlid'];
  }

  // Render top level and make sure we have an actual link.
  if (!empty($link['#href'])) {
    $rendered_link = NULL;

    // Foundation offers some of the same functionality as Special Menu Items;
    // ie: Dividers and Labels in the top bar. So let's make sure that we
    // render them the Foundation way.
    if (module_exists('special_menu_items')) {
      if ($link['#href'] === '<nolink>') {
        $rendered_link = '<label>' . $link['#title'] . '</label>';
      }
      else if ($link['#href'] === '<separator>') {
        $link['#attributes']['class'][] = 'divider';
        $rendered_link = '';
      }
    }

    if (!isset($rendered_link)) {
      $rendered_link = theme('fett_menu_link', array('link' => $link));
    }

    // Test for localization options and apply them if they exist.
    if (isset($link['#localized_options']['attributes']) && is_array($link['#localized_options']['attributes'])) {
      $link['#attributes'] = drupal_array_merge_deep($link['#attributes'], $link['#localized_options']['attributes']);
    }
    $output .= '<li' . drupal_attributes($link['#attributes']) . '>' . $rendered_link;

    if (!empty($link['#below'])) {
      // Add repeated link under the dropdown for small-screen.
      $small_link['#attributes']['class'][] = 'show-for-small';
      $sub_menu = '<li' . drupal_attributes($small_link['#attributes']) . '>' . l($link['#title'], $link['#href'], $link['#localized_options']);

      // Build sub nav recursively.
      foreach ($link['#below'] as $sub_link) {
        if (!empty($sub_link['#href'])) {
          fett_icon_link($sub_link['#title'], $sub_link['#localized_options']);
          $sub_menu .= _fett_render_link($sub_link);
        }
      }

      $output .= '<ul class="dropdown">' . $sub_menu . '</ul>';
    }

    $output .=  '</li>';
  }

  return $output;
}

/**
 * Theme function to render a single top bar menu link.
 */
function theme_fett_menu_link($vars) {
  $link = $vars['link'];
  return l($link['#title'], $link['#href'], $link['#localized_options']);
}
