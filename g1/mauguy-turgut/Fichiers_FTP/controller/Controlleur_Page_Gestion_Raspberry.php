<?php
$IdUser = $_SESSION["IdUserRasp"];
$raspberrys = [];
$req = $bdd->prepare("SELECT Id FROM raspberry WHERE User_Id = ?");
$data = $req->execute(array($IdUser));
while($data = $req->fetch())
{
	$raspberrys[] = $data["Id"]; 
}
?>