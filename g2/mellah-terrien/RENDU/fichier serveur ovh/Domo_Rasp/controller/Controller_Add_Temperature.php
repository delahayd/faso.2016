<?php 

require_once ('../model/temperature.php');


	$temp = htmlspecialchars($_GET['temp']);
	
	temperature::add_new_temperature($temp);


?>