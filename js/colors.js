
$(document).ready(function() {
  var f = $.farbtastic('#color-picker');

  $('#color-selections dd').each(function() {
    var color_input_field = $(this).children('input');
    var preview_color = $(this).children('.preview-color');

    // Set color on preview
    preview_color.css('background-color', color_input_field.val());

    // Set click event on preview
    preview_color.click(function() {
      // Connect color wheel to input fields
      f.linkTo(function() {
        $('#color-hex').val(f.color);
        color_input_field.val(f.color);
        preview_color.css('background-color', f.color);
      });
      // Update color wheel
      f.setColor(color_input_field.val());
      // Update hex color value
      $('#color-hex').val(color_input_field.val());
    });
  });
});
