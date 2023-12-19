// demo-abstract-class.ts
class Position {
}
class Piece {
    moveTo(pos) {
        this.position = pos;
    }
}
class King extends Piece {
    canMoveTo(pos) {
        console.log("This method must be implemented.");
    }
}
function main() {
    //error TS2511: Cannot create an instance of an abstract class.
    //var p = new Piece();
}
