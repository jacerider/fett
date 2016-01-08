module.exports = {
  browserSync: {
    hostname: "localhost",
    port: 8080,
    openAutomatically: false,
    reloadDelay: 50
  },

  drush: {
    enabled: false,
    alias: 'drush @SITE-ALIAS cache-rebuild'
  },

  twig: {
    useCache: true
  }
};
