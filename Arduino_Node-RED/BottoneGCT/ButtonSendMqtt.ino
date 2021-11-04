#include <ArduinoMqttClient.h>
#include <WiFiNINA.h>

const char ssid[] = "Wi-Fi Casa 2.4GHz";
const char pass[] = "aalino98";

WiFiClient wifiClient;
MqttClient mqttClient(wifiClient);

const char broker[] = "broker.hivemq.com";
int        port     = 1883;
const char topic_client[]  = "castellano_client";
const char topic_server[]  = "castellano_server";


//Ultima temperatura rilevata
const double gradiPrevisti = 0;
int pausa = 0;

//Bottone
const int buttonPin = 2;  // the number of the pushbutton pin
int buttonState = 0;  // variable for reading the pushbutton status

void connect(){
  Serial.print("Attempting to connect to WPA SSID: ");
  Serial.println(ssid);
  while (WiFi.begin(ssid, pass) != WL_CONNECTED) {
    // failed, retry
    Serial.print(".");
  }
  mqttClient.subscribe("/castellano_server");
  Serial.println("Connessione wifi riuscita");
  Serial.println();
}

void setup() {
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT); //Led integrato
  pinMode(buttonPin, INPUT); //Bottone
  connect(); //wifi and broker
}

void send() {
    Serial.print("Richiesta previsione meteo: ");
    Serial.println(topic_client);
    mqttClient.connect(broker, port);
    mqttClient.beginMessage(topic_client);
    mqttClient.print("Forecast request"); //msg che arriva al server
    mqttClient.endMessage();
    Serial.println();
}

void loop() {
  mqttClient.poll();
  buttonState = digitalRead(buttonPin);
  
  if (buttonState == HIGH) {
    delay(3000);
    digitalWrite(LED_BUILTIN, HIGH); //Led di conferma
    send(); //Richiesta previsioni meteo
  }

}
