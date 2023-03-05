// demo-abstract-class.ts

class Position {}

abstract class Piece {
	private position: Position;

	moveTo(pos: Position) {
		this.position = pos;
	}

	abstract canMoveTo(pos: Position);
}

class King extends Piece {

	canMoveTo(pos: Position) {
		console.log("This method must be implemented.");
	}
}

function main() {
	//error TS2511: Cannot create an instance of an abstract class.
	//var p = new Piece();
}
