<?php
include($_SERVER['DOCUMENT_ROOT']."/testConnexion.php");
testConnexion();

if(empty($_POST["IdRasp"]))
{
	$messageErreur = "Renter un Id.";
	header("Location: ../Erreur.php?erreur=".$messageErreur);
}
else
{
	$IdRasp = str_replace(":","",$_POST["IdRasp"]);
	echo $IdRasp;
	$req = $bdd->prepare("SELECT * FROM raspberry WHERE Id = ?");
	$req->execute(array($IdRasp));
	$data = $req->fetch();
	if(empty($data["Id"]))
	{
		$messageErreur = "Ce raspberry n'a encore jamais été connecté.";
		//header("Location: ../Erreur.php?erreur=".$messageErreur);
	}
	else
	{
		if(empty($data["User_Id"]))
		{
			$req = $bdd->prepare("UPDATE raspberry SET User_Id = ? WHERE Id = ?");
			$req->execute(array($_SESSION["IdUserRasp"],$IdRasp));
			header("Location: ../Gestion_Raspberry.php");
		}
		else
		{
			$messageErreur = "Ce raspberry appartient déjà à un autre utilisateur.";
			header("Location: ../Erreur.php?erreur=".$messageErreur);
		}
	}
}
?>