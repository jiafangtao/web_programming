const ls = function(dir) {
	console.log("listing a remote dir");
};

var fs = {};
fs.list = ls;

fs.list('foo');

export { ls, fs };
