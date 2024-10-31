//let number1 = 1;
//let number2 = 2;

let isTrue : boolean

console.log("isTrue: ", isTrue)

//isTrue = "true"

let message : any;
message = "hello"

console.log(message)

// This will result in an error - endWith is not defined. It's a runtime error rather than compile-time error.
console.log(message.endWith("c"))

console.log(message.endsWith("o"))

let dd2 = (message as string).endsWith('c')

