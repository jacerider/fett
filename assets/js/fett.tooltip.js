(function ($, Drupal) {

Drupal.behaviors.fett_tooltip = {

  attach: function(context, settings) {
    var selector, options, $element;
    var self = this;
    var defaults = {
      theme: 'fett-tooltip radius',
      position: 'bottom'
    };

    $('.tip').tooltipster(defaults);

    // $('.form-item').once().each(function(){
    //   var $this = $(this);
    //   $this.tooltipster({
    //     theme: 'fett-tooltip radius',
    //     position: 'bottom',
    //     functionInit: function(){
    //       return $('.description', $this).hide().html();
    //     },
    //     functionReady: function(){
    //       $('.description', $this).attr('aria-hidden', false);
    //     },
    //     functionAfter: function(){
    //       $('.description', $this).attr('aria-hidden', true);
    //     },
    //     trigger: 'custom'
    //   });

    //   $('input', $this).focus(function(){
    //     $this.tooltipster('show');
    //   })
    //   .blur(function(){
    //     $this.tooltipster('hide');
    //   })

    // });

    if (!settings.fett_tooltip) {
      return;
    }
    for (selector in settings.fett_tooltip) {
      options = $.extend({}, defaults, settings.fett_tooltip[selector]);
      $element = $(selector);
      if($element.length){
        $element.once('fett-tooltip').tooltipster(options);
      }
    }
  }
};

})(jQuery, Drupal);
