const express = require('express');
const app = express();
const http = require('http');
const server = http.createServer(app);
const { Server } = require("socket.io");
const io = new Server(server);


app.get("*", (req, res, next) => {
  res.setHeader('Access-Control-Allow-Origin', '"*"');
  next();
});

app.get('/', (req, res) => {
  res.sendFile(__dirname + '/index.html');
});

io.on('connection', (socket) => {
  console.log('a user connected with id: ', socket.id);

  socket.broadcast.emit('welcome', 'socket.broadcast.emit');
  socket.emit('welcome', 'socket.emit');

  socket.on('disconnect', () => {
    console.log('user disconnected');
  });

  socket.emit('ping', 'server ping');

  socket.on('pong', (message) => {
    console.log("got reply from client. pong: ", message);
  });

  socket.emit("date", "2023-05-22");
  socket.emit("id", socket.id);
});

server.listen(3000, () => {
  console.log('server is listening on *:3000');
});
