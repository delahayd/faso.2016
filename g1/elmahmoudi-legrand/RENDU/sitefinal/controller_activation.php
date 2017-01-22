<?php

$allumer = !empty($_POST["allumer"]) ? $_POST["allumer"] : NULL;

if($allumer==1){
echo "Le systeme est maintenant actif";
system("./Systeme_Surveillance");
echo '<a type="button"  href="javascript:history.back()"> Retour</a> ';

} else {
if($allumer==0){
system("echo reboot");
echo "Le systeme est maintenant éteint";
echo '<a type="button"  href="javascript:history.back()"> Retour</a> ';
}
}
?>
