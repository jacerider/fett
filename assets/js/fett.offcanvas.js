(function ($, Drupal) {

var FettOffCanvas = {
  runOnce: false,
  isMobile: Modernizr.touch
};

FettOffCanvas.attach = function(context, settings) {
  var self = this;

  if(!self.runOnce){
    self.runOnce = true;
    self.$container = $('.oc-wrapper', context);
    self.$container.data('oclasses', self.$container[0].className);
    self.$buttons = $('.oc-link', context);
    self.eventType = self.isMobile ? 'touchstart' : 'click';

    self.$buttons.on(self.eventType, function(e){
      e.stopPropagation();
      e.preventDefault();
      var id = $(this).data('oc-id');
      var effect = $(this).data('oc-effect');
      var direction = $(this).data('oc-direction');
      self.open(id, effect, direction);
    });
  }
}

FettOffCanvas.open = function(id, effect, direction) {
  var self = this;

  $('#oc-block-' + id).addClass('active');

  self.$container[0].className = self.$container.data('oclasses');
  self.$container.addClass('oc-effect-' + effect + ' oc-direction-' + direction);

  // Remove
  // $('.oc-block')[0].className = 'oc-block';
  // $('.oc-block').addClass('oc-effect-' + effect);

  setTimeout( function() {
    self.$container.addClass('oc-open');
  }, 25 );

  $(document).on(self.eventType, function(e){
    if(!$(e.target).closest('.oc-block').length){
      self.close();
      $(this).off(self.eventType);
    }
  });
}

FettOffCanvas.close = function() {
  var self = this;
  self.$container.removeClass('oc-open');
  $('.oc-block.active').removeClass('active');
}

Drupal.behaviors.fettOffCanvas = FettOffCanvas;

})(jQuery, Drupal);
