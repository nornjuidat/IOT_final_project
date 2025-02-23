#include <ESP8266WiFi.h>
#include <WebSocketsClient.h>
#include "WiFiConfig.h"

#define LIGHT_SENSOR_PIN A0
#define TEMP_SENSOR_PIN A1
#define BUTTON_PINS {D2, D3, D4, D5}
#define JOYSTICK_X A2
#define JOYSTICK_Y A3

WebSocketsClient webSocket;
int puzzleStep = 0;
const int correctSequence[4] = {0, 1, 2, 3};
int userSequence[4];
int inputIndex = 0;
void sendPuzzleSolved(int step) {
    String msg = String(step);
    webSocket.sendTXT(msg);
}

void handleLightPuzzle() {
    int lightValue = analogRead(LIGHT_SENSOR_PIN);
    if (lightValue < 800) { 
        delay(2000);
        sendPuzzleSolved(0);
    }
}
void handleTemperaturePuzzle() {
    int tempValue = analogRead(TEMP_SENSOR_PIN);
    if (tempValue < 500) {  
        delay(2000);
        sendPuzzleSolved(1);
    }
}




