#include "piece.h"

const char Piece::EMPTY_SQUARE = char(32);
const char Piece::NONE_SQUARE = char(0);

const Piece Piece::EMPTY = emptyPiece();
const Piece Piece::NONE = nonePiece();

Piece::Piece(int colour, char symbol, string label, string name, vector<Piece::Move> moves,
			 bool king, bool pawn, vector<Piece> promote_set, vector<Piece::Move> captures,
			 bool advance) {
    setColour(colour);
    setSymbol(symbol);
    setLabel(label);
    setName(name);
    setMoves(moves);
    setKing(king);
    setPawn(pawn);
    setPromoteSet(promote_set);
    captures.empty() ? setCaptures(moves) : setCaptures(captures);
    setAdvance(advance);
}

Piece::Piece(int colour, string symbol, string label, string name, vector<Piece::Move> moves,
			 bool king, bool pawn, vector<Piece> promote_set, vector<Piece::Move> captures,
			 bool advance) {
    setColour(colour);
    setSymbol(symbol);
    setLabel(label);
    setName(name);
    setMoves(moves);
    setKing(king);
    setPawn(pawn);
    setPromoteSet(promote_set);
    captures.empty() ? setCaptures(moves) : setCaptures(captures);
    setAdvance(advance);
}

Piece::~Piece() {

}

void Piece::setLabel(string l) {
    label = l;
}

void Piece::setName(string n) {
	name = n;
}

void Piece::setMoves(vector<Move> m) {
    moves = m;
}

void Piece::setKing(bool k) {
    king = k;
}

void Piece::setPawn(bool p) {
    pawn = p;
}

void Piece::setPromoteSet(vector<Piece> p) {
    promote_set = p;
}

void Piece::setCaptures(vector<Move> c) {
    captures = c;
}

void Piece::setColour(int c) {
    colour = c;
}

void Piece::setSymbol(char s) {
    symbol = string(1, s);
}

void Piece::setSymbol(string s) {
    symbol = s;
}

void Piece::setAdvance(bool a) {
    advance = a;
}

int Piece::getColour() {
    return colour;
}

string Piece::getSymbol() {
    return symbol;
}

string Piece::getLabel() {
    return label;
}

string Piece::getName() {
	return name;
}

vector<Piece::Move> Piece::getMoves() {
    return moves;
}

bool Piece::getKing() {
    return king;
}

bool Piece::getPawn() {
    return pawn;
}

vector<Piece> Piece::getPromoteSet() {
    return promote_set;
}

vector<Piece::Move> Piece::getCaptures() {
    return captures;
}

bool Piece::getAdvance() {
    return advance;
}

void Piece::flipMoves() {
	vector<Move> flipped_moves = {};
	int r;
	vector<vector<int>> mov = {};
	for (Move M : this->getMoves()) {
		r = M.range;
		for (vector<int> m : M.moves) mov.push_back({-m[0], m[1]});
		flipped_moves.push_back({r, mov});
	}
	this->setMoves(flipped_moves);
	
	vector<Move> flipped_captures = {};
	vector<vector<int>> cap = {};
	for (Move C : this->getCaptures()) {
		r = C.range;
		for (vector<int> c : C.moves) cap.push_back({-c[0], c[1]});
		flipped_captures.push_back({r, cap});
	}
	this->setCaptures(flipped_captures);
}

Piece Piece::emptyPiece() {
    Piece empty_piece(0, EMPTY_SQUARE, "", "Empty");

    return empty_piece;
}

Piece Piece::nonePiece() {
    Piece none_piece(-1, NONE_SQUARE, "", "None");

    return none_piece;
}

Piece Piece::promotePiece() {
    string prom;
    bool promoted = false;
    
    vector<Piece> promote_set = this->getPromoteSet();
    
    cout << this->getName() << " can promote to the following pieces:\n";
    for (Piece p : promote_set) {
    	cout << p.getName() << ": " << p.getSymbol() << "\n";
    }
    
    cout << "Promote to (enter symbol): ";
    do {
        cin >> prom;
        for (Piece p : promote_set) {
            if (prom == p.getSymbol()) {
                return p;
            }
        }
        if (!promoted) cout << "Entered invalid promotion, please re-enter: ";
    } while (!promoted);
    return nonePiece();
}

Piece Piece::neutralPiece(char symbol, vector<Move> moves, bool king, bool pawn, vector<Piece> promote_set,
                   vector<Move> captures, bool advance) {
    Piece neutral_piece(0, symbol, "", "", moves, king, pawn,
                        promote_set, captures, advance);

    return neutral_piece;
}

Piece Piece::neutralPiece(string symbol, vector<Move> moves, bool king, bool pawn, vector<Piece> promote_set,
                   vector<Move> captures, bool advance) {
    Piece neutral_piece(0, symbol, "", "", moves, king, pawn,
                        promote_set, captures, advance);

    return neutral_piece;
}

Piece Piece::colouredPiece(Piece piece, int colour, string label, string name, bool flip_moves, vector<Piece> promote_set) {
    Piece coloured_piece = Piece(colour, piece.getSymbol(), label, name, piece.getMoves(),
                                 piece.getKing(), piece.getPawn(),
                                 promote_set, piece.getCaptures(), piece.getAdvance());
    
    if (flip_moves) coloured_piece.flipMoves();

    return coloured_piece;
}

bool Piece::CompareMoves(vector<Move> M1, vector<Move> M2) {
	// Compare size first
	if (M1.size() != M2.size()) return false;
	Move Move1, Move2;
	for (int i = 0; i < M1.size(); i++) {
		Move1 = M1[i];
		Move2 = M2[i];
		// Compare range
		if (Move1.range != Move2.range) return false;
		// Compare movement
		else if (Move1.moves != Move2.moves) return false;
	}
	// Identical
	return true;
}