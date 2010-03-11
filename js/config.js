
$(document).ready(function() {
  // Prevent normal submit
  $('#conf_region').submit(function() {
    return false;
  });

  // Add form action
  $('#saveBtn').click(function() {
    trySave($('#conf_region'), 'Kommuniker med serveren');
  });

  $('#logoutBtn').click(function () {
    window.location = 'logout.php';
  });
});

function trySave(form, msg) {
  // Disable save button
  $('#saveBtn').attr("disabled", "disabled")
  
  // Update feedback
  displayFeedback('info', msg);

  // Send ajax request
  $.post('regions.php', form.serialize(), saveResponse, 'json');

  return true;
}

function saveResponse(response) {
  if (response['status'] == 1) {
    displayFeedback('info', response['msg']);
  }

  // Enable save button
  $('#saveBtn').removeAttr("disabled");
}
