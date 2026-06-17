// 아래 블록은 PC에서 테스트할 때만 쓰이는 부분으로, 실제 아두이노에서는 무시됩니다.
#ifndef ARDUINO
typedef unsigned char byte;

#define HIGH 0x1
#define LOW 0x0
#define OUTPUT 0x1

struct SerialMock {
  void begin(long baudRate) {}
} Serial;

void pinMode(int pin, int mode);
void digitalWrite(int pin, int value);
void delay(unsigned long ms);
#endif

const byte SEGMENT_COUNT = 7;    // 세그먼트(LED) 개수 (a~g)
const byte DISPLAY_COUNT = 16;   // 표시할 문자/숫자의 총 개수

// 세그먼트 a~g를 연결한 핀 번호 목록
const byte segmentPins[SEGMENT_COUNT] = {8, 9, 2, 3, 4, 6, 5};

// 각 문자/숫자를 나타내는 세그먼트 켜짐(HIGH)/꺼짐(LOW) 패턴 표
const byte displayPatterns[DISPLAY_COUNT][SEGMENT_COUNT] = {
  {HIGH, HIGH, HIGH, LOW, HIGH, HIGH, HIGH},   // A
  {HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH},  // B
  {HIGH, LOW, LOW, HIGH, HIGH, HIGH, LOW},     // C
  {HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, LOW},   // D
  {HIGH, LOW, LOW, HIGH, HIGH, HIGH, HIGH},    // E
  {HIGH, LOW, LOW, LOW, HIGH, HIGH, HIGH},     // F
  {LOW, HIGH, HIGH, LOW, LOW, LOW, LOW},       // 1
  {HIGH, HIGH, LOW, HIGH, HIGH, LOW, HIGH},    // 2
  {HIGH, HIGH, HIGH, HIGH, LOW, LOW, HIGH},    // 3
  {LOW, HIGH, HIGH, LOW, LOW, HIGH, HIGH},     // 4
  {HIGH, LOW, HIGH, HIGH, LOW, HIGH, HIGH},    // 5
  {HIGH, LOW, HIGH, HIGH, HIGH, HIGH, HIGH},   // 6
  {HIGH, HIGH, HIGH, LOW, LOW, LOW, LOW},      // 7
  {HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH},  // 8
  {HIGH, HIGH, HIGH, HIGH, LOW, HIGH, HIGH},   // 9
  {HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, LOW}    // 0
};

void setup()
{
  // 모든 세그먼트 핀을 출력으로 설정
  for (byte index = 0; index < SEGMENT_COUNT; index++) {
    pinMode(segmentPins[index], OUTPUT);
  }

  Serial.begin(9600);  // 시리얼 통신 시작 (9600bps)
  clr();               // 시작할 때 화면을 모두 끔
}

void loop()
{
  LoopDisplay();  // 문자/숫자를 순서대로 반복 표시
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

// 모든 문자와 숫자를 순서대로 화면에 표시한다.
void LoopDisplay()
{
  for (byte index = 0; index < DISPLAY_COUNT; index++) {
    showPattern(displayPatterns[index]);  // 현재 순서의 패턴을 표시
    delay(1000);                          // 1초간 유지 후 다음으로
  }
}