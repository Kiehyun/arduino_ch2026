int R_pin = 13;  // 빨강(R) LED를 13번 핀에 연결
int G_pin = 12;  // 초록(G) LED를 12번 핀에 연결
int B_pin = 11;  // 파랑(B) LED를 11번 핀에 연결

void setup(){
   pinMode(R_pin, OUTPUT);  // R 핀을 출력으로 설정
   pinMode(G_pin, OUTPUT);  // G 핀을 출력으로 설정
   pinMode(B_pin, OUTPUT);  // B 핀을 출력으로 설정
}

void loop() {
   // analogWrite로 0~255 값을 주어 빨강 LED의 밝기를 점점 키운다.
   // (0: 꺼짐 ~ 255: 가장 밝음)
   analogWrite(R_pin, 0);    // 빨강 꺼짐
   analogWrite(G_pin, 0);
   analogWrite(B_pin, 0);
   delay(500);
   analogWrite(R_pin, 64);   // 빨강 약하게
   analogWrite(G_pin, 0);
   analogWrite(B_pin, 0);
   delay(500);
   analogWrite(R_pin, 128);  // 빨강 중간 밝기
   analogWrite(G_pin, 0);
   analogWrite(B_pin, 0);
   delay(500);
   analogWrite(R_pin, 255);  // 빨강 가장 밝게
   analogWrite(G_pin, 0);
   analogWrite(B_pin, 0);
   delay(500);
}
