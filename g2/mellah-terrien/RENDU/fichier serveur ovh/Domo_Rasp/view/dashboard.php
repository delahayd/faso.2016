<!doctype html>

<html lang="en">
  <head>
    <title>Dashboard</title>
    <meta name="Content-Type" content="UTF-8">
    <meta name="Content-Language" content="fr">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1.0, minimum-scale=1.0">
    <link rel="stylesheet" href="../CSS/material.css">
	<link rel="stylesheet" href="../CSS/styles.css">
	<script src="../CSS/material.js"></script>
   

  </head>

  <body>

    <div class="dashboard-title">
      <h1>
        DomoRasp - Dashboard
      </h1>
      

    </div>

<!-- =======================================================-->
    <div class="mdl-grid">

    <!-- =======================================================-->
      <div class="mdl-cell mdl-cell--6-col mdl-cell--8-col-tablet">
        <div class="alarm">

          <h2> Alarm </h2>
          <?php if(is_null($activation['Activation_End_Date'])) {?>
          <p>L'alarme est EN MARCHE depuis <?php echo date_format(date_create($activation['Activation_Begin_Add_Date']),'H:i:s') ; ?> le <?php echo date_format(date_create($activation['Activation_Begin_Add_Date']),'d/m/y') ; ?> !</p>
          <?php  } else { ?>
          <p> L'alarme est éteinte ! </p>
          
          <?php  } ?>
          <?php if(is_null($lastincident['Incident_Id'])) {?>
          <p> Aucune Alerte ! </p>
          <?php }else{ ?>
          <p> Dernière alerte à <?php echo date_format(date_create($lastincident['Incident_Begin_Add_Date']),'H:i:s') ; ?> le <?php echo date_format(date_create($lastincident['Incident_Begin_Add_Date']),'d/m/y') ; ?> est <?php echo $lastincident['Incident_Status'] ; ?>    </p>
          <?php }?>
          
          <div class="alarm-button">
            <button class="mdl-button mdl-js-button mdl-button--raised mdl-js-ripple-effect">
            ON
            </button>
            <button class="mdl-button mdl-js-button mdl-button--raised mdl-js-ripple-effect">
             OFF
            </button>
          </div>

          


        </div>

      </div>
    <!-- =======================================================-->

      <div class="mdl-cell mdl-cell--6-col mdl-cell--8-col-tablet">
        <div class="temperature">
          <h2> Temperature </h2>
          <p> Dernier relevé : <?php echo round($lasttemp['Temperature_Value'],2) ; ?>°C à <?php echo date_format(date_create($lasttemp['Temperature_Add_Date']),'H:i:s') ; ?> le <?php echo date_format(date_create($lasttemp['Temperature_Add_Date']),'d/m/y') ; ?> </p>

        </div>
      </div>

    <!-- =======================================================-->
      <div class="mdl-cell mdl-cell--6-col mdl-cell--8-col-tablet">
        <div class="sms">
          <h2> SMS </h2>

        </div>
      </div>
    </div>
	
  	
  	


	  	



  </body>

  </html>