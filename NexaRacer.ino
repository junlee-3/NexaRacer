#include <Arduino.h>
#include <WiFi.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <WebSocketsClient.h>
#include <Servo.h>

const char* ssid = "Your_SSID";
const char* password = "Your_PASSWORD";

Servo steering;
Servo ESC;

WebSocketsClient webSocket;