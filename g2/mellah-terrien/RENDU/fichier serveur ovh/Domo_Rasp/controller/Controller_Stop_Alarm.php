<?php 

require_once ('../model/Activation.php');

	$end=date("Y-m-d H:i:s");
	
	$id=activation::get_last_activation();

	activation::end_activation($end,$id['Activation_Id']);

	require_once('../email/Email_Alert_End_Incident.php');



?>