// Create an Object
const person = {
    firstName: "John",
    lastName: "Doe",
    age: 50,
    eyeColor: "blue"
  };
  
  // Destructuring Assignment - note that 'region' is not defined at all.
  let { firstName, age, region } = person;

  // 'region' field will be undefined
  console.log(firstName, age, region);

