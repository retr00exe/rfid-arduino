const serialport = require("serialport");
const Readline = require('@serialport/parser-readline');
const SerialPort = serialport.SerialPort;
const portName = 'COM10';

const http = require("http").createServer();
const io = require("socket.io")(http, {
  cors: {
    origin: "*"
  }
});

const port = new serialport(portName,{
  baudRate: 9600
});

const parser = port.pipe(new Readline())
parser.on('data', (data) => {
  console.log(data.trim());
  io.emit('message', data.trim());
});

io.on('connection', (socket) => {
  socket.on('message', (message) => {
    console.log(message);
  });
  socket.on('disconnect', () => {
    console.log('disconnected');
  });
});

http.listen(8080, () => console.log(`Listening on http://localhost:8080`))