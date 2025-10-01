#include <WiFi.h>

const String SSID = "iPhone";
const String PSWD = "iot_sul_123";

// SSID = NOME
// RSSI = Intesidade do sinal

void connectToWiFi();

void setup() {
  Serial.begin(115200);
  connectToWiFi();
}

void loop() {
  if (WiFi.status() != WL_CONNECTED){
    connectToWiFi();
  } 
  delay(2000); 
}


void connectToWiFi() {
  Serial.println("\nIniciando conexão com rede WiFi");
  WiFi.begin(SSID, PSWD);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(200);
  }
  Serial.print("\nConectado!");
}