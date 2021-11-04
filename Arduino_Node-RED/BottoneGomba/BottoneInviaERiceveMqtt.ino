#define BROKER_IP "broker.hivemq.com"
#define DEV_NAME "mqttdevice"
#define MQTT_USER ""
#define MQTT_PW ""
const char ssid[] = "Wi-Fi Casa 2.4GHz";
const char pass[] = "aalino98";
#include <MQTT.h>
#ifdef ARDUINO_SAMD_MKRWIFI1010
#include <WiFiNINA.h>
#elif ARDUINO_SAMD_MKR1000
#include <WiFi101.h>
#elif ESP8266
#include <ESP8266WiFi.h>
#else
#error unknown board
#endif
WiFiClient net;
MQTTClient client;
unsigned long lastMillis = 0;

#include <Arduino_JSON.h>

const int buttonPin = 2; // the number of the pushbutton pin
int buttonState = 0;     // variable for reading the pushbutton status

void connect()
{
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(1000);
  }
  while (!client.connect(DEV_NAME, MQTT_USER, MQTT_PW))
  {
    Serial.print(".");
    delay(1000);
  }
  client.subscribe("/castellano_server"); //SUBSCRIBE TO TOPIC /hello
}

void messageReceived(String &topic, String &payload)
{
  Serial.println("incoming: " + topic + " - " + payload);
  // TODO DA FARE PROSSIMA VOLTA
  Serial.println(payload.toDouble());
}

/*void sendGCT(){
    JSONVar myObject;
    myObject["temp"] = //lettura sennsore temp;
    myObject["hum"] = //lettura sennsore umidità;
}*/

void setup()
{
  Serial.begin(9600);
  WiFi.begin(ssid, pass);
  pinMode(LED_BUILTIN, OUTPUT); //Led integrato
  pinMode(buttonPin, INPUT);    //Bottone
  client.begin(BROKER_IP, 1883, net);
  client.onMessage(messageReceived);
  connect();
}

void loop()
{
  client.loop();
  if (!client.connected())
  {
    connect();
  }
  // publish a message roughly every second.
  if (buttonState == HIGH)
  {
    digitalWrite(LED_BUILTIN, HIGH); //Led di conferma
    client.publish("/castellano_client", "world"); //PUBLISH TO TOPIC /hello MSG world
  }
}
