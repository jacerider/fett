<?php

/**
 * Processes variables to format a video player.
 *
 * @param array $vars
 *   Contains the following information:
 *    - $url
 *    - $style
 *    - $video_data
 *
 * @see video-embed.tpl.php
 */
function fett_preprocess_video_embed_field_embed_code(&$vars) {
  // Get the handler.
  $handler = video_embed_get_handler($vars['url']);
  $vars['handler'] = $handler['name'];

  // Load the style.
  $style = video_embed_field_video_style_load($vars['style']);
  // If there was an issue load in the default style.
  if ($style == FALSE) {
    $style = video_embed_field_video_style_load('normal');
  }
  if (isset($style->data[$vars['handler']])) {
    $vars['style_settings'] = $style->data[$vars['handler']];
  }
  // Safety value for when we add new handlers and there are styles stored.
  else {
    $vars['style_settings'] = $handler['defaults'];
  }

  // Prepare the URL.
  if (!stristr($vars['url'], 'http://') && !stristr($vars['url'], 'https://')) {
    $vars['url'] = 'http://' . $vars['url'];
  }

  // Prepare embed code.
  if ($handler && isset($handler['function']) && function_exists($handler['function'])) {
    $embed_code = call_user_func($handler['function'], $vars['url'], $vars['style_settings']);
    $vars['embed_code'] = '<div class="player flex-video widescreen vimeo">' . drupal_render($embed_code) . '</div>';
  }
  else {
    $vars['embed_code'] = l($vars['url'], $vars['url']);
  }

  // Prepare video data.
  if(isset($vars['video_data'])) $vars['data'] = $vars['video_data'];
  unset($vars['video_data']);
}
