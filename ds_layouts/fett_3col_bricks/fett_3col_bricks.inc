<?php
/**
 * @file
 * Definition of Fett Three column bricks Display Suite layout.
 */

function ds_fett_3col_bricks() {
  return array(
    'label' => t('Fett Three column bricks'),
    'regions' => array(
      'top' => t('Top'),
      'above_left' => t('Above Left'),
      'above_middle' => t('Above Middle'),
      'above_right' => t('Above Right'),
      'middle' => t('Middle'),
      'below_left' => t('Below Left'),
      'below_middle' => t('Below Middle'),
      'below_right' => t('Below Right'),
      'bottom' => t('Bottom'),
    ),
    'image' => TRUE,
  );
}
