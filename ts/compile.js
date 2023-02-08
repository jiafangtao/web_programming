var john = {
    name: "John Doe",
    id: 0
};
function logUser(u) {
    console.log("User with name " + u.name + " and id " + u.id);
}
function main() {
    logUser(john);
}
