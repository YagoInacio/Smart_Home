#include <ESP8266WiFi.h>

#include <MQTT.h>

#define relay D1

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

  while (!client.connect("Wemos D1")) {

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
    digitalWrite(relay,!digitalRead(relay));
  }

}



void setup() {

  Serial.begin(115200);

  WiFi.begin(ssid, pass);

  pinMode(relay, OUTPUT); // Inicializa o relay pin como output (saída)

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
