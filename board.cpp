#include "board.h"

const char Board::WHITE_SQUARE = char(219);
const char Board::BLACK_SQUARE = char(255);

Board::Board() = default;

Board::Board(int rows, int cols) {
	board.resize(cols, vector<Piece>(rows));
	setRows(rows);
	setCols(cols);
}

Board::~Board() = default;

char Board::toX(char r) const { // Convert to x-coordinate
	return (char) this->getRows() + '0' - r;
}

char Board::toY(char c) { // Convert to y-coordinate
	return c - 97;
}

char Board::toCol(char y) {
	return y + 97;
}

void Board::setRows(int r) {
	rows = r;
}

void Board::setCols(int c) {
	cols = c;
}

int Board::getRows() const {
	return rows;
}

int Board::getCols() const {
	return cols;
}

void Board::setPiecePositions(vector<vector<Piece>> b) {
	board = std::move(b);
}

vector<vector<Piece>> Board::getPiecePositions() {
	return board;
}

void Board::setPieceAtPosition(int row, int col, const Piece &piece) {
	board[row][col] = piece;
}

Piece Board::getPieceAtPosition(int row, int col) {
	if (row >= this->getRows() || row < 0 || col >= this->getCols() || col < 0) return Piece::NONE;
	else return board[row][col];
}

void Board::drawBoard() {
	char board_colour;
	
	cout << "\n";
	for (int row = 0; row < this->getRows(); row++) {
		for (int i = 0; i <= 2; i++) {
			// plot rank markings
			i == 1 ? (cout << "   " << this->getRows() - row << "   ") : (cout << "       ");
			for (int col = 0; col < this->getCols(); col++) {
				(row + col) % 2 == 0 ? board_colour = WHITE_SQUARE : board_colour = BLACK_SQUARE;
				for (int j = 0; j <= 5; j++) {
					if (i == 1 && j == 2) {
						this->getPieceAtPosition(row, col).getColour() == 0 ? cout << board_colour << board_colour :
						cout << this->getPieceAtPosition(row, col).getLabel();
						j++;
					} else cout << board_colour;
				}
			}
			cout << "\n";
		}
	}
	
	// plot file markings
	string files;
	string five_space = "     ";
	
	files = "\n" + five_space;
	for (int i = 97; i < 97 + this->getCols(); i++) {
		files += five_space;
		files.push_back(char(i));
	}
	files = files + "\n";
	cout << files;
}

void Board::refreshBoard() {
	this->drawBoard();
}
