(function ($, Drupal) {

Drupal.behaviors.fett_fixed = {
  attach: function (context, settings) {
    var $header = $('#header').once('fett-fixed');
    if($header.length){
      var floated = false;
      var $placeholder = $('<div id="sticky-placeholder"></div>');
      var viewPosOriginal, viewPosLast;
      var options = settings.fett_fixed;

      var fixed = function(viewPos){
        viewPosOriginal = viewPosOriginal || viewPos;
        if(!floated && viewPosOriginal.bottom <= viewPos.windowTopPos){
          floated = true;
          $placeholder.height($header.outerHeight()).insertAfter($header);
          $header.addClass('sticky');
        }
        if(floated && (viewPosOriginal.bottom + viewPosOriginal.height) <= viewPos.windowTopPos){
          if(options.scroll){
            if(viewPosLast && viewPos.windowTopPos < viewPosLast.windowTopPos){
              $header.removeClass('sticky-animate-out').addClass('sticky-animate-in');
            }
            else{
              $header.removeClass('sticky-animate-in').addClass('sticky-animate-out');
            }
          }
          else{
            $header.addClass('sticky-animate');
          }
        }
        if(floated && (viewPosOriginal.bottom + viewPosOriginal.height) > viewPos.windowTopPos){
          // $header.removeClass('sticky-animate');
        }
        if(floated && viewPos.windowTopPos == 0){
          unfloat(viewPos);
        }
        viewPosLast = viewPos;
      }

      var unfloat = function(){
        floated = false;
        $placeholder.remove();
        $header.removeClass('sticky sticky-animate sticky-animate-in sticky-animate-out');
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
