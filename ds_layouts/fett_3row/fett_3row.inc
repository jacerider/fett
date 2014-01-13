<?php
/**
 * @file
 * Definition of Fett Three row Display Suite layout.
 */

function ds_fett_3row() {
  return array(
    'label' => t('Fett Three row'),
    'regions' => array(
      'header' => t('Header'),
      'ds_content' => t('Content'),
      'footer' => t('Footer'),
    ),
    'image' => TRUE,
  );
}
