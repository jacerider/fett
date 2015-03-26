<?php

function _fett_preprocess_views_view_table(&$vars){
  if(theme_get_setting('fett_responsive_tables')){
    $vars['classes_array'][] = 'responsive';
  }
}
