// demo-functions.ts

function greet(name: string) {
	return 'hello, ' + name
}

let greet2 = function(name: string) {
	return 'hello, ' + name
}

let greet3 = (name: string) => {
	return 'hello, ' + name;
}

let greet4 = (name: string) => 
	'hello, ' + name;

function multi_return_types(n: number) {
	if ( n == 0) {
		return null;
	}
	else if ( n == 1) {
		return 0.618;
	}
	else if (n > 1 && n < 4) {
		return 3.14159;
	}
	else {
		return "oops";
	}
}
