
function initMap(){
	/* Créé une nouvelle carte google dans l'élément d'id "map" */
	var map = new google.maps.Map(document.getElementById('map'), {zoom: 8});
	/* On récupère la position de l'utilisateur */ 
	if(navigator.geolocation){
		navigator.geolocation.getCurrentPosition(function(position) {
			console.log(position);
			var initialLocation = new google.maps.LatLng(position.coords.latitude,position.coords.longitude);
			setMap(initialLocation,map);
		});
	}
	else{
		/*Si on ne peut pas récupérer la position via le navigateur on place le centre de la carte à montpellier */
	    var initialLocation = new google.maps.LatLng(43.62505, 3.862038);
	    setMap(initialLocation,map);
	}
	
}

function setMap(initialLocation,map){
	
	map.setCenter(initialLocation);
	var marker = new google.maps.Marker({
		position: initialLocation,
		title: "Je suis là"
	});
	marker.setMap(map);
}