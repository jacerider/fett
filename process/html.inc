<?php

function fett_process_html(&$vars){
  $start_time = microtime(TRUE);
  // Flatten attributes arrays
  $vars['html_attributes'] = empty($vars['html_attributes_array']) ? '' : drupal_attributes($vars['html_attributes_array']);

  // $rdf_namespaces is kept to maintain backwards compatibility, and because we
  // only want this to print once in html.tpl.php, and not in every conditional
  // comment for IE.
  $vars['rdf_namespaces'] = empty($vars['rdf_namespaces_array']) ? '' : drupal_attributes($vars['rdf_namespaces_array']);

  // Dintenter
  // Only show if krumo has not been invoked.
  require_once(dirname(dirname(__FILE__)) . '/libraries/dindent/Indenter.php');
  $indenter = new \Gajus\Dindent\Indenter();
  if(strpos($vars['page'], 'krumo') === FALSE){
    $vars['page'] = $indenter->indent($vars['page']);
  }
  $vars['page_top'] = $indenter->indent($vars['page_top']);
  $vars['page_bottom'] = $indenter->indent($vars['page_bottom']);
}
