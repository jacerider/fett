(function ($, Drupal) {

var FettMegaMenu = {
  runOnce: false,
  isMobile: Drupal.fett.isMobile()
};

FettMegaMenu.attach = function(context, settings) {
  var self = this;

  if(!self.runOnce){

    // new mlPushMenu( document.getElementById( 'main-nav-offcanvas' ), document.getElementById( 'oc-link-main-nav' ) );

    // $('.megamenu').each(function(){
    //   self.megamenu($(this), settings);
    // });
  }
}

FettMegaMenu.megamenu = function($megamenu, settings) {
  var self = this;
  var eventType = self.isMobile ? 'touchstart' : 'mouseenter';

  $('li.drop > a', $megamenu).on(eventType, function(e){
    e.stopPropagation();
    e.preventDefault();
    var $drop = $(this).closest('li.drop');
  });
}

Drupal.behaviors.fettMegaMenu = FettMegaMenu;



var FettMegaMenuOffCanvas = {
  runOnce: false,
  isMobile: Drupal.fett.isMobile(),
  support: Modernizr.csstransforms3d,
  level: 0,
  levelTotal: 0,
  open: false,
  eventType: null,
  options: {
    type: 'overlap',
    levelSpacing : 40
  },
  direction: 'left',
  $trigger: null,
  $el: null,
  $wrapper: null,
  $levels: null,
  $menuItems: null,
};

FettMegaMenuOffCanvas.attach = function(context, settings) {
  var self = this;
  if(self.support && !self.runOnce){
    self.$trigger = $('#oc-link-main-nav');
    self.$el = $('#main-nav-offcanvas');
    self.$wrapper = $('.oc-wrapper');
    self.$levels = $('div.mp-level', self.$el);
    self.setLevelDepth();
    self.$menuItems = $('li', self.$el);
    self.eventType = self.isMobile ? 'touchstart' : 'click';
    self.$el.addClass('mp-' + self.options.type);
    self.init();
  }
}

FettMegaMenuOffCanvas.init = function() {
  var self = this;

  self.$wrapper.on('offcanvas-open', function(e, direction){
    if( self.open ) {
      self.resetMenu();
    }
    else {
      self.direction = direction;
      self.openMenu();
      // the menu should close if clicking somewhere on the body (excluding clicks on the menu)
      // $(document).on(self.eventType + '.megamenu', function(e){
      //   if(self.open && !$(e.target).closest('#' + self.$el.attr('id')).length){
      //     self.resetMenu();
      //     $(document).off(self.eventType + '.megamenu');
      //   }
      // });
    }
  });

  self.$wrapper.on('offcanvas-close', function(){
    self.resetMenu();
  })

  // self.$trigger.on(self.eventType, function(e){
  //   e.preventDefault();
  //   if( self.open ) {
  //     self.resetMenu();
  //   }
  //   else {
  //     self.openMenu();
  //     // the menu should close if clicking somewhere on the body (excluding clicks on the menu)
  //     $(document).on(self.eventType + '.megamenu', function(e){
  //       if(self.open && !$(e.target).closest('#' + self.$el.attr('id')).length){
  //         self.resetMenu();
  //         $(document).off(self.eventType + '.megamenu');
  //       }
  //     });
  //   }
  // });

  self.$menuItems.each(function(e){
    var $li = $(this);
    var $subLevel = $('div.mp-level:first', $li);
    if($subLevel.length){
      $('a:first', $li).on(self.eventType, function(e){
        e.stopPropagation();
        var $level = $('.mp-level:first', $li);
        var level = $level.data('mp-level');
        if(self.level <= level){
          e.preventDefault();
          $(this).closest('.mp-level').addClass('mp-level-overlay');
          self.openMenu($subLevel);
        }
      });
    }
  });

  // closing the sub levels :
  // by clicking on the visible part of the level element
  self.$levels.each(function(e){
    $(this).on(self.eventType, function(e){
      e.stopPropagation();
      var level = $(this).data('mp-level');
      if(self.level > level){
        e.preventDefault();
        self.level = level;
        self.closeMenu();
      }
    })
  });
}

FettMegaMenuOffCanvas.openMenu = function($subLevel) {
  var self = this;
  self.level++;

  var levelFactor = ( self.level - 1 ) * self.options.levelSpacing;
  var translateVal = self.options.type === 'overlap' ? self.$el.width() + levelFactor : self.$el.width();

  // self.$wrapper.css({transform: 'translate3d(' + translateVal + 'px,0,0)'});
  // self.$el.parent().css({width: translateVal + 'px'});

  // self.$wrapper.removeClass('mp-level-' + (self.level - 1)).addClass('mp-level-' + self.level);
  self.levelClass();

  if($subLevel) {
    // reset transform for sublevel
    $subLevel.css({transform: ''});
    // need to reset the translate value for the level menus that have the same level depth and are not open
    self.$levels.each(function(){
      var $levelEl = $(this);
      if(!$subLevel.is($levelEl) && !$levelEl.hasClass('mp-level-open')){
        if(self.direction == 'right'){
          $levelEl.css({transform: 'translate3d(0,0,0) translate3d(' - -1*levelFactor + 'px,0,0)'});
        }
        else{
          $levelEl.css({transform: 'translate3d(-100%,0,0) translate3d(' + -1*levelFactor + 'px,0,0)'});
        }
      }
    });
  }

  if(self.level === 1){
    // self.$wrapper.addClass('mp-pushed');
    self.open = true;
  }

  $subLevel = $subLevel || $(self.$levels[0]);

  // add class mp-level-open to the opening level element
  $subLevel.addClass('mp-level-open');
}

FettMegaMenuOffCanvas.levelClass = function(){
  var self = this;
  for( var i = 0; i < self.levelTotal; ++i ) {
    self.$wrapper.removeClass('mp-level-' + (i + 1));
  }
  self.$wrapper.addClass('mp-level-' + self.level);
}

FettMegaMenuOffCanvas.closeMenu = function(){
  var self = this;
  var levelFactor = ( self.level - 1 ) * self.options.levelSpacing;
  var translateVal = self.options.type === 'overlap' ? self.$el.width() + levelFactor : self.$el.width();
  // self.$wrapper.css({transform: 'translate3d(' + translateVal + 'px,0,0)'});
  self.levelClass();
  self.toggleLevels();
}

FettMegaMenuOffCanvas.resetMenu = function(){
  var self = this;
  // self.$wrapper.css({transform: 'translate3d(0,0,0)'});
  self.level = 0;
  // self.$wrapper.removeClass('mp-pushed');
  self.toggleLevels();
  self.open = false;
}

FettMegaMenuOffCanvas.toggleLevels = function(){
  var self = this;
  self.$levels.each(function(){
    var $levelEl = $(this);
    var level = Number($levelEl.data( 'mp-level' ));
    if( level  >= self.level + 1 ) {
      $levelEl.removeClass('mp-level-open mp-level-overlay');
    }
    else if( level == self.level ) {
      $levelEl.removeClass('mp-level-overlay');
    }
  });
}

FettMegaMenuOffCanvas.setLevelDepth = function() {
  var self = this;
  self.$levels.each(function(){
    var level = $(this).parents('.mp-level').length + 1;
    self.levelTotal = Math.max(level, self.levelTotal);
    $(this).data('mp-level', level).attr('data-mp-mp-level', level);
  });
}

Drupal.behaviors.fettMegaMenuOffcanvas = FettMegaMenuOffCanvas;


})(jQuery, Drupal);
