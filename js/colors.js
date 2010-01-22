
$(document).ready(function() {
  var f = $.farbtastic('#color-picker');

  // Setup color selector box
  $('#color-box-selection').hide();
  // Hook into save btn
  $('#color-save').click(save_color);

  // Hook into the color preview elements
  $('#color-selections dd').each(function() {
    var color_input_field = $(this).children('input');
    var preview_color = $(this).children('.preview-color');

    // Set color on preview
    preview_color.css('background-color', color_input_field.val());

    // Set click event on preview
    preview_color.click(function() {
      $('#color-box-selection').fadeOut(600, function() {
        // Save color
        save_color();

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
        // Update hidden id field
        $('#region-id').val(color_input_field.attr('id').split('_')[1]);
        // Display color picker
        $('#color-box-selection').fadeIn(600);
        //
      });
    });
  });

  function save_color() {
    if ($('#color-hex').val() != '#') {
      
    }
  }
});