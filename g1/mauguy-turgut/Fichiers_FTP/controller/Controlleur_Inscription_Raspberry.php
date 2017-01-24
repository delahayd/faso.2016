<?php
include($_SERVER['DOCUMENT_ROOT']."/testConnexion.php");
testConnexion();
if(empty($_POST["mailRaspberry"]) || empty($_POST["passwordRaspberry"]) || empty($_POST["passwordRaspberry2"]))
{
	$messageErreur = "Des champs sont vides.";
	header("Location: ../Erreur.php?erreur=".$messageErreur);
}
else
{
	$mailRasp = strtolower($_POST["mailRaspberry"]);
	$passwordRasp = $_POST["passwordRaspberry"];
	$passwordRasp2 = $_POST["passwordRaspberry2"];
	if(strlen($passwordRasp) < 8)
	{
		$messageErreur = "Le mot de passe doit faire au moins 8 caractères.";
		header("Location: ../Erreur.php?erreur=".$messageErreur);
	}
	elseif($passwordRasp != $passwordRasp2)
	{
		$messageErreur = "Les mots de passes ne sont pas identiques.";
		header("Location: ../Erreur.php?erreur=".$messageErreur);
	}
	else
	{
		$req = $bdd->prepare("SELECT Id FROM userRaspberry WHERE mail = ?");
		$req->execute(array($mailRasp));
		$data = $req->fetch();
		if(empty($data["Id"]))
		{
			echo $mailRasp." : ".$passwordRasp;
			$req = $bdd->prepare("INSERT INTO userRaspberry (mail,password) VALUES (?,?)");
			$req->execute(array($mailRasp,md5($passwordRasp)));
			$data = $req->fetch();
			$_SESSION["IdUserRasp"] = $data["Id"];
			header("Location: ../Gestion_Raspberry.php");
		}
		else
		{
			$messageErreur = "Adresse mail déjà utilisée.";
			header("Location: ../Erreur.php?erreur=".$messageErreur);
		}		
	}
}
?>