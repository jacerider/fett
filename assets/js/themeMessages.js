Drupal.behaviors.fettMessages = {
  attach: function(context, settings) {
    jQuery('#status-messages.reveal-modal', context).foundation('reveal', 'open');
  }
}
