var gulp = require('gulp');
var gutil = require('gulp-util');
var sass = require('gulp-sass');
var watch = require('gulp-watch');
var shell = require('gulp-shell');
var notify = require('gulp-notify');
var browserSync = require('browser-sync');
var sourcemaps = require('gulp-sourcemaps');
var uglify = require('gulp-uglify');
var fs = require("fs");
var config = null;

/**
 * If config.js exists, load that config for overriding certain values below.
 */
function loadConfig() {
  if (config === null && fs.existsSync(__dirname + "/./config.js")) {
    config = {};
    config.local = require("./config");
  }

  return config;
}

loadConfig();

/**
 * This task generates CSS from all SCSS files and compresses them down.
 */
gulp.task('sass', function () {
  return gulp.src('./scss/**/*.scss')
    .pipe(sourcemaps.init())
    .pipe(sass({
      noCache: true,
      outputStyle: "compressed",
      lineNumbers: false,
      loadPath: './css/*',
      sourceMap: true
    }))
    .pipe(sourcemaps.write('./maps'))
    .pipe(gulp.dest('./css'))
    .pipe(notify({
      title: "SASS Compiled",
      message: "All SASS files have been recompiled to CSS.",
      onLast: true
    }));
});

/**
 * This task minifies javascript in the js/js-src folder and places them in the js directory.
 */
gulp.task('compress', function() {
  return gulp.src('./js/js-src/*.js')
    .pipe(sourcemaps.init())
    .pipe(uglify())
    .pipe(sourcemaps.write('./maps'))
    .pipe(gulp.dest('./js'))
    .pipe(notify({
      title: "JS Minified",
      message: "All JS files in the theme have been minified.",
      onLast: true
    }));
});

/**
 * Task when css or js files are changed: recompress the css and js in
 * parallel, then when those are both done reload the browser.
 * Assumes drupal css and js aggregation is off and doesn't clear drupal
 * caches, which makes this run much faster.
 */
gulp.task('cssjs:reload', ['sass', 'compress'], function() {
  browserSync.reload();
});

/**
 * Task when css or js files are changed: recompress the css and js in
 * parallel, then when those are both done reload the browser.
 * Assumes drupal css and js aggregation is off and doesn't clear drupal
 * caches, which makes this run much faster.
 */
gulp.task('twig:reload', ['drush:cc'], function() {
  browserSync.reload();
});

/**
 * Defines a task that triggers a Drush cache rebuild.
 */
gulp.task('drush:cc', function () {
  if (config !== null && !config.local.drush.enabled) {
    return;
  }

  return gulp.src('', {read: false})
    .pipe(shell([
      config.local.drush.alias
    ]))
    .pipe(notify({
      title: "Caches cleared",
      message: "Drupal CSS/JS caches cleared.",
      onLast: true
    }));
});

/**
 * Defines the watcher task.
 */
gulp.task('watch', function() {
  browserSync({
    port: config.local.browserSync.port || 8080,
    proxy: config.local.browserSync.hostname || "localhost",
    open: config.local.browserSync.openAutomatically || false,
    reloadDelay: config.local.browserSync.reloadDelay || 50
  });

  // watch scss and js and clear drupal theme cache on change, reload browsers
  gulp.watch(['scss/**/*.scss', 'js-src/**/*.js'], ['cssjs:reload']);

  // If user has not specified an override, assume twig changes don't need cache reload
  if ((config !== null && config.local.twig.useCache) || config === null) {
    gulp.watch(['templates/**/*.html.twig']).on('change', browserSync.reload);
  }

  // If user has specified an override, reload twig cache
  if (config !== null && !config.local.twig.useCache) {
    gulp.watch(['templates/**/*.html.twig'], ['twig:reload']);
  }
});

gulp.task('default', ['watch']);
