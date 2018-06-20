var express = require('express');

var app = express();

app.use(function (req, resp) {
    var content = '';
    var ua = req.get('User-Agent');
    content += 'User-Agent: ' + ua;
    resp.send(content);

});

app.listen(3000);

console.log ("Listening on port 3000");

