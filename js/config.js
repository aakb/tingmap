
$(document).ready(function() {
  // Prevent normal submit
  $('#conf_region').submit(function() {
    return false;
  });

  // Add form action
  $('#saveBtn').click(function()
  {
    var feedback = $('#feedback');
    feedback.removeClass('err msg ok');
    trySave($('#conf_region'), 'Kommuniker med serveren');
  });

  $('#logoutBtn').click(function () {
    window.location = 'logout.php';
  });
});

function trySave(form, msg) {
  // Disable save button
  $('#saveBtn').attr("disabled", "disabled")

  // Get feedback fields
  var feedback = $('#feedback');
  var fbMsg = $('#feedback span');
  
  // Update feedback
  feedback.addClass('msg');
  fbMsg.html(msg);
  fbMsg.fadeIn('slow');

  // Send ajax request
  $.post('admin.php', form.serialize(), saveResponse, 'json');

  return true;
}

function saveResponse(response) {
  // Get feedback fields
  var feedback = $('#feedback');
  var fbMsg = $('#feedback span');
  feedback.removeClass('err msg ok');

  if (response['status'] == 1) {
    feedback.addClass('ok');
    fbMsg.html(response['msg']);
    fbMsg.fadeIn('slow');
  }

  // Enable save button
  $('#saveBtn').removeAttr("disabled");
}
