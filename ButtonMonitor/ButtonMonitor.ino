const int buttonPin = 2;
const int redPin = 3;
const int greenPin = 4;
const int bluePin = 5;

int ledcolor = 0;
bool buttonPressed = false;

void setup() {
  Serial.begin(9600);
  Serial.println("Red");
  pinMode(buttonPin, INPUT);
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
}

void loop() {
  int buttonState = digitalRead(buttonPin);

  // 按下，而且這次還沒切換過
  if (buttonState == LOW && buttonPressed == false) {
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
    buttonPressed = true;
    delay(30);
  }

  // 放開後，允許下一次按下再切換
  if (buttonState == HIGH && buttonPressed == true) {
    buttonPressed = false;
    delay(30);
  }

  // 你的 LED 是 LOW 亮、HIGH 熄滅
  if (ledcolor == 0) {
    digitalWrite(redPin, LOW);
    digitalWrite(greenPin, HIGH);
    digitalWrite(bluePin, HIGH);
  } else if (ledcolor == 1) {
    digitalWrite(redPin, HIGH);
    digitalWrite(greenPin, LOW);
    digitalWrite(bluePin, HIGH);
  } else {
    digitalWrite(redPin, HIGH);
    digitalWrite(greenPin, HIGH);
    digitalWrite(bluePin, LOW);
  }
}