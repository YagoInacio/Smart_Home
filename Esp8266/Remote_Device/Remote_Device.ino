//#include <ESP8266WiFi.h>
//#include <MQTTClient.h>
// 
//const char* ssid     = "Faran"; 
//const char* password = "cerveja123";
// 
//WiFiClient WiFiclient;
//MQTTClient client;
// 
//unsigned long lastMillis = 0;
// 
//void setup() {
// Serial.begin(115200);
// delay(10);
// Serial.println();
// Serial.println();
// Serial.print("Connecting to ");
// Serial.println(ssid);
// 
// WiFi.begin(ssid, password);
//  while (WiFi.status() != WL_CONNECTED) {
//   delay(500);
//   Serial.print(".");
// }
// 
// Serial.println("");
// Serial.println("WiFi connected");  
// Serial.println("IP address: ");
// Serial.println(WiFi.localIP());
// 
// delay(2000);
// 
// Serial.print("connecting to MQTT broker...");
// client.begin("192.168.0.115", 1234, WiFiclient);
// connect();
//}
// 
//void connect() {
// while (!client.connect("nodemcu")) {
//   Serial.print(".");
// }
// 
// Serial.println("\nconnected!");
// client.subscribe("yasir/ali/test/topic", 0);
//}
// 
//void loop() {
// int val = analogRead(A0);
// client.loop();
// if(!client.connected()) {
//   connect();
// }
//}
// 
//void messageReceived(String topic, String payload, char * bytes, unsigned int length) {
// Serial.print("incoming: ");
// Serial.print(topic);
// Serial.print(" - ");
// Serial.print(payload);
// Serial.println();
//}

// This example uses an ESP32 Development Board

// to connect to shiftr.io.

//

// You can check on your device after a successful

// connection here: https://shiftr.io/try.

//

// by Joël Gähwiler

// https://github.com/256dpi/arduino-mqtt



#include <ESP8266WiFi.h>

#include <MQTT.h>



const char* ssid = "Faran";

const char* pass = "cerveja123";



WiFiClient net;

MQTTClient client;



unsigned long lastMillis = 0;



void connect() {

  Serial.print("checking wifi...");

  while (WiFi.status() != WL_CONNECTED) {

    Serial.print(".");

    delay(1000);

  }



  Serial.print("\nconnecting...");

  while (!client.connect("NodeMCU")) {

    Serial.print(".");

    delay(1000);

  }



  Serial.println("\nconnected at MQTT!");



  client.subscribe("casa/quarto/yago");

  // client.unsubscribe("/hello");

}



void messageReceived(String &topic, String &payload) {

  Serial.println("incoming: " + topic + " - " + payload);

  if (payload == "lamp"){
    digitalWrite(LED_BUILTIN,!digitalRead(LED_BUILTIN));
  }

}



void setup() {

  Serial.begin(115200);

  WiFi.begin(ssid, pass);

  pinMode(LED_BUILTIN, OUTPUT); // Inicializa o LED_BUILTIN pin como output (saída)

  // Note: Local domain names (e.g. "Computer.local" on OSX) are not supported by Arduino.

  // You need to set the IP address directly.

  client.begin("192.168.0.115",1234, net);

  client.onMessage(messageReceived);



  connect();

}



void loop() {

  client.loop();

  delay(10);  // <- fixes some issues with WiFi stability



  if (!client.connected()) {

    connect();

  }



  // publish a message roughly every second.

//  if (millis() - lastMillis > 1000) {
//
//    lastMillis = millis();
//
//    client.publish("yasir/ali/test/topic", "Hola chiquitas!");
//
//  }

}
