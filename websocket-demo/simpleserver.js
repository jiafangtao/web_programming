const ws = require("nodejs-websocket");
const PORT = 3000;


var server = ws.createServer(function (conn) { 
    console.log("New connection")
    conn.on("text", function (str) {
        console.log("Received "+str)
        conn.sendText(str + "!!!")
    })
    conn.on("close", function (code, reason) {
 
        console.log("Connection closed")
    })
 
    conn.on("error", function(err){
 
        console.log("handle err");
        console.log(err);
    })
 
});


server.listen(PORT);
console.log("Server is listening on port " + PORT);
