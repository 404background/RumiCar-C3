//DRV8835 with XIAO ESP32C3
//https://404background.com/circuit/drv8835/
const int PIN_IN1 = D1;
const int PIN_IN2 = D2;
int value_IN1 = 0;
int value_IN2 = 0;
int interval = 100;

void DRV8835(int in1, int in2) {
  analogWrite(PIN_IN1, in1);
  analogWrite(PIN_IN2, in2);
}

void setup() {
  Serial.begin(115200);
  pinMode(PIN_IN1, OUTPUT);
  pinMode(PIN_IN2, OUTPUT);
}

void loop() {
  //coast
  DRV8835(0, 0);
  delay(2000);

  //forward/coast at speed PWM %
  for (int i = 0; i <= 255; i++) {
    DRV8835(i, 0);
    Serial.println(i);
    delay(interval);
  }
  for (int i = 255; i >= 0; i--) {
    DRV8835(i, 0);
    Serial.println(i);
    delay(interval);
  }
  delay(2000);

  //reverse/coast at speed PWM %
  for (int i = 0; i <= 255; i++) {
    DRV8835(0, i);
    Serial.println(i);
    delay(interval);
  }
  for (int i = 255; i >= 0; i--) {
    DRV8835(0, i);
    Serial.println(i);
    delay(interval);
  }
  delay(2000);

  //reverse/brake at speed 100% − PWM %
  for (int i = 0; i <= 255; i++) {
    DRV8835(i, 1);
    Serial.println(i);
    delay(interval);
  }
  for (int i = 255; i >= 0; i--) {
    DRV8835(i, 1);
    Serial.println(i);
    delay(interval);
  }
  delay(2000);

  //forward/brake at speed 100% − PWM %
  for (int i = 0; i <= 255; i++) {
    DRV8835(1, i);
    Serial.println(i);
    delay(interval);
  }
  for (int i = 255; i >= 0; i--) {
    DRV8835(1, i);
    Serial.println(i);
    delay(interval);
  }
  delay(2000);

  //brake low (outputs shorted to ground)
  DRV8835(1, 1);
  delay(2000);
}
