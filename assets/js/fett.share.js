(function ($, Drupal) {

Drupal.behaviors.fett_share = {

  attach: function(context, settings) {
    var self = this;
    $('.share-buttons').once(function(){
      self.$wrapper = $(this);
      self.$buttons = self.$wrapper.find('li');
      self.$wrapper.find('.popup').on('click', function(e){
        var $button = $(this);
        self.popup($button.attr('href'), $button.find('.share-text').html(), 580, 470);
        e.preventDefault();
      });
      self.fit();

      $(window).resize(function () {
        self.fit();
      });
    });
  },

  fit: function() {
    var self = this;
    self.$wrapper.removeClass('share-small');
    var wrapperWidth = self.$wrapper.outerWidth();
    var buttonsWidth = self.$buttons.length * 4;
    self.$buttons.each(function(){
      buttonsWidth += $(this).outerWidth();
    });
    if(buttonsWidth > wrapperWidth){
      self.$wrapper.addClass('share-small');
    }
  },

  popup: function(url, title, w, h) {
    // Fixes dual-screen position
    var dualScreenLeft = window.screenLeft !== undefined ? window.screenLeft : screen.left;
    var dualScreenTop = window.screenTop !== undefined ? window.screenTop : screen.top;

    var width = window.innerWidth ? window.innerWidth : document.documentElement.clientWidth ? document.documentElement.clientWidth : screen.width;
    var height = window.innerHeight ? window.innerHeight : document.documentElement.clientHeight ? document.documentElement.clientHeight : screen.height;

    var left = ((width / 2) - (w / 2)) + dualScreenLeft;
    var top = ((height / 3) - (h / 3)) + dualScreenTop;

    var newWindow = window.open(url, title, 'scrollbars=yes, width=' + w + ', height=' + h + ', top=' + top + ', left=' + left);

    // Puts focus on the newWindow
    if (window.focus) {
      newWindow.focus();
    }
  }
};

})(jQuery, Drupal);
