<?php
include($_SERVER['DOCUMENT_ROOT']."/testConnexion.php");
testConnexion();
?>
<!DOCTYPE html>
<html>
    <head>
        <meta charset="UTF-8" />
		<meta name="description" content="Erreur"/>
		<meta name="Content-Language" content="fr">
		<meta name="Author" content="Fabien TURGUT">
		<title>Erreur</title>
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
			<h3>Erreur :</h3>
			<p><?php echo htmlspecialchars($_GET["erreur"]);?></p>
			<a class="buton" href="javascript:history.go(-1)">Retour</a>
		</div>
		<script src="../jQuery.js"></script>
		<script src="../script.js"></script>
    </body>
</html>