<?php 

session_start();
$start=microtime(true);
require_once('constant.php');
require_once('RainTPL.php');
class_exists('Functions') or require_once('Functions.class.php');


//error_reporting(E_ALL);

//Calage de la date
date_default_timezone_set('Europe/Paris'); 



//Instanciation du template
$tpl = new RainTPL();
//Definition des dossiers de template
raintpl::configure("base_url", null );
raintpl::configure("tpl_dir", './templates/'.DEFAULT_THEME.'/' );
raintpl::configure("cache_dir", "./cache/tmp/" );

$view = '';

if(isset($_SESSION['myUser'])){
	$tpl->assign('myUser',unserialize($_SESSION['myUser']));
}

//Récuperation et sécurisation de toutes les variables POST et GET
$_ = array('action'=>'');
foreach($_POST as $key=>$val){
$_[$key]=Functions::secure($val);
}
foreach($_GET as $key=>$val){
$_[$key]=Functions::secure($val);
}

$tpl->assign('_',$_);
?>