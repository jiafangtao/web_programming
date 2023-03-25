var koa = require('koa');
var router = require('koa-router');
var app = new koa();

var _ = new router(); //Instantiate the router

_.get('/hello', getMessage);
_.post('/hello', postMessage);

function *getMessage() {
    this.body = "Hello world!";
};
function *postMessage() {
   this.body = "You just called the post method at '/hello'!\n";
};
app.use(_.routes()); //Use the routes defined using the router
app.listen(3000);
