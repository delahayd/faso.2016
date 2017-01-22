<?php
class activation
{

	public static function add_new_activation()
	{
		require_once('pdo.php');
		$domoraspbd=connexion();

		$req = $domoraspbd->prepare('INSERT INTO Activation VALUES ()');

		$req->execute();
	}

	public static function get_last_activation()
	{
		require_once('pdo.php');
		$domoraspbd=connexion();

		$req = $domoraspbd->query("SELECT * FROM Activation WHERE Activation_Id=(SELECT MAX(Activation_Id) FROM Activation)");

		$data=$req->fetch();

		return $data;
	}

	public static function get_all_activation()
	{
		require_once('pdo.php');
		$domoraspbd=connexion();

		$req = $domoraspbd->query("SELECT * FROM Activation");

		$data=$req->fetchAll();

		return $data;
	}

	public static function get_20_activation()
	{
		require_once('pdo.php');
		$domoraspbd=connexion();

		$req = $domoraspbd->query("SELECT * FROM Activation ORDER BY Activation_Id DESC LIMIT 20 ");

		$data=$req->fetchAll();

		return $data;
	}

/*Cette fonction permet de rechercher les activités liées à un statut placé en paramètre.*/
	
	public static function end_activation($end,$id)
	{
		require_once('pdo.php');
		$domoraspbd=connexion();

		$req = $domoraspbd->prepare("UPDATE Activation SET Activation_End_Date=:enddate WHERE Activation_Id =:Id");
		$req->bindParam(':enddate',$end);
		$req->bindParam(':Id',$id);

		$req->execute();
	}
	

}

?>