/**
 * @file
 * Initialize fastclick.
 */

/* global FastClick */
(function ($, document) {

  'use strict';

  Drupal.behaviors.FettFastclick = {
    attach: function (context) {
      FastClick.attach(document.body);
    }
  };

}(jQuery, document));
