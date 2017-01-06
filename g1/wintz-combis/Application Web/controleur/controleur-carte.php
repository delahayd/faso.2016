<?php
	if(isset($_POST["action"]) && $_POST["action"] == "ADD"){
		if($_POST["name"] == ""){
			header("location:../views/carte.php?erreur=PSEUDO_EMPTY");
		}
		else {
			$bdd = new PDO("");
			$req = $bdd->query("SELECT * FROM Users WHERE user_name='".$_POST["name"]."'");
			$res = $req->fetchAll();
			if(count($res)>0){
				header("location:../views/carte.php?erreur=PSEUDO_OCCUPE");
			}
			else{
				$req = $bdd->prepare("INSERT INTO Users(user_id,user_name) VALUES(?,?)");
				$res = $req->execute(array("user_id" => '',"user_name" => $_POST["name"]));
				if($res){
					header("location:../views/carte.php?erreur=AUCUNE");
				}
				else{
					header("location:../views/carte.php?erreur=INCONNUE");
				}
			} 
		}
	}
	else if(isset($_POST["action"]) && $_POST["action"] == "GET"){
		$bdd = new PDO("");
		$req = $bdd->query("SELECT * FROM Positions WHERE position_user='".$_POST["select"]."'");
		$res = $req->fetchAll();
		echo json_encode($res);
	}
	
?>