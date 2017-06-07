# es6


**NOTE**: This folder contains not only ES6 (or others like ES7), but also some node.js code snippets drafted along I learn
node.js.

##### What The Files Are

- calculator.js
	- This is a simple class written in ES6.
	- Not fully implemented yet (at all).
	- Using ES6 features for module export, class definition, getter/setter, etc.

- calculator.test.js
	- Test code for class Calculator
	- Using mocha(摩卡), should.js
	- **Unfortunately** node.js v6.9 nor mocha doesn't support ES6 module export, this test code cannot directly load calculator.js. Instead it loads build/main.bundle.js which was compiled by babel.
	
- cpus.js
	- node.js code snippet to get CPU information

- pid.js
	- node.js code snippet to get process id

##### How to Play

- Run "npm install -g mocha" to install mocha globally. Thus you can run "mocha" from any directory.
- Run "npm install" to set up all. It will install babel-cli, babel-core, babel-preset-es2015, and should.js.
- Run "npm run babel" to compile ES6 code to be compatible with major JavaScript environments
- Run "npm test" to execute tests

