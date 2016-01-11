# Fett Starter (Fett, Gulp, Bourbon, Neat, Bitters) Drupal Theme

## System Setup

If you have not already done so, please reference the README.md file found in
the *fett* parent theme.

## Installation

From your theme directory, enter the following in the command line. This will
install the required tools to compile assets.

    npm install

Make a copy of example.config.js and set your local development settings here.
Add this file to your .gitignore file to prevent breaking of team-members' dev
setup.

    cp example.config.js config.js

## Usage

Run 'gulp' from the theme directory via command line to compile CSS from SASS.
gulpfile.js controls what happens in this process. Feel free to add your own
tools into this file to facilitate development. Saving will trigger a cache
rebuild, css/js rebuild, and all BrowserSync browsers to reload.
