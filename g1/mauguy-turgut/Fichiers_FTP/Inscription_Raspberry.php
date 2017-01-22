<?php
include($_SERVER['DOCUMENT_ROOT']."/testConnexion.php");
testConnexion();
include("controller/Controlleur_Page_ConnexionRaspberry.php");
?>
<!DOCTYPE html>
<html>
    <head>
        <meta charset="UTF-8" />
		<meta name="description" content="Raspberry du site Onama"/>
		<meta name="Content-Language" content="fr">
		<meta name="Author" content="Fabien TURGUT">
		<title>Inscription Rasp</title>
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
			<?php if(isset($messageErreur))
			{?>
			<p><?php echo $messageErreur; ?></p>
			<a href="ConnexionRaspberry.php">Retour</a>
			<?php
			}?>
			<form method="post" action="controller/Controlleur_Inscription_Raspberry.php">
				<h3>Entrez un mail et deux fois le meme mot de passe</h3>
				<input type="mail" placeholder="Adresse Mail" name="mailRaspberry"/><br>
				<input type="password" placeholder="Password" name="passwordRaspberry"/><br>
				<input type="password" placeholder="Password" name="passwordRaspberry2"/><br>
				<input type="submit" name="nomForm" value="Inscription"/>
			</form>
		</div>
		<script src="../jQuery.js"></script>
		<script src="../script.js"></script>
    </body>
</html>