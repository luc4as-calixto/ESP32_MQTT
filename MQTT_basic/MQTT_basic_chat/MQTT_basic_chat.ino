#include <WiFi.h>
#include <PubSubClient.h>

const byte pin_led = 20;

const String SSID = "iPhone";
const String PSWD = "iot_sul_123";

const String brokerUrl = "test.mosquitto.org";  // URL do broker   (servidor)
const int port = 1883;                          // Porta do broker (servidor)

String message = "";

WiFiClient espClient;                // Criando Cliente WiFi
PubSubClient mqttClient(espClient);  // Criando Cliente MQTT

// SSID = NOME
// RSSI = Intesidade do sinal

void connectToWiFi();
void connectToBroker();

void setup() {
  Serial.begin(115200);
  connectToWiFi();
  pinMode(pin_led, OUTPUT);
}

void loop() {
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("\nConexão WiFi perdida");
    connectToWiFi();
  }
  delay(500);
  if (!mqttClient.connected()) {
    Serial.println("\nConexão MQTT perdida");
    connectToBroker();
  }
  delay(500);

  if (Serial.available() > 0) {
    message = Serial.readStringUntil('\n');
    //message = "Lucas: " +message;

    // mqttClient.publish("AulaIoTSul/Chat", message.c_str());  // envia mensagem
    mqttClient.publish("toten2/chat", message.c_str());
    delay(1000);
  }

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

void connectToBroker() {
  Serial.println("\nConectando ao broker");
  mqttClient.setServer(brokerUrl.c_str(), port);
  String userId = "ESP-CALIXTO";
  userId += String(random(0xfff), HEX);
  while (!mqttClient.connected()) {
    mqttClient.connect(userId.c_str());
    Serial.print(".");
    delay(500);
    //mqttClient.subscribe("AulaIoTSul/Chat");
    mqttClient.subscribe("toten1/chat");
    mqttClient.setCallback(callback);
  }
  Serial.println("\nConectado com sucesso!");
}

void callback(char* topic, byte* payload, unsigned long length) {
  String resposta = "";
  for (int i = 0; i < length; i++) {
    resposta += (char) payload[i];
  }
  if (resposta == "on") {
    digitalWrite(pin_led, HIGH);
  } else if (resposta == "off"){
    digitalWrite(pin_led, LOW);
  }

  Serial.println(resposta);
}
