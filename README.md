# Fett Drupal 8 Theme
##### Gulp, Bourbon, Neat, Bitters

## System Setup

**Gulp and Bower are required to manage assets.**

First, you will need to install [NodeJS](https://nodejs.org/en/download/package-manager/).

Install gulp and bower with the following from the command line. On some setups,
sudo may be required.

    npm install -g gulp bower

## Installation

From the fett theme directory, enter the following in the command line. This
will pull in the component assets for Fett. These are referenced includes from
the KAST theme for you - no need to copy them into the KAST/subthemes.

    bower install

Create a subtheme. See the *Build a theme with Drush* section below on how to
do that.


## Build a theme with Drush

It is highly encouraged to use Drush to generate a sub theme for editing. **Do
not edit the parent 'fett' theme!** Enter the following drush command:

     drush fett [THEMENAME] [Description !Optional]


## Subtheme Setup

See the subtheme README.md for further instructions.
