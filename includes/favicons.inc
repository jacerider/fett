<?php

/**
 * Load the responsive favicons that are valid.
 */
function fett_favicons_load_all_icons() {
  global $theme_key;
  $icons = &drupal_static(__FUNCTION__);
  $key = $theme_key . '_favicons_icons';
  if (!isset($icons)) {
    $tags = _fett_favicons_defaults();
    if ($cached = cache_get($key, 'cache')) {
      $icons = $cached->data;
    }
    else {
      $tags = fett_get_setting('favicons_tags', null, null);
      if(!$tags){
        $tags = _fett_favicons_defaults();
      }
      if (empty($tags)) {
        $icons = array(
          'found' => array(),
          'missing' => array(),
        );
      }
      else {
        $html = implode(PHP_EOL, $tags);
        $icons = _fett_favicons_validate_tags($html);
        if (empty($icons['missing'])) {
          cache_set($key, $icons, 'cache');
        }
      }
    }
  }
  return $icons;
}

function _fett_favicons_defaults(){
  $tags = '<link rel="apple-touch-icon" sizes="57x57" href="/apple-touch-icon-57x57.png">
<link rel="apple-touch-icon" sizes="60x60" href="/apple-touch-icon-60x60.png">
<link rel="apple-touch-icon" sizes="72x72" href="/apple-touch-icon-72x72.png">
<link rel="apple-touch-icon" sizes="76x76" href="/apple-touch-icon-76x76.png">
<link rel="apple-touch-icon" sizes="114x114" href="/apple-touch-icon-114x114.png">
<link rel="apple-touch-icon" sizes="120x120" href="/apple-touch-icon-120x120.png">
<link rel="apple-touch-icon" sizes="144x144" href="/apple-touch-icon-144x144.png">
<link rel="apple-touch-icon" sizes="152x152" href="/apple-touch-icon-152x152.png">
<link rel="apple-touch-icon" sizes="180x180" href="/apple-touch-icon-180x180.png">
<link rel="icon" type="image/png" href="/favicon-32x32.png" sizes="32x32">
<link rel="icon" type="image/png" href="/android-chrome-192x192.png" sizes="192x192">
<link rel="icon" type="image/png" href="/favicon-96x96.png" sizes="96x96">
<link rel="icon" type="image/png" href="/favicon-16x16.png" sizes="16x16">
<link rel="manifest" href="/manifest.json">
<meta name="apple-mobile-web-app-title" content="Fett">
<meta name="application-name" content="Fett">
<meta name="msapplication-TileColor" content="#da532c">
<meta name="msapplication-TileImage" content="/mstile-144x144.png">
<meta name="theme-color" content="#ffffff">';
  $tags = explode(PHP_EOL, $tags);
  return $tags;
}

/**
 * Helper function to check whether responsive favicon files exist and are
 * readable. This function also strips any pasted content that is not a link
 * or a meta tag.
 *
 * @param string $html
 *   html tag
 * @return array $missing_files
 */
function _fett_favicons_validate_tags($html) {
  global $base_path;

  $found = array();
  $missing = array();

  $dom = new DOMDocument();
  $dom->loadHTML($html);

  // DRUPAL_ROOT contains the sub directory of the Drupal install (if present),
  // in our case we do not want this as $file_path already contains this.
  $docroot = preg_replace('/' . preg_quote($base_path, '/') . '$/', '/', DRUPAL_ROOT);

  // Find all the apple touch icons.
  $tags = $dom->getElementsByTagName('link');
  foreach ($tags as $tag) {
    $file_path = _fett_favicons_normalise_path($tag->getAttribute('href'));
    $tag->setAttribute('href', $file_path);

    if (file_exists($docroot . $file_path) && is_readable($docroot . $file_path)) {
      $found[] = $dom->saveXML($tag);
    }
    else {
      $missing[] = $dom->saveXML($tag);
    }
  }

  // Find any Windows 8 meta tags.
  $tags = $dom->getElementsByTagName('meta');
  foreach ($tags as $tag) {
    $name = $tag->getAttribute('name');

    // We only validate the image file.
    if ($name === 'msapplication-TileImage') {
      $file_path = _fett_favicons_normalise_path($tag->getAttribute('content'));
      $tag->setAttribute('content', $file_path);

      if (file_exists($docroot . $file_path) && is_readable($docroot . $file_path)) {
        $found[] = $dom->saveXML($tag);
      }
      else {
        $missing[] = $dom->saveXML($tag);
      }
    }
    // Just add any other meta tags and assume they contain no images.
    else {
      $found[] = $dom->saveXML($tag);
    }
  }

  return array(
    'found' => $found,
    'missing' => $missing,
  );
}

/**
 * Help to normalise the path to the icons.
 *
 * @param $file_path
 *   The filename of the icon.
 * @return string
 *   The full relative path to the icon within public files.
 */
function _fett_favicons_normalise_path($file_path) {
  global $base_path;

  // Remove absolute URLs.
  if (url_is_external($file_path)) {
    $file_path = str_replace($base_path, '', $file_path);
  }

  // There appears to be no sane way of getting a relative path to a file, so
  // this is the best for now.
  // @see https://www.drupal.org/node/837794#comment-9124435
  $wrapper = file_stream_wrapper_get_instance_by_uri('public://');
  if ($wrapper instanceof DrupalLocalStreamWrapper) {
    $tags = fett_get_setting('favicons_tags', null, null);
    $path = !empty($tags) ? $wrapper->getDirectoryPath() . '/' . fett_get_setting('favicons_path', null, 'favicons') : drupal_get_path('theme', 'fett') . '/assets/favicons';
    $relative_path = $path . $file_path;
  }

  return $base_path . $relative_path;
}
