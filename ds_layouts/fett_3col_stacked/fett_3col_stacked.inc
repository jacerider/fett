<?php
/**
 * @file
 * Definition of Fett Three column stacked Display Suite layout.
 */

function ds_fett_3col_stacked() {
  return array(
    'label' => t('Fett Three column stacked'),
    'regions' => array(
      'header' => t('Header'),
      'left' => t('Left'),
      'middle' => t('Middle'),
      'right' => t('Right'),
      'footer' => t('Footer'),
    ),
    'image' => TRUE,
  );
}
