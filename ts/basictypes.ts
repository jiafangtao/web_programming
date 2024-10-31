const demoStringInterpolation = () => {
    let firstName : string = "bruce"
    let s = `我叫${firstName}`
    
    console.log(s);
    
}

demoStringInterpolation()


let list4 = [1, "str"]
let list5 : any[] = [1, 'str']

//This doesn't work because list4 accepts only number or string.
//list4.push([1,2,3])

// This is okay.
list5.push([1,2,3])

let person1: [number, string] = [1, "Alex"];

// A bug for tuple in ts
person1.push("Alice")

console.log(person1)


let person2 = [2, "Bob"]
console.log(person2)


let union : string | number

function merge(n1 : number | string, n2 : number | string) {
    if (typeof n1 === "string" || typeof n2 === "string") {
        return n1.toString() + n2.toString()
    }
    else 
        return n1 + n2
}

console.log(merge(2, 5))
console.log(merge("hello", "world"))

console.log(merge(888, "what"))
