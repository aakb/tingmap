
var map = null;
var count = 0;

// Call this function when the page has been loaded
function initialize() {
  map = new google.maps.Map2(document.getElementById("ting_gmap"));
  map.setCenter(new google.maps.LatLng(56.016808, 10.431763), 7);
  map.setMapType(G_SATELLITE_MAP);

  // Request coordinates
  GEvent.addListener(map, "click", function() {
    $.post('index.php', {'action' : 'loadCoordinates'}, tingmapResponse, 'json');
  });
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
          // Inside singel coordinate
          var coordinate = coordinates[name][i][j].split(',');
          var point = new GLatLng(coordinate[1], coordinate[0]);
          points.push(point);

          //map.addOverlay(new GMarker(point));

        }
        var polygon = new GPolygon(points, "#f33f00", 5, 1, "#ff0000", 0.2);
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
