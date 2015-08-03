<?php

/**
 * Processes variables to format a video player.
 *
 * @param array $variables
 *   Contains the following information:
 *    - $url
 *    - $style
 *    - $video_data
 *
 * @see video-embed.tpl.php
 */
function _fett_preprocess_video_embed_field_embed_code(&$variables) {
  // Get the handler.
  $handler = video_embed_get_handler($variables['url']);
  $variables['handler'] = $handler['name'];

  // Load the style.
  $style = video_embed_field_video_style_load($variables['style']);
  // If there was an issue load in the default style.
  if ($style == FALSE) {
    $style = video_embed_field_video_style_load('normal');
  }
  if (isset($style->data[$variables['handler']])) {
    $variables['style_settings'] = $style->data[$variables['handler']];
  }
  // Safety value for when we add new handlers and there are styles stored.
  else {
    $variables['style_settings'] = $handler['defaults'];
  }

  // Prepare the URL.
  if (!stristr($variables['url'], 'http://') && !stristr($variables['url'], 'https://')) {
    $variables['url'] = 'http://' . $variables['url'];
  }

  // Prepare embed code.
  if ($handler && isset($handler['function']) && function_exists($handler['function'])) {
    $embed_code = call_user_func($handler['function'], $variables['url'], $variables['style_settings']);
    $variables['embed_code'] = '<div class="player flex-video widescreen vimeo">' . drupal_render($embed_code) . '</div>';
  }
  else {
    $variables['embed_code'] = l($variables['url'], $variables['url']);
  }

  // Prepare video data.
  if(isset($variables['video_data'])) $variables['data'] = $variables['video_data'];
  unset($variables['video_data']);
}
