<!DOCTYPE html>
<html>
	<head>
		<title>Page de connexion</title>
		<meta http-equiv="Content-Type" content="text/html;charset=utf-8">
		<link rel="stylesheet" href="style.css">
	</head>
	<body bgcolor=white body text=#163233>
<img src="images/banniere.jpg" align=center; width=100%, height=40%>
	

<h1 align=center>Site de gestion du systeme de surveillance Waleed</h1>

<div id="menu">
  <ul id="onglets">
    <li ><a href="index.php"> Accueil </a></li>
    <li class="active"><a href="activation.php"> Lancer le système </a></li>
    <li><a href="controller_mail.php"> Configurer son profil </a></li>
    <li><a href="photos/photo.php"> Accès aux photos </a></li>
    <li><a href="propos.php"> A propos </a></li>
  </ul>
</div>


<h3> 	Activation du système Waleed</h3>
<div align=center>
<form name="question" method="post" action="controller_activation.php">


		
			Activer <input type="radio" name="allumer" value = 1  > <br>
			Désactiver<input type="radio" name="allumer" value = 0  > <br><br>
			
		
		




<input type="submit" name="suivant" value="Valider">
</div>
</body>
</html>

