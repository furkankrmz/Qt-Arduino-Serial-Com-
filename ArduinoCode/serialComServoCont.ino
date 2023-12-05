#include <Servo.h>

Servo myservo;

void setup() {
  Serial.begin(9600);
  myservo.attach(9);
  //myservo.write(0);
  //delay(200);

}

void loop() {
  int aci = Serial.parseInt();
  Serial.println(aci);
  Serial.println("Bu isi yapiyorsun kraaalllll");
  myservo.write(aci);
}
