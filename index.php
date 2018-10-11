<?php

require("phpMQTT/phpMQTT.php");
 
$mqtt = new phpMQTT("localhost", 1234, "MQTT Publisher Client");

if ($mqtt->connect()) {
	//$mqtt->publish("yasir/ali/test/topic","Hello World! at ".date("r"),0);
	$mqtt->publish("casa/quarto/yago","lamp",0);
	echo "oie";
	$mqtt->close();
}

?>