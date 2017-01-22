<?php
class temperature
{
	public static function add_new_temperature($temp)
	{
		require_once('pdo.php');
		$domoraspbd=connexion();

		$req = $domoraspbd->prepare('INSERT INTO Temperature(Temperature_Value) VALUES (:temperature)');
		$req->bindParam(':temperature',$temp);

		$req->execute();
	}

	public static function get_Last_temperature()
	{
		require_once('pdo.php');
		$domoraspbd=connexion();

		$req = $domoraspbd->prepare("SELECT * FROM Temperature ORDER BY Temperature_Id DESC LIMIT 1");
		$req->execute();
		$data=$req->fetch();

		return $data;
	}

	public static function get_all_temperature()
	{
		require_once('pdo.php');
		$domoraspbd=connexion();

		$req = $domoraspbd->prepare("SELECT * FROM Temperature");
		$req->execute();
		$data=$req->fetchAll();

		return $data;
	}

	public static function get_20_temperature()
	{
		require_once('pdo.php');
		$domoraspbd=connexion();

		$req = $domoraspbd->query("SELECT * FROM Temperature ORDER BY Temperature_Id DESC LIMIT 20 ");

		$data=$req->fetchAll();

		return $data;
	}
}

?>