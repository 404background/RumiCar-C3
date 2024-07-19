#include <WiFi.h>
#include <WiFiClient.h>
#include <WiFiAP.h>

const int ServoPin1 = D1;
const int ServoPin2 = D2;
const int DutyMax = 2300;
const int DutyMin = 700;
int speed1 = 0;
int speed2 = 0;

const char *ssid = "ESP32C3";
const char *password = "123456789";
WiFiServer server(80);

int test = 12345;

String str =
  "Click <a href=\"/G\">here</a> to Gp straight.<br>"
  "Click <a href=\"/B\">here</a> to Go back.<br>"
  "Click <a href=\"/N\">here</a> to Stop.<br>"
  "Click <a href=\"/R\">here</a> to turn right.<br>"
  "Click <a href=\"/L\">here</a> to turn left.<br>";

void ServoSpeed(int pin, int speed) {
  if (speed != 0) {
    int Duty = map(speed, -10, 10, DutyMin, DutyMax);
    digitalWrite(pin, HIGH);
    delayMicroseconds(Duty);
    digitalWrite(pin, LOW);
    delayMicroseconds(20 * 1000 - Duty);
  }
}

void setup() {
  Serial.begin(115200);

  pinMode(ServoPin1, OUTPUT);
  pinMode(ServoPin2, OUTPUT);
  ServoSpeed(ServoPin1, 5);
  ServoSpeed(ServoPin2, 5);

  while (!WiFi.softAP(ssid, password)) {}
  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);
  server.begin();
}

void loop() {
  WiFiClient client = server.available();  // listen for incoming clients
  ServoSpeed(ServoPin1, speed1);
  ServoSpeed(ServoPin2, speed2);

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
            client.print(str);
            client.println();
            break;
          } else {
            currentLine = "";
          }
        } else if (c != '\r') {
          currentLine += c;
        }

        if (currentLine.endsWith("GET /G")) {
          speed1 = 5;
          speed2 = -5;
        }
        if (currentLine.endsWith("GET /B")) {
          speed1 = -5;
          speed2 = 5;
        }
        if (currentLine.endsWith("GET /N")) {
          speed1 = 0;
          speed2 = 0;
        }
        if (currentLine.endsWith("GET /R")) {
          speed1 = 2;
          speed2 = 2;
        }
        if (currentLine.endsWith("GET /L")) {
          speed1 = -2;
          speed2 = -2;
        }
      }
    }
    client.stop();
  }
}
