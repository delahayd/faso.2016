<HTML>
 <HEAD>
<title>Systeme de surveillance </title>
<link rel=stylesheet href=../style.css type=text/css>
<meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
</HEAD>



<BODY bgcolor=white body text=#163233>
<img src="../images/banniere.jpg" align=center; width=100%, height=40%>


<h1 align=center>Site de gestion du systeme de surveillance Waleed-IGRASP</h1>

<div id="menu">
  <ul id="onglets">
    <li><a href="../index.php"> Accueil </a></li>
    <li><a href="../activation.php"> Lancer le système </a></li></li>
    <li><a href="../controller_mail.php"> Configurer son profil </a></li>
    <li class="active"><a href="photo.php"> Accès aux photos </a></li>
    <li><a href="../propos.html"> A propos </a></li>
  </ul>
</div>




<h3> Acces aux photos</h3>

<?
//declaration de la variable de couleur de ligne
 $coul_ligne = "#FFFFFF";
 
//lecture de tous les fichiers jpg du repertoire
//::::::::::::::::::::::::::::::::::::::::::::::
        $handle=opendir('.');
 
//creation du tableau
        $f=array();
        $nf=0;
?>
<table style=text-align:center>
<thead>
		<tr>
			<th> Photos prises </th>
			<th> Date </th>
		</tr>
	</thead>
<?php
 while($file = readdir($handle))
        {
        //tant qu'on a des jpg
         if ($file != "." && $file != ".." && ereg(".jpg",$file))
                {
                //stockage dans un tableau
                 $f[$nf++]=$file;
                }
        }
 
        //on trie le tableau
                sort($f);
 
                 for ($i=0;$i<count($f);$i++)
                 {

 
                  // On écrit le lien 
                  
                  
                  echo "<tr><td> <img src=\"".$f[$i]."\" , width=420, height=420 </td> ";
         	  $nomstring = " ".basename($f[$i], ".jpg").PHP_EOL;
			
		  $annee = substr($nomstring,5,4);
	          $mois = substr($nomstring,9,2);
	          $jour = substr($nomstring,11,2);
		  $heure = substr($nomstring,14,2);
		  $minute = substr($nomstring,16,2);
		  $seconde = substr($nomstring,18,2); 
			

		  $nom = "Prise le $jour/$mois/$annee à $heure:$minute:$seconde";
		  echo "<td>".$nom."</td> </tr>" ; 
	 
		  
 
		
                  
                 }
   		closedir($handle);
//::::::::::::::::::::::::::::::::::::::::::::::
?>


</table>
</BODY>
</html>
