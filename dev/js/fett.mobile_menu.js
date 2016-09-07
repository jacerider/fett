/**
 * @file
 * Fett Mobile Menu.
 */
(function ($, window, document) {

  'use strict';

  Drupal.behaviors.fettMobileMenu = {
    $wrapper: null,
    $menu: null,
    $links: null,
    $trail: null,
    animating: false,
    transitionDelay: 500,

    attach: function (context, settings) {
      var self = this;
      $('div.mobile-menu-wrapper', context).once('fett-mobile-menu').each(function () {
        self.$wrapper = $(this);
        self.$trail = $('.mobile-menu-trail', self.$wrapper);
        self.$menu = $('.mobile-menu', self.$wrapper);
        self.$links = $('li.children > a, li.children > span', self.$menu);
        self.init();
      });
    },

    init: function () {
      this.$links.on('click', this.linkClick.bind(this));
      this.trailBuild();
    },

    linkClick: function (e) {
      var self = this;
      var level;
      e.preventDefault();
      if (!self.animating) {
        self.animating = true;
        level = $(e.currentTarget).next('ul').attr('data-level');
        $(e.currentTarget).parent('li').addClass('active-trail');
        self.$menu.attr('data-depth', level);
        self.trailBuild();
        setTimeout(function () {
          self.animating = false;
        }, self.transitionDelay);
      }
    },

    trailBuild: function () {
      var self = this;
      var level = 0;
      var items = [{text: 'All', level: level++}];
      var links = [];
      $('li.active-trail.children > a, li.active-trail.children > span', this.$menu).each(function () {
        items.push({text: $(this).text(), level: level++});
      });
      this.$trail.html('');
      items.forEach(function (item) {
        var link = $('<a href="#">' + item.text + '</a>').appendTo(self.$trail).on('click', function (e) {
          e.preventDefault();
          self.levelRevert(item.level);
          self.trailClean(links, item.level);
        });
        links.push(link);
      });
    },

    trailClean: function (links, level) {
      links.forEach(function (link, index) {
        if (level < index) {
          link.remove();
        }
      });
    },

    levelRevert: function (level) {
      var self = this;
      self.animating = true;
      self.$menu.attr('data-depth', level);
      setTimeout(function () {
        $('ul[data-level="' + level + '"] li.active-trail').removeClass('active-trail');
        self.animating = false;
      }, self.transitionDelay);
    }
  };

}(jQuery, window, document));
