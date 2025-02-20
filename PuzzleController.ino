#include <ESP8266WiFi.h>
#include <WebSocketsClient.h>
#include "WiFiConfig.h"

#define LIGHT_SENSOR_PIN A0
#define TEMP_SENSOR_PIN A1
#define BUTTON_PINS {D2, D3, D4, D5}
#define DISTANCE_SENSOR_TRIGGER D6
#define DISTANCE_SENSOR_ECHO D7

WebSocketsClient webSocket;
int puzzleStep = 0;
const int correctSequence[4] = {0, 1, 2, 3};
int userSequence[4];
int inputIndex = 0;
