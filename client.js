// Simple TCP Client example

const {Socket} = require('net');

const port = '22333';
const host = '192.168.1.70';

const client = new Socket();

client.on('data', data => {
    console.log(data.toString());
});

client.on('end', () => {
    console.log('Connection ended');
});

client.on('error', err => {
    console.log(err);
});

client.connect({port, host}, () => {
    console.log('Connected to the server');
    client.write('Hello!!!! \r');
});

