<!doctype html>

<html lang="en">
  <head>
    <title>Connexion DomoRasp</title>
    <meta name="Content-Type" content="UTF-8">
    <meta name="Content-Language" content="fr">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1.0, minimum-scale=1.0">
    <link rel="stylesheet" href="../CSS/material.css">
	<link rel="stylesheet" href="../CSS/styles.css">
	<script src="../CSS/material.js"></script>
   

  </head>

  <body>
	
  	
  	<div class="boite-connexion">

  		<h2>DOMO RASP</h2>

  		<form method="post" action="../controller/Controller_Connexion.php">
  		  <div class="mdl-textfield mdl-js-textfield mdl-textfield--floating-label form-connexion">
  		    <input class="mdl-textfield__input" type="text" id="email" name="email">
  		    <label class="mdl-textfield__label" for="sample3">Mail</label>
  		  </div>
  	
  		  <div class="mdl-textfield mdl-js-textfield mdl-textfield--floating-label form-connexion">
  		    <input class="mdl-textfield__input" type="password" id="mdp" name="mdp">
  		    <label class="mdl-textfield__label" for="sample3">Password</label>
  		  </div>

        <div class="valid-button">
          <button class="mdl-button mdl-js-button mdl-button--primary" id="submit" value="valider">Submit
          </button>
        </div>

  		</form>

  	</div> <!-- Fin boite connexion-->


	  	



  </body>

  </html>