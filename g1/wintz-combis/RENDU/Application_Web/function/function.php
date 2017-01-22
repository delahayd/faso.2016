<?php

  function get_bdd(){
    return new PDO('mysql:host=mysql.hostinger.fr;dbname=u852548259_fas', "u852548259_fas", "projetfas");
  }
	function affiche_select_utilisateur(){
		$bdd = get_bdd();
		$req = $bdd->query("SELECT * FROM Users");
		$res = $req->fetchAll();
    if(count($res)== 0){
      $content = "<p>Aucun utilisateur pour l'instant</p>";
    }
    else{
      $content = "<select name='select'>";
  		foreach ($res as $e) {
  			$content .= "<option value='".$e["user_name"]."'>".$e["user_name"]."</option>";
  		}
  		$content .= "</select>";
    }
    return $content;
	}
?>
