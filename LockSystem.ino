#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include "WiFiSetup.h"

#define LOCK_PIN D8
#define DISPLAY_PINS {D1, D2, D3, D4}

ESP8266WebServer server(80);
String accessCode = "1234";
String enteredCode = "";
int currentDigit = 0;

void openLock() {
    digitalWrite(LOCK_PIN, HIGH);
    delay(5000);
    digitalWrite(LOCK_PIN, LOW);
}
void updateDisplay() {
    int displayPins[] = DISPLAY_PINS;
    for (int i = 0; i < currentDigit; i++) {
        digitalWrite(displayPins[i], HIGH);
    }
}
