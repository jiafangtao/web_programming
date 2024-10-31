
const myObject = {
    name: "name",
    age: 25,
}

const anotherObject = {...myObject, name: "bruce"}

const thirdObject = {age: 19, ...myObject}


console.log(anotherObject);
console.log(thirdObject)

// interface is part of TS, not ES6.
interface Props {
    name: string,
    age: number,
}


// Create an Array
const fruits = ["Banana", "Orange", "Apple", "Mango"];

// Destructuring Assignment
let [fruit1, fruit2] = fruits;

console.log('=============== fruits : demo of array destructuring ============')

console.log(fruits)
console.log(fruit1, fruit2)

console.log("=========== object destructuring ===============")

// Create an Object
const person = {
    firstName: "John",
    lastName: "Doe",
    age: 50,
    eyeColor: "blue"
  };
  
  // Destructuring Assignment
  let { firstName, age } = person;
  console.log(firstName, age, region);
