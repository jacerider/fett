(function ($, Drupal) {

Drupal.behaviors.fett_fixed = {
  attach: function (context, settings) {
    var $header = $('#header').once('fett-fixed');
    if($header.length){
      var floated = false;
      var $placeholder = $('<div id="sticky-placeholder"></div>');
      var viewPosOriginal;

      var fixed = function(viewPos){
        viewPosOriginal = viewPosOriginal || viewPos;
        if(!floated && viewPosOriginal.bottom <= viewPos.windowTopPos){
          floated = true;
          $placeholder.height($header.outerHeight()).insertAfter($header);
          $header.addClass('sticky');
        }
        if(floated && (viewPosOriginal.bottom + viewPosOriginal.height) <= viewPos.windowTopPos){
          $header.addClass('sticky-animate');
        }
        if(floated && (viewPosOriginal.bottom + viewPosOriginal.height) > viewPos.windowTopPos){
          // $header.removeClass('sticky-animate');
        }
        if(floated && viewPos.windowTopPos == 0){
          unfloat(viewPos);
        }
      }

      var unfloat = function(){
        floated = false;
        $placeholder.remove();
        $header.removeClass('sticky sticky-animate');
      }

      var pause = function(viewPos, isInit){
        fixed(viewPos);
      }
      var on = function(viewPos){
        fixed(viewPos);
      }
      var size = function(){
        viewPosOriginal = null;
        unfloat();
      }

      Fett.position.track('header', $header, {
        onPause: pause,
        onVisible: on,
        onSize: size
      });
    }
  }
}

})(jQuery, Drupal);
