<?php
include($_SERVER['DOCUMENT_ROOT']."/testConnexion.php");
testConnexion();

if(empty($_POST["IdRasp"]) && empty($_GET["IdRasp"]))
{
	header("Location: ../Gestion_Raspberry.php");
}
else
{
	$IdRasp = (empty($_POST["IdRasp"])) ? htmlspecialchars($_GET["IdRasp"]) : htmlspecialchars($_POST["IdRasp"]);
	$req = $bdd->prepare("SELECT * FROM raspberry WHERE Id = ?");
	$req->execute(array($IdRasp));
	$data = $req->fetch();
	if($data["User_Id"] != $_SESSION["IdUserRasp"])
	{
		header("Location: ../Gestion_Raspberry.php");
	}
	else
	{
		if(!empty($_GET["action"]))
		{
			if($_GET["action"] == "suppr")
			{
				if(empty($_GET["img"]))
				{
					$messageErreur = "Il n'y a pas d'image ne paramètre.";
					header("Location: ../Erreur.php?erreur=".$messageErreur);
				}
				else
				{
					$image = htmlspecialchars($_GET["img"]);
					unlink("../Raspberry".$IdRasp."/".$image);
					if(empty($_GET["ajax"]))
					{
						header("Location: ../Raspberry.php?Id=".$IdRasp);
					}
					else
					{
						echo "suppr";
					}
				}
			}
			elseif($_GET["action"] == "supprAll" || $_GET["action"] == "retirerRasp")
			{
				if($_GET["action"] == "retirerRasp")
				{
					$req = $bdd->prepare("UPDATE raspberry SET User_Id = 0, etatProgramme = 0, mail = '' WHERE Id = ?");
					$req->execute(array(htmlspecialchars($IdRasp)));
					header("Location: ../Gestion_Raspberry.php");
				}
				if($dossier = opendir('../Raspberry'.$IdRasp))
				{
					while(false !== ($fichier = readdir($dossier)))
					{
						if($fichier != '.' && $fichier != '..' && $fichier != 'index.php')
						{
							unlink("../Raspberry".$IdRasp."/".$fichier);
						}
					}
				}
				header("Location: ../Raspberry.php?Id=".$IdRasp);
			}
			else
			{
				$messageErreur = "Action impossible.";
				header("Location: ../Erreur.php?erreur=".$messageErreur);
			}			
		}
		elseif(empty($_POST["mailRasp"]) || empty($_POST["infSupRasp"]) || empty($_POST["distance"]) || empty($_POST["tpsLatence"]))
		{
			$messageErreur = "Tous les champs ne sont pas valide.";
			header("Location: ../Erreur.php?erreur=".$messageErreur);
		}
		else
		{
			$req = $bdd->prepare("UPDATE raspberry SET mail = ?, infSup = ?, distance = ?, tpsLatence = ?, etatProgramme = ?, reception = '0' WHERE Id = ?");
			$req->execute(array(htmlspecialchars($_POST["mailRasp"]), htmlspecialchars($_POST["infSupRasp"]), htmlspecialchars($_POST["distance"]), htmlspecialchars($_POST["tpsLatence"]), htmlspecialchars($_POST["etatProgramme"]),$IdRasp));
			header("Location: ../Raspberry.php?Id=".$IdRasp);
		}
	}
}
?>