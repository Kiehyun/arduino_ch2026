// 아래 블록은 PC에서 테스트할 때만 쓰이는 부분으로, 실제 아두이노에서는 무시됩니다.
#ifndef ARDUINO
typedef unsigned char byte;

#define HIGH 0x1
#define LOW 0x0
#define OUTPUT 0x1
#define INPUT_PULLUP 0x2
#define A3 17

struct SerialMock {
  void begin(long baudRate) {}
} Serial;

void pinMode(int pin, int mode);
void digitalWrite(int pin, int value);
int digitalRead(int pin);
void delay(unsigned long ms);
unsigned long millis();
#endif

const byte SEGMENT_COUNT = 7;                   // 세그먼트(LED) 개수 (a~g)
const byte BUTTON_PIN = A3;                     // 버튼을 연결한 핀 (아날로그 A3 핀)
const unsigned long TENS_DISPLAY_MS = 120;      // 십의 자리를 보여주는 시간 (밀리초)
const unsigned long DISPLAY_CYCLE_MS = 1000;    // 십의 자리/일의 자리 표시 한 주기 (밀리초)

// 세그먼트 a~g를 연결한 핀 번호 목록
const byte segmentPins[SEGMENT_COUNT] = {8, 9, 2, 3, 4, 6, 5};

// 숫자 0~9를 나타내는 세그먼트 켜짐(HIGH)/꺼짐(LOW) 패턴 표
const byte digitPatterns[10][SEGMENT_COUNT] = {
  {HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, LOW},   // 0
  {LOW, HIGH, HIGH, LOW, LOW, LOW, LOW},       // 1
  {HIGH, HIGH, LOW, HIGH, HIGH, LOW, HIGH},    // 2
  {HIGH, HIGH, HIGH, HIGH, LOW, LOW, HIGH},    // 3
  {LOW, HIGH, HIGH, LOW, LOW, HIGH, HIGH},     // 4
  {HIGH, LOW, HIGH, HIGH, LOW, HIGH, HIGH},    // 5
  {HIGH, LOW, HIGH, HIGH, HIGH, HIGH, HIGH},   // 6
  {HIGH, HIGH, HIGH, LOW, LOW, LOW, LOW},      // 7
  {HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH},  // 8
  {HIGH, HIGH, HIGH, HIGH, LOW, HIGH, HIGH}    // 9
};

bool timerRunning = false;          // 타이머가 동작 중인지 여부
bool previousButtonState = HIGH;    // 이전 버튼 상태 (눌림 순간을 감지하기 위함)
unsigned long startMillis = 0;      // 타이머를 시작한 시각 (밀리초)

void setup()
{
  // 모든 세그먼트 핀을 출력으로 설정
  for (byte index = 0; index < SEGMENT_COUNT; index++) {
    pinMode(segmentPins[index], OUTPUT);
  }

  pinMode(BUTTON_PIN, INPUT_PULLUP);  // 버튼 핀을 내부 풀업 입력으로 설정

  Serial.begin(9600);  // 시리얼 통신 시작 (9600bps)
  clr();               // 시작할 때 화면을 모두 끔
}

void loop()
{
  bool currentButtonState = digitalRead(BUTTON_PIN);  // 현재 버튼 상태를 읽음

  // 버튼을 누른 순간(HIGH → LOW)을 감지하면 타이머 시작
  if (previousButtonState == HIGH && currentButtonState == LOW) {
    timerRunning = true;
    startMillis = millis();  // 시작 시각을 기록
  }

  previousButtonState = currentButtonState;  // 다음 비교를 위해 현재 상태를 저장

  if (timerRunning) {
    // 시작 후 흐른 시간을 초 단위로 계산해 화면에 표시
    unsigned long elapsedSeconds = (millis() - startMillis) / 1000;
    showElapsedTime(elapsedSeconds);
  }
  else {
    clr();  // 타이머가 멈춰 있으면 화면을 끔
  }

  delay(20);  // 0.02초 대기 (버튼을 너무 자주 읽지 않도록)
}

// 모든 세그먼트를 꺼서 화면을 지움
void clr()
{
  for (byte index = 0; index < SEGMENT_COUNT; index++) {
    digitalWrite(segmentPins[index], LOW);
  }
}

// 주어진 패턴(배열)대로 각 세그먼트를 켜고 끔
void showPattern(const byte pattern[SEGMENT_COUNT])
{
  for (byte index = 0; index < SEGMENT_COUNT; index++) {
    digitalWrite(segmentPins[index], pattern[index]);
  }
}

// 숫자 하나(0~9)를 화면에 표시
void showDigit(byte digit)
{
  showPattern(digitPatterns[digit]);
}

// 흐른 시간(초)을 7세그먼트에 표시 (한 자리 숫자는 그대로, 두 자리는 번갈아 표시)
void showElapsedTime(unsigned long elapsedSeconds)
{
  unsigned long cappedSeconds = elapsedSeconds;

  // 99초를 넘으면 99로 제한 (세그먼트가 한 자리만 있으므로)
  if (cappedSeconds > 99) {
    cappedSeconds = 99;
  }

  // 10초 미만이면 한 자리 숫자를 그대로 표시
  if (cappedSeconds < 10) {
    showDigit(cappedSeconds);
    return;
  }

  byte tensDigit = cappedSeconds / 10;   // 십의 자리 숫자
  byte onesDigit = cappedSeconds % 10;   // 일의 자리 숫자
  unsigned long cyclePosition = millis() % DISPLAY_CYCLE_MS;  // 현재 주기에서의 위치

  // 한 주기 안에서 잠깐 십의 자리를 보여준 뒤, 나머지 시간은 일의 자리를 표시
  if (cyclePosition < TENS_DISPLAY_MS) {
    showDigit(tensDigit);
  }
  else {
    showDigit(onesDigit);
  }
}