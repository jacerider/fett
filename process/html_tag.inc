<?php

function _fett_process_html_tag(&$vars){
  if (theme_get_setting('html_tags')) {
    $el = &$vars['element'];

    // Remove type="..." and CDATA prefix/suffix.
    unset($el['#attributes']['type'], $el['#value_prefix'], $el['#value_suffix']);

    // Remove media="all" but leave others unaffected.
    if (isset($el['#attributes']['media']) && $el['#attributes']['media'] === 'all') {
      unset($el['#attributes']['media']);
    }
  }
}
