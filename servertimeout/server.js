var express = require('express');
var sleep = require("system-sleep");
var app = express();

app.get("/timeout", function(req, resp) {

    var receivedAt = new Date().toLocaleString();
    console.log("Processing request for " + req.url);
    // sleep for a while (in miliseconds)
    sleep(1000 * 60 * 2);
    var processedAt = new Date().toLocaleString();
    resp.send("Calling handler for GET /timeout. Reqeust received at " + receivedAt + " and processed at " + processedAt);
});

app.use(function (req, resp) {
    var content = '';

    var ua = req.get('User-Agent');
    content += 'User-Agent: ' + ua;

    var clen = req.get('Content-Length');

    if (clen != null)
        content += '\nContent-Length: ' + clen;

    console.log(content);
    resp.send(content);
});

app.listen(3000);

console.log ("Listening on port 3000 ......");

