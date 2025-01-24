function getRandomInt(max) {
    return Math.floor(Math.random() * Math.floor(max));
}

var amqp = require('amqplib/callback_api');
amqp.connect('amqp://localhost', function(err, conn) {
    if (err) {
        console.error(err);
        return;
    }

  conn.createChannel(function(err, ch) {
    if (err) {
      console.error(err);
      throw err;
    }

    var q = 'hello';
    ch.assertQueue(q, {durable: false});
    let rand = getRandomInt(1000);
    let msg = `Hello World! ${rand}`;
    ch.sendToQueue(q, Buffer.from(msg));
    console.log(" [x] Sent ", msg);
  });
  setTimeout(function() { conn.close(); process.exit(0) }, 500);
});

