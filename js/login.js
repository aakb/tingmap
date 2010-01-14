
$(document).ready(function() {
  // Prevent normal submit
  $('#login').submit(function() {
    return false;
  })
			
  // Set focus
  $('#username').focus();
			
  // Add form action
  $('#loginBtn').click(function() {
    var feedback = $('#feedback');
    feedback.removeClass('err msg ok');
    tryLogin('login', 'Kommuniker med serveren', 'Udfyld alle felter');
  });
});

function tryLogin(formID, msg, errMsg) {
  // Disable login button
  $('#loginBtn').attr("disabled", "disabled")
		
  // Validate fields
  if ($('#username').val() == '' || $('#passwd').val() == '') {
    // Set error
    displayFeedback('err', errMsg);

    // Enable login button
    $('#loginBtn').removeAttr("disabled");

    return false;
  }

  // Update feedback
  displayFeedback('info', msg);

  // Send ajax request
  $.post('index.php', $('#login').serialize(), loginResponse, 'json');
  return true;
}

function loginResponse(response) {	
  if (response['status'] == 'denied') {
    $('#passwd').focus();
    displayFeedback('err', response['message']);
  }
  else if (response['status'] == 'granted') {
    displayFeedback('ok', response['message']);
    window.location = response['url'];
  }
  else {
    displayFeedback('err', response['message']);
  }
	
  // Enable login button
  $('#loginBtn').removeAttr("disabled");
}
