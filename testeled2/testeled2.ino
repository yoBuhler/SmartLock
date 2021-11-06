int ledVermelho = 5;
int ledVerde = 6;

void setup() {
  // put your setup code here, to run once:

  pinMode(ledVerde, OUTPUT);
  pinMode(ledVermelho, OUTPUT);
}

void loop() {
  for (int i = 0; i <= 255; i++) {
    analogWrite(ledVerde, i);
    analogWrite(ledVermelho, i);
    delay(10);
  }
  for (int i = 255; i >= 0; i--) {
    analogWrite(ledVerde, i);
    analogWrite(ledVermelho, i);
    delay(10);
  }
//  for (int i = 0; i <= 255; i++) {
//    analogWrite(ledVermelho, i);
//    delay(10);
//  }
//  for (int i = 255; i >= 0; i--) {
//    analogWrite(ledVermelho, i);
//    delay(10);
//  }
}
