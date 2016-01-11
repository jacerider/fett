# Fett (Gulp, Bourbon, Neat, Bitters) Drupal Theme

## Installation

**Gulp and Bower are required to manage assets.**

First, you will need to install NodeJS.

Install gulp and bower with 'npm install -g gulp bower' from the command line. On some setups, sudo may be required.

From the parent (fett) theme directory, enter 'bower install' in the command line. This will pull in the component assets for Fett. These
are referenced includes from the KAST theme for you - no need to copy them into the KAST/subthemes.

Create a subtheme. See the BUILD A THEME WITH DRUSH section below on how to do that.


## Build a theme with Drush

It is highly encouraged to use Drush to generate a sub theme for editing. Do not edit the parent 'neato' theme!

  1. Enable the Fett theme and set as default. You can unset it as default after you are done step 2.
  2. Enter the drush command: drush ngt [THEMENAME] [Description !Optional]


## Subtheme Setup

See the subtheme README.md for further instructions.
