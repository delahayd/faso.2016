<?php
class incident
{

	public static function add_new_incident($status,$activationId)
	{
		require_once('pdo.php');
		$domoraspbd=connexion();

		$req = $domoraspbd->prepare('INSERT INTO Incident(Incident_Status,Activation_Id) VALUES (:status,:activationId)');
		$req->bindParam(':status',$status);
		$req->bindParam(':activationId',$activationId);

		$req->execute();
	}

	public static function get_last_status()
	{
		require_once('pdo.php');
		$domoraspbd=connexion();

		$req = $domoraspbd->query("SELECT * FROM Incident WHERE Incident_Id=(SELECT MAX(Incident_Id) FROM Incident)");

		$data=$req->fetch();

		return $data;
	}

	public static function get_last_status_activation($activationid)
	{
		require_once('pdo.php');
		$domoraspbd=connexion();

		$req = $domoraspbd->query("SELECT * FROM Incident WHERE Activation_Id='".$activationid."'");
		

		$data=$req->fetch();

		return $data;
	}

	public static function get_all_incident()
	{
		require_once('pdo.php');
		$domoraspbd=connexion();

		$req = $domoraspbd->query("SELECT * FROM incident");

		$data=$req->fetchAll();

		return $data;
	}

	public static function get_20_incident()
	{
		require_once('pdo.php');
		$domoraspbd=connexion();

		$req = $domoraspbd->query("SELECT * FROM incident ORDER BY incidentId DESC LIMIT 20 ");

		$data=$req->fetchAll();

		return $data;
	}

/*Cette fonction permet de rechercher les activités liées à un statut placé en paramètre.*/
	

	public static function update_status($status,$Id)
	{
		require_once('pdo.php');
		$domoraspbd=connexion();

		$req = $domoraspbd->prepare("UPDATE Incident SET Incident_Status =:status WHERE Incident_Id =:Id");
		$req->bindParam(':status',$status);
		$req->bindParam(':Id',$Id);

		$req->execute();
	}

}

?>