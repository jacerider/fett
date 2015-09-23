(function ($, Drupal) {

var FettOffCanvas = {
  runOnce: false
};

FettOffCanvas.attach = function(context, settings) {
  var self = this;

  if(!self.runOnce){
    self.runOnce = true;
    self.$container = $('.oc-wrapper', context);
    if(self.$container.length){
      self.$container.data('oclasses', self.$container[0].className);
      self.$buttons = $('.oc-link', context);

      self.$buttons.on('click', function(e){
        e.stopPropagation();
        e.preventDefault();
        var id = $(this).data('oc-id');
        var effect = $(this).data('oc-effect');
        var direction = $(this).data('oc-direction');
        self.open(id, effect, direction);
      });
    }
  }
}

FettOffCanvas.open = function(id, effect, direction) {
  var self = this;
  self.id = id;

  $('#oc-block-' + id).addClass('active');

  self.$container[0].className = self.$container.data('oclasses');
  self.$container.addClass('oc-effect-' + effect + ' oc-direction-' + direction);

  setTimeout( function() {
    self.$container.addClass('oc-open');
    self.$container.trigger('offcanvas-open', [id, effect, direction]);
  }, 25 );

  $('.oc-push').on('click' + '.offcanvas', function(e){
    if(!$(e.target).closest('.oc-block').length){
      self.close();
      $(this).off('click' + '.offcanvas');
    }
  });


}

FettOffCanvas.close = function() {
  var self = this;
  self.$container.removeClass('oc-open');
  $('.oc-block.active').removeClass('active');
  self.$container.trigger('offcanvas-close', [self.id]);
}

Drupal.behaviors.fettOffCanvas = FettOffCanvas;

})(jQuery, Drupal);
