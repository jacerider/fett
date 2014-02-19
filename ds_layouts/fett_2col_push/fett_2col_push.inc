<?php
/**
 * @file
 * Definition of Fett Two column Display Suite layout.
 */

function ds_fett_2col_push() {
  return array(
    'label' => t('Fett Two column push'),
    'regions' => array(
      'left' => t('Left'),
      'right' => t('Right'),
    ),
    'image' => TRUE,
  );
}
