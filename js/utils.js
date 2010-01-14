
$(document).ready(function() {
  var setting = {
    tl: { radius: 8 },
    tr: { radius: 8 },
    bl: { radius: 8 },
    br: { radius: 8 },
    antiAlias: true
  }
  curvyCorners(setting, ".roundedCorners");
});

function displayFeedback(type, msg) {
  var feedback = $('#feedback');
  feedback.removeClass('err info ok');
  feedback.addClass(type);
  $('#feedback #msg').html(msg);
  feedback.slideDown('slow');
}
