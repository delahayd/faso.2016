<?php
class member
{

public static function connexiontest($UserPassword,$User_Mail)
{
	require_once('pdo.php');
	$domoraspbd=connexion();
   //connecté à la base de donnée 

	$req = $domoraspbd->prepare("SELECT User_Password FROM User WHERE User_Mail='".$User_Mail."'");

	$req->execute();
	$data=$req->fetch();

	return ($data['User_Password']==$User_Password);
	
}
public static function add_cookie_code($User_Mail,$cookiecode){

	require_once('pdo.php');
	$domoraspbd=connexion();

	$req = $domoraspbd->prepare("UPDATE User SET User_Cookie_Code =:User_Cookie_Code WHERE User_Mail=:User_Mail");
	$req->bindParam(':User_Cookie_Code',$cookiecode);
	$req->bindParam(':User_Mail',$User_Mail);

	$req->execute();
}

public static function get_UserId ($cookiecode){
	require_once('pdo.php');
	$domoraspbd=connexion();


	$req = $domoraspbd->prepare("SELECT User_Id FROM User WHERE User_Cookie_Code='".$cookiecode."'");

	$req->execute();
	$data=$req->fetch();

	return $data;
}

public static function get_name($Userid){
	require_once('pdo.php');
	$domoraspbd=connexion();


	$req = $domoraspbd->prepare("SELECT User_First_Name FROM User WHERE User_Id=:id");
	$req->bindParam(':id',$Userid);

	$req->execute();
	$data=$req->fetch();

	return $data;
}

}

?>