int led = 3; 
int sw = 5; 

boolean ledState = LOW;     // LED의 현재 상태 (꺼짐/켜짐)를 저장
boolean lastButtonState = HIGH; // 이전 버튼의 상태를 저장

void setup() {
  pinMode(led, OUTPUT);
  pinMode(sw, INPUT_PULLUP);
}

void loop() {
  // 현재 버튼의 상태를 읽음
  boolean currentButtonState = digitalRead(sw);

  // 버튼을 누른 순간 (평소 HIGH였다가 누르는 순간 LOW가 됨)을 감지
  if (lastButtonState == HIGH && currentButtonState == LOW) {
    ledState = !ledState; // LED 상태를 반전 (꺼져있으면 켜고, 켜져있으면 끔)
    digitalWrite(led, ledState);
    delay(50); // 버튼을 누를 때 발생하는 노이즈(채터링) 방지
  }

  // 다음 루프를 위해 현재 버튼 상태를 이전 상태 변수에 저장
  lastButtonState = currentButtonState;
}