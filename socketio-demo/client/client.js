//index.js

const { io } = require("socket.io-client");

const local = "http://127.0.0.1:3000";
//const k8s = "http://127.0.0.1:54241/socket.io/";

const k8s = "http://localhost";

const sockserver = "http://net-socket"

const socket = io(k8s, {
  transports: ['websocket', 'polling'],
  reconnection: true,
  upgrade: true,
  timeout: 3000,
  auth: {
    token: "123"
  },
  query: {
    "my-key": "my-value"
  }
});

console.log("socket.id: ", socket.id);

socket.on('connect', () =>{
  console.log("socket.id: ", socket.id);  
});


socket.io.on("error", (error) => {
  console.error(error);
});

const callback = (message) => {
  console.log("[message] ", message);
}

socket.on('ping', (message) => {
  console.log("client - got a ping: ", message);
  socket.emit("pong", 3.14);
});


socket.onAny((event, ...args) => {
  console.warn(`onAny got ${event}: ${args}`);
});
