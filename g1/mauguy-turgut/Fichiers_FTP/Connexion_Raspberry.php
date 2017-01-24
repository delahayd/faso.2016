<?php
include($_SERVER['DOCUMENT_ROOT']."/testConnexion.php");
testConnexion();
?>
<!DOCTYPE html>
<html>
    <head>
        <meta charset="UTF-8" />
		<meta name="description" content="Raspberry du site Onama"/>
		<meta name="Content-Language" content="fr">
		<meta name="Author" content="Fabien TURGUT">
		<title>Connexion Rasp</title>
		<link rel="stylesheet" href="../Style.css" />
		<link rel="stylesheet" href="Style_perso.css" />
		<link rel="shortcut icon" type="image/x-icon" href="../TeteCerf.png" />
		<meta name="google-site-verification" content="hVyIUPTunit1_d7YZHXMSKpeCkrk069v93y2Mi1w3Ys" />
		<meta name="google-site-verification" content="ZPvIeZYs7R11L4CqtGYttbTV-FOk7dwbukl6AsxHq2o" />
		<link rel="alternate" hreflang="fr" href="http://onama.fr/" />
    </head>
		<?php 
		include("../header.php");
		include("../nav.php");
		?>
	<body>
		<div class="overlay" onclick="closeOverlay()">
			<p style="color: white; text-align: left; padding-left: 33%">Cliquer pour quitter</p>
			<img class="ImageOverlay" src="" alt="Photo de diapo"/>
		</div>
		<div class="page">
			<form method="post" action="controller/Controlleur_ConnexionRaspberry.php">
				<h3>Entrez vos identifiants</h3>
				<input type="text" placeholder="Adresse Mail" name="mailRaspberry" id="mailRaspberry"/><br>
				<input type="password" placeholder="Mot de passe" name="passwordRaspberry" id="passwordRaspberry"/><br>
				<input type="submit" value="Entrer"/>
			</form>
			<form method="post" action="controller/Controlleur_MotDePasseOublie.php">
				<input placeholder="Adresse mail" type="mail" name="mailRaspberry"/>
				<input type="submit" value="Mot de passe oublié"/>
			</form>
			<a class="Bouton" href="Inscription_Raspberry.php">Inscription</a>
		</div>
		<script src="../jQuery.js"></script>
		<script src="../script.js"></script>
    </body>
</html>