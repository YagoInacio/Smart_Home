<form action="?a=ok" method="POST" >
    <input type=submit value='Lamp 1' />
</form>
<form action="?a=notok" method="POST" >
    <input type=submit value='Lamp 2' />
</form>

<?php

require_once("config.php");
 
$mqtt = new phpMQTT("localhost", 1234, "MQTT Publisher Client");

if ($mqtt->connect()) {
	echo "MQTT Connected!";
}
else{
	echo "MQTT Could Not Connect";
}

if (isset($_GET['a']) && $_GET['a'] == 'ok'){
	$mqtt->publish("casa/quarto/yago","lamp",0);
	$mqtt->close();
}


?>