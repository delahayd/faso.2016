<?php
header('Content-type: application/json; charset=iso-8859-1');




//Récuperation et sécurisation des variables get et post dans un même tableau '$_'
$_ = array();
foreach($_GET as $key=>$value){
    $_[addslashes(htmlentities($key))] = addslashes(htmlentities($value));
}
foreach($_POST as $key=>$value){
    $_[addslashes(htmlentities($key))] = addslashes(htmlentities($value));
}

//Tableau de correspondance position lampe/pin GPIO raspberry pi utilisé
$pin_engine = array(
    'LAMPE_SALON'=>7,
    'LAMPE_CHAMBRE'=>13,
    'LAMPE_SALLE_DE_BAIN'=>8,
    );


//Réponse par défaut à syntétiser en retour.
$response = 'Aucune action n\'a été spécifiée';    


//en conftion de la variable action spécifiée par yuri desktop, on execute les actions ci dessous
switch ($_['action']){

    //action permettant l'activation/la désactivation d'un PIN GPIO (par exemple rélié a une carte relais elle même reliée a une lampe)
    // $_['engine'] = position de la lampe visée(ex : LAMPE_SALON)
    // $_['state'] = etat ciblé (0 désactivé, 1 activé)
    case 'CHANGE_ENGINE_STATE':
        system('gpio mode '.$pin_engine[$_['engine']].' out');
        system('gpio write '.$pin_engine[$_['engine']].' '.$_['state']);
        $response = 'Action effectuée';
    break;

    //action de récuperation de l'heure courante
    case 'GET_TIME':
        $response = 'Il est '.date('H').' heures '.date('i');
    break;
    
    //Action qui balance une insulte débile aléatoirement
    case 'GET_AFFRONT':
        $affronts = array(
        'Espaice de Rideau pas tringlai',
        'Espaice d\'Innovation pairimaie',
        'Espaice de Star academicien croate',
        'Espaice d\'Improvisateurs à texte',
        'Espaice de Visage sans nez',
        'Espaice de colléoptère unijambiste',
        'Espaice d\'Excrément maternel',
        'Espaice de Catcheur manchot',
        'Espaice de Lunettes sans verre',
        'Espaice de Carrai sans cotai',
        'Espaice de Pot catholitique',
        'Espaice de Fille de lémurien',
        'Espaice de Cheveux sans racine',
        'Espaice d\'Hectoplasme circonscit',
        'Espaice de Vomi',
        'Espaice de Ragout d\'uranium',
        'Espaice de Pom pom girl',
        'Espaice de Pantalon en soldes',
        'Espaice de Naturiste en mailllot',
        'Espaice de String sans ficelle',
        'Espaice de Haut parleur aphone',
        'Espaice de Cochon anoraixique',
        'Espaice de Queue de cheval sans cheval',
        'Espaice de WC sans chasse d\'eau',
        'Tes cheveux poussent aux bouts des pieds',
        'Espaice de Régle tordue',
        'Espaice de Aisselles sans poil',
        'Espaice de Trou de nez sur pattes',
        'Espaice de Bière sans alcool',
        'Espaice de Dent carriai',
        'Espaice de Cravate sans costard',
        'Espaice de Beignet daicongelai',
        'Espaice de Taite de grille pain',
        'Remet ta culotte sale gueuse',
        'Avec tes lunettes, tu ressembles à des toilettes'
        );
        
        $response = $affronts[rand(0,count($affronts))];
    break;
    
    //action de récuperation de la phrase d'identification de YURI
    case 'GET_IDENTIFICATION':
        $response = 'Je suis YOURI, ce sigle signifie : Yaisse aïe am youniversole raisidence ïntellidgence.J\'ai été programmée par Valentin CARRUESCO pour gérer et surveiller cette maison';
    break;
    
    //action de récuperation de la date courante
    case 'GET_DATE':
        $month = array(
            'number'=>array('01','02','03','04','05','06','07','08','09','10','11','12'),
            'name'=>array('Janvier','Fevrier','Mars','Avril','Mai','Juin','Juillet','Aout','Septembre','Octobre','Novembre','Decembre')
        );
        $response = 'Nous sommes le '.date('d').' '.str_replace($month['number'],$month['name'],date('m')).' '.date('Y');
    break;
}

//Impression de la réponse a synthétiser par YURI
echo $response;
?>