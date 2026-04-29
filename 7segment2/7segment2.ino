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

const byte SEGMENT_COUNT = 7;
const byte DISPLAY_COUNT = 16;

const byte segmentPins[SEGMENT_COUNT] = {8, 9, 2, 3, 4, 6, 5};

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
  for (byte index = 0; index < SEGMENT_COUNT; index++) {
    pinMode(segmentPins[index], OUTPUT);
  }

  Serial.begin(9600);
  clr();
}

void loop()
{
  LoopDisplay();
}

void clr()
{
  for (byte index = 0; index < SEGMENT_COUNT; index++) {
    digitalWrite(segmentPins[index], LOW);
  }
}

void showPattern(const byte pattern[SEGMENT_COUNT])
{
  for (byte index = 0; index < SEGMENT_COUNT; index++) {
    digitalWrite(segmentPins[index], pattern[index]);
  }
}

//모든 문자와 숫자를 순서대로 Display한다.
void LoopDisplay()
{
  for (byte index = 0; index < DISPLAY_COUNT; index++) {
    showPattern(displayPatterns[index]);
    delay(1000);
  }
}