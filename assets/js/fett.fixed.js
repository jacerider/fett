(function ($, Drupal) {

Drupal.behaviors.fett_fixed = {
  attach: function (context, settings) {
    var $header = $('#header').once('fett-fixed');
    if($header.length){
      var $placeholder = $('<div id="sticky-placeholder"></div>'),
          viewPosOriginal,
          viewPosLast,
          animEvent,
          fixed = 0,
          shown = 0,
          options = settings.fettFixed;

      $placeholder.height($header.outerHeight()).insertAfter($header);

      var check = function(viewPos){
        viewPosOriginal = viewPosOriginal || viewPos;

        if(viewPosOriginal.bottom <= viewPos.windowTopPos){
          fix();

          if((viewPosOriginal.bottom + viewPosOriginal.height) <= viewPos.windowTopPos){
            if(options.scroll){
              if(viewPosLast && viewPos.windowTopPos < viewPosLast.windowTopPos){
                show();
              }
              else{
                hide();
              }
            }
            else{
              show();
            }
          }
          else{
            hide();
          }
        }
        else{
          if(fixed){
            animEvent = $header.on(Fett.transEndEventName + '.fixed', function(e){
              if(e.originalEvent.propertyName == 'transform'){
                reset();
              }
            });
          }
        }

        viewPosLast = viewPos;
      }

      var fix = function(){
        if(!fixed){
          $header.off(Fett.transEndEventName + '.fixed');
          fixed = 1;
          $header.addClass('sticky');
          $placeholder.show();
        }
      }

      var reset = function(){
        fixed = shown = 0;
        $header.removeClass('sticky sticky-show sticky-hide');
        $placeholder.hide();
      }

      var show = function(){
        if(!shown){
          shown = 1;
          $header.removeClass('sticky-hide').addClass('sticky-show');
        }
      }

      var hide = function(){
        if(shown){
          shown = 0;
          $header.removeClass('sticky-show').addClass('sticky-hide');
        }
      }

      var size = function(){
        viewPosOriginal = null;
        reset();
        $placeholder.height($header.outerHeight());
      }

      Fett.position.track('header', $header, {
        onPause: check,
        onVisible: check,
        onSize: size
      });
    }
  }
}

})(jQuery, Drupal);
