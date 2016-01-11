# Fett Starter (Fett, Gulp, Bourbon, Neat, Bitters) Drupal Theme

## Installation

From your theme directory, enter 'npm install' in the command line. This will install the required tools to compile
assets.

Make a copy of example.config.js and set your local development settings here. Add this file to your .gitignore file to prevent breaking of team-members' dev setup.

cp example.config.js config.js

## Usage

Run 'gulp' from the theme directory via command line to compile CSS from SASS. gulpfile.js controls what happens in this process. Feel free to
add your own tools into this file to facilitate development. Saving will trigger a cache rebuild, css/js rebuild, and all BrowserSync browsers to reload.
