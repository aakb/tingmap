
$(document).ready(function() 
{
  // Prevent normal submit
  $('#login').submit(function() {
    return false;
  });
			
  // Set focus
  $('#username').focus();
			
  // Add form action
  $('#loginBtn').click(function()
  {
    var feedback = $('#feedback');
    feedback.removeClass('err msg ok');
    tryLogin('login', 'Kommuniker med serveren', 'Udfyld alle felter');
  });
});

function tryLogin(formID, msg, errMsg)
{
  // Disable login button
  $('#loginBtn').attr("disabled", "disabled")
	
  // Get feedback fields
  var feedback = $('#feedback');
  var fbMsg = $('#feedback span');
	
  // Validate fields
  if ($('#username').val() == '' || $('#passwd').val() == '')
  {
    feedback.addClass('err');
    fbMsg.html(errMsg);
    fbMsg.fadeIn('slow');
		
    // Enable login button
    $('#loginBtn').removeAttr("disabled");

    return false;
  }
	
  // Update feedback
  feedback.addClass('msg');
  fbMsg.html(msg);
  fbMsg.fadeIn('slow');
	
  // Send ajax request
  $.post('index.php', $('#login').serialize(), loginResponse, 'json');

  return true;
}

function loginResponse(response) {
  // Get feedback fields
  var feedback = $('#feedback');
  var fbMsg = $('#feedback span');
  feedback.removeClass('err msg ok');

  if (response['status'] == 'denied') {
    $('#passwd').focus();
    feedback.addClass('err');
    fbMsg.html(response['message']);
    fbMsg.fadeIn('slow');
  }
  else if (response['status'] == 'granted') {
    feedback.addClass('ok');
    fbMsg.html(response['message']);
    fbMsg.fadeIn('slow');
    window.location = response['url'];
  }
  else {
    feedback.addClass('err');
    fbMsg.html(response['message']);
    fbMsg.fadeIn('slow');
  }
	
  // Enable login button
  $('#loginBtn').removeAttr("disabled");
}
