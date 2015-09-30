(function ($, Drupal) {

Fett.position = {};

// Initialize
Fett.position.init = function(){
  var self = this;
  self.$window = $('.window').first();
  if(self.$window.length){
    self.$document = $(document);
    self.sizes();

    var $window = $(window);
    var windowW = $window.width();
    var windowH = $window.height();
    var timeout;
    $window.resize(function(){
      var newWindowW = $window.width();
      var newWindowH = $window.height();
      if(newWindowW!==windowW || newWindowH!==windowH){ //IE 8 fix
        windowW = newWindowW;
        windowH = newWindowH;
        clearTimeout(timeout);
        timeout = setTimeout(function(){
          self.sizes();
          self.scrolling(self.windowTopPosition());
        }, 300);
      }
    });

    self.scroll();
  }
}

// Size
Fett.position.sizes = function(){
  var self = this;
  self.windowH = self.$window.height();
  self.documentH = self.$document.height();
  for(var i=0; i<self.targets.length; i++){
    self.targets[i].size();
  }
}

// Window top position
Fett.position.windowTopPosition = function(){
  var self = this;
  return self.$window[0].scrollTop + self.$window.offset().top;
}

// Scroll
Fett.position.scroll = function(){
  var self = this;
  window.requestAnimFrame = (function(){
    return  window.requestAnimationFrame ||
      window.webkitRequestAnimationFrame ||
      window.mozRequestAnimationFrame    ||
      window.oRequestAnimationFrame      ||
      window.msRequestAnimationFrame     ||
      function(/* function */ callback, /* DOMElement */ element){
        window.setTimeout(callback, 1000 / 60);
      };
  })();
  var lastPosition = -1;
  (function animate(time){
    var windowTopPos = self.windowTopPosition();
    if (lastPosition !== windowTopPos) {
      self.scrolling(windowTopPos);
    }
    lastPosition = windowTopPos;
    // TWEEN.update();
    requestAnimFrame(animate);
  })();
}

// Scrolling
Fett.position.scrolling = function(windowTopP){
  var self = this;
  self.windowTopPos = typeof windowTopP != 'undefined' ? windowTopP : (self.windowTopPos || 0);
  self.windowBottomPos = windowTopP + self.windowH;
  for(var i=0; i<self.targets.length; i++){
    var viewPos = self.scrollingPosition(self.targets[i].$view);
    if(viewPos.visible){
      self.targets[i].play(viewPos);
    }else{
      self.targets[i].pause(viewPos);
    }
  }
}

// Scrolling Position
Fett.position.scrollingPosition = function($element) {
  var self = this;
  var blockH = $element.outerHeight();
  var blockTopPos = $element.data('positionTop');
  var blockLeftPos = $element.offset().left;
  var blockBottomPos = blockTopPos + blockH;
  var totalH = blockTopPos + blockH;
  var percent = 0;

  var canScrollDown = blockBottomPos + self.windowH < self.documentH;
  var canScrollUp = blockTopPos > self.windowH;
  var direction;
  if(canScrollDown){
    direction = 'top';
    percent = Math.min(Math.max(100 - (((totalH - (totalH - self.windowTopPos)) / totalH) * 100), 0), 100);
  }
  else if(canScrollUp){
    direction = 'bottom';
    percent = Math.min(Math.max(100 - ((self.windowBottomPos - blockTopPos) / (self.documentH - blockTopPos)) * 100 , 0), 100);
  }
  else{
    direction = 'middle';
    percent = Math.min(Math.max(100 - (self.windowTopPos / (self.documentH - self.windowH) * 100), 0), 100);
  }

  return {
    top: blockTopPos,
    left: blockLeftPos,
    bottom: blockBottomPos,
    height: blockH,
    percent: percent,
    direction: direction,
    windowH: self.windowH,
    windowTopPos: self.windowTopPos,
    windowBottomPos: self.windowBottomPos,
    visible: blockTopPos<self.windowBottomPos && blockBottomPos>self.windowTopPos
  };
}

// Players
Fett.position.targets = [];
Fett.position.track = function($view, options) {
  var self = this;
  var defaults = {
    // Called the first time an element is viewable.
    play: function(viewPos){},
    // Called when element is no longer viewable.
    pause: function(viewPos, is_init){},
    // Called when element comes back into view.
    resume: function(viewPos){},
    // Called on scroll when element is viewable.
    on: function(viewPos){},
    // Called when elements are sized on init and window resize.
    size: function(){},
  };
  options = $.extend({}, defaults, options);
  Fett.position.targets.push(
    new (function(){
      var played = false;
      var started = false;
      var init = false;
      this.$view = $view;
      $view.addClass('target').data('target-ind', Fett.position.targets.length);
      this.play = function(viewPos){
        if(!played){
          played = true;
          if(!started){
            started = true;
            options.play(viewPos);
          }else{
            options.resume(viewPos);
          }
        }
        options.on(viewPos);
      };
      this.pause = function(viewPos){
        if(played || (!played && !init)){
          played = false;
          init = false;
          options.pause(viewPos);
        }
      };
      this.size = function(){
        options.size();
        $view.data('positionTop', ($view.offset().top + self.$window.scrollTop()) | 0);
      }
    })()
  );
}

Drupal.behaviors.fett_position = {
  once:0,
  attach: function (context, settings) {
    if(!this.once){
      this.once = 1;
      setTimeout(function(){
        Fett.position.init();
      }, 10);
    }
  }
}

})(jQuery, Drupal);
