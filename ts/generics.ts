let lastInArray = (input: Array<any>) => {
    if (!input || input.length == 0) {
        return undefined;
    }

    return input[input.length - 1]
}

console.log(lastInArray([1, 2, 3, 4, 5]))
console.log(lastInArray(["a", "b", "c"]))

// The problem with 'any' type is that it has no meaningful constraints for the input type.
console.log(lastInArray([1, true, "blah"]))


let lastInArrayWithGP = <T>(input: Array<T>) => {
    if (!input || input.length == 0) {
        return undefined;
    }

    return input[input.length - 1]
}

console.log("=== play with GP ===")

console.log(lastInArrayWithGP([1, 2, 3, 4, 5]))
console.log(lastInArrayWithGP(["a", "b", "c"]))

// NOTE: TS will deduce T as "number | string | boolean", aka a union type.
// In my mind I'm not quite in favor of the union types.
console.log(lastInArrayWithGP([1, true, "blah"]))

// demo with multiple generic types

const makeTuple = (x, y) => [x, y]

let v1 = makeTuple(1, "one")
let v2 = makeTuple(true, "是")

console.log(v1)
console.log(v2)

const makeTupleWithGP = <T, Y = string>(x: T, y: Y) => [x, y]

console.log(makeTupleWithGP(1, true))
console.log(makeTupleWithGP<number>(2, "two")) // with default generic type parameter
