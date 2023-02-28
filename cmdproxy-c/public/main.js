const list = function(dir) {
	console.log("listing a remote dir");
};

var fs = {};
fs.list = list;

fs.list('foo');
