
// Call this function when the page has been loaded
function initialize() {
  var map = new google.maps.Map2(document.getElementById("ting_gmap"));
  map.setCenter(new google.maps.LatLng(56.016808, 10.431763), 7);
  map.setMapType(G_SATELLITE_MAP);

  // Request coordinates


  // Insert polygons
  
}

// Load google maps
google.load("maps", "2.x", {"other_params":"sensor=false"});
google.setOnLoadCallback(initialize);
