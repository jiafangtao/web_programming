var number1 = 1
var number2 = 2


function doSomethingWithVar() {
    //NOTE: the value will be undefined. BUT when i is declared in the function scope as a var, it's actually defined.
    // So you will NOT get an "undefined" error.
    console.log("init value:", i) 

    for (var i = 0; i<5; i++) {
        console.log(i)
    }

    console.log("(var) final value: ", i)
}

doSomethingWithVar();
doSomethingWithVar();



function doSomethingWithLet() {
    // Error: not defined
    //console.log("init value:", i)
    for (let i = 10; i<15; i++) {
        console.log(i)
    }

    // Error: not defined
    //console.log("(let) final value: ", i)
}

doSomethingWithLet();
doSomethingWithLet();
