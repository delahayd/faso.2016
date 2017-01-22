<?php
    $headers ='From: DomoRasp <contact@jamesterrien.fr>'."\n";
    $headers .='Reply-To: contact@jamesterrien.fr'."\n";
    $headers .='Content-Type: text/html; charset="UTF-8"'."\n";
    $headers .='Content-Transfer-Encoding: 8bit';
    $message =' <html>
      <head>
       <title>ALERTE INTRUSION ! </title>
      </head>
      <body>
      <h3>Votre alarme a detecté un mouvement : </h3>

      <p> Un mouvement a été detecté par votre alarme à '.date_format(date_create($incident['Incident_Begin_Add_Date']),'H:i:s').' le '.date_format(date_create($incident['Incident_Begin_Add_Date']),'d/m/y').' .  </p>

      <a href="http://www.jamesterrien.fr">Mon Dashboard</a>

      
      </body>
     </html>';


    mail('ilias.mellah@gmail.com', 'ALERTE : Alarme déclenchée ! ',$message, $headers); 
?>