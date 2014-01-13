<?php
/**
 * @file
 * Definition of Fett Two column stacked Display Suite layout.
 */

function ds_fett_2col_stacked() {
  return array(
    'label' => t('Fett Two column stacked'),
    'regions' => array(
      'header' => t('Header'),
      'left' => t('Left'),
      'right' => t('Right'),
      'footer' => t('Footer'),
    ),
    'image' => TRUE,
  );
}
