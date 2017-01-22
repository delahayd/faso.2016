<?php 

require_once ('../model/incident.php');
require_once ('../model/Activation.php');

	$status = htmlspecialchars($_GET['status']);

	$status = str_replace('_', ' ', $status);

	$activationid=activation::get_last_activation();
	
	incident::add_new_incident($status,$activationid['Activation_Id']);

	$incident=incident::get_last_status();

	require_once('../email/Email_Alert_New_Incident.php');



?>