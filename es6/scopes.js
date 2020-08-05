a = 0; // in global namespace
b = 0;

(function () {
    a = 1; // this will change a in global namespace
    let b = 1; // this is only visible in local function namespace
})();

console.log("a = " + a);
console.log(this);
