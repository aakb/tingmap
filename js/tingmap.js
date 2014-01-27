
var map = null;
var count = 0;
var regions = null;
var population = 0;

function addCommas(nStr) {
  nStr += '';
  x = nStr.split('.');
  x1 = x[0];
  x2 = x.length > 1 ? '.' + x[1] : '';
  var rgx = /(\d+)(\d{3})/;
  while (rgx.test(x1)) {
    x1 = x1.replace(rgx, '$1' + '.' + '$2');
  }
  return x1 + x2;
}

// Call this function when the page has been loaded
var map;
function initialize() {
  var mapOptions = {
    zoom: 7,
    mapTypeId: google.maps.MapTypeId.TERRAIN,
    center: new google.maps.LatLng(56.016808, 10.431763)
  };
  
  map = new google.maps.Map(document.getElementById('ting_gmap'), mapOptions);

  // Request selected regions and population
  $.post('index.php', {'action' : 'loadselectedregions'}, tingmapResponse, 'json');
  $.post('index.php', {'action' : 'loadpopulation'}, populationResponse, 'json');

  // Request interested and not interested regions
  $.post('index.php', {'action' : 'loadinterestedregions'}, tingmapResponse, 'json');
  $.post('index.php', {'action' : 'loadnotinterestedregions'}, tingmapResponse, 'json');
}

function addRegionToMap(polylines, color, name) {

  var paths = new Array();

  for(var i=0; i<polylines.length;i++) {
    paths.push(google.maps.geometry.encoding.decodePath(polylines[i]))
  }

  var polygon = new google.maps.Polygon({
    map: map,
    paths: paths,
    strokeColor: '#000000',
    strokeOpacity: 1,
    strokeWeight: 1,
    fillColor: color,
    fillOpacity: 0.4
  });

  google.maps.event.addListener(polygon, "mouseover", function() {
    this.setOptions( { strokeWeight: 2, fillOpacity: 0.6});
  });
  google.maps.event.addListener(polygon, "mouseout", function() {
    this.setOptions( { strokeWeight: 1, fillOpacity: 0.4});
  });

  console.log(name);
}

function tingmapResponse(response) {

  if (response['status'] == 'selected_regions') {
    regions = response['regions'];

    for (var region_ID in regions) {
      var region = regions[region_ID];
      var region_polygons = region['region_polygons'];
      
      for (var region_polygons_ID in region_polygons) {
        // Inside region polygon
        var polylines = new Array();

        for (var polygon_ID in region_polygons[region_polygons_ID]) {
          // Inside polygon
          var data = region_polygons[region_polygons_ID][polygon_ID];
          // Create ploylines array
          polylines.push(data['Points']);
        }

        // Add polylines to map
        addRegionToMap(polylines, region['color'], region['name']);
      }
    }
  }
  else {
    alert(response['msg']);
  }
}

function populationResponse(response) {
  if (response['status'] == 'population') {
    var data = response['population'];

    // Ting population
    var total = $('#population #pop-total');
    $('.num', total).append(addCommas(data['total']));
    
    var selected = $('#population #pop-selected')
    $('.num', selected).append(addCommas(data['selected']));
    $('.pro', selected).append(pro(data['total'], data['selected']) + '%');

    var interested = $('#population #pop-interested')
    $('.num', interested).append(addCommas(data['interested']));
    $('.pro', interested).append(pro(data['total'], data['interested']) + '%');

    /* LAST MINUTE CHANGE - Calculate this as being remain % */
    var remain_pro = 100-(pro(data['total'], data['selected']) + pro(data['total'], data['interested']));
    var remain_num = data['total'] - data['selected'] - data['interested'];
    var not_interested = $('#population #pop-not-interested');
    $('.num', not_interested).append(addCommas(remain_num));
    $('.pro', not_interested).append((Math.round(remain_pro*10)/10) + '%');
  }
  else {
    alert(response['msg']);
  }
  
}

function pro(total, x) {
  var original = (x / total) * 100;
  return Math.round(original*10)/10;
}

google.maps.event.addDomListener(window, 'load', initialize);