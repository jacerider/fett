/**
 * @file
 * Initialize fastclick.
 */
(function ($, document) {
  Drupal.behaviors.FettFastclick = {
    attach: function (context) {
      FastClick.attach(document.body);
    }
  };
}(jQuery, document));
