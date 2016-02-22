<?php

/**
 * Implements template_preprocess_page().
 *
 * @see fett_preprocess_page()
 */
function fett_share_preprocess_node(&$vars){
  $node = $vars['node'];
  $enabled_bundles = fett_get_setting('share_node_bundles', NULL, array());
  if($vars['view_mode'] != 'full' || !in_array($node->type, $enabled_bundles)){
    return;
  }

  $path_fett = drupal_get_path('theme', 'fett');
  $share = array();

  $share['#attached']['css']["$path_fett/assets/scss/_share.scss"] = array(
    'group' => CSS_DEFAULT,
  );
  $share['#attached']['js'][] = "$path_fett/assets/js/fett.share.js";
  $share['#markup'] = fett_share_node_render($vars['node']);
  $share['#weight'] = 1000;

  $vars['content']['share'] = $share;
}

function fett_share_node_render($node){
  $icons = fett_share_fawesome();
  $services = fett_share_services();

  $url = url('node/' . $node->nid, array('absolute' => TRUE));
  $title = $node->title;
  $text = variable_get('site_name') . ' - ' . $node->title . ' - ' . $url;
  $media = theme_get_setting('logo');

  $output = array();
  $output[] = '<ul class="share-buttons clearfix">';
  foreach(fett_get_setting('share_services', NULL, array()) as $service){
    $path = fett_share_service_url($service, $url, $title, $text, $media);
    $tooltip = '';
    $attributes = array();
    switch($service){
      case 'print':
        $attributes['onClick'] = 'window.print()';
        $tooltip = t('Print this page');
        break;
      case 'email':
        $attributes['href'] = $path;
        $tooltip = t('Email this page');
        break;
      default:
        $tooltip = t('Share on') . ' ' . $services[$service];
        $attributes['href'] = $path;
        $attributes['class'][] = 'popup';
        break;
    }
    fett_tooltip_add('.share-' . $service . ' a', $tooltip);
    $output[] = '<li class="share-' . $service . '">';
    $output[] = '<a ' . drupal_attributes($attributes) . '>';
    $output[] = '<span class="share-icon">';
    $output[] = '<i class="fa fa-' . $icons[$service] . '"></i>';
    $output[] = '</span>';
    $output[] = '<span class="share-text">'.$services[$service].'</span>';
    $output[] = '</a>';
    $output[] = '</li>';
  }
  $output[] = '</ul>';
  return implode('', $output);
}

function fett_share_fawesome(){
  return array(
    'facebook' => 'facebook',
    'twitter' => 'twitter',
    'tumblr' => 'tumblr',
    'linkedin' => 'linkedin',
    'reddit' => 'reddit',
    'googleplus' => 'google-plus',
    'pinterest' => 'pinterest',
    'pocket' => 'get-pocket',
    'email' => 'envelope',
    'print' => 'print',
  );
}

function fett_share_services(){
  return array(
    'facebook' => 'Facebook',
    'twitter' => 'Twitter',
    'tumblr' => 'Tumblr',
    'linkedin' => 'LinkedIn',
    'reddit' => 'Reddit',
    'googleplus' => 'Google+',
    'pinterest' => 'Pinterest',
    'pocket' => 'Pocket',
    'email' => t('Email'),
    'print' => t('Print'),
  );
}

function fett_share_service_url($service, $url = '', $title = '', $text = '', $media = ''){
  $urls = fett_share_service_urls();
  return format_string($urls[$service], array(
    '!url' => urlencode(check_plain($url)),
    '!title' => urlencode(check_plain($title)),
    '!text' => urlencode(check_plain($text)),
    '!media' => urlencode(check_plain($media)),
  ));
}

function fett_share_service_urls(){
  return array(
    'facebook' => 'https://www.facebook.com/sharer/sharer.php?u=!url',
    'twitter' => 'https://twitter.com/intent/tweet?text=!text',
    'tumblr' => 'http://tumblr.com/share/link?url=!url&title=!title',
    'linkedin' => 'http://www.linkedin.com/shareArticle?mini=true&url=!url&title=!title&summary=!text',
    'reddit' => 'http://www.reddit.com/submit?url=!url&title=!title&text=!text',
    'googleplus' => 'https://plus.google.com/share?url=!text',
    'pinterest' => 'http://pinterest.com/pin/create/button/?url=!url&media=!media&description=!text',
    'pocket' => 'https://getpocket.com/save?url=!url',
    'email' => 'mailto:?subject=!title&body=!text',
    'print' => '',
  );
}
