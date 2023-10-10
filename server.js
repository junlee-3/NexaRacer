const express = require('express');
const mqtt = require('mqtt');
const app = express();
const port = 3000;

const mqttBroker = 'mqtt://test.mosquitto.org'; // Use a free test broker
const client = mqtt.connect(mqttBroker);

client.on('connect', function () {
  console.log('Connected to MQTT Broker');
});

app.use(express.static('public'));

app.get('/send', (req, res) => {
  const { slider, value } = req.query;
  console.log(`Sending ${slider} with value ${value} to MQTT broker.`);
  client.publish('esp/car', JSON.stringify({ slider, value }));
  res.sendStatus(200);
});

app.listen(port, () => {
  console.log(`Server started on http://localhost:${port}`);
});
