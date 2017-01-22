function initMap(bool,tab){
  //nouvelle instance de carte google maps
  var map = new google.maps.Map(document.getElementById('map'), {
   zoom: 8
 });
 //centre de la carte par defaut
  var center = new google.maps.LatLng({lat:43.631497,lng:3.860603});

 //on recentre la map
 map.setCenter(center);
 //instance d'un nouveau marker google Maps.
 // placé au centre de la carte avec le texte "je suis là" en survol.
 var marker = new google.maps.Marker({
   position : center,
   map : map,
   title : "Je suis là!"
 });
 if(bool){
   var polyLineArray = [];
   for(var i=0;i<tab.length;i++){
     var pos  =new google.maps.LatLng({lat:parseFloat(tab[i].position_lat),lng:parseFloat(tab[i].position_lng)});
     polyLineArray.push(pos);
     var marker = new google.maps.Marker({
       position :pos,
       map:map,
       title : "Position de "+tab[i].position_user+" à "+tab[i].position_date
     });
   }
   var flightPath = new google.maps.Polyline({
    path: polyLineArray,
    geodesic: true,
    strokeColor: '#FF0000',
    strokeOpacity: 1.0,
    strokeWeight: 2
  });
  flightPath.setMap(map);
 }
}
function afficherPos(){
  var req = new XMLHttpRequest();
  var user = document.getElementsByName("select")[0].value;
  req.open('GET', "../controleur/controleur-carte.php?action=GET&select="+user, false);
  req.send();
  if(req.status == 200){
    var pos = JSON.parse(req.responseText);
    initMap(true,pos);
  }
}
