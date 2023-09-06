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

void webSocketEvent(WStype_t type, uint8_t* payload, size_t length) {
    switch(type) {
        case WStype_DISCONNECTED:
            Serial.printf("[WSc] Disconnected!\n");
            break;
        case WStype_CONNECTED:
            Serial.printf("[WSc] Connected to url: %s\n");
            break;
        case WStype_TEXT:
            handleWebSocketMessage(payload, length);
            break;
    }
}

void handleWebSocketMessage(uint8_t* data, size_t len) {
    String receivedMsg = String((char*)data);
    if (receivedMsg.startsWith("steering:")) {
        String value = receivedMsg.substring(9); // 9 is the length of "steering:"
        int angle = value.toInt();
        steering.write(angle);  // Adjust the steering servo based on the received angle
    } else if (receivedMsg.startsWith("speed:")) {
        String value = receivedMsg.substring(6); // 6 is the length of "speed:"
        int speedValue = value.toInt();
        ESC.write(speedValue);  // Adjust the speed ESC based on the received speed value
    }
}

void setup() {
    Serial.begin(9600);

    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.println("Connecting to WiFi ...");
    }
    Serial.println("Connected to WiFi!");

    webSocket.begin("YOUR_NODE_SERVER_IP", 3000, "/");
    webSocket.onEvent(webSocketEvent);

    steering.attach(5); //Setup Pin numbers - CHANGE LATER
    ESC.attach(16, 1000, 2000);
}

void loop() {
    webSocket.loop();
}