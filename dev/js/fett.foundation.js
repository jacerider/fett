/**
 * @file
 * Fett Core.
 */
(function ($, window, document) {

  'use strict';

  Drupal.behaviors.fettFoundation = {
    attach: function (context, settings) {
      var $document = $(document);
      if ($document.foundation) {
        $(document).foundation();
      }
    }
  };

}(jQuery, window, document));
