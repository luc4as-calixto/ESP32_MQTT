#include <WiFi.h>
const String SSID = "iPhone";
const String PSWD = "iot_sul_123";

// SSID = NOME
// RSSI = Intesidade do sinal

void scanLocalNetworks();

void setup() {
  Serial.begin(115200);
  scanLocalNetworks();
  Serial.println("Iniciando conexão com rede WiFi");
  WiFi.begin(SSID, PSWD);
  while(WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(200);
  }
  Serial.print("\nConectado!");
}

void loop() {
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