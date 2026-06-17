/*
  Blink

  Turns an LED on for one second, then off for one second, repeatedly.

  Most Arduinos have an on-board LED you can control. On the UNO, MEGA and ZERO
  it is attached to digital pin 13, on MKR1000 on pin 6. LED_BUILTIN is set to
  the correct LED pin independent of which board is used.
  If you want to know what pin the on-board LED is connected to on your Arduino
  model, check the Technical Specs of your board at:
  https://docs.arduino.cc/hardware/

  modified 8 May 2014
  by Scott Fitzgerald
  modified 2 Sep 2016
  by Arturo Guadalupi
  modified 8 Sep 2016
  by Colby Newman

  This example code is in the public domain.

  https://docs.arduino.cc/built-in-examples/basics/Blink/
*/

// setup 함수는 리셋 버튼을 누르거나 보드에 전원을 켤 때 한 번만 실행됩니다.
void setup() {
  // 내장 LED 핀(LED_BUILTIN)을 출력으로 설정합니다.
  pinMode(LED_BUILTIN, OUTPUT);
}

// loop 함수는 계속 반복해서 실행됩니다.
void loop() {
  digitalWrite(LED_BUILTIN, HIGH);  // 핀에 HIGH(5V) 전압을 주어 LED를 켭니다.
  delay(1000);                      // 1초(1000ms) 동안 기다립니다.
  digitalWrite(LED_BUILTIN, LOW);   // 핀에 LOW(0V) 전압을 주어 LED를 끕니다.
  delay(1000);                      // 1초(1000ms) 동안 기다립니다.
}
