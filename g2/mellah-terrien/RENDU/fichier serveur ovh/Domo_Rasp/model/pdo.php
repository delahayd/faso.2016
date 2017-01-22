<?php
function connexion()
{
	try
{
	$domoraspbd = new PDO('mysql:host=jamesternedomo.mysql.db;dbname=jamesternedomo;charset=utf8','jamesternedomo','Moinscher86');
}
catch (Exception $e)
{
        die('Erreur : ' . $e->getMessage());
}
return($domoraspbd);
}
?>