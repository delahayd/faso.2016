<?php
	require_once ('../model/user.php');

	
	$mdp = sha1(sha1(htmlspecialchars($_POST['mdp'])));
	$mail = htmlspecialchars($_POST['email']);
	

	if (empty($mdp)|| empty($mail)) {
		$messageErreur = "Vous n'avez pas remplis tous les champs ! Merci de completer les champs manquants ! ";
		
		require("../view/errorPage.php");
	}
	elseif (!(filter_var($mail, FILTER_VALIDATE_EMAIL))) {
		$messageErreur = "Votre email n'est pas valide  ! ";
		
		require("../view/errorPage.php");	
	}
	else
	{
		if(User::Connexion_Test($mdp,$mail))
		{
			$cookiecode=substr(str_shuffle("0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"), 0, 20);


			

			setcookie('codeconnexion', $cookiecode, time()+(500), "/");

			User::Add_Cookie_Code($mail,$cookiecode);
			
			header("Location: http://88.191.130.33/premier.pl");
		}
		else
		{
			$messageErreur = "Email ou mot de passe erroné ";
		
			require("../view/errorPage.php");	
		}

		
		
		
	}