import { readdir } from 'node:fs';

const list = function(dir) {
	try {
		readdir(dir);
	} catch (err) {
		console.error("listing a remote dir");
	}
		
};

module.exports.list = list;
