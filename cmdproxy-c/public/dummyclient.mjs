import { foo, PI } from './dummy.mjs';

function bar () {
	console.log("calling bar ");
	foo();

	console.log("pi = " + PI);
}

bar();

