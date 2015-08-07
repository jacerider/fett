# Fett 2.0
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

Adding a new SASS file is the same as adding a CSS file to Drupal. You can use
drupal_add_css(), #attached, or add the file directly to your theme's .info file.

### jQuery ###

Foundation requires no less than jQuery 1.10. Using the jQuery Update module
(https://drupal.org/project/jquery_update) is the recommended way of updating
Drupal's version of jQuery. Currently, the dev version of this module is the
only one that support 1.10.

### Off-Canvas ###

Adding off-canvas elements is incredibly easy. There are theme settings that
allow easy enabling of off-canvas for the main nav as well as the sidebars.

You can easily add your own items by calling:

    fett_offcanvas_add($content)

This will return a link that will trigger the off-canvas block.
