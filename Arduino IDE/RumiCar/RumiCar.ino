#include <WiFi.h>
#include <WiFiClient.h>
#include <WiFiAP.h>
#include "controller.h"
const int servoPin = D1;
int DutyMax = 2500;  //180:2500  conitnuous:2300
int DutyMin = 500;   //180:500   continuout:700
int DutyCycle = DutyMin;

const int PIN_IN1 = D2;
const int PIN_IN2 = D3;
int value_IN1 = 0;
int value_IN2 = 0;

int motor1 = 0;
int motor2 = 0;
int servo1 = 90;
int speedMax = 80;   //0~255, recommend 80

const char *ssid = "RumiCar-C3";
const char *password = "12345678";
WiFiServer server(80);

void servoAngle(int pin, int angle) {
  if (angle != 0) {
    int Duty = map(angle, 0, 180, DutyMin, DutyMax);
    digitalWrite(pin, HIGH);
    delayMicroseconds(Duty);
    digitalWrite(pin, LOW);
    delayMicroseconds(20 * 1000 - Duty);
  }
}

void DRV8835(int in1, int in2) {
  pinMode(servoPin, OUTPUT);
  analogWrite(PIN_IN1, in1);
  analogWrite(PIN_IN2, in2);
}

void setup() {
  Serial.begin(115200);
  pinMode(PIN_IN1, OUTPUT);
  pinMode(PIN_IN2, OUTPUT);
  DRV8835(0, 0);
  servoAngle(servoPin, 90);

  while (!WiFi.softAP(ssid, password)) {}
  IPAddress myIP = WiFi.softAPIP();
  server.begin();
}

void loop() {
  WiFiClient client = server.available();
  servoAngle(servoPin, servo1);
  DRV8835(motor1, motor2);

  if (client) {
    String currentLine = "";
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        if (c == '\n') {
          if (currentLine.length() == 0) {
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println();
            client.println(controllerHTML);
            break;
          } else {
            currentLine = "";
          }
        } else if (c != '\r') {
          currentLine += c;
        }

        if (currentLine.endsWith("GET /G")) {
          motor1 = 0;
          motor2 = speedMax;
          servo1 = 90;
        }
        if (currentLine.endsWith("GET /B")) {
          motor1 = speedMax;
          motor2 = 0;
          servo1 = 90;
        }
        if (currentLine.endsWith("GET /N")) {
          motor1 = 0;
          motor2 = 0;
          servo1 = 90;
        }
        if (currentLine.endsWith("GET /R")) {
          servo1 = 60;
        }
        if (currentLine.endsWith("GET /L")) {
          servo1 = 120;
        }
        if (currentLine.endsWith("GET /LG")) {
          motor1 = 0;
          motor2 = speedMax;
          servo1 = 120;
        }
        if (currentLine.endsWith("GET /RG")) {
          motor1 = 0;
          motor2 = speedMax;
          servo1 = 60;
        }
        if (currentLine.endsWith("GET /LB")) {
          motor1 = speedMax;
          motor2 = 0;
          servo1 = 120;
        }
        if (currentLine.endsWith("GET /RB")) {
          motor1 = speedMax;
          motor2 = 0;
          servo1 = 60;
        }
      }
    }
    client.stop();
  }
}
