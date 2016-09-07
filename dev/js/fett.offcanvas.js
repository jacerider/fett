/**
 * @file
 * Fett Offcanvas.
 */
(function ($, window, document) {

  'use strict';

  Drupal.behaviors.fettOffcanvas = {
    $wrapper: null,
    $push: null,
    wrapperClasses: '',
    $items: null,
    $links: null,
    items: [],
    isOpen: false,

    attach: function (context, settings) {
      if (settings.fettOffcanvas && settings.fettOffcanvas.items) {
        this.items = settings.fettOffcanvas.items;
        this.$wrapper = $('.offcanvas-wrapper');
        this.$push = $('.offcanvas-push');
        this.wrapperClasses = this.wrapperClasses || this.$wrapper.attr('class');
        this.$items = $('.offcanvas-item');
        this.$links = $('.offcanvas-link').removeClass('js-hide');
        this.$links.once('fett-offcanvas').on('click', this.linkClickOpen.bind(this));
        $('.offcanvas-close').once('fett-offcanvas').on('click', this.linkClickClose.bind(this));
      }
    },

    getSettings: function (id) {
      return this.items[id] ? this.items[id] : {};
    },

    linkClickOpen: function (e) {
      e.preventDefault();
      var id = $(e.currentTarget).data('id');
      this.open(id);
    },

    linkClickClose: function (e) {
      e.preventDefault();
      this.close();
    },

    open: function (id) {
      var self = this;
      var settings = this.getSettings(id);
      var timeout = 0;
      if (this.isOpen) {
        this.close();
        timeout = 525;
      }
      setTimeout(function () {
        self.isOpen = true;
        self.$push.on('click.offcanvas', function (e) {
          if (!$(e.target).closest('.offcanvas-items').length) {
            self.close();
          }
        });
        self.$items.filter('.offcanvas-item-' + id).addClass('active');
        self.$wrapper.addClass('active ' + settings.position);
        setTimeout(function () {
          self.$wrapper.addClass('animate');
        }, 25);
      }, timeout);
    },

    close: function () {
      if (this.isOpen) {
        var self = this;
        this.$wrapper.removeClass('animate');
        this.$push.off('click.offcanvas');
        setTimeout(function () {
          self.isOpen = false;
          self.$wrapper.attr('class', self.wrapperClasses);
          self.$items.removeClass('active');
        }, 500);
      }
    }
  };

}(jQuery, window, document));
