#ifndef ASCII_CHESS_CPP_BOARD_H
#define ASCII_CHESS_CPP_BOARD_H

#include "general.h"
#include "piece.h"

class Board {
private:
	// Board properties
	int rows{}, cols{};
	vector<vector<Piece>> board;
public:
	Board();
	
	Board(int rows, int cols);
	
	~Board();
	
	[[nodiscard]] char toX(char r) const;
	
	[[nodiscard]] static char toY(char c);
	
	static char toCol(char y);
	
	void setRows(int r);
	
	void setCols(int c);
	
	[[nodiscard]] int getRows() const;
	
	[[nodiscard]] int getCols() const;
	
	void setPiecePositions(vector<vector<Piece>> b);
	
	vector<vector<Piece>> getPiecePositions();
	
	void setPieceAtPosition(int row, int col, const Piece &piece);
	
	Piece getPieceAtPosition(int row, int col);
	
	void drawBoard();
	
	void refreshBoard();
	
	// Hard-coded symbols
	static const char WHITE_SQUARE;
	static const char BLACK_SQUARE;
};


#endif //ASCII_CHESS_CPP_BOARD_H
