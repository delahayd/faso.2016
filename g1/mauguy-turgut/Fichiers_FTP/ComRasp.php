<?php
include($_SERVER['DOCUMENT_ROOT']."/testConnexion.php");
testConnexion();
if(!empty($_POST["IdRasp"]))
{
	$IdRasp = $_POST["IdRasp"];
	$req = $bdd->prepare("SELECT * FROM raspberry WHERE Id = ?");
	$req->execute(array($IdRasp));
	$data = $req->fetch();
	if(empty($data["Id"]))
	{
		$req = $bdd->prepare("INSERT INTO raspberry (Id,lastCo, reception) VALUES (?,NOW(), reception)");
		$req->execute(array($IdRasp));
		mkdir("Raspberry".$IdRasp);
	}
	else
	{
		$req = $bdd->prepare("UPDATE raspberry SET lastCo = NOW(), reception = 1 WHERE Id = ?");
		$req->execute(array($IdRasp));
	}
	echo '{"mail" : "'.$data['mail'].'", "infSup" : "'.$data['infSup'].'", "distance" : "'.$data['distance'].'", "tpsLatence" : "'.$data['tpsLatence'].'", "etatProgramme" : "'.$data['etatProgramme'].'"}';
}
?>