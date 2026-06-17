int led = 3;   // PWM 핀 (3번은 PWM 지원)
int sw = 5;
boolean ledOn = false;          // LED가 켜진 상태인지 여부
boolean lastButtonState = HIGH; // 이전 버튼 상태
void setup() {
  pinMode(led, OUTPUT);
  pinMode(sw, INPUT_PULLUP);
  analogWrite(led, 0); // 시작 시 LED 꺼짐
}

void loop() {
  boolean currentButtonState = digitalRead(sw);

  // 버튼을 누른 순간 감지 (HIGH → LOW)
  if (lastButtonState == HIGH && currentButtonState == LOW) {
    delay(30); // 채터링 방지
    if (!ledOn) {
      // LED 꺼진 상태 → 점점 밝아지면서 켜짐
      for (int brightness = 0; brightness <= 255; brightness++) {
        analogWrite(led, brightness);
        delay(8);
      }
      ledOn = true;
    } else {
      // LED 켜진 상태 → 점점 어두워지면서 꺼짐
      for (int brightness = 255; brightness >= 0; brightness--) {
        analogWrite(led, brightness);
        delay(8);
      }
      ledOn = false;
    }
  }

  lastButtonState = currentButtonState;
}

