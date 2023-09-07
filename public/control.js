var gateway = `ws://${window.location.hostname}:3000`;
var websocket;

function initWebSocket()  {
    websocket = new WebSocket(gateway);
    websocket.onmessage = onMessage;
}

function onMessage(event) {
    console.log(event.data); //Handle ESP32 Messages
}

function updateValue(type, value) {
    if (type === 'steering') {
        document.getElementById('steeringValue').innerText = value;
    } else {
        document.getElementById('speedValue').innerText = value;
    }
    websocket.send(`${type}:${value}`);
}

window.onload = initWebSocket;