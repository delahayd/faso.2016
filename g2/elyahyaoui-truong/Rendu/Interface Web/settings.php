<?php 


require_once('header.php'); 

$db = (file_exists(PATH_BDD)?Functions::unstore():array());
$tpl->assign('places', $db['places']);
$tpl->assign('engines', $db['engines']);




$view = "settings";
require_once('footer.php'); ?>
