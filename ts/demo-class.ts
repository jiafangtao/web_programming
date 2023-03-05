class Game {}

type Color = 'Black' | 'White'
type FileType = 'A' | 'B' | 'C' | 'D' | 'E' | 'F' | 'G' | 'H'
type Rank = 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8


abstract class Piece {
	protected position: Position;

	constructor(
		private readonly color: Color,
		file: FileType,
		rank: Rank) {
		this.position = new Position(file, rank);
	}
}

class Position {
	constructor(
		private file: FileType,
		private rank: Rank
	) {}
}

class King extends Piece {}
class Queen extends Piece {}
class Bishop extends Piece {}
class Knight extends Piece {}
class Rook extends Piece {}
class Pawn extends Piece {}


function requiresKing(k: King) {}
function requiresQueen(q: Queen) {}

function test() {
	//Q: the declared type of k doesn't matter, why?
	// const k: King
	// const k: Queen
	const k: King = new King('Black', 'A', 1);

	requiresKing(new King('White', 'B', 2));
	requiresQueen(new Queen("Black", "C", 6));

	requiresKing(new Queen('Black', 'A', 8));

	return 3.14;
}
