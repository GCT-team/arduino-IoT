#include <Arduino_JSON.h>
#include <MQTT.h>
#include <WiFiNINA.h>

#define BROKER_IP    "broker.hivemq.com"
#define DEV_NAME     "mqttdevice"
#define MQTT_USER    "user"
#define MQTT_PW      "password"

//const char ssid[] = "Eventi";
//const char pass[] = "Di.Toro.567!";
const char ssid[] = "Wi-Fi Casa 2.4GHz";
const char pass[] = "aalino98";
const char topic_client[]  = "castellano_client";
const char topic_server[]  = "castellano_server";
 
WiFiClient net;
MQTTClient client;
const int buttonPin = 2;  // the number of the pushbutton pin
int buttonState = 0;  // variable for reading the pushbutton status

void connect() {
  Serial.print("Attempting to connect to WPA SSID: ");
  Serial.println(ssid);
  while (WiFi.begin(ssid, pass) != WL_CONNECTED) {
    Serial.print(".");
  }
  /*while (!client.connect(DEV_NAME, MQTT_USER, MQTT_PW)) {

    Serial.print(".");
    delay(1000);
  }
  */
  client.connect(BROKER_IP, 1883);
  Serial.println("\nconnected!");
  client.subscribe(topic_server);
   
}

void messageReceived(String &topic, String &payload) {
  Serial.println("incoming: " + topic + " - " + payload);
  Serial.println(payload.toDouble());
}
 
void setup() {
  Serial.begin(9600);
  WiFi.begin(ssid, pass);

  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(buttonPin, INPUT);
  client.begin(BROKER_IP, 1883, net);
  client.onMessage(messageReceived);
  connect();
}

void send() {
    Serial.print("Richiesta previsione meteo: ");
    Serial.println(topic_client);
    client.publish(topic_client, "forecast_request");
    Serial.println();
}

void loop() {
  if (buttonState == HIGH) {
    client.loop();
    digitalWrite(LED_BUILTIN, HIGH);
    send(); 
  }
}