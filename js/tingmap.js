
var map = null;
var count = 0;
var regions = null;

// Call this function when the page has been loaded
function initialize() {
  map = new google.maps.Map2(document.getElementById("ting_gmap"));
  map.setCenter(new google.maps.LatLng(56.016808, 10.431763), 7);
  map.setMapType(G_PHYSICAL_MAP);
  map.addControl(new GSmallMapControl());

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
          var points = region_polygons[region_polygons_ID][polygon_ID];
          // Display region on the map
          map.addOverlay(new GPolygon.fromEncoded({
                                                  polylines: [
                                                    {points: points['Points'],
                                                     levels: points['Levels'],
                                                     color: "#000000",
                                                     opacity: 1,
                                                     weight: 1,
                                                     numLevels: points['NumLevels'],
                                                     zoomFactor: points['ZoomFactor']}],
                                                  fill: true,
                                                  color: region['color'],
                                                  opacity: 0.4,
                                                  outline: true
                                                }));
        }
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
