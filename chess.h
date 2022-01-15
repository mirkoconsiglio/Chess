#ifndef ASCII_CHESS_CPP_CHESS_H
#define ASCII_CHESS_CPP_CHESS_H

#include "general.h"
#include "board.h"

class Chess {
public:
	struct Round {
		int round;
		string white_move;
		string black_move;
	};
	
	Chess();
	
	~Chess();
	
	void setBoard(int rows, int cols);
	
	void startGame();
	
	void endGame(string message, int winner);
	
	void recordFEN(bool capture, bool pawn);
	
	void recordMove(string move, bool pawn, bool capture, char promote);
	
	void printWhiteCaptures();
	
	void printBlackCaptures();
	
	void printCaptures();
	
	void printPGN(int colour = -1);
	
	void printFEN(int i);
	
	char canPromote(Piece piece, int row, int col);
	
	string isValid(string move);
	
	string findPiece(string move, int new_row, int new_col, Piece piece, int friendly_colour, bool capture);
	
	string makeMove(string move, int old_row, int old_col, int new_row, int new_col, Piece piece, bool capture);
	
	string advance(string move, int old_row, int col, int new_row, Piece piece);
	
	void castle(string move, int row, int king_col, int rook_col, bool kingside);
	
	string enPassant(string move, int old_row, int old_col, int new_row, int new_col, Piece piece);
	
	bool positionInCheck(int pos_colour, int pos_row, int pos_col);
	
	bool kingInCheck(int king_colour);
	
	bool kingInCheckmate(int king_colour);
	
	bool kingInStalemate(int king_colour);
	
	bool isDraw();
	
	bool isEnPassant(int row, int col, int enemy_colour);
	
	void kingMove(Piece piece);
	
	void rookMove(Piece piece, int col);
	
	void setRound(int i);
	
	int getRound();
	
	void incrementRound();
	
	void setHalfmove(int i);
	
	int getHalfmove();
	
	void incrementHalfmove();
	
	void setTurn(int i);
	
	int getTurn();
	
	void changeTurn();
	
	void setEnd(bool b);
	
	bool getEnd();
	
	void resetRounds();
	
	vector<Round> getRounds();
	
	void addWhiteMove(string move);
	
	void addBlackMove(string move);
	
	void resetFEN();
	
	string getFEN(int i);
	
	void addFEN(string f);
	
	void setPlayerOneColour(string c);
	
	void setPlayerTwoColour(string c);
	
	string getPlayerOneColour();
	
	string getPlayerTwoColour();
	
	void setWhitePieces(vector<Piece> p);
	
	void setBlackPieces(vector<Piece> p);
	
	vector<Piece> getWhitePieces();
	
	vector<Piece> getBlackPieces();
	
	void setWhitePromotionRows(vector<int> r);
	
	void setBlackPromotionRows(vector<int> r);
	
	void setWhiteAdvanceRows(vector<int> r);
	
	void setBlackAdvanceRows(vector<int> r);
	
	vector<int> getWhitePromotionRows();
	
	vector<int> getBlackPromotionRows();
	
	vector<int> getWhiteAdvanceRows();
	
	vector<int> getBlackAdvanceRows();
	
	void resetCaptures();
	
	void pushWhiteCaptures(string s);
	
	void pushBlackCaptures(string s);
	
	vector<string> getWhiteCaptures();
	
	vector<string> getBlackCaptures();
	
	void setWhiteKingsideCastle(bool b);
	
	void setWhiteQueensideCastle(bool b);
	
	void setBlackKingsideCastle(bool b);
	
	void setBlackQueensideCastle(bool b);
	
	bool getWhiteKingsideCastle();
	
	bool getWhiteQueensideCastle();
	
	bool getBlackKingsideCastle();
	
	bool getBlackQueensideCastle();
	
	void setEnPassant(int i);
	
	int getEnPassant();
	
	void refreshBoard();

private:
	int round, halfmove, turn;
	bool end;
	
	vector<Round> rounds;
	
	string player_one_colour, player_two_colour;
	
	Board board;
	
	vector<int> white_promotion_rows, black_promotion_rows;
	vector<int> white_advance_rows, black_advance_rows;
	vector<string> white_captures, black_captures;
	
	// Chess symbols
	static const char KING_SYMBOL = 'K';
	static const char QUEEN_SYMBOL = 'Q';
	static const char BISHOP_SYMBOL = 'B';
	static const char KNIGHT_SYMBOL = 'N';
	static const char ROOK_SYMBOL = 'R';
	static const char PAWN_SYMBOL = 'P';
	static const char CASTLE_SYMBOL = 'O';
	
	vector<Piece> pieces, white_pieces, black_pieces;
	
	bool white_kingside_castle;
	bool white_queenside_castle;
	bool black_kingside_castle;
	bool black_queenside_castle;
	int en_passant;
	
	vector<string> FEN;
};


#endif //ASCII_CHESS_CPP_CHESS_H
