int R_pin = 13;  // 빨강(R) LED를 13번 핀에 연결
int G_pin = 12;  // 초록(G) LED를 12번 핀에 연결
int B_pin = 11;  // 파랑(B) LED를 11번 핀에 연결

void setup(){
   pinMode(R_pin, OUTPUT);  // R 핀을 출력으로 설정
   pinMode(G_pin, OUTPUT);  // G 핀을 출력으로 설정
   pinMode(B_pin, OUTPUT);  // B 핀을 출력으로 설정
}

void loop(){
   // LED 모듈을 빨간색으로 켠다 (R만 HIGH)
   digitalWrite(R_pin, HIGH);
   digitalWrite(G_pin, LOW);
   digitalWrite(B_pin, LOW);
   delay(1000);
   // LED 모듈을 초록색으로 켠다 (G만 HIGH)
   digitalWrite(R_pin, LOW);
   digitalWrite(G_pin, HIGH);
   digitalWrite(B_pin, LOW);
   delay(1000);
   // LED 모듈을 파란색으로 켠다 (B만 HIGH)
   digitalWrite(R_pin, LOW);
   digitalWrite(G_pin, LOW);
   digitalWrite(B_pin, HIGH);
   delay(1000);
}
