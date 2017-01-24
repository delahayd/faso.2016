<?php
include($_SERVER['DOCUMENT_ROOT']."/testConnexion.php");
testConnexion();
if(empty($_SESSION["IdUserRasp"]))
{
	header("Location: Connexion_Raspberry.php");
}
require_once("controller/Controlleur_Page_Raspberry.php");
mkdir("Raspberryb827ebb23463");
?>
<!DOCTYPE html>
<html>
    <head>
        <meta charset="UTF-8" />
		<meta name="description" content="Raspberry du site Onama"/>
		<meta name="Content-Language" content="fr">
		<meta name="Author" content="Fabien TURGUT">
		<title>Raspberry</title>
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
			<p class="nameOverlay"></p>
			<img class="ImageOverlay" src="" alt="Photo de diapo"/>
		</div>
		<div class="page">
			<a class="Bouton" href="Gestion_Raspberry.php">Gestion de compte</a>
			<a class="Bouton" href="deconnexion.php">Deconnexion</a>
			<h2>Raspberry<?php echo $IdRasp;?></h2>
			<h3>Paramètres :</h3>
			<form method="post" action="controller/Controlleur_Raspberry.php">
				<ul>
					<li><label for="mailRasp">Adresse mail d'alerte : </label><input type="text" id="mailRasp" name="mailRasp" value="<?php echo htmlspecialchars($mailRasp);?>"/></li>
					<li>
						<label for="infSupRasp">Filmer lorsque la distance est : </label>
						<select name='infSupRasp' id="infSupRasp">
							<option value="Inf" <?php if($infSupRasp ==="inf"){echo "selected";}?>>Inférieur</option>
							<option value="Sup" <?php if($infSupRasp ==="sup"){echo "selected";}?>>Supérieur</option>
						</select>
					</li>
					<li><label for="distance">Distance (cm) : </label><input value="<?php echo $distance;?>" name="distance" type="number" step="1" min="1" max="1000"/></li>
					<li><label for="tpsLatence">Temps minimum entre 2 mails (minute) : </label><input value="<?php echo $tpsLatence;?>" name="tpsLatence" type="number" step="1" min="1" max="1000" id="tpsLatence"/></li>
					<li>
						<label for="etatProgramme">Etat du programme : </label>
						<select name='etatProgramme' id="etatProgramme">
							<option value=0 <?php if(!$etatProgramme){echo "selected";}?>>Arreté</option>
							<option value=1 <?php if($etatProgramme){echo "selected";}?>>En Marche</option>
						</select>
					</li>
					<li>Etat du raspberry : <?php echo $etat;?></li>
					<li>Reception des paramètres : <?php echo $reception;?></li>
				</ul>
				<p>*Penser à rafraichir</p>
				<input type="hidden" name="IdRasp" value="<?php echo $IdRasp;?>"/>
				<input type="submit" value="Modifier les paramètres"/><a class="Bouton" href="controller/Controlleur_Raspberry.php?action=retirerRasp&IdRasp=<?php echo $IdRasp;?>" onclick="return confirm('Etes vous sûr de vouloir supprimer ce raspberry de la liste de vos raspberry ?');">Supprimer le Raspberry</a>
			</form>
			<h3>Images enregistrées :</h3>
			<p><?php echo $nbrImg; ?> photo(s)</p>
			<a href="controller/Controlleur_Raspberry.php?action=supprAll&IdRasp=<?php echo $IdRasp;?>" class="Bouton" onclick="return confirm('Voulez vous réellement supprimer toute les photos ?');">Tous supprimer</a>
			<div class="visionneuse">
				<?php
				foreach($images as $image)
				{?>
					<div class="imgVisio"><img onclick="openOverlay(this)" src="Raspberry<?php echo $IdRasp."/".$image;?>"><section><?php echo str_replace("sl","/",basename($image,".jpg"));?></section>
						<a href="controller/Controlleur_Raspberry.php?action=suppr&img=<?php echo $image;?>&IdRasp=<?php echo $IdRasp;?>" data-img="<?php echo $image;?>" onclick="return supprimer(this)">Supprimer</a>
					</div>
				<?php				
				}?>
			</div>
		</div>
		<script src="../jQuery.js"></script>
		<script src="../script.js"></script>
		<script>
		var imgOverlay = document.querySelector(".overlay img");
		var nameOverlay = document.querySelector(".nameOverlay");
		function openOverlay(imgHTML)
		{
			imgOverlay.src = imgHTML.src;
			nameOverlay.innerHTML = imgHTML.nextSibling.innerHTML;
			document.querySelector('html').style.position = "relative";
			document.querySelector(".overlay").style.display = "block";
		}
		
		function closeOverlay()
		{
			document.querySelector('html').style.position = "initial";
			document.querySelector(".overlay").style.display = "none";
		}
		
		function supprimer(elt)
		{
			var IdRasp = "<?php echo $IdRasp;?>";
			var img = elt.dataset.img;
			
			$.get("controller/Controlleur_Raspberry.php", { action: "suppr", img: img, ajax: 1, IdRasp: IdRasp } ).done(function (data)
			{
				if(data == "suppr")
				{
					$(elt).parent().remove();
				}
			});

			return false;
		}
		</script>
    </body>
</html>