const int buttonPin = 2;
const int redPin = 3;
const int greenPin = 4;
const int bluePin = 5;

int ledcolor = 0;
bool ledOn = true;

// 按鈕狀態
int lastReading = HIGH;
int stableButtonState = HIGH;
unsigned long lastDebounceTime = 0;

// 閃爍計時
unsigned long previousMillis = 0;
const unsigned long interval = 500;

void setup() {
  Serial.begin(9600);

  pinMode(buttonPin, INPUT);
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);

  // LOW 亮、HIGH 熄滅
  digitalWrite(redPin, LOW);
  digitalWrite(greenPin, HIGH);
  digitalWrite(bluePin, HIGH);

  Serial.println("Red");
}

void loop() {
  unsigned long now = millis();
  int reading = digitalRead(buttonPin);

  // 按鈕訊號改變時，重新計時
  if (reading != lastReading) {
    lastDebounceTime = now;
  }

  // 訊號穩定 30 毫秒後才接受
  if (now - lastDebounceTime >= 30) {
    if (reading != stableButtonState) {
      stableButtonState = reading;

      // 只有按下時切換一次
      if (stableButtonState == LOW) {
        ledcolor = ledcolor + 1;

        if (ledcolor > 2) {
          ledcolor = 0;
        }

        if (ledcolor == 0) {
          Serial.println("Red");
        } else if (ledcolor == 1) {
          Serial.println("Green");
        } else {
          Serial.println("Blue");
        }
      }
    }
  }

  lastReading = reading;

  // 每 500 毫秒切換亮／滅
  if (now - previousMillis >= interval) {
    previousMillis = now;
    ledOn = !ledOn;
  }

  // 只有目前選到的顏色會亮
  digitalWrite(redPin,
               (ledOn && ledcolor == 0) ? LOW : HIGH);
  digitalWrite(greenPin,
               (ledOn && ledcolor == 1) ? LOW : HIGH);
  digitalWrite(bluePin,
               (ledOn && ledcolor == 2) ? LOW : HIGH);
}