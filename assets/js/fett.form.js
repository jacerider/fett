(function ($, Drupal) {

Drupal.behaviors.fett_form = {

  attach: function (context, settings) {
    var self = this;
    $('.fett-form .fett-radios', context).once('fett-form').each(self.fettRadios);
    $('.fett-form .fett-checkboxes', context).once('fett-form').each(self.fettCheckboxes);
    $('*[data-dependency]', context).once('fett-form-dependency').each(self.fettDependency);
  },

  fettRadios: function () {
    var $this = $(this);
    $('.form-radio', $this).change(function(){
      $('.active', $this).removeClass('active');
      $(this).parent().toggleClass('active');
    }).each(function(){
      var $self = $(this);
      if($self.is(':checked')){
        $self.parent().addClass('active');
      }
    });
  },

  fettCheckboxes: function () {
    var $this = $(this);
    $('.form-checkbox', $this).change(function(){
      $(this).parent().toggleClass('active');
    }).each(function(){
      var $self = $(this);
      if($self.is(':checked')){
        $self.parent().addClass('active');
      }
    });
  },

  fettDependency: function () {
    var self = Drupal.behaviors.fett_form;
    var $this = $(this);
    var selector = $(this).data('dependency');
    var $dependency = $('*' + selector);
    if($dependency.length){
      var callback;
      if($dependency.is(':checkbox')){
        callback = self.fettDependencyCheckbox;
      }
      if(callback){
        $dependency.on('change', function(){
          callback($this, $dependency);
        });
        callback($this, $dependency);
      }
    }
  },

  fettDependencyCheckbox: function ($element, $dependency) {
    $element.hide();
    $dependency.prop('checked') ?
      $element.fadeIn() :
      $element.fadeOut();
  }
};

})(jQuery, Drupal);
