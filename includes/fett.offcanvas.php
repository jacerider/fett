<?php

use Drupal\Component\Utility\Html;
use Drupal\Core\Template\Attribute;

/**
 * Implements hook_theme().
 */
function fett_offcanvas_theme($module_path) {
  return [
    // Offcanvas
    'fett_offcanvas' => [
      'variables' => [
        'items' => [],
      ],
      'path' => $module_path . '/templates/offcanvas',
    ],
    'fett_offcanvas_link' => [
      'variables' => [
        'id' => NULL,
        'attributes' => [],
        'item' => [],
      ],
      'path' => $module_path . '/templates/offcanvas',
    ]
  ];
}

/**
 * Implements hook_preprocess_page().
 */
function fett_offcanvas_preprocess_page(&$vars, $config) {

  // fett_offcanvas_add(['#markup' => 'bam bam boom kaboom wham whack slug pow!'], ['link_text' => 'Left']);
  // fett_offcanvas_add(['#markup' => 'bam bam boom kaboom wham whack slug pow!'], ['link_text' => 'Right', 'position' => 'right']);
  // fett_offcanvas_add(['#markup' => 'bam bam boom kaboom wham whack slug pow!'], ['link_text' => 'Top', 'position' => 'top']);
  // fett_offcanvas_add(['#markup' => 'bam bam boom kaboom wham whack slug pow!'], ['link_text' => 'Bottom', 'position' => 'bottom']);

  $vars['offcanvas_links'] = [];
  if ($offcanvas_items = fett_offcanvas_get()) {
    // Wrap the page within a wrapper.
    $vars['prefix']['offcanvas_wrapper'] = [
      '#markup' => '<div class="offcanvas-wrapper">',
      '#weight' => -10005,
    ];
    $vars['suffix']['offcanvas_wrapper'] = [
      '#markup' => '</div>',
      '#weight' => 10000,
    ];
    // Wrap the content with a wrapper.
    $vars['prefix']['offcanvas_push'] = [
      '#markup' => '<div class="offcanvas-push">',
      '#weight' => -10000,
    ];
    $vars['suffix']['offcanvas_push'] = [
      '#markup' => '</div>',
      '#weight' => 10005,
    ];
    // Page gets a scroll class.
    $vars['attributes']['class'][] = 'offcanvas-scroll';

    $attached = [];
    $attached['library'][] = 'fett/fett.offcanvas';
    foreach ($offcanvas_items as $id => $item) {
      $vars['offcanvas_links'][$id] = [
        '#theme' => 'fett_offcanvas_link',
        '#item' => $item,
      ];
      $attached['drupalSettings']['fettOffcanvas']['items'][$id] = $item['options'];
    }
    $vars['prefix']['offcanvas'] = [
      '#theme' => 'fett_offcanvas',
      '#items' => $offcanvas_items,
      '#attached' => $attached,
      '#weight' => -10001,
    ];
  }
}

/**
 * Implements hook_preprocess_fett_offcanvas().
 */
function fett_preprocess_fett_offcanvas(&$vars) {
  $vars['attributes']['class'][] = 'offcanvas-items';
  foreach ($vars['items'] as &$item) {
    $attributes = $item['options']['attributes'];
    $attributes['class'][] = 'offcanvas-item';
    $attributes['class'][] = 'offcanvas-item-' . $item['id'];
    $item['attributes'] = new Attribute($attributes);
  }
}

/**
 * Implements hook_preprocess_fett_offcanvas_link().
 */
function fett_preprocess_fett_offcanvas_link(&$vars) {
  $item = $vars['item'];
  $vars['attributes'] += $item['options']['link_attributes'];
  $vars['attributes']['class'][] = 'offcanvas-link';
  $vars['attributes']['class'][] = 'offcanvas-link-' . $item['id'];
  $vars['attributes']['class'][] = 'js-hide';
  $vars['attributes']['data-id'] = $item['id'];
  $vars['text']['#markup'] = $item['options']['link_text'];
}

/**
 * Adds an offcanvas element to the page.
 */
function fett_offcanvas_add($content, $options = []) {
  $items = &drupal_static(__FUNCTION__, []);
  $id = count($items);
  if (!isset($items[$id])) {
    $options += [
      'link_text' => t('Toggle'),
      'position' => 'left', // left, right, top, bottom
      'attributes' => [],
      'link_attributes' => [],
    ];
    $items[$id] = [
      'id' => $id,
      'content' => $content,
      'options' => $options,
    ];
  }
  return $items;
}

/**
 * Get all offcanvas items.
 */
function fett_offcanvas_get() {
  return drupal_static('fett_offcanvas_add');
}
