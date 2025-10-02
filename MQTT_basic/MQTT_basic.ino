#include <WiFi.h>
#include <PubSubClient.h>

const String SSID = "iPhone";
const String PSWD = "iot_sul_123";

const String brokerUrl = "test.mosquitto.org";     // URL do broker   (servidor)
const int port = 1883;                             // Porta do broker (servidor)

WiFiClient espClient;                              // Criando Cliente WiFi
PubSubClient mqttClient(espClient);                // Criando Cliente MQTT

// SSID = NOME
// RSSI = Intesidade do sinal

void connectToWiFi();

void setup() {
  Serial.begin(115200);
  connectToWiFi();
  Serial.println("\nConectando ao broker");
  mqttClient.setServer(brokerUrl.c_str(), port);
  String userId = "ESP-CALIXTO";
  userId += String(random(0xfff), HEX);
  mqttClient.connect(userId.c_str());
  while (!mqttClient.connected()) {
    Serial.println("Erro de conexão");
    delay(500);
  }
  Serial.println("Conectado com sucesso!");
}

void loop() {
  if (WiFi.status() != WL_CONNECTED){
    connectToWiFi();
  } 
  delay(2000); 
  mqttClient.loop();
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