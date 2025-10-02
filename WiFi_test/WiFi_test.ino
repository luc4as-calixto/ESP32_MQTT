#include <WiFi.h>
const String SSID = "iPhone";
const String PSWD = "iot_sul_123";

// SSID = NOME
// RSSI = Intesidade do sinal

void scanLocalNetworks();
void connectToWiFi();

void setup() {
  Serial.begin(115200);
  scanLocalNetworks();
  connectToWiFi();
}

void loop() {
  if (WiFi.status() != WL_CONNECTED){
    connectToWiFi();
  } 
  delay(2000); 
}

void scanLocalNetworks() {
  Serial.println("Iniciando Scan de redes Wi-Fi");
  int number = WiFi.scanNetworks();
  delay(500);
  if (number == -1) {
    Serial.println("ERRO!. Não deu bom");
  } else {
    Serial.printf("Número de redes encontradas: %d\n", number);
    for (int net = 0; net < number; net++) {
      Serial.printf("%d - %s | %d db\n", net, WiFi.SSID(net), WiFi.RSSI(net));
    }
  }
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