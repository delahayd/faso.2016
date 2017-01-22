<?php
include($_SERVER['DOCUMENT_ROOT']."/testConnexion.php");
testConnexion();
if(empty($_SESSION["IdUserRasp"]))
{
	header("Location: ../Connexion_Raspberry.php");
}
if(empty($_POST["passwordRaspberry"]) || empty($_POST["newPasswordRaspberry"]) || empty($_POST["newPasswordRaspberry2"]))
{
	$messageErreur = "Des champs sont vides.";
	header("Location: ../Erreur.php?erreur=".$messageErreur);
}
else
{
	$IdUser = $_SESSION["IdUserRasp"];
	$passwordRasp = $_POST["passwordRaspberry"];
	$newPasswordRasp = $_POST["newPasswordRaspberry"];
	$newPasswordRasp2 = $_POST["newPasswordRaspberry2"];
	if($newPasswordRasp != $newPasswordRasp2)
	{
		$messageErreur = "Les deux mots de passe ne sont pas identiques.";
		header("Location: ../Erreur.php?erreur=".$messageErreur);
	}
	else
	{
		
		if(strlen($newPasswordRasp) < 8)
		{
			$messageErreur = "Le mot de passe doit faire au minimum 8 caractères.";
			header("Location: ../Erreur.php?erreur=".$messageErreur);
		}
		else
		{
			$req = $bdd->prepare("SELECT password FROM userRaspberry WHERE Id = ?");
			$req->execute(array($IdUser));
			$data = $req->fetch();
			echo md5($passwordRasp)." : ".$data["password"];
			if(md5($passwordRasp) != $data["password"])
			{
				$messageErreur = "Le mot de passe est incorrecte.";
				header("Location: ../Erreur.php?erreur=".$messageErreur);
			}
			else
			{	
				$req = $bdd->prepare("UPDATE userRaspberry SET password = ? WHERE Id = ?");
				$req->execute(array(md5($newPasswordRasp),$IdUser));
				header("Location: ../Gestion_Raspberry.php");
			}
		}
	}
}
?>