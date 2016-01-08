<?php
/**
 * @file
 * Contains functions only needed for drush integration.
 */

/**
 * Implementation of hook_drush_command().
 */
function fett_drush_command() {
  $items = array();

  $items['fett-generate'] = array(
    'description' => 'Create a Fett sub-theme',
    'aliases' => array('fett'),
    'arguments' => array(
      'name'         => 'Your sub-theme name.',
    ),
    'options' => array(
      'machine_name' => 'A machine-readable name for your theme, optional. Machine name must be lowercase only, with underscores instead of spaces.',
      'description'  => 'Your sub-theme description.',
    ),
    'examples' => array(
      'drush ngt "custom theme name"' => 'Create a sub-theme with the default options.',
      'drush ngt "foo bar" "foo_bar" --description="My custom Fett theme."' => 'Create a sub-theme with additional options.',
    ),
  );

  return $items;
}

/**
 * Create a Fett sub-theme.
 */
function drush_fett_generate($name) {
  $description = drush_get_option('description');
  $machine_name = drush_get_option('machine_name');

  if (empty($name)) {
    drush_set_error(dt("Please provide a name for the sub-theme.\nUSAGE:\tdrush ngt [name] --machine_name=[machine_name !OPTIONAL] --description=[description !OPTIONAL]\n"));
    return;
  }

  //Filter everything but letters, numbers, underscores, and hyphens
  $machine_name = !empty($machine_name) ? preg_replace('/[^a-z0-9_-]+/', '', strtolower($machine_name)) : preg_replace('/[^a-z0-9_-]+/', '', strtolower($name));
  // Eliminate hyphens
  $machine_name = str_replace('-', '_', $machine_name);

  // Find theme paths.
  $fett_path = drush_get_context('DRUSH_DRUPAL_ROOT') . '/' . drupal_get_path('theme', 'fett');
  $subtheme_path = dirname($fett_path) . '/' . $machine_name;
  $relative_path = str_replace('fett', $machine_name, drupal_get_path('theme', 'fett'));

  // Make sure bower components are present
  if (!file_exists("$fett_path/bower_components")) {
    drush_set_error(dt("Please run bower install before generating the subtheme.\n"));
    return;
  }

  // Make a fresh copy of the subtheme.
  $s = drush_copy_dir("$fett_path/KAST/", $subtheme_path);
  if (empty($s)) {
    return;
  }

  // Copy Bitters to the subtheme folder
  $b = drush_copy_dir("$fett_path/bower_components/bitters/app/assets/stylesheets/", "$subtheme_path/scss/base", FILE_EXISTS_MERGE);
  if (empty($b)) {
    return;
  }

  // Fix the bitters grid settings neat import (unneeded import).
  drush_op('fett_fix_bitters_neat_import', "$subtheme_path/scss/base/_grid-settings.scss");

  // Rename files and fill in the theme machine name
  drush_op('rename', "$subtheme_path/KAST.info.yml.txt", "$subtheme_path/$machine_name.info.yml");
  drush_op('rename', "$subtheme_path/KAST.libraries.yml", "$subtheme_path/$machine_name.libraries.yml");
  drush_op('rename', "$subtheme_path/KAST.theme", "$subtheme_path/$machine_name.theme");
  drush_op('rename', "$subtheme_path/css/KAST.css", "$subtheme_path/css/$machine_name.css");
  drush_op('rename', "$subtheme_path/scss/KAST.scss", "$subtheme_path/scss/$machine_name.scss");
  drush_op('rename', "$subtheme_path/templates/base/page--front.html.twig.txt", "$subtheme_path/templates/base/page--front.html.twig");

  // Replace KAST in info.yml
  drush_op('fett_file_str_replace', "$subtheme_path/$machine_name.info.yml", 'KAST', "$machine_name");

  // Change the description of the theme
  if (!empty($description)) {
    drush_op('fett_file_str_replace', "$subtheme_path/$machine_name.info.yml", '[Fett] Boba Fett was a Mandalorian warrior and bounty hunter. Not a clone.', "$description");
  }

  // Rename functions in .theme
  drush_op('fett_file_str_replace', "$subtheme_path/$machine_name.theme", 'KAST', "$machine_name");

  // Replace KAST in package.json
  drush_op('fett_file_str_replace', "$subtheme_path/package.json", 'KAST', "$machine_name");

  // Replace KAST in Gulpfile.js
  drush_op('fett_file_str_replace', "$subtheme_path/gulpfile.js", 'KAST', "$machine_name");

  // Replace THEMENAME in KAST.scss
  drush_op('fett_file_str_replace', "$subtheme_path/scss/$machine_name.scss", 'THEMENAME', "$machine_name");

  // Replace KAST in the libraries.yml
  drush_op('fett_file_str_replace', "$subtheme_path/$machine_name.libraries.yml", 'KAST', "$machine_name");

  // Notify user of the newly created theme.
  drush_print(dt("\n!name sub-theme was created in !path. \n",
    array(
      '!name' => $name,
      '!path' => $subtheme_path,
    )
  ));
}

/**
 * Internal helper: Replace strings in a file.
 */
function fett_file_str_replace($file_path, $find, $replace) {
  $file_contents = file_get_contents($file_path);
  $file_contents = str_replace($find, $replace, $file_contents);
  file_put_contents($file_path, $file_contents);
}

/**
  * Internal Helper: Remove first line of file.
  */
function fett_fix_bitters_neat_import($file_path) {
  $file = file($file_path);
  $file[0] = '@import "../../../fett/bower_components/neat/app/assets/stylesheets/neat-helpers";';
  file_put_contents($file_path, $file);
}

/**
 * Implements hook_drush_help().
 */
function fett_drush_help($section) {
  switch ($section) {
    case 'drush:fett-sub-theme':
      return dt("Create a sub-theme based on Fett.");
  }
}
