(function ($, Drupal) {

Drupal.behaviors.fettMobileMenu = {
  attach: function(context, settings) {
    // Mobile menu toggle
    $('.l-overlay ul li.expanded').once().append('<span class="expand-sub"></span>');
    $('.l-overlay .expand-sub').once().click(function() {
      $(this).siblings('ul.menu').slideToggle();
      $(this).toggleClass('active');
    });
  }
};

var triggerBttn = $( '#mobile-trigger-overlay' );
if(!triggerBttn.length) return;

var overlay = $( 'div.l-overlay' ),
  closeBttn = $( 'button.l-overlay-close' );
  transEndEventNames = {
    'WebkitTransition': 'webkitTransitionEnd',
    'MozTransition': 'transitionend',
    'OTransition': 'oTransitionEnd',
    'msTransition': 'MSTransitionEnd',
    'transition': 'transitionend'
  },
  transEndEventName = transEndEventNames[ Modernizr.prefixed( 'transition' ) ],
  support = { transitions : Modernizr.csstransitions };

function toggleOverlay() {
  if( overlay.hasClass( 'open' ) ) {
    overlay.removeClass( 'open' );
    overlay.addClass( 'close' );
    var onEndTransitionFn = function( ev ) {
      if( support.transitions ) {
        if( ev.originalEvent.propertyName !== 'visibility' ) return;
        $(this).off( transEndEventName, onEndTransitionFn );
      }
      overlay.removeClass( 'close' );
    };
    if( support.transitions ) {
      overlay.on( transEndEventName, onEndTransitionFn );
    }
    else {
      onEndTransitionFn();
    }
  }
  else if( !overlay.hasClass( 'close' ) ) {
    overlay.addClass( 'open' );
  }
}

triggerBttn.on( 'click', toggleOverlay );
closeBttn.on( 'click', toggleOverlay );

})(jQuery, Drupal);
