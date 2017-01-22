<?php
$IdRasp = htmlspecialchars($_GET["Id"]);
$req = $bdd->prepare("SELECT * FROM raspberry WHERE Id = ?");
$req->execute(array($IdRasp));
$data = $req->fetch();
if(empty($data["User_Id"]) || $data["User_Id"] != $_SESSION["IdUserRasp"])
{
	header("Location: Gestion_Raspberry.php");
}
else
{
	$mailRasp = $data["mail"];
	$infSupRasp = $data["infSup"];
	$distance = $data["distance"];
	$tpsLatence = $data["tpsLatence"];
	$etatProgramme = $data["etatProgramme"];
	$reception = $data["reception"];
	if($reception)
	{
		$reception = "Paramètres reçus";
	}
	else
	{
		$reception = "Paramètres en attente de reception";
	}
	$lastCo = $data["lastCo"];$lastCo = new DateTime($lastCo);
	$lastCo = mktime($lastCo->format("H"), $lastCo->format("i"), $lastCo->format("s"), $lastCo->format("m"), $lastCo->format("d"), $lastCo->format("Y"));
	$second = time() - $lastCo;
	if($second > 15)
	{
		$etat = "Hors ligne";
	}
	else
	{
		$etat = "En ligne";
	}
	if($dossier = opendir('Raspberry'.$IdRasp))
	{
		while(false !== ($fichier = readdir($dossier)))
		{
			if($fichier != '.' && $fichier != '..' && $fichier != 'index.php')
			{
				$images[] = $fichier;
			}
		}
		arsort($images);
		$nbrImg = count($images);
	}
}
?>
