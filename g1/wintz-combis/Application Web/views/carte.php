<!DOCTYPE html>
<html lang="fr">
	<head>
		<link rel="stylesheet" href="theme.css">

		<script async defer src="https://maps.googleapis.com/maps/api/js?key=AIzaSyBxWZNOMx3hmeUAbhwbKzO9jJfmp6NoNFY"
  type="text/javascript"></script>
  		<script src="../js/controleur-carte.js" type="text/javascript"></script>
	</head>
	<body onload="initMap()">

		<h1>Carte de Tracking du raspberry</h1>
		<form action="../controleur/controleur-carte.php" method="POST">
			<?php affiche_select_utilisateur(); ?>
			<input type="hidden" name="action" value="GET">
		</form>
		<form action="../controleur/controleur-carte.php" metho="POST">
			<?php 
				if(isset($_GET["erreur"]) && $_GET["erreur"] == "PSEUDO_VIDE"){
					echo "<div class='error_message'><p>Le pseudo doit contenir au moins un caractère</p></div>";
				}
				else if($_GET["erreur"] == "AUCUNE"){
					echo "<div class='success_message'><p>L'utilisateur a bien été ajouté</p></div>"
				}
				else if($_GET["erreur"] == "INCONNUE"){
					echo "<div class='error_message'><p>Erreur de connection avec la base de données essayer plus tard.</p></div>"
				}
				else{
					echo "<div class='error_message'><p>Le pseudo est déjà prit</p></div>";
				}
			?>
			<label for="name">Ajouter un nouvel utilisateur</label>
			<input type="text" id="name" name="name" placeholder="Entrez un nom">
			<input type="hidden" name="action" value="ADD">
			<input type="submit" value="Valider">
		</form>
		<div id="map">
		</div>

	</body>
</html>