<?php

/**
 * Add a tooltip to the page.
 *
 * @param $selector
 *   The jQuery selector to attach the tooltip to.
 * @param $content
 *   The HTML markup to place into the tooltip.
 * @param array $options
 *   Options to pass to the tooltip. See URL for list of options.
 *   http://iamceege.github.io/tooltipster/#getting-started
 */
function fett_tooltip_add($selector = NULL, $content = NULL, $options = array()){
  $tooltips = &drupal_static(__FUNCTION__, array());

  if (isset($selector)) {

    $defaults = array(
      'contentAsHTML' => TRUE,
      'theme' => 'fett-tooltip radius',
    );
    if(isset($options['class'])){
      if(!is_array($options['class'])){
        $options['class'] = array($options['class']);
      }
      $defaults['theme'] .= ' ' . implode(' ', $options['class']);
    }
    $options['content'] = $content;
    $options += $defaults;
    $tooltips[$selector] = $options;
  }

  return $tooltips;
}

/**
 * Add tooltips to request.
 */
function fett_tooltip_process(){
  $tooltips = fett_tooltip_add();
  if(!empty($tooltips)){
    drupal_add_library('fett', 'fett.tooltips');
    drupal_add_js(array('fett_tooltip' => $tooltips), 'setting');
  }
}
