<?php
class User
{

public static function Connexion_Test($UserPassword,$UserMail)
{
	require_once('pdo.php');
	$domoraspbd=connexion();
   //connecté à la base de donnée 

	$req = $domoraspbd->prepare("SELECT User_Password FROM User WHERE User_Mail='".$UserMail."'");

	$req->execute();
	$data=$req->fetch();

	return ($data['User_Password']==$UserPassword);
	
}
public static function Add_Cookie_Code($UserMail,$cookiecode){

	require_once('pdo.php');
	$domoraspbd=connexion();

	$req = $domoraspbd->prepare("UPDATE User SET User_Cookie_Code =:UserCookieCode WHERE User_Mail=:UserMail");
	$req->bindParam(':UserCookieCode',$cookiecode);
	$req->bindParam(':UserMail',$UserMail);

	$req->execute();
}

public static function Get_User_Id ($cookiecode){
	require_once('pdo.php');
	$domoraspbd=connexion();


	$req = $domoraspbd->prepare("SELECT User_Id FROM User WHERE User_Cookie_Code='".$cookiecode."'");

	$req->execute();
	$data=$req->fetch();

	return $data;
}

public static function Get_User_Name($UserId){
	require_once('pdo.php');
	$domoraspbd=connexion();


	$req = $domoraspbd->prepare("SELECT User_First_Name FROM User WHERE User_Id=:id");
	$req->bindParam(':id',$UserId);

	$req->execute();
	$data=$req->fetch();

	return $data;
}

}

?>