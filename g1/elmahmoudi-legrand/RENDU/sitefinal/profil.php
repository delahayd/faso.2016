<HTML>
 <HEAD>
<title>Systeme de surveillance </title>
<link rel=stylesheet href=style.css type=text/css>
<meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
</HEAD>


<body bgcolor=white body text=#163233>
<img src="images/banniere.jpg" align=center; width=100%, height=40%>


<h1 align=center>Gestion du profil utilisateur</h1>

<div id="menu">
  <ul id="onglets">
    <li> <a href="index.php"> Accueil </a></li>
    <li><a href="activation.php"> Lancer le système </a></li></li>
    <li class="active"><a href="controller_mail.php"> Configurer son profil </a></li>
    <li><a href="photos/photo.php"> Accès aux photos </a></li>
    <li><a href="propos.html"> A propos </a></li>
  </ul>
</div>


<p>Mail de la personne à alerter en cas d'intrusion :
<?php 
echo $mailadress;
?>
<br />
Modifier le mail : 
<form name="parametre" method="POST" action="controller_mail.php">
	<input type="text" name="mail" placeholder="Adresse mail" />
	<input type="submit" value="Valider" />
</form>

</body>
</html>
