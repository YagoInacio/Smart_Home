<form action="?a=ok" method="POST" >
    <input type=submit value='Lampada 1' />
</form>

<?php

require_once("config.php");
 
$mqtt = new phpMQTT("localhost", 1234, "MQTT Publisher Client");

if ($mqtt->connect()) {
	//$mqtt->publish("yasir/ali/test/topic","Hello World! at ".date("r"),0);

	echo "oie";
	
}

if (isset($_GET['a'])){
	$mqtt->publish("casa/quarto/yago","lamp",0);
	$mqtt->close();
}


?>