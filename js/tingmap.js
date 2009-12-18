
var map = null;
var count = 0;

// Call this function when the page has been loaded
function initialize() {
  map = new google.maps.Map2(document.getElementById("ting_gmap"));
  map.setCenter(new google.maps.LatLng(56.016808, 10.431763), 7);
  map.setMapType(G_SATELLITE_MAP);

  // Request coordinates
  $.post('index.php', {'action' : 'loadCoordinates'}, tingmapResponse, 'json');
}

function tingmapResponse(response) {

  if (response['status'] == 1) {
    var coordinates = response['coordinates'];
    for (var name in coordinates) {
      // Inside region (aalborg, aarhus etc.)
      for (var i in coordinates[name]) {
        // Inside polygon
        var points = new Array();
        for (var j in coordinates[name][i]) {
          // Inside point
          var coordinate = coordinates[name][i][j].split(',');
          var point = new GLatLng(coordinate[1], coordinate[0]);
          points.push(point);
        }

        // Display regions on the map
        var polygon = new GPolygon(points, "#000", 1, 1, "#00F", 0.4);
        map.addOverlay(polygon);
      }
    }
  }
  else {
    alert(response['msg']);
  }
}

// Load google maps
google.load("maps", "2.x", {"other_params":"sensor=false"});
google.setOnLoadCallback(initialize);
