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
void handleLEDSequencePuzzle() {
    int buttonPins[] = BUTTON_PINS;
    for (int i = 0; i < 4; i++) {
        pinMode(buttonPins[i], INPUT_PULLUP);
    }

    int buttonPressed = -1;
    for (int i = 0; i < 4; i++) {
        if (digitalRead(buttonPins[i]) == LOW) {
            buttonPressed = i;
            break;
        }
    }
       if (buttonPressed != -1 && inputIndex < 4) {
        userSequence[inputIndex++] = buttonPressed;
        if (inputIndex == 4) {
            bool success = true;
            for (int i = 0; i < 4; i++) {
                if (userSequence[i] != correctSequence[i]) {
                    success = false;
                    break;
                }
            }
            if (success) sendPuzzleSolved(2);
        }
    }
}
void handleJoystickPuzzle() {
    int xValue = analogRead(JOYSTICK_X);
    int yValue = analogRead(JOYSTICK_Y);
    
    if ((xValue < 200 && yValue < 200) || (xValue > 800 && yValue < 200) || 
        (xValue < 200 && yValue > 800) || (xValue > 800 && yValue > 800)) {
        delay(2000);
        sendPuzzleSolved(3);
    }
}

void setup() {
    setupWiFi();
    webSocket.begin("<LOCK_CONTROLLER_IP>", 81, "/");
}

void loop() {
    handleLightPuzzle();
    handleTemperaturePuzzle();
    handleLEDSequencePuzzle();
    handleJoystickPuzzle();
    webSocket.loop();
{



