<?php
/**
 * @file
 * Definition of Fett Two column Display Suite layout.
 */

function ds_fett_2col() {
  return array(
    'label' => t('Fett Two column'),
    'regions' => array(
      'left' => t('Left'),
      'right' => t('Right'),
    ),
    'image' => TRUE,
  );
}
