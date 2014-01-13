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

  $items['fett-sub-theme'] = array(
    'description' => 'Create a Fett sub-theme',
    'aliases' => array('fett'),
    'arguments' => array(
      'name'         => 'Your sub-theme name.',
      'machine_name' => 'A machine-readable name for your theme, optional only  [a-z, 0-9] ',
    ),
    'options' => array(
      'description'  => 'Your sub-theme description.',
      'machine-name' => '[a-z, 0-9] A machine-readable name for your theme.',
    ),
    'examples' => array(
      'drush fett "custom theme name"' => 'Create a sub-theme with the default options.',
      'drush fett "foo bar" "foo_bar"  --description="My supersweet awesome theme"' => 'Create a sub-theme with additional options.',
    ),
  );

  return $items;
}

/**
 * Create a Zurb fett sub-theme.
 */
function drush_fett_sub_theme($name = NULL, $machine_name = NULL, $description = NULL) {
  if (empty($name)) {
    drush_set_error(dt("Please provide a name for the sub-theme.\nUSAGE:\tdrush fett [name] [machine_name !OPTIONAL] [description !OPTIONAL]\n"));
    return;
  }
  //Filter everything but letters, numbers, underscores, and hyphens
  $machine_name = !empty($machine_name) ? preg_replace('/[^a-z0-9_-]+/', '', strtolower($machine_name)) : preg_replace('/[^a-z0-9_-]+/', '', strtolower($name));
  // Eliminate hyphens
  $machine_name = str_replace('-', '_', $machine_name);

  // Find theme paths.
  $fett_path = drush_locate_root() . '/' . drupal_get_path('theme', 'fett');
  $subtheme_path = dirname($fett_path) . '/' . $machine_name;

  // Make a fresh copy of the subtheme.
  $s = drush_copy_dir("$fett_path/STARTER/", $subtheme_path);
  if (empty($s)) {
    return;
  }

  // Rename files and fill in the theme machine name
  drush_op('rename', "$subtheme_path/STARTER.info.txt", "$subtheme_path/$machine_name.info");
  drush_op('rename', "$subtheme_path/assets/js/theme.js", "$subtheme_path/assets/js/$machine_name.js");
  // Update the .info file
  drush_op('fett_file_str_replace', "$subtheme_path/$machine_name.info", 'Fett Sub-theme Starter', "$name");
  // Change the name of the theme
  if (!empty($description)){
    drush_op('fett_file_str_replace', "$subtheme_path/$machine_name.info", 'Custom sub-theme based on the the Fett base theme.', "$description");
  }
  // Create the template.php file with replaced theme name
  drush_op('fett_file_str_replace', "$subtheme_path/template.php", 'STARTER', "$machine_name");
  // Rename the .info reference to the custom js file
  drush_op('fett_file_str_replace', "$subtheme_path/$machine_name.info", 'theme.js', "$machine_name.js");
  // Rename the Drupal behavior name in the custom js file.
  drush_op('fett_file_str_replace', "$subtheme_path/assets/js/$machine_name.js", 'STARTER', "$machine_name");

  // Notify user of the newly created theme.
  drush_print(dt("\n!name sub-theme was created in !path. \n",
    array(
      '!name' => $name,
      '!path' => $subtheme_path,
    )
  ));
  drush_pm_enable_validate($machine_name);
  drush_pm_enable($machine_name);
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
 * Implements hook_drush_help().
 */
function fett_drush_help($section) {
  switch ($section) {
    case 'drush:fett-sub-theme':
      return dt("Create a Fett custom sub-theme.");
  }
}
