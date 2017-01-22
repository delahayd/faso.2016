<?php
    $headers ='From: DomoRasp <contact@jamesterrien.fr>'."\n";
    $headers .='Reply-To: contact@jamesterrien.fr'."\n";
    $headers .='Content-Type: text/html; charset="UTF-8"'."\n";
    $headers .='Content-Transfer-Encoding: 8bit';
    $message =' <html>
      <head>
       <title>Incident Clos ! </title>
      </head>
      <body>
      <h3>L\'incident a été résolu : </h3>

      <p>  L\'alarme activée à '.date_format(date_create($id['Activation_Begin_Add_Date']),'H:i:s').' le '.date_format(date_create($id['Activation_Begin_Add_Date']),'d/m/y').'  a été désactivée à  '.date_format(date_create($id['Activation_End_Date']),'H:i:s').' le '.date_format(date_create($id['Activation_End_Date']),'d/m/y').' !  </p>

      <a href="http://www.jamesterrien.fr">Mon Dashboard</a>

      
      </body>
     </html>';


    mail('ilias.mellah@gmail.com', 'FIN ALERTE : Alarme désactivée ! ',$message, $headers); 
?>