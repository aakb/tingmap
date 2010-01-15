
var map = null;
var count = 0;
var regions = null;

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
    regions = response['regions'];

    for (var region_ID in regions) {
      var region = regions[region_ID];
      var region_polygons = region['region_polygons'];
      
      for (var region_polygons_ID in region_polygons) {
        // Inside region polygon
        for (var polygon_ID in region_polygons[region_polygons_ID]) {
          // Inside polygon
          var points = new Array();
          
          for (var point_ID in region_polygons[region_polygons_ID][polygon_ID]) {

            // Inside point
            var coordinate = region_polygons[region_polygons_ID][polygon_ID][point_ID];
            var point = new GLatLng(coordinate[0], coordinate[1]);
            points.push(point);
          }

          // Display region on the map
          var polygon = new GPolygon(points, "#000", 1, 1, region['color'], 0.4);
          map.addOverlay(polygon);
        }
      }
    }

    /*
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
    */
  }
  else {
    alert(response['msg']);
  }
}

// Load google maps
google.load("maps", "2.x", {"other_params":"sensor=false"});
google.setOnLoadCallback(initialize);
