
#include <SPI.h>
#include <Ethernet.h>
#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN 10
#define RST_PIN 9
MFRC522 mfrc522(SS_PIN, RST_PIN);

byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };

EthernetClient client;

int    HTTP_PORT   = 80;
String HTTP_METHOD = "GET";
char   HOST_NAME[] = "example.com";
String PATH_NAME   = "/testKey";
String queryStringKey = "?key=";
String queryStringLock = "&lock=";

int ledVerde = 12;
int ledVermelho = 11;

void setup() {
  Serial.begin(9600);
  if (Ethernet.begin(mac) == 0) {
    Serial.println("Failed to obtaining an IP address using DHCP");
    while (true);
  }
  SPI.begin();
  mfrc522.PCD_Init();

  pinMode(ledVerde, OUTPUT);
  pinMode(ledVermelho, OUTPUT);
}

void loop() {
  if ( ! mfrc522.PICC_IsNewCardPresent())
  {
    return;
  }
  if ( ! mfrc522.PICC_ReadCardSerial())
  {
    return;
  }

  String Key = "";
  for (byte i = 0; i < mfrc522.uid.size; i++)
  {
    Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
    Serial.print(mfrc522.uid.uidByte[i], HEX);
    Key.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
    Key.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  Key.toUpperCase();
  if (client.connect(HOST_NAME, HTTP_PORT)) {
    Serial.println("Connected to server");


    client.println(HTTP_METHOD + " " + PATH_NAME + queryStringKey + Key.substring(1) + queryStringLock + "01" + " HTTP/1.1");
    client.println("Host: " + String(HOST_NAME));
    client.println("Connection: close");
    client.println();

  String readHTTPRequest = "";

    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        Serial.print(c);
        readHTTPRequest += String(c);
      }
    }

    client.stop();

    if (readHTTPRequest == "true") {
      Serial.print("Welcome");
      digitalWrite(ledVerde, HIGH);
      delay(10);
      digitalWrite(ledVerde, LOW);
    } else {
      Serial.print("Access Denied");
      digitalWrite(ledVermelho, HIGH);
      delay(10);
      digitalWrite(ledVermelho, LOW);
    }

    Serial.println("disconnected");
  } else {
    Serial.println("connection failed");
  }
}
