<?php
include($_SERVER['DOCUMENT_ROOT']."/testConnexion.php");
testConnexion();
if(empty($_SESSION["IdUserRasp"]))
{
	header("Location: Connexion_Raspberry.php");
}
require_once("controller/Controlleur_Page_Gestion_Raspberry.php");
?>
<!DOCTYPE html>
<html>
    <head>
        <meta charset="UTF-8" />
		<meta name="description" content="Raspberry du site Onama"/>
		<meta name="Content-Language" content="fr">
		<meta name="Author" content="Fabien TURGUT">
		<title>Gestion Compte</title>
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
			<a class="Bouton" href="deconnexion.php">Deconnexion</a>
			<h2>Gestion du compte</h2>
			<h3>Liste des Raspberry :</h3>
			<ul>
			<?php
			foreach($raspberrys as $idRasp)
			{?>
				<li><a href="Raspberry.php?Id=<?php echo htmlspecialchars($idRasp);?>">Raspberry<?php echo htmlspecialchars($idRasp);?></a></li>
			<?php
			}
			?>
			</ul>
			<form method="post" action='controller/Controlleur_Ajouter_Raspberry.php'>
				<input type="text" placeholder="xx:xx:xx:xx:xx:xx" title="adresse MAC du Raspberry" name="IdRasp"/>
				<input type="submit" value="Ajouter un Raspberry"/>
			</form>
			<h3>Modifier le mot de passe :</h3>
			<form method="post" action="controller/Controlleur_ModifMDP_Raspberry.php">
				<input type="password" placeholder="Mot de passe actuel" name="passwordRaspberry"/><br>
				<input type="password" placeholder="Password" name="newPasswordRaspberry"/><br>
				<input type="password" placeholder="Password" name="newPasswordRaspberry2"/><br>
				<input type="submit" name="nomForm" value="Modifier"/>
			</form>
		</div>
		<script src="../jQuery.js"></script>
		<script src="../script.js"></script>
    </body>
</html>