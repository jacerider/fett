<?php
/**
 * @file
 * Definition of Fett Three column Display Suite layout.
 */

function ds_fett_3col() {
  return array(
    'label' => t('Fett Three column'),
    'regions' => array(
      'left' => t('Left'),
      'middle' => t('Middle'),
      'right' => t('Right'),
    ),
    'image' => TRUE,
  );
}
