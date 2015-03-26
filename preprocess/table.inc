<?php

function _fett_preprocess_table(&$vars){
  if(theme_get_setting('fett_responsive_tables')){
    $vars['attributes']['class'][] = 'responsive';
  }
}
