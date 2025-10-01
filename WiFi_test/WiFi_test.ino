#include <WiFi.h>

// SSID = NOME
// RSSI = Intesidade do sinal

void setup() {
  Serial.begin(115200);
  Serial.println("Iniciando Scan de redes Wi-Fi");

}

void loop() {
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

