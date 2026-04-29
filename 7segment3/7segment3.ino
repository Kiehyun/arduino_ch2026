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

const byte SEGMENT_COUNT = 7;
const byte BUTTON_PIN = A3;
const unsigned long TENS_DISPLAY_MS = 120;
const unsigned long DISPLAY_CYCLE_MS = 1000;

const byte segmentPins[SEGMENT_COUNT] = {8, 9, 2, 3, 4, 6, 5};

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

bool timerRunning = false;
bool previousButtonState = HIGH;
unsigned long startMillis = 0;

void setup()
{
  for (byte index = 0; index < SEGMENT_COUNT; index++) {
    pinMode(segmentPins[index], OUTPUT);
  }

  pinMode(BUTTON_PIN, INPUT_PULLUP);

  Serial.begin(9600);
  clr();
}

void loop()
{
  bool currentButtonState = digitalRead(BUTTON_PIN);

  if (previousButtonState == HIGH && currentButtonState == LOW) {
    timerRunning = true;
    startMillis = millis();
  }

  previousButtonState = currentButtonState;

  if (timerRunning) {
    unsigned long elapsedSeconds = (millis() - startMillis) / 1000;
    showElapsedTime(elapsedSeconds);
  }
  else {
    clr();
  }

  delay(20);
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

void showDigit(byte digit)
{
  showPattern(digitPatterns[digit]);
}

void showElapsedTime(unsigned long elapsedSeconds)
{
  unsigned long cappedSeconds = elapsedSeconds;

  if (cappedSeconds > 99) {
    cappedSeconds = 99;
  }

  if (cappedSeconds < 10) {
    showDigit(cappedSeconds);
    return;
  }

  byte tensDigit = cappedSeconds / 10;
  byte onesDigit = cappedSeconds % 10;
  unsigned long cyclePosition = millis() % DISPLAY_CYCLE_MS;

  if (cyclePosition < TENS_DISPLAY_MS) {
    showDigit(tensDigit);
  }
  else {
    showDigit(onesDigit);
  }
}