<?php 
$tpl->assign('copyYears',date('Y').'-'.(date('Y')+1));
$tpl->assign('executionTime',number_format(microtime(true)-$start,3));
$html = $tpl->draw($view);
?>