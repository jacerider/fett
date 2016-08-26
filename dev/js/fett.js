/**
 * @file
 * Fett Core.
 */
(function ($, window, document) {

Drupal.behaviors.fett = {
  attach: function (context, settings) {
    var $document = $(document);
    if ($document.foundation) {
      $(document).foundation();
    }
  }
};

}(jQuery, window, document));
