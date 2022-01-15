#ifndef ASCII_CHESS_CPP_SHOGI_H
#define ASCII_CHESS_CPP_SHOGI_H


#include "general.h"
#include "board.h"

class Shogi {
	public:
	struct Round {
		int round;
	    string black_move;
	    string white_move;
	};
	
	Shogi();
	
	~Shogi();
	
	void setBoard(int rows, int cols);
	
	Board getBoard();
	
	void startGame();
	
	void endGame(string message, int winner);
	
	void recordMove(string move, bool pawn, bool capture, char promote);
	
	void printCaptures();
	
	void printPGN(int colour = -1);
	
	char canPromote(Piece piece, int row, int col);
	
	string isValid(string move);
	
	string findPiece(string move, int new_row, int new_col, Piece piece, int friendly_colour, bool capture);
	
	string makeMove(string move, int old_row, int old_col, int new_row, int new_col, Piece piece, bool capture);
	
    bool positionInCheck(int pos_colour, int pos_row, int pos_col);

    bool kingInCheck(int king_colour);
    
    bool kingInCheckmate(int king_colour);

	bool kingInStalemate(int king_colour);
    
    bool isDraw();
    
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
    
    vector<int> getWhitePromotionRows();
    
    vector<int> getBlackPromotionRows();
    
    void resetCaptures();
    
    void pushWhiteCaptures(string s);
    
    void pushBlackCaptures(string s);
    
    vector<string> getWhiteCaptures();
    
    vector<string> getBlackCaptures();
    
    void printWhiteCaptures();
    
    void printBlackCaptures();
    
    void refreshBoard();

private:
	int round, halfmove, turn;
	bool end;
	
	vector<Round> rounds;
	
	string player_one_colour, player_two_colour;
	
	Board board;
	
	vector<int> black_promotion_rows, white_promotion_rows;
    vector<string> black_captures, white_captures;
	
	// Chess symbols
	static const char KING_SYMBOL = 'K';
	static const char GOLD_GENERAL_SYMBOL = 'G';
	static const char SILVER_GENERAL_SYMBOL = 'S';
	static const char KNIGHT_SYMBOL = 'N';
	static const char LANCE_SYMBOL = 'L';
	static const char BISHOP_SYMBOL = 'B';
	static const char ROOK_SYMBOL = 'R';
	static const char PAWN_SYMBOL = 'P';
	
	inline static const string PROMOTED_SILVER_GENERAL_SYMBOL = "+S";
	inline static const string PROMOTED_KNIGHT_SYMBOL = "+N";
	inline static const string PROMOTED_LANCE_SYMBOL = "+L";
	inline static const string DRAGON_HORSE_SYMBOL = "+B";
	inline static const string DRAGON_KING_SYMBOL = "+R";
	inline static const string TOKIN_SYMBOL = "+P";
	
	vector<Piece> black_pieces, white_pieces;
};


#endif //ASCII_CHESS_CPP_SHOGI_H
