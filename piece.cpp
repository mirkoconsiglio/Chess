#include "piece.h"

#include <utility>

const char Piece::EMPTY_SQUARE = char(32);
const char Piece::NONE_SQUARE = char(0);

const Piece Piece::EMPTY = emptyPiece();
const Piece Piece::NONE = nonePiece();

Piece::Piece(int colour, char symbol, string label, string name, const vector<Piece::Move> &moves,
             bool king, bool pawn, vector<Piece> promote_set, const vector<Piece::Move> &captures,
             bool advance) {
	setColour(colour);
	setSymbol(symbol);
	setLabel(std::move(label));
	setName(std::move(name));
	setMoves(moves);
	setKing(king);
	setPawn(pawn);
	setPromoteSet(std::move(promote_set));
	captures.empty() ? setCaptures(moves) : setCaptures(captures);
	setAdvance(advance);
}

Piece::Piece(int colour, string symbol, string label, string name, const vector<Piece::Move> &moves,
             bool king, bool pawn, vector<Piece> promote_set, const vector<Piece::Move> &captures,
             bool advance) {
	setColour(colour);
	setSymbol(std::move(symbol));
	setLabel(std::move(label));
	setName(std::move(name));
	setMoves(moves);
	setKing(king);
	setPawn(pawn);
	setPromoteSet(std::move(promote_set));
	captures.empty() ? setCaptures(moves) : setCaptures(captures);
	setAdvance(advance);
}

Piece::~Piece() = default;

void Piece::setLabel(string l) {
	label = std::move(l);
}

void Piece::setName(string n) {
	name = std::move(n);
}

void Piece::setMoves(vector<Move> m) {
	moves = std::move(m);
}

void Piece::setKing(bool k) {
	king = k;
}

void Piece::setPawn(bool p) {
	pawn = p;
}

void Piece::setPromoteSet(vector<Piece> p) {
	promote_set = std::move(p);
}

void Piece::setCaptures(vector<Move> c) {
	captures = std::move(c);
}

void Piece::setColour(int c) {
	colour = c;
}

void Piece::setSymbol(char s) {
	symbol = string(1, s);
}

void Piece::setSymbol(string s) {
	symbol = std::move(s);
}

void Piece::setAdvance(bool a) {
	advance = a;
}

int Piece::getColour() const {
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

bool Piece::getKing() const {
	return king;
}

bool Piece::getPawn() const {
	return pawn;
}

vector<Piece> Piece::getPromoteSet() {
	return promote_set;
}

vector<Piece::Move> Piece::getCaptures() {
	return captures;
}

bool Piece::getAdvance() const {
	return advance;
}

void Piece::flipMoves() {
	vector<Move> flipped_moves = {};
	int r;
	vector<vector<int>> mov = {};
	for (const Move &M: this->getMoves()) {
		r = M.range;
		for (vector<int> m: M.moves) mov.push_back({-m[0], m[1]});
		flipped_moves.push_back({r, mov});
	}
	this->setMoves(flipped_moves);
	
	vector<Move> flipped_captures = {};
	vector<vector<int>> cap = {};
	for (const Move &C: this->getCaptures()) {
		r = C.range;
		for (vector<int> c: C.moves) cap.push_back({-c[0], c[1]});
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
	
	promote_set = this->getPromoteSet();
	
	cout << this->getName() << " can promote to the following pieces:\n";
	for (Piece p: promote_set) {
		cout << p.getName() << ": " << p.getSymbol() << "\n";
	}
	
	cout << "Promote to (enter symbol): ";
	do {
		cin >> prom;
		for (Piece p: promote_set) {
			if (prom == p.getSymbol()) {
				return p;
			}
		}
		cout << "Entered invalid promotion, please re-enter: ";
	} while (true);
}

Piece Piece::neutralPiece(char symbol, const vector<Move> &moves, bool king, bool pawn, vector<Piece> promote_set,
                          const vector<Move> &captures, bool advance) {
	Piece neutral_piece(0, symbol, "", "", moves, king, pawn,
	                    std::move(promote_set), captures, advance);
	
	return neutral_piece;
}

Piece Piece::neutralPiece(string symbol, const vector<Move> &moves, bool king, bool pawn, vector<Piece> promote_set,
                          const vector<Move> &captures, bool advance) {
	Piece neutral_piece(0, std::move(symbol), "", "", moves, king, pawn,
	                    std::move(promote_set), captures, advance);
	
	return neutral_piece;
}

Piece
Piece::colouredPiece(Piece piece, int colour, string label, string name, bool flip_moves, vector<Piece> promote_set) {
	Piece coloured_piece = Piece(colour, piece.getSymbol(), std::move(label), std::move(name), piece.getMoves(),
	                             piece.getKing(), piece.getPawn(),
	                             std::move(promote_set), piece.getCaptures(), piece.getAdvance());
	
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
		if (Move1.moves != Move2.moves) return false;
	}
	// Identical
	return true;
}