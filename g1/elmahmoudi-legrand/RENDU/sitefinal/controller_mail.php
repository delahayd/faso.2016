<?php 


system("sudo chmod 777 -R /opt/lampp/htdocs/*");


//lecture et fermeture
$usermail=fopen('usermail.txt','a+');
$mailadress=fgets($usermail);
//fclose($usermail);
$mail = !empty($_POST["mail"]) ? $_POST["mail"] : NULL;
//modification si nouveau mail



if(isset($mail))
	{
		//$usermail=fopen('usermail.txt','w');
		fseek($usermail,0);
		file_put_contents('usermail.txt', '');
		fputs($usermail,htmlspecialchars($mail));
		fclose($usermail);
		unset($_POST);
		require("confirmation_profil.php");
	}

else {
require("profil.php");
fclose($usermail);
}
?>

