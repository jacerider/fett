# Fett
##### He's no good to me dead. #####

      _____       __    __
    _/ ____\_____/  |__/  |_
    \   __\/ __ \   __\   __\
     |  | \  ___/|  |  |  |
     |__|  \___  >__|  |__|
               \/

### Sub Theme Creation ###

**Never modify the Fett base theme.**

The recommended and easiest way to create a sub theme based on Fett is to use
Drush. Use the "fett" command to start the creation process.

*Example: drush fett [name] [machine_name !OPTIONAL] [description !OPTIONAL]*

### SASS ###

This module is best when utilizing SASS. It has been built to work with the
Sonar module (https://github.com/JaceRider/Sonar). Once installing and enabling
this module you will be able to utilize the full power of SASS in your theme.
If you have Compass installed, Sonar can use Compass to compile your SASS
locally. Otherwise, you can use Sonar's remote SASS compiler.

Adding a new SASS file is the same as adding a CSS file to Drupal. You can use
drupal_add_css() or add the file directly to your theme's .info file.

### jQuery ###

Foundation requires no less than jQuery 1.10. Using the jQuery Update module
(https://drupal.org/project/jquery_update) is the recommended way of updating
Drupal's version of jQuery. Currently, the dev version of this module is the
only one that support 1.10.

### Modernizr.js ###

Modernizr.js is required and is automatically added via CDN. As Modernizr is
a toolkit containing many components it is recommended that a customized version
is used instead.

To add your own version, visit http://modernizr.com/download/ and customize to
your needs. Then place the file so that the path to it is
THEME/assets/js/modernizr.min.js. If done correctly, this file will be
automatically used instead of the CDN version.
