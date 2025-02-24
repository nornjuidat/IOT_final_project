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

String correctCode = "1234"; 
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
