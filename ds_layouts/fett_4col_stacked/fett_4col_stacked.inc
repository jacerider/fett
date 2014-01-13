<?php
/**
 * @file
 * Definition of Fett Four column stacked Display Suite layout.
 */

function ds_fett_4col_stacked() {
  return array(
    'label' => t('Fett Four column stacked'),
    'regions' => array(
      'header' => t('Header'),
      'first' => t('First'),
      'second' => t('Second'),
      'third' => t('Third'),
      'fourth' => t('Fourth'),
      'footer' => t('Footer'),
    ),
    'image' => TRUE,
  );
}
