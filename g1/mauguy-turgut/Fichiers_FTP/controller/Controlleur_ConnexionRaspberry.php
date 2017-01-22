<?php
include($_SERVER['DOCUMENT_ROOT']."/testConnexion.php");
testConnexion();
if(isset($_POST["mailRaspberry"]) && isset($_POST["passwordRaspberry"]))
{
	
	$mailRaspberry = strtolower($_POST["mailRaspberry"]);
	$passwordRaspberry = $_POST["passwordRaspberry"];
	$req = $bdd->prepare("SELECT Id, password FROM userRaspberry WHERE mail = ?");
	$req->execute(array($mailRaspberry));
	$data = $req->fetch();
	if(empty($data))
	{
		$messageErreur = "Mail ou mot de passe invalide.";
		header("Location: ../Erreur.php?erreur=".$messageErreur);
	}
	else
	{
		if(md5($passwordRaspberry) != $data["password"])
		{
			$messageErreur = "Mail ou mot de passe invalide.";
			header("Location: ../Erreur.php?erreur=".$messageErreur);
		}
		else
		{
			$_SESSION["IdUserRasp"] = $data["Id"];
			header("Location: ../Gestion_Raspberry.php");
		}
	}
}
else
{
	header("Location: ../Connexion_Raspberry.php");
}
?>