<?php

require_once("config.php");
require_once("form.html");
 
$mqtt = new phpMQTT("localhost", 1234, "MQTT Publisher Client");

if ($mqtt->connect()) {
	//echo "MQTT Connected!";	// It doesn't need to show
}
else{
	echo "MQTT Could Not Connect";
}

if (isset($_GET['a']) && $_GET['a'] == 'ok'){
	$mqtt->publish("casa/quarto/yago","lamp",0);
	$mqtt->close();
}

else if (isset($_GET['color']) && strlen($_GET['color']) == 9){
	$mqtt->publish("casa/quarto/yago", $_GET['color'], 0);
	$mqtt->close();
}


?>