#include <ESP8266WiFi.h>

#include <MQTT.h>

#define blue D0
#define green D5
#define red D6

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

  while (!client.connect("Table Backlight")) {

    Serial.print(".");

    delay(1000);

  }



  Serial.println("\nconnected at MQTT!");



  client.subscribe("casa/quarto/yago");

  // client.unsubscribe("/hello");

}



void messageReceived(String &topic, String &payload) {
  static long int  redCode = 0,
                   greenCode = 0,
                   blueCode = 0;
  static bool power = false;

  Serial.println("incoming: " + topic + " - " + payload);

  if (payload[0] == '#'){
    char buf[8];
    for (int i = 0; i < 8; i++){
      buf[i] = payload[i+1];
    }
    
    char * pEnd;
    redCode = strtoul(buf, &pEnd, 16);
    greenCode = strtoul(pEnd, &pEnd, 16);
    blueCode = strtoul(pEnd, NULL, 16);
  }

  else if (payload == "ON"){
    power = true;
  }
  
  else if (payload == "OFF"){
    power = false;
  }

  if(power){
    analogWrite(red, redCode);
    analogWrite(green, greenCode);
    analogWrite(blue, blueCode);
  }
  else{
    digitalWrite(red, LOW);
    digitalWrite(green, LOW);
    digitalWrite(blue, LOW);
  }

}



void setup() {

  Serial.begin(115200);

  WiFi.begin(ssid, pass);

  pinMode(blue, OUTPUT); // Inicializa os led pins como output (saída)
  pinMode(green, OUTPUT);
  pinMode(red, OUTPUT);

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

}
