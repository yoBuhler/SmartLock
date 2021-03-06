#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN 10
#define RST_PIN 9
MFRC522 mfrc522(SS_PIN, RST_PIN);

int ledVerde = 3;
int ledVermelho = 2;

void setup()
{
  Serial.begin(9600);
  SPI.begin();
  mfrc522.PCD_Init();
  Serial.println("Aproxime o seu cartao do leitor...");
  Serial.println();

  pinMode(ledVerde, OUTPUT);
  pinMode(ledVermelho, OUTPUT);
}

void loop()
{
  // Look for new cards
  if ( ! mfrc522.PICC_IsNewCardPresent())
  {
    Serial.println("PICC_IsNewCardPresent");
    return;
  }
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial())
  {
    Serial.println("PICC_ReadCardSerial");
    return;
  }
  //Mostra UID na serial
  Serial.print("UID da tag :");
  String conteudo = "";
  byte letra;
  for (byte i = 0; i < mfrc522.uid.size; i++)
  {
    Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
    Serial.print(mfrc522.uid.uidByte[i], HEX);
    conteudo.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
    conteudo.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  Serial.println();
  conteudo.toUpperCase();
  if (conteudo.substring(1) == "1B 2A D5 21")
  {
    Serial.println("Ola Cartão 1!");
    digitalWrite(ledVerde, HIGH);
    delay(10);
    digitalWrite(ledVerde, LOW);
    Serial.println();
    delay(3000);
  }

  if (conteudo.substring(1) == "BD 9B 06 7D")
  {
    Serial.println("Ola Cartao 2!");
    Serial.println();
    delay(3000);
  }
}
