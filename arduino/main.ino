#include <SoftwareSerial.h>
SoftwareSerial gsmSerial(9, 8); // RX, TX

void sendATCommand(String command, unsigned long timeout) {
  gsmSerial.println(command);
  unsigned long start = millis();
  while (millis() - start < timeout) {
    if (gsmSerial.available()) {
      String resp = gsmSerial.readStringUntil('\n');
      Serial.println(resp);
    }
  }
}

void sendSMS(String number, String message) {
  gsmSerial.print("AT+CMGS=\"");
  gsmSerial.print(number);
  gsmSerial.println("\"");
  delay(100);
  
  gsmSerial.print(message);
  delay(100);
  
  gsmSerial.write(26);  // Envia Ctrl+Z
  delay(2000);
  
  Serial.println("Mensagem enviada!");
}

void setup() {
  Serial.begin(9600);  // Serial Monitor
  gsmSerial.begin(115200);  // Módulo GSM
  
  Serial.println("Aguardando a conexão...");
  
  delay(5000); //Necessário até que o módulo ligue e dê conexão
  sendATCommand("AT", 1000);
  sendATCommand("AT+CMGF=1", 1000);
}

int i = 0;

void loop() {
  i++;
  String smsText = "MENSAGEM NUMERO ";
  smsText.concat(i);
  smsText.concat(" CONTENDO APROXIMADAMENTE 60 CARACTERES DE TEXTO");

  Serial.println("ENVIANDO MENSAGEM " + String(i));
  sendSMS("44999991234", smsText);
  delay(5000);
}