<form method=get >
    <input type=submit value='Meu Botão' />
</form>

<?php

require("phpMQTT/phpMQTT.php");
 
$mqtt = new phpMQTT("localhost", 1234, "MQTT Publisher Client");

if ($mqtt->connect()) {
	//$mqtt->publish("yasir/ali/test/topic","Hello World! at ".date("r"),0);
	if (isset($_GET)){
		$mqtt->publish("casa/quarto/yago","lamp",0);
		$mqtt->close();
	}
	echo "oie";
	
}


?>