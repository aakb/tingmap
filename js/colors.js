
$(document).ready(function() {
  $('#color-selections dd').each(function() {
    $(this).children('.preview-color')
    .css('background-color', $(this).children('input').val());
  });


});
