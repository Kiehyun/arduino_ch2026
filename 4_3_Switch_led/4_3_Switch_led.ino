int led = 3;  // LED를 3번핀으로 선언합니다.
int sw = 5;   // 스위치를 5번핀으로 선언합니다.

void setup() {
  pinMode(led, OUTPUT);  //LED 핀을 OUTPUT으로 설정
  pinMode(sw, INPUT_PULLUP);  //INPUT_PULLUP 상태
}

void loop() {
  if (digitalRead(sw) == LOW) {        
    digitalWrite(led, HIGH);       
  }
  else {
    digitalWrite(led, LOW);
  }
}