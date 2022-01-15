#ifndef ASCII_CHESS_CPP_PIECE_H
#define ASCII_CHESS_CPP_PIECE_H

#include "general.h"

class Piece {
public:
	struct Move {
		int range;
		vector<vector<int>> moves;
	};
	
	// Hard-coded symbols
	static const char EMPTY_SQUARE;
	static const char NONE_SQUARE;
	
	// Empty and null squares
	static const Piece EMPTY; // signifies a vacant square
	static const Piece NONE; // signifies a square outside the board
	
	explicit Piece(int colour = 0, char symbol = char(0), string label = "", string name = "",
	               const vector<Move> &moves = {}, bool king = false,
	               bool pawn = false, vector<Piece> promote_set = {},
	               const vector<Move> &captures = {}, bool advance = false);
	
	Piece(int colour, string symbol, string label = "", string name = "",
	      const vector<Move> &moves = {}, bool king = false,
	      bool pawn = false, vector<Piece> promote_set = {},
	      const vector<Move> &captures = {}, bool advance = false);
	
	~Piece();
	
	void setColour(int c);
	
	void setSymbol(char s);
	
	void setSymbol(string s);
	
	void setLabel(string l);
	
	void setName(string n);
	
	void setMoves(vector<Move> m);
	
	void setKing(bool k);
	
	void setPawn(bool p);
	
	void setPromoteSet(vector<Piece> p);
	
	void setCaptures(vector<Move> c);
	
	void setAdvance(bool a);
	
	[[nodiscard]] int getColour() const;
	
	string getSymbol();
	
	string getLabel();
	
	string getName();
	
	vector<Move> getMoves();
	
	[[nodiscard]] bool getKing() const;
	
	[[nodiscard]] bool getPawn() const;
	
	vector<Piece> getPromoteSet();
	
	vector<Move> getCaptures();
	
	[[nodiscard]] bool getAdvance() const;
	
	void flipMoves();
	
	static Piece emptyPiece();
	
	static Piece nonePiece();
	
	Piece promotePiece();
	
	static Piece
	neutralPiece(char symbol, const vector<Move> &moves, bool king = false, bool pawn = false,
	             vector<Piece> promote_set = {},
	             const vector<Move> &captures = {}, bool advance = false);
	
	static Piece neutralPiece(string symbol, const vector<Move> &moves, bool king = false, bool pawn = false,
	                          vector<Piece> promote_set = {},
	                          const vector<Move> &captures = {}, bool advance = false);
	
	static Piece colouredPiece(Piece piece, int colour, string label, string name, bool flip_moves = false,
	                           vector<Piece> promote_set = {});
	
	static bool CompareMoves(vector<Move> M1, vector<Move> M2);

private:
	int colour{};
	string symbol;
	string label;
	string name;
	vector<Move> moves;
	bool king{};
	bool pawn{};
	vector<Piece> promote_set;
	vector<Move> captures;
	bool advance{};
};


#endif //ASCII_CHESS_CPP_PIECE_H
