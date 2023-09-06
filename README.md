# 🏎️ NexaRacer IoTRacer: The IoT Connected Racecar 🌐

Drive into the future with `NexaRacer`, an Internet of Things (IoT) connected racecar controlled seamlessly from a web interface.

## 📖 Overview

`NexaRacer` combines the thrill of racing with the power of modern IoT technologies. Using a Node.js backend server and a sleek web interface, users can control the speed and steering of their ESP32-based racecar in real-time. With WebSocket integration, commands from the browser are instantly translated to movements on the ground.
The project utilises an ESP32 board running firmware and NodeJS to control a remote-controlled car. Through websockets, the ESP32 is able to recive data and turn that into movements.

## ✨ Features

- **Real-time Control**: No lag. Just pure, unadulterated speed. 🚀
- **Web Interface**: Control your racer from any device with a browser. 📱💻
- **IoT Enabled**: Harness the power of connected devices. 🌐🔗

## 🛠️ Dependencies

- `Node.js` and `npm`: The backbone of our server.
- `express`: Powers our web server.
- `ws`: Handles WebSocket connections for real-time control.
- `ESPAsyncTCP`, `ESPAsyncWebServer`, `WebSocketsClient` Arduino libraries for ESP32 communication.

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

   ## ESP32 Setup:

1. Open the `ESP_Car.ino` in the Arduino IDE.
2. Ensure you've installed the necessary libraries (refer to Dependencies).
3. Upload the sketch to your ESP32.

## Racing Time! 🏁:

With both your Node.js server running and the ESP32 powered up, head over to [http://localhost:3000](http://localhost:3000) in your web browser. Adjust the sliders, and watch your `IoTRacer` come to life!

## 🤝 Contributing

Contributions are what make the open-source community such a fantastic place to learn, inspire, and create. We warmly welcome any contributions you'd like to make to `IoTRacer`.

## 📜 License

Distributed under the MIT License. See `LICENSE` for more information.

   
