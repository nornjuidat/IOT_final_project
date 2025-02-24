#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <WebSocketsServer.h>
#include <SPI.h>
#include <Wire.h>
#include "Adafruit_GFX.h"
#include "Adafruit_LEDBackpack.h"
#include "WiFiConfig.h"

#define LOCK_PIN D1  // פין לנעילה
ESP8266WebServer server(80);
WebSocketsServer webSocket(81);
Adafruit_7segment display = Adafruit_7segment();

String correctCode = "1234"; // הקוד לפתיחת הדלת
String enteredCode = "";
String revealedDigits = "____";

void handleRoot() {
  server.send(200, "text/html", 
    "<!DOCTYPE html><html><body><h2>Enter Code:</h2>"
    "<input type='text' id='code'><button onclick='sendCode()'>Unlock</button>"
    "<script>function sendCode(){var x=new XMLHttpRequest();"
    "x.open('GET','/unlock?code='+document.getElementById('code').value,true);x.send();}"
    "</script></body></html>"
  );
}

void handleUnlock() {
  if (server.hasArg("code")) {
    enteredCode = server.arg("code");
    if (enteredCode == correctCode) {
      digitalWrite(LOCK_PIN, LOW); // פתיחת הדלת
      server.send(200, "text/plain", "Unlocked!");
    } else {
      server.send(200, "text/plain", "Wrong code!");
    }
  }
}

void webSocketEvent(uint8_t num, WStype_t type, uint8_t * payload, size_t length) {
  if (type == WStype_TEXT) {
    String msg = (char*)payload;
    if (msg.length() == 1) {
      revealedDigits[msg.toInt()] = correctCode[msg.toInt()];
      updateDisplay();
    }
  }
}

void updateDisplay() {
  for (int i = 0; i < 4; i++) {
    display.writeDigitNum(i, revealedDigits[i] == '_' ? '-' : revealedDigits[i] - '0');
  }
  display.writeDisplay();
}

void setup() {
  pinMode(LOCK_PIN, OUTPUT);
  digitalWrite(LOCK_PIN, HIGH); // נעילה ראשונית
  setupWiFi(); // פונקציה מוגדרת ב-WiFiConfig.h
  server.on("/", handleRoot);
  server.on("/unlock", handleUnlock);
  server.begin();
  webSocket.begin();
  webSocket.onEvent(webSocketEvent);
  display.begin(0x70);
  updateDisplay();
}
 

