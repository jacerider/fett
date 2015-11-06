(function ($, Drupal) {

$.fn.fettUploadMultiFile = function() {

  return this.each(function() {
    var $file = $(this),
        $fileWrapper = $('<div class="file-upload-list small-12 medium-9 columns" />'),
        $fileInner = $('<div class="inner" />');
        $wrap = $('<div class="file-upload-wrapper row collapse">'),
        $buttonWrapper = $('<div class="small-12 medium-3 columns" />'),
        $button = $('<button type="button" class="file-upload-button button postfix" style="border-radius:0;"><i class="fa fa-upload"></i> Select</button></div>');
    console.log($file);

    $wrap.insertBefore( $file ).append($file, $button);
    $file.wrap($fileWrapper).wrap($fileInner);
    $button.wrap($buttonWrapper);

    // Prevent focus
    $button.attr('tabIndex', -1);

    $button.on('click', function (e) {
      e.preventDefault();
      console.log('hit');
      $('input[type=file].multi:last', $wrap).focus().click(); // Open dialog
    });
  });

}

Drupal.behaviors.fettUploadMultiFile = {
  attach: function(context, settings) {
    $("input[type=file].multi").once('fett-upload').fettUploadMultiFile();
  }
};

if($.fn.MultiFile){

}

})(jQuery, Drupal);
