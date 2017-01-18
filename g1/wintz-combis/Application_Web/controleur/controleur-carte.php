<?php
  require_once("../function/function.php");
	if(isset($_POST["action"]) && $_POST["action"] == "ADD"){
		if($_POST["name"] == ""){
			header("location:../views/carte.php?erreur=PSEUDO_EMPTY");
		}
		else {
			$bdd = get_bdd();
			$req = $bdd->query("SELECT * FROM Users WHERE user_name='".$_POST["name"]."'");
			$res = $req->fetchAll();
			if(count($res)>0){
				header("location:../views/carte.php?erreur=PSEUDO_OCCUPE");
			}
			else{
				$req = $bdd->prepare("INSERT INTO Users(user_id,user_name) VALUES(?,?)");
			     $res = $req->execute(array('',$_POST["name"]));
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
		$bdd = get_bdd();
		$req = $bdd->query("SELECT * FROM Positions WHERE position_user='".$_POST["select"]."'");
		$res = $req->fetchAll();
		echo json_encode($res);
    header("location:../views/carte.php");
	}

  else if(isset($_POST["action"]) && $_POST["action"] == "SEND_POS"){
    /**
    * @var $_GET contient une requette get envoyé via curl depuis un raspberry.
    **/
    $bdd = get_bdd();
    $req = $bdd->prepare("INSERT INTO Positions(position_id,position_lat,position_lng,position_date,position_user) VALUES(?,?,?,?,?)");
    var_dump($res = $req->execute(array('',$_POST["lat"],$_POST["lng"],$_POST["date"],$_POST["user"])));
    if($res){
      echo "La position a bien été enregistrée dans la base de donnée";
    }
    else{
      echo "Désolé mais une erreur est survenue lors de l'insertion de la position";
    }
  }
  var_dump($_GET);
  var_dump($_POST);

?>
