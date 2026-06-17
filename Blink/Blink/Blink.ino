void setup() {
 pinMode(5, INPUT_PULLUP);  // 5번 핀을 내부 풀업 저항을 사용하는 입력으로 설정
 Serial.begin(9600);        // 시리얼 통신 시작 (통신 속도 9600bps)
}

void loop() {
  int d_sig = digitalRead(5);  // 5번 핀의 디지털 값을 읽음 (스위치 안 누름: 1, 누름: 0)

  Serial.println(d_sig);  // 읽은 값을 시리얼 모니터에 출력
  delay(50);              // 0.05초 대기 (출력이 너무 빠르지 않도록)
}
