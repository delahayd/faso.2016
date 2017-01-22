<?php 

require_once ('../model/incident.php');


	$status = htmlspecialchars($_GET['status']);

	$incident=incident::get_last_status();

	incident::update_status($status,$incident['Incident_Id']);



?>