//Mr Z said I am allowed to not use EJS 
const express = require('express');
const mqtt = require('mqtt');
const app = express();
const port = 3000;

const mqttBroker = 'mqtt://test.mosquitto.org'; // Use a free test broker
const client = mqtt.connect(mqttBroker);

let clients = [];

client.on('connect', function () {
    console.log('Connected to MQTT Broker');
    client.subscribe('esp/car/distance');
});

client.on('message', function (topic, message) {
    if (topic === 'esp/car/distance') {
        clients.forEach(clientRes => clientRes.write(`data: ${message}\n\n`));
    }
});

app.use(express.static('public'));

app.get('/send', (req, res) => {
    const { slider, value } = req.query;
    console.log(`Sending ${slider} with value ${value} to MQTT broker.`);
    client.publish('esp/car', JSON.stringify({ slider, value }));
    res.sendStatus(200);
});

app.get('/events', (req, res) => {
    res.setHeader('Content-Type', 'text/event-stream');
    res.setHeader('Cache-Control', 'no-cache');
    res.setHeader('Connection', 'keep-alive');
    res.flushHeaders();
    
    clients.push(res);

    req.on('close', () => {
        clients = clients.filter(client => client !== res);
    });
});

app.listen(port, () => {
    console.log(`Server started on http://localhost:${port}`);
});
