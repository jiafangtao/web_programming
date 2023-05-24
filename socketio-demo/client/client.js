//index.js

const { io } = require("socket.io-client");

const local = "http://127.0.0.1:3000";

// Based on the tests both schemes (http and ws) work well.
//const thismachine = "http://thismachine:3000"; // ok
const thismachine = "ws://thismachine:3000"; // ok

const sockserver = "http://net-socket";
const devServer = "http://192.168.88.67";

const k8s = "http://127.0.0.1";

//const server = thismachine;
const server = k8s;


console.log("Connecting websocket server at ", server);

const socket = io(server, {
  transports: ['websocket', 'polling'],
  reconnection: true,
  upgrade: true,
  timeout: 10000,
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
