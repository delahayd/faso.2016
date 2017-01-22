<?php

	require_once ('../model/Activation.php');
	require_once ('../model/user.php');
	require_once ('../model/temperature.php');
	require_once ('../model/incident.php');

exec("http://88.191.130.33/temperature");

if (isset($_COOKIE['codeconnexion']))
{
	$cookieperso=$_COOKIE['codeconnexion'];
	$memberId=User::Get_User_Id($cookieperso);
	if (empty($memberId)) {
		
		header("Location: Controller_Page_Connexion.php");
	}
	else {
		$activation=activation::get_last_activation();
		$lastincident=incident::get_last_status_activation($activation['Activation_Id']);
		$lasttemp=temperature::get_Last_temperature();
		require "../view/dashboard.php";
	}
	
}
else
{
	header("Location: Controller_Page_Connexion.php");
}
