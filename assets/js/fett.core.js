(function ($, Drupal) {

//Change &amp;, &#039; and &quot; to &, ' and " in select list options
$('select option').each(function() {
  var text = $(this).text();
  var replaced = text.replace(/&amp;/g , "&").replace(/&#039;/g , "'").replace(/&quot;/g , '"');
  $(this).text(replaced);
});

Drupal.behaviors.fett = {
  attach: function(context, settings) {
  }
};

})(jQuery, Drupal);
