# 🏎️ NexaRacer NexaRacer: The IoT Connected Racecar 🌐

Drive into the future with `NexaRacer`, an Internet of Things (IoT) connected racecar controlled seamlessly from a web interface.

## 📖 Overview

`NexaRacer` combines the thrill of racing with the power of modern IoT technologies. Using a Node.js backend server and a sleek web interface, users can control the speed and steering of their ESP8266-based racecar in real-time. With    MQTT, the start for communication with IoT devicesi, commands from the browser are instantly translated to movements on the ground.
The project utilises an ESP8266 board running firmware and NodeJS to control a remote-controlled car. Through MQTT, the ESP8266 is able to recive data and turn that into movements.

## ✨ Features

- **Real-time Control**: No lag. Just pure, unadulterated speed. 🚀
- **Web Interface**: Control your racer from any device with a browser. 📱💻
- **IoT Enabled**: Harness the power of connected devices. 🌐🔗
- **Obstacle Avoidance**: Car will warn you if an obstacle is ahead, and emergency stop if needed!

## 🛠️ Dependencies

- `Node.js` and `npm`: The backbone of our server.
- `express`: Powers our web server.
- `mqtt`: Handles sending our data to the car.
- `ESP8266WiFi.h`, `PubSubClient.h`, `Servo.h`, `Adafruit_NeoPixel.h` Arduino libraries for our ESP8266

# Documentation 📚

## 🚀 Installation & Running

1. **Node.js Setup**:
   
   First, clone this repository:
   ```bash
   git clone [your-repository-link]
   cd [your-repository-directory]
   ```
   Install the necessary Node.js packages:
   ```bash
   npm install
   ```
   Now, fire up the server
   ```bash
   node server.js
   ```

   ## ESP8266 Setup:

1. Open the `NexaRacer.ino` in the Arduino IDE.
2. Ensure you've installed the necessary libraries (refer to Dependencies).
3. Upload the sketch to your ESP8266.

## Racing Time! 🏁:

With both your Node.js server running and the ESP8266 powered up, head over to [http://localhost:3000](http://localhost:3000) in your web browser. Adjust the sliders, and watch your `NexaRacer` come to life!

## 🤝 Contributing

Contributions are what make the open-source community such a fantastic place to learn, inspire, and create. We warmly welcome any contributions you'd like to make to `NexaRacer`.

## 📜 License

Distributed under the MIT License. See `LICENSE` for more information.

![alt text](https://hobbiesdirect.com.au/image/cache/catalog/product/HSP/HSP-94607/HSP-94607_13-1200x800.webp)

## Credits
All of this code is my own code and work. Thank you to Arjun Sharma, Damian Camilleri, and Will Madl for teaching me how to use the Car chasis at various Code Cadets Sessions, along with teaching me C++.
