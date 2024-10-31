var firstName = "bruce";
var s = "\u6211\u53EB".concat(firstName);
console.log(s);
var list4 = [1, "str"];
var list5 = [1, 'str'];
//This doesn't work because list4 accepts only number or string.
//list4.push([1,2,3])
// This is okay.
list5.push([1, 2, 3]);
var person1 = [1, "Alex"];
// A bug for tuple in ts
person1.push("Alice");
console.log(person1);
var person2 = [2, "Bob"];
console.log(person2);
var union;
function merge(n1, n2) {
    if (typeof n1 === "string" || typeof n2 === "string") {
        return n1.toString() + n2.toString();
    }
    else
        return n1 + n2;
}
console.log(merge(2, 5));
console.log(merge("hello", "world"));
console.log(merge(888, "what"));
