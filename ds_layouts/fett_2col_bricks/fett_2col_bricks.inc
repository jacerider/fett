<?php
/**
 * @file
 * Definition of Fett Two column bricks Display Suite layout.
 */

function ds_fett_2col_bricks() {
  return array(
    'label' => t('Fett Two column bricks'),
    'regions' => array(
      'top' => t('Top'),
      'above_left' => t('Above Left'),
      'above_right' => t('Above Right'),
      'middle' => t('Middle'),
      'below_left' => t('Below Left'),
      'below_right' => t('Below Right'),
      'bottom' => t('Bottom'),
    ),
    'image' => TRUE,
  );
}
