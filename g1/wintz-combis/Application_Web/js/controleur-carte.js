function initMap(){
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
}
