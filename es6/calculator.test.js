
var Calculator = require ("./build/main.bundle").default;
var should = require ('should');

describe ('Class Calculator', function () {

	before ( function () {

	}
	);

	describe ('#name()', function () {
		it ('should be able to get name', function () {
			var target = new Calculator ();
			should.equal(target.name, 'calculator');
		});
	});

	describe ('dummy', function () {
		it ('should be able to call dummy', function () {});
	});
});
