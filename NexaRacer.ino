#include <ESP8266WiFi.h> //THIS PROJECT USES THE ESP8266 RATHER THAN THE ESP32, MR ZAMPOGNA HAS GIVEN ME PERMISSION
#include <PubSubClient.h> //TO USE THIS
#include <Servo.h>
#include <Adafruit_NeoPixel.h>

// WiFi and MQTT Credentials
//THIS PROJECT USES MQTT! THIS MEANS IT NEEDS AN INTERNET CONNECTION
//PROXIMA WILL NOT WORK! PLEASE USE CGS-WIFI OR ANOTHER FORM OF NETWORK THAT CAN CONNECT TO THE INTERNET
const char* ssid = "";
const char* password = "";
const char* mqtt_server = "test.mosquitto.org";

// Define Servos and other variables
Servo steering;
Servo ESC;

WiFiClient espClient;
PubSubClient client(espClient);
Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

#define trigPin D2
#define echoPin D3
#define buzzerPin D4
#define LED_PIN    D6
#define LED_COUNT 30

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Serial.begin(9600);
  steering.attach(D5);
  ESC.attach(D8, 1000, 2000);
  
  // Initialize servos to neutral position
  steering.write(90);
  ESC.write(90);
  delay(1000);
  
  // Connect to WiFi and then to the MQTT server
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);

  ESC.attach(D8, 1000, 2000);
  steering.attach(D5);

  strip.begin();
  strip.show();
}

void setup_wifi() {
  delay(10);
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP() );
}

void callback(char* topic, byte* payload, unsigned int length) {
  String slider = "";
  int value = 0;

  // Convert the payload to a string
  String payloadString = String((char*)payload).substring(0, length);

  // Find the slider value in the payload
  int sliderStart = payloadString.indexOf("\"slider\":\"") + 10;
  int sliderEnd = payloadString.indexOf("\"", sliderStart);
  if (sliderStart != -1 && sliderEnd != -1) {
      slider = payloadString.substring(sliderStart, sliderEnd);
  }

  // Find the value in the payload
  int valueStart = payloadString.indexOf("\"value\":\"") + 9;
  int valueEnd = payloadString.indexOf("\"", valueStart);
  if (valueStart != -1 && valueEnd != -1) {
      value = payloadString.substring(valueStart, valueEnd).toInt();
  }

  Serial.print("Received slider: ");
  Serial.print(slider);
  Serial.print(", value: ");
  Serial.println(value);

  if (slider == "steering") {
    steering.attach(D5);
    steering.write(value);
    delay(10);
  } 
  else if (slider == "speed") {
    int previousSpeed = ESC.read(); // Store the previous speed value
    ESC.attach(D8, 1000, 2000);
    ESC.write(value);
    delay(10);
    if (previousSpeed > value) { // Check if the speed has been lowered
        // Turn entire strip red
        for(int i=0; i<strip.numPixels(); i++) {
            strip.setPixelColor(i, strip.Color(255,0,0)); // Red color
        }
        strip.show();
        delay(2000); // Wait for 2 seconds

        // Turn off the strip
        for(int i=0; i<strip.numPixels(); i++) {
            strip.setPixelColor(i, strip.Color(0,0,0)); // Off
        }
        strip.show();
    }
  }
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    String clientId = "ESP8266Client_" + String(random(0xffff), HEX);
    if (client.connect(clientId.c_str())) {
      Serial.println("connected");
      client.subscribe("esp/car");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);
    }
  }
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();


  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  // Send a 10-microsecond pulse to the TRIG_PIN
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Read the time for which the ECHO_PIN stays HIGH
  long duration = pulseIn(echoPin, HIGH);

  // Calculate the distance in centimeters (Speed of sound is 343m/s)
  // The sound travels to the object and then back, so we have to divide by 2
  float distance = (duration * 0.0343) / 2;

  // Print the distance to the serial monitor
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");
  client.publish("esp/car/distance", String(distance).c_str());
  if (distance <= 15) {
    digitalWrite(buzzerPin, HIGH); // Start the buzzer
    delay(3000); // Wait for 3 seconds
    digitalWrite(buzzerPin, LOW); // Stop the buzzer
    ESC.write(90); // Emergency stop
  } else if (distance <= 30) {
    digitalWrite(buzzerPin, HIGH);
    delay(100); // Short beep
    digitalWrite(buzzerPin, LOW);
  }
  delay(100);
}