
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
      // Save color
      if ($('#color-hex').val() != $('#region-color').val()) {
        var answer = confirm("Save color changes!")
        if (answer){
          save_color();
        }
        else {
          // Restor org. color
          var color_input_field_prev = $('#region_' + $('#region-id').val());
          color_input_field_prev.val($('#region-color').val());
          color_input_field_prev.siblings('div').css('background-color', $('#region-color').val());
        }
      }

      // Fade out selection box
      $('#color-box-selection').fadeOut(600, function() {
        // Connect color wheel to input fields
        f.linkTo(function() {
          $('#color-hex').val(f.color);
          color_input_field.val(f.color);
          preview_color.css('background-color', f.color);
          $('#color-save').removeAttr('disabled');
        });

        // Make manuale input update color wheel
        $('#color-hex').change(function() {
          f.setColor($(this).val());
        });

        // Save org. region color
        $('#region-color').val(color_input_field.val());
        // Update color wheel
        f.setColor(color_input_field.val());
        // Update hex color value
        $('#color-hex').val(color_input_field.val());
        // Update hidden id field
        $('#region-id').val(color_input_field.attr('id').split('_')[1]);
        // Disable save btn
        $('#color-save').attr('disabled', 'disabled');
        // Display color picker
        $('#color-box-selection').fadeIn(600);
        //
      });
    });
  });

  function save_color() {
    if ($('#color-hex').val() != $('#region-color').val()) {
      $.post('colors.php',
             {'id' : $('#region-id').val(),
              'color' : $('#region_' + $('#region-id').val()).val(),
              'action': 'updatecolor'},
             function(data) {}, 'json');
      // Disable save btn
      $('#color-save').attr('disabled', 'disabled');
      // Update org. color
      $('#region-color').val($('#color-hex').val());
    }
  }
});