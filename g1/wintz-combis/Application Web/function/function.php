<?php

	function affiche_select_utilisateur(){
		$bdd = new PDO("");
		$req = $bdd->query("SELECT * FROM Users");
		$res = $req->fetchAll();
		$content = "<select name='select'>";
		foreach ($res as $e) {
			$content .= "<option value='".$e["name"]."'>".$e["name"]."</option>";
		}
		$content .= "</select>";
	}
?>