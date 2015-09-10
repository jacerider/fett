(function ($, Drupal) {

var FettMegaMenuOffCanvas = {
  runOnce: false,
  isMobile: Fett.isMobile(),
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
  $el: null,
  $wrapper: null,
  $levels: null,
  $menuItems: null,
  $levelBack: null
};

FettMegaMenuOffCanvas.attach = function(context, settings) {
  var self = this;
  if(self.support && !self.runOnce){
    self.$el = $('#main-nav-oc-offcanvas');
    self.$wrapper = $('.oc-wrapper');
    self.$levels = $('div.mp-level', self.$el);
    self.setLevelDepth();
    self.$menuItems = $('li', self.$el);
    self.$levelBack = $('.mp-back', self.$el);
    self.$activeLink = $('a.active-trail:last', self.$el);
    self.$activeLevel = null;
    self.eventType = 'click';
    self.$el.addClass('mp-' + self.options.type);
    self.init();
  }
}

FettMegaMenuOffCanvas.init = function() {
  var self = this;
  self.$wrapper.on('offcanvas-open', function(e, id, effect, direction){
    // Only act on main-nav.
    if(id == 'main-nav'){
      if( self.open ) {
        self.resetMenu();
      }
      else {
        // Set active level
        if(self.$activeLink.length && self.$activeLink.length === 1){
          self.$activeLevel = $(self.$activeLink).closest('div.mp-level');
          var level = self.$activeLevel.data('mp-level');
          if(level > 1){
            self.$activeLevel.parents('.mp-level').addClass('mp-level-overlay');
            self.level = level - 1;
          }
        }

        self.direction = direction;
        self.openMenu(self.$activeLevel);
      }
    }
  });

  self.$wrapper.on('offcanvas-close', function(e, id){
    // Only act on main-nav.
    if(id == 'main-nav'){
      self.resetMenu();
    }
  });

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

  // by clicking on a specific element
  self.$levelBack.each(function(e){
    $(this).on(self.eventType, function(e){
      e.preventDefault();
      var level = $(this).closest('.mp-level').data('mp-level');
      if(self.level <= level){
        e.stopPropagation();
        self.level = level - 1;
        self.level === 0 ? self.resetMenu() : self.closeMenu();
      }
    })
  });
}

FettMegaMenuOffCanvas.openMenu = function($subLevel) {
  var self = this;
  self.level++;

  var levelFactor = ( self.level - 1 ) * self.options.levelSpacing;
  var translateVal = self.options.type === 'overlap' ? self.$el.width() + levelFactor : self.$el.width();

  self.levelClass();

  if($subLevel) {
    // reset transform for sublevel
    $subLevel.css({transform: ''});
    // need to reset the translate value for the level menus that have the same level depth and are not open

    self.$levels.each(function(){
      var $levelEl = $(this);
      if(!$subLevel.is($levelEl) && !$levelEl.hasClass('mp-level-open') && !$levelEl.hasClass('mp-level-base')){
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
    self.open = true;
  }

  $subLevel = $subLevel || $(self.$levels[0]);

  // add class mp-level-open to the opening level element
  $subLevel.addClass('mp-level-open');
  $subLevel.parents('div.mp-level').addClass('mp-level-open');
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
  self.levelClass();
  self.toggleLevels();
}

FettMegaMenuOffCanvas.resetMenu = function(){
  var self = this;
  self.level = 0;
  self.toggleLevels();
  self.open = false;
}

FettMegaMenuOffCanvas.toggleLevels = function(){
  var self = this;
  self.$levels.each(function(){
    var $levelEl = $(this);
    var level = Number($levelEl.data( 'mp-level'));
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
    $(this).data('mp-level', level).attr('data-mp-level', level);
  });
}

Drupal.behaviors.fettMegaMenuOffcanvas = FettMegaMenuOffCanvas;


})(jQuery, Drupal);
