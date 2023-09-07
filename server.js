const express = require("express");
const http = require("http");
const WebSocket = require("ws");
const path = require("path");

const app = express();
const server = http.createServer(app);
const wss = new WebSocket.Server({ server });

wss.on("connection", (ws) => {
    console.log("ESP32 connected");

    ws.on('message', (message) => {
        console.log(`Received message => ${message}`);
    });
});

app.use(express.static('public'));  // Your HTML, CSS, JS are in a directory named "public"

server.listen(3000, () => {
    console.log('Server started on http://localhost:3000');
});