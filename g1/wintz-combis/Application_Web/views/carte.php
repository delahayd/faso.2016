<!DOCTYPE html>
<html lang="fr">
	<head>
		<link rel="stylesheet" href="../css/theme.css">
    <link rel="icon" type="image/png" href="../img/polytech.png" />
		<script async defer src="https://maps.googleapis.com/maps/api/js?key=AIzaSyBxWZNOMx3hmeUAbhwbKzO9jJfmp6NoNFY"
  type="text/javascript"></script>
  		<script src="../js/controleur-carte.js" type="text/javascript"></script>
      <style>
        #map{
          height:500px;
          width:90%;
        }
      </style>
	</head>
	<body onload="initMap()">

		<h1>Carte de Tracking du raspberry</h1>
    <?php
      if(isset($_GET["erreur"]) && $_GET["erreur"] == "PSEUDO_VIDE"){
        echo "<div class='error_message'><p>Le pseudo doit contenir au moins un caractère</p></div>";
      }
      else if($_GET["erreur"] == "AUCUNE"){
        echo "<div class='success_message'><p>L'utilisateur a bien été ajouté</p></div>";
      }
      else if($_GET["erreur"] == "INCONNUE"){
        echo "<div class='error_message'><p>Erreur de connection avec la base de données essayer plus tard.</p></div>";
      }
      else if($_GET["erreur"] == "PSEUDO_OCCUPE"){
        echo "<div class='error_message'><p>Le pseudo est déjà prit</p></div>";
      }
    ?>
		<form action="../controleur/controleur-carte.php" method="POST">
      <label>Utilisateur courant </label>
			<?php
        require_once("../function/function.php");
        echo affiche_select_utilisateur();
      ?>
      <br/>
      <input type="submit" value="Afficher le Parcours">
			<input type="hidden" name="action" value="GET">
		</form>

    <form action="../controleur/controleur-carte.php" method="POST">
			<label for="name">Ajouter un nouvel utilisateur</label><br/>
			<input type="text" id="name" name="name" placeholder="Entrez un nom">
			<input type="hidden" name="action" value="ADD">
			<input type="submit" value="Valider">
		</form>
		<div id="map">
		</div>

	</body>
</html>
