#include "chess.h"

#include <utility>

Chess::Chess() {
	// Initial conditions
	this->setRound(1);
	this->setHalfmove(1);
	this->setTurn(1);
	this->setEnd(false);
	
	// Define player colours
	this->setPlayerOneColour("White");
	this->setPlayerTwoColour("Black");
	
	// Define the board
	this->setBoard(8, 8);
	
	// Promotion rows
	this->setWhitePromotionRows({0});
	this->setBlackPromotionRows({board.getRows() - 1});
	
	// Advance rows
	this->setWhiteAdvanceRows({board.getRows() - 2});
	this->setBlackAdvanceRows({1});
	
	// Reset
	this->resetRounds();
	this->resetCaptures();
	
	// Define piece movement
	int max_range = max(board.getCols(), board.getRows()) - 1;
	vector<Piece::Move> king_moves = {{1, {{1, 0}, {0, 1}, {-1, 0}, {0, -1}, {1, 1}, {-1, 1}, {1, -1}, {-1, -1}}}};
	vector<Piece::Move> queen_moves = {
			{max_range, {{1, 0}, {0, 1}, {-1, 0}, {0, -1}, {1, 1}, {-1, 1}, {1, -1}, {-1, -1}}}};
	vector<Piece::Move> bishop_moves = {{max_range, {{1, 1}, {-1, 1}, {1, -1}, {-1, -1}}}};
	vector<Piece::Move> knight_moves = {{1, {{1, 2}, {2, 1}, {-1, 2}, {2, -1}, {1, -2}, {-2, 1}, {-1, -2}, {-2, -1}}}};
	vector<Piece::Move> rook_moves = {{max_range, {{1, 0}, {0, 1}, {-1, 0}, {0, -1}}}};
	vector<Piece::Move> pawn_moves = {{1, {{1, 0}}}};
	vector<Piece::Move> pawn_captures = {{1, {{1, 1}, {1, -1}}}};
	
	// Define neutral pieces
	Piece king = Piece::neutralPiece(KING_SYMBOL, king_moves, true);
	Piece queen = Piece::neutralPiece(QUEEN_SYMBOL, queen_moves);
	Piece bishop = Piece::neutralPiece(BISHOP_SYMBOL, bishop_moves);
	Piece knight = Piece::neutralPiece(KNIGHT_SYMBOL, knight_moves);
	Piece rook = Piece::neutralPiece(ROOK_SYMBOL, rook_moves);
	Piece pawn = Piece::neutralPiece(PAWN_SYMBOL, pawn_moves, false, true,
	                                 {queen, bishop, knight, rook}, pawn_captures, true);
	
	// Define white pieces
	Piece white_king = Piece::colouredPiece(king, 1, " K", "White King");
	Piece white_queen = Piece::colouredPiece(queen, 1, " Q", "White Queen");
	Piece white_bishop = Piece::colouredPiece(bishop, 1, " B", "White Bishop");
	Piece white_knight = Piece::colouredPiece(knight, 1, " N", "White Knight");
	Piece white_rook = Piece::colouredPiece(rook, 1, " R", "White Rook");
	Piece white_pawn = Piece::colouredPiece(pawn, 1, " P", "White Pawn", false,
	                                        {white_queen, white_bishop, white_knight, white_rook});
	this->setWhitePieces({white_king, white_queen, white_bishop, white_knight, white_rook, white_pawn});
	
	// Define black pieces
	Piece black_king = Piece::colouredPiece(king, 2, " k", "Black King", true);
	Piece black_queen = Piece::colouredPiece(queen, 2, " q", "Black Queen", true);
	Piece black_bishop = Piece::colouredPiece(bishop, 2, " b", "Black Bishop", true);
	Piece black_knight = Piece::colouredPiece(knight, 2, " n", "Black Knight", true);
	Piece black_rook = Piece::colouredPiece(rook, 2, " r", "Black Rook", true);
	Piece black_pawn = Piece::colouredPiece(pawn, 2, " p", "Black Pawn", true,
	                                        {black_queen, black_bishop, black_knight, black_rook});
	this->setBlackPieces({black_king, black_queen, black_bishop, black_knight, black_rook, black_pawn});
	
	// Fill in black pieces
	board.setPieceAtPosition(0, 0, black_rook);   // a8
	board.setPieceAtPosition(0, 1, black_knight); // b8
	board.setPieceAtPosition(0, 2, black_bishop); // c8
	board.setPieceAtPosition(0, 3, black_queen);  // d8
	board.setPieceAtPosition(0, 4, black_king);   // e8
	board.setPieceAtPosition(0, 5, black_bishop); // f8
	board.setPieceAtPosition(0, 6, black_knight); // g8
	board.setPieceAtPosition(0, 7, black_rook);   // h8
	
	// Fill in white pieces
	board.setPieceAtPosition(7, 0, white_rook);   // a1
	board.setPieceAtPosition(7, 1, white_knight); // b1
	board.setPieceAtPosition(7, 2, white_bishop); // c1
	board.setPieceAtPosition(7, 3, white_queen);  // d1
	board.setPieceAtPosition(7, 4, white_king);   // e1
	board.setPieceAtPosition(7, 5, white_bishop); // f1
	board.setPieceAtPosition(7, 6, white_knight); // g1
	board.setPieceAtPosition(7, 7, white_rook);   // h1
	
	// Fill in pawns
	for (int i = 0; i < board.getCols(); i++) {
		board.setPieceAtPosition(1, i, black_pawn); // a7 - h7
		board.setPieceAtPosition(board.getRows() - 2, i, white_pawn); // a2 - h2
	}
	
	// Fill in empty squares
	for (int i = 2; i < board.getRows() - 2; i++) {
		for (int j = 0; j < board.getCols(); j++) {
			board.setPieceAtPosition(i, j, Piece::EMPTY); // other squares
		}
	}
	
	this->setWhiteKingsideCastle(true);
	this->setWhiteQueensideCastle(true);
	this->setBlackKingsideCastle(true);
	this->setBlackQueensideCastle(true);
	this->setEnPassant(-1);
	
	this->resetFEN();
	
	// Piece placement
	string fen;
	int counter;
	char symbol;
	int colour;
	for (int i = 0; i < board.getRows(); i++) {
		counter = 0;
		for (int j = 0; j < board.getCols(); j++) {
			if (i > 0 && j == 0) fen.push_back('/');
			
			Piece piece = board.getPieceAtPosition(i, j);
			symbol = piece.getSymbol()[0];
			colour = piece.getColour();
			
			if (colour == 0) {
				counter++;
				if (j == board.getCols() - 1) fen += to_string(counter);
			} else if (colour > 0) {
				if (counter > 0) fen += to_string(counter);
				fen.push_back(symbol);
				counter = 0;
			}
		}
	}
	
	// First move is white
	fen += " w ";
	
	if (this->getWhiteKingsideCastle()) fen.push_back(toupper(KING_SYMBOL));
	if (this->getWhiteQueensideCastle()) fen.push_back(toupper(QUEEN_SYMBOL));
	if (this->getBlackKingsideCastle()) fen.push_back(tolower(KING_SYMBOL));
	if (this->getBlackQueensideCastle()) fen.push_back(tolower(QUEEN_SYMBOL));
	
	// No en passant, pawn moves and first round
	fen += " - 0 1";
	
	// Append FEN to list
	this->addFEN(fen);
	
	this->startGame();
}

Chess::~Chess() = default;

void Chess::setBoard(int rows, int cols) {
	board = Board(rows, cols);
}

void Chess::startGame() {
	string player, move, other, valid;
	this->refreshBoard();
	
	do {
		player = this->getTurn() == 1 ? this->getPlayerOneColour() : this->getPlayerTwoColour();
		cout << "Enter move for " << player << ": ";
		cin >> move;
		other = to_upper(move);
		
		if (other == "EXIT" || other == "QUIT") this->setEnd(true);
		else if (other == "RESIGN") {
			player = this->getTurn() == 1 ? this->getPlayerTwoColour() : this->getPlayerOneColour();
			this->endGame(player + " wins!", (this->getTurn() % 2) + 1);
		} else if (other == "CAPTURES") this->printCaptures();
		else if (other == "PGN") this->printPGN();
		else if (other == "FEN") this->printFEN(this->getHalfmove() - 1);
		else if (other == "DRAW") this->endGame("Draw!", 0);
		else {
			valid = this->isValid(move);
			// check if valid move
			if (to_upper(valid) != "VALID") {
				// Invalid move, ask user to input again
				cout << valid << "\n";
			} else {
				this->changeTurn();
				this->incrementHalfmove();
				if (this->getTurn() == 1) this->incrementRound();
				this->refreshBoard();
			}
		}
	} while (!this->getEnd());
	clearScreen();
}

void Chess::endGame(const string &message, int winner) {
	cout << message << "\n";
	this->printCaptures();
	this->printPGN(winner);
	this->printFEN(this->getHalfmove() - 1);
	system("pause");
	
	this->setEnd(true);
	clearScreen();
}

void Chess::recordFEN(bool capture, bool pawn) {
	int enemy_colour = (this->getTurn() % 2) + 1;
	string fen;
	
	// Piece placement
	int counter;
	char symbol;
	int colour;
	for (int i = 0; i < board.getRows(); i++) {
		counter = 0;
		for (int j = 0; j < board.getCols(); j++) {
			if (i > 0 && j == 0) fen.push_back('/');
			
			Piece piece = board.getPieceAtPosition(i, j);
			symbol = piece.getSymbol()[0];
			colour = piece.getColour();
			
			if (colour == 0) {
				counter++;
				if (j == board.getCols() - 1) fen += to_string(counter);
			} else if (colour > 0) {
				if (counter > 0) fen += to_string(counter);
				fen.push_back(symbol);
				counter = 0;
			}
		}
	}
	
	// Active colour
	fen += enemy_colour == 1 ? " w " : " b ";
	
	// Castling availability
	if (white_kingside_castle) fen.push_back(toupper(KING_SYMBOL));
	if (white_queenside_castle) fen.push_back(toupper(QUEEN_SYMBOL));
	if (black_kingside_castle) fen.push_back(tolower(KING_SYMBOL));
	if (black_queenside_castle) fen.push_back(tolower(QUEEN_SYMBOL));
	
	// En passant target square
	fen.push_back(' ');
	if (en_passant != -1) {
		fen.push_back(Board::toCol(en_passant));
		fen += to_string(enemy_colour == 1 ? board.getRows() - 2 : 3);
	} else fen.push_back('-');
	fen.push_back(' ');
	
	// Halfmove clock
	if (capture || pawn) fen += "0 ";
	else if (this->getTurn() == 1 && this->getRound() == 1) fen += "1 ";
	else {
		string previous_fen = this->getFEN(this->getHalfmove() - 1);
		string pawn_moves;
		pawn = false;
		
		for (int i = previous_fen.length() - 1; i >= 0; i--) {
			if (pawn && previous_fen[i] != ' ') {
				pawn_moves.push_back(previous_fen[i]);
			} else if (previous_fen[i] == ' ') {
				if (!pawn) pawn = true;
				else break;
			}
		}
		fen += to_string(stoi(pawn_moves) + 1);
		fen.push_back(' ');
	}
	
	// Fullmove number
	fen += to_string(enemy_colour == 1 ? this->getRound() + 1 : this->getRound());
	
	// Append to list
	this->addFEN(fen);
}

void Chess::recordMove(string move, bool pawn, bool capture, char promote) {
	int enemy_colour = (this->getTurn() % 2) + 1;
	bool check = this->kingInCheck(enemy_colour);
	bool checkmate = false;
	bool stalemate = false;
	
	if (move != "O-O" || move != "O-O-O") {
		int len = move.length();
		if (len > 2) {
			char row = move[len - 1];
			char col = tolower(move[len - 2]);
			char piece;
			string substring;
			
			// Pawn move
			if (pawn) {
				substring = move.substr(0, 1);
			}
				// Piece move
			else {
				piece = move[0];
				if (move[len - 3] == 'x') {
					substring = move.substr(1, len - 4);
				} else {
					substring = move.substr(1, len - 3);
				}
				substring.insert(0, 1, piece);
			}
			
			move = capture ? substring + "x" : substring;
			
			move.push_back(col);
			move.push_back(row);
		}
		
		if (promote != Piece::NONE_SQUARE) {
			move += &"="[promote];
		}
	}
	
	// Check for checkmate or stalemate
	check ? checkmate = this->kingInCheckmate(enemy_colour) : stalemate = this->kingInStalemate(enemy_colour);
	
	if (checkmate) {
		move = move + "#";
	} else if (check) {
		move = move + "+";
	}
	
	this->getTurn() == 1 ? this->addWhiteMove(move) : this->addBlackMove(move);
	
	this->recordFEN(capture, pawn);
	
	// Notify game conditions
	if (checkmate) {
		cout << "Checkmate!\n";
		this->endGame(this->getTurn() == 1 ? "White wins!" : "Black wins!", this->getTurn());
	} else if (stalemate) {
		this->endGame("Stalemate!", 0);
	} else if (check) {
		cout << "Check!\n";
	} else if (this->isDraw()) {
		this->endGame("Draw!", 0);
	}
}

void Chess::printWhiteCaptures() {
	vector<string> captures = this->getWhiteCaptures();
	for (auto &capture: captures) {
		cout << capture << " ";
	}
	cout << "\n";
}

void Chess::printBlackCaptures() {
	vector<string> captures = this->getBlackCaptures();
	for (auto &capture: captures) {
		cout << capture << " ";
	}
	cout << "\n";
}

void Chess::printCaptures() {
	cout << "White captured: ";
	this->printWhiteCaptures();
	
	cout << "Black captured: ";
	this->printBlackCaptures();
}

void Chess::printPGN(int winner) {
	for (const Round &r: this->getRounds()) {
		cout << r.round << ". " + r.white_move + " " + r.black_move + " ";
	}
	if (winner == 0) cout << "1/2-1/2";
	else if (winner == 1) cout << "1-0";
	else if (winner == 2) cout << "0-1";
	cout << "\n";
}

char Chess::canPromote(Piece piece, int row, int col) {
	vector<int> prs;
	char prom;
	prs = this->getTurn() == 1 ? this->getWhitePromotionRows() : this->getBlackPromotionRows();
	if (!piece.getPromoteSet().empty() &&
	    find(prs.begin(), prs.end(), row) != prs.end()) {
		piece = piece.promotePiece();
		board.setPieceAtPosition(row, col, piece);
		prom = piece.getSymbol()[0];
	}
	prom = Piece::NONE_SQUARE;
	return prom;
}

string Chess::isValid(string move) {
	int len = move.length();
	
	// General initial condition checks
	for (int i = 0; i < len; i++) {
		if (!(isalnum(move[i]) || move[i] == '-')) return "Move contains non-alphanumeric characters";
	}
	if ((islower(move[0]) && !(len == 2 || (len == 4 && move[1] == 'x'))) || len > 6 ||
	    (isupper(move[0]) && (len < 3 || (move[1] == 'x' && len < 4))) ||
	    !isalpha(move[0])) {
		return "Entered invalid move";
	}
	// Check for castling
	if (move[0] == CASTLE_SYMBOL) {
		if (move == "O-O" || move == "O-O-O") {
			if (this->kingInCheck(this->getTurn())) return "Cannot castle, king is in check";
			
			int row, col;
			for (int i = 0; i < board.getRows(); i++) {
				for (int j = 0; j < board.getCols(); j++) {
					Piece piece = board.getPieceAtPosition(i, j);
					if (piece.getKing() && this->getTurn() == piece.getColour()) {
						row = i;
						col = j;
						goto king_found;
					}
				}
			}
			king_found:
			
			char symbol;
			// Kingside
			if (move == "O-O" &&
			    ((this->getTurn() == 1 && this->getWhiteKingsideCastle()) ||
			     (this->getTurn() == 2 && this->getBlackKingsideCastle())) &&
			    !this->positionInCheck(this->getTurn(), row, col + 1) &&
			    !this->positionInCheck(this->getTurn(), row, col + 2)) {
				for (int i = 1; i < board.getCols() - col; i++) {
					Piece piece = board.getPieceAtPosition(row, col + i);
					symbol = piece.getSymbol()[0];
					if (symbol == ROOK_SYMBOL) {
						this->castle(move, row, col, col + i, true);
						return "VALID";
					} else if (symbol != Piece::EMPTY_SQUARE) {
						return "Cannot castle, there is a piece in the way";
					}
				}
			}
				// Queenside
			else if (move == "O-O-O" &&
			         ((this->getTurn() == 1 && this->getWhiteQueensideCastle()) ||
			          (this->getTurn() == 2 && this->getBlackQueensideCastle())) &&
			         !this->positionInCheck(this->getTurn(), row, col - 1) &&
			         !this->positionInCheck(this->getTurn(), row, col - 2)) {
				for (int i = 1; i <= col; i++) {
					Piece piece = board.getPieceAtPosition(row, col - i);
					symbol = piece.getSymbol()[0];
					if (symbol == ROOK_SYMBOL) {
						this->castle(move, row, col, col - i, false);
						return "VALID";
					} else if (symbol != Piece::EMPTY_SQUARE) {
						return "Cannot castle: there is a friendly piece in the way";
					}
				}
			}
		}
		return "Entered invalid castling move\nEnter O-O for kingside, O-O-O for queenside";
	}
	
	int new_row = (unsigned char) board.toX(move[len - 1]);
	int new_col = (unsigned char) Board::toY(move[len - 2]);
	int new_colour = board.getPieceAtPosition(new_row, new_col).getColour();
	
	// Cannot move onto a friendly piece
	if (new_colour == this->getTurn()) return "Cannot move onto a friendly piece";
		// Destination is either empty or has an enemy piece
	else {
		int enemy_colour = (this->getTurn() % 2) + 1;
		bool upper = isupper(move[0]);
		bool capture;
		vector<Piece> pieces = this->getTurn() == 1 ? this->getWhitePieces() : this->getBlackPieces();
		for (Piece p: pieces) {
			if ((upper && move[0] == p.getSymbol()[0]) || (!upper && p.getPawn())) {
				if (new_colour == enemy_colour) capture = true;
				else capture = this->isEnPassant(new_row, new_col, enemy_colour);
				return this->findPiece(move, new_row, new_col, p, this->getTurn(), capture);
			}
		}
	}
	return "Entered invalid move";
}

string Chess::findPiece(string move, int new_row, int new_col, Piece piece, int friendly_colour, bool capture) {
	char symbol = piece.getSymbol()[0];
	vector<Piece::Move> Moves;
	int range;
	vector<int> moves;
	int colour;
	int enemy_colour = (friendly_colour % 2) + 1;
	int counter = 0;
	int row, col, old_row, old_col, index, x, b, positions[2][2];
	
	Moves = capture ? piece.getCaptures() : piece.getMoves();
	
	// Search for relevant piece
	for (const Piece::Move &M: Moves) {
		range = M.range;
		for (vector<int> m: M.moves) {
			for (int r = 1; r <= range; r++) {
				row = new_row + m[0] * r;
				col = new_col + m[1] * r;
				
				Piece p = board.getPieceAtPosition(row, col);
				colour = p.getColour();
				
				// Non-eligible piece
				if (colour == -1 || colour == enemy_colour ||
				    (colour == friendly_colour && symbol != p.getSymbol()[0]))
					break;
				
				// Check for advance move
				if (piece.getAdvance() && !capture) {
					vector<int> advance_rows;
					int i;
					if (this->getTurn() == 1) {
						advance_rows = this->getWhiteAdvanceRows();
						i = 1;
					} else {
						advance_rows = this->getBlackAdvanceRows();
						i = -1;
					}
					for (int a_row: advance_rows) {
						if (row + i == a_row) {
							p = board.getPieceAtPosition(a_row, col);
							
							if (p.getColour() == -1 || board.getPieceAtPosition(row, col).getColour() != 0) break;
							else if (p.getAdvance() && p.getColour() == friendly_colour) {
								return this->advance(move, a_row, col, new_row, p);
							}
						}
					}
				}
				
				// Check if en passant
				if (en_passant == new_col && piece.getPawn() && p.getPawn() &&
				    colour == friendly_colour)
					return this->enPassant(move, row, col, new_row, new_col, p);
				
				// Found a relevant piece
				if (symbol == p.getSymbol()[0] && colour == friendly_colour) {
					counter++;
					if (counter == 3) { // more than two pieces are eligible
						old_row = (unsigned char) board.toX(move[2]);
						old_col = (unsigned char) Board::toY(move[1]);
						piece = board.getPieceAtPosition(old_row, old_col);
						return this->makeMove(move, old_row, old_col, new_row, new_col, p, capture);
					}
					positions[counter - 1][0] = row;
					positions[counter - 1][1] = col;
				}
			}
		}
	}
	
	// no pieces are eligible
	if (counter == 0) return "Cannot find an eligible piece to move";
		// one piece is eligible
	else if (counter == 1) {
		old_row = positions[0][0];
		old_col = positions[0][1];
		piece = board.getPieceAtPosition(old_row, old_col);
		return this->makeMove(move, old_row, old_col, new_row, new_col, piece, capture);
	}
		// Two pieces are eligible
	else {
		// Check what type of discriminant it is
		if (piece.getPawn()) {
			x = (unsigned char) Board::toY(move[0]);
			b = 1;
		} else {
			if (isdigit(move[1])) {
				x = (unsigned char) board.toX(move[1]);
				b = 0;
			} else {
				x = (unsigned char) Board::toY(move[1]);
				b = 1;
			}
		}
		
		// Determine exactly which piece
		if (positions[0][b] == x && positions[1][b] == x) {
			return "Need to discriminate which piece to move";
		} else if (positions[0][b] == x) {
			index = 0;
		} else if (positions[1][b] == x) {
			index = 1;
		} else {
			return "Need to discriminate which piece to move";
		}
		
		// Discriminant has col preference (used for PGN)
		if (positions[0][1] != positions[1][1]) {
			move[1] = Board::toCol(positions[index][1]);
		}
		
		old_row = positions[index][0];
		old_col = positions[index][1];
		piece = board.getPieceAtPosition(old_row, old_col);
		return this->makeMove(move, old_row, old_col, new_row, new_col, piece, capture);
	}
}

string Chess::makeMove(string move, int old_row, int old_col, int new_row, int new_col, const Piece &piece,
                       bool capture) {
	vector<vector<Piece>> piece_positions = board.getPiecePositions();
	string captured_piece_label = board.getPieceAtPosition(new_row, new_col).getLabel();
	
	// Update board
	board.setPieceAtPosition(old_row, old_col, Piece::EMPTY);
	board.setPieceAtPosition(new_row, new_col, piece);
	
	// Cannot put the king in check
	if (this->kingInCheck(this->getTurn())) {
		board.setPiecePositions(piece_positions);
		return "Illegal move: king would be in check";
	}
	
	// Check for promotion
	char prom = this->canPromote(piece, new_row, new_col);
	
	// Reset en passant
	en_passant = -1;
	
	// Record captured piece
	if (capture)
		this->getTurn() == 1 ? this->pushWhiteCaptures(captured_piece_label) : this->pushBlackCaptures(
				captured_piece_label);
	
	// King or rook move
	this->kingMove(piece);
	this->rookMove(piece, old_col);
	
	this->recordMove(std::move(move), piece.getPawn(), capture, prom);
	
	return "VALID";
}

string Chess::advance(string move, int old_row, int col, int new_row, const Piece &piece) {
	vector<vector<Piece>> piece_positions = board.getPiecePositions();
	
	// Update board
	board.setPieceAtPosition(old_row, col, Piece::EMPTY);
	board.setPieceAtPosition(new_row, col, piece);
	
	// Cannot put the king in check
	if (this->kingInCheck(this->getTurn())) {
		board.setPiecePositions(piece_positions);
		return "Illegal move: king would be in check";
	}
	
	// Check for promotion
	char prom = this->canPromote(piece, new_row, col);
	
	// declare en passant possible
	this->setEnPassant(Board::toY(move[0]));
	
	this->recordMove(move, piece.getPawn(), false, prom);
	
	return "VALID";
}

void Chess::castle(string move, int row, int king_col, int rook_col, bool kingside) {
	Piece king = board.getPieceAtPosition(row, king_col);
	Piece rook = board.getPieceAtPosition(row, rook_col);
	en_passant = -1;
	
	// Castle kingside
	if (kingside) {
		board.setPieceAtPosition(row, king_col, Piece::EMPTY);
		board.setPieceAtPosition(row, rook_col, Piece::EMPTY);
		board.setPieceAtPosition(row, king_col + 2, king);
		board.setPieceAtPosition(row, king_col + 1, rook);
	}
		// Castle Queenside
	else {
		board.setPieceAtPosition(row, king_col, Piece::EMPTY);
		board.setPieceAtPosition(row, rook_col, Piece::EMPTY);
		board.setPieceAtPosition(row, king_col - 2, king);
		board.setPieceAtPosition(row, king_col - 1, rook);
	}
	
	if (this->getTurn() == 1) {
		this->setWhiteKingsideCastle(false);
		this->setWhiteQueensideCastle(false);
	} else {
		this->setBlackKingsideCastle(false);
		this->setBlackQueensideCastle(false);
	}
	
	this->recordMove(std::move(move), false, false, Piece::NONE_SQUARE);
}

string Chess::enPassant(string move, int old_row, int old_col, int new_row, int new_col, const Piece &piece) {
	vector<vector<Piece>> piece_positions = board.getPiecePositions();
	string captured_piece_label = board.getPieceAtPosition(new_row, new_col).getLabel();
	
	// Update board
	board.setPieceAtPosition(old_row, old_col, Piece::EMPTY);
	board.setPieceAtPosition(new_row, new_col, piece);
	board.setPieceAtPosition(old_row, new_col, Piece::EMPTY);
	
	// Cannot put the king in check
	if (this->kingInCheck(this->getTurn())) {
		board.setPiecePositions(piece_positions);
		return "Illegal move: king would be in check";
	}
	
	en_passant = -1;
	
	// Record captured piece
	this->getTurn() == 1 ? this->pushWhiteCaptures(captured_piece_label) : this->pushBlackCaptures(
			captured_piece_label);
	
	this->recordMove(std::move(move), piece.getPawn(), true, Piece::NONE_SQUARE);
	
	return "VALID";
}

bool Chess::positionInCheck(int pos_colour, int pos_row, int pos_col) {
	int row, col, range, colour;
	int enemy_colour = (pos_colour % 2) + 1;
	vector<Piece> pieces = enemy_colour == 1 ? this->getWhitePieces() : this->getBlackPieces();
	vector<Piece::Move> Moves;
	
	for (Piece p: pieces) {
		Moves = p.getCaptures();
		for (const Piece::Move &M: Moves) {
			range = M.range;
			for (vector<int> c: M.moves) {
				for (int r = 1; r <= range; r++) {
					row = pos_row + c[0] * r;
					col = pos_col + c[1] * r;
					
					Piece piece = board.getPieceAtPosition(row, col);
					colour = piece.getColour();
					
					// piece is friendly
					if (colour == pos_colour || colour == -1) break;
					// found enemy piece
					if (colour == enemy_colour && piece.getSymbol()[0] == p.getSymbol()[0]) return true;
				}
			}
		}
	}
	return false;
}

bool Chess::kingInCheck(int king_colour) {
	int king_row, king_col;
	
	// Find king
	for (int i = 0; i < board.getRows(); i++) {
		for (int j = 0; j < board.getCols(); j++) {
			Piece piece = board.getPieceAtPosition(i, j);
			if (piece.getKing() && king_colour == piece.getColour()) {
				king_row = i;
				king_col = j;
				goto king_found;
			}
		}
	}
	// See if it is under check
	king_found:
	return positionInCheck(king_colour, king_row, king_col);
}

bool Chess::kingInCheckmate(int king_colour) {
	int enemy_colour = (king_colour % 2) + 1;
	int king_row, king_col, row, col, range, colour;
	vector<Piece::Move> Moves, Captures;
	vector<vector<Piece>> piece_positions = board.getPiecePositions();
	
	// Find king
	for (int i = 0; i < board.getRows(); i++) {
		for (int j = 0; j < board.getCols(); j++) {
			Piece piece = board.getPieceAtPosition(i, j);
			if (piece.getKing() && king_colour == piece.getColour()) {
				king_row = i;
				king_col = j;
				goto king_found;
			}
		}
	}
	
	king_found:
	Piece king = board.getPieceAtPosition(king_row, king_col);
	Moves = king.getMoves();
	Captures = king.getCaptures();
	
	// Check if the king has a free square to move
	for (const Piece::Move &M: Moves) {
		range = M.range;
		for (vector<int> m: M.moves) {
			for (int r = 1; r <= range; r++) {
				row = king_row + m[0] * r;
				col = king_col + m[1] * r;
				
				Piece piece = board.getPieceAtPosition(row, col);
				colour = piece.getColour();
				
				// there is a friendly piece in the way
				if (colour == king_colour || colour == -1) break;
				
				// Destination is empty or piece can be captured
				if (piece.getSymbol()[0] == Piece::EMPTY_SQUARE ||
				    (Piece::CompareMoves(Moves, Captures) &&
				     piece.getColour() == enemy_colour)) {
					// Destination also in check?
					board.setPieceAtPosition(king_row, king_col, Piece::EMPTY);
					board.setPieceAtPosition(row, col, king);
					
					// King would be in check after move
					if (this->kingInCheck(king_colour)) board.setPiecePositions(piece_positions);
						// King can be moved
					else {
						board.setPiecePositions(piece_positions);
						return false;
					}
				}
			}
		}
	}
	// Check if the king has a free square to capture if moves != captures
	if (!Piece::CompareMoves(Moves, Captures)) {
		for (const Piece::Move &C: Captures) {
			range = C.range;
			for (vector<int> c: C.moves) {
				for (int r = 1; r <= range; r++) {
					row = king_row + c[0] * r;
					col = king_col + c[1] * r;
					
					Piece piece = board.getPieceAtPosition(row, col);
					colour = piece.getColour();
					
					// there is a friendly piece in the way
					if (colour == king_colour || colour == -1) break;
					
					// An enemy piece can be captured
					if (colour == enemy_colour) {
						// Destination also in check?
						board.setPieceAtPosition(king_row, king_col, Piece::EMPTY);
						board.setPieceAtPosition(row, col, king);
						
						// Defending piece is pinned
						if (this->kingInCheck(king_colour)) board.setPiecePositions(piece_positions);
							// Attacking piece can be taken
						else {
							board.setPiecePositions(piece_positions);
							return false;
						}
					}
				}
			}
		}
	}
	// Check if there are two or more attacking pieces
	int counter = 0;
	int attacking_row, attacking_col;
	vector<Piece> pieces = enemy_colour == 1 ? this->getWhitePieces() : this->getBlackPieces();
	for (Piece p: pieces) {
		// Opponent's king cannot be an attacker
		if (p.getKing()) continue;
		
		for (const Piece::Move &C: p.getCaptures()) {
			range = C.range;
			for (vector<int> c: C.moves) {
				for (int r = 1; r <= range; r++) {
					row = king_row + c[0] * r;
					col = king_col + c[1] * r;
					
					Piece piece = board.getPieceAtPosition(row, col);
					colour = piece.getColour();
					
					if (colour == -1 || colour == king_colour) break;
					
					if (piece.getSymbol()[0] == p.getSymbol()[0] && colour == enemy_colour) {
						counter++;
						// Checkmate since two or more pieces cannot be stopped at the same time
						if (counter == 2) return true;
						// save attacker's position in case the piece is the sole attacker
						attacking_row = row;
						attacking_col = col;
						// stop searching along this direction
						break;
					}
				}
			}
		}
	}
	// Check if the attacking piece can be taken by a defending piece
	pieces = king_colour == 1 ? this->getWhitePieces() : this->getBlackPieces();
	for (Piece p: pieces) {
		for (const Piece::Move &C: p.getCaptures()) {
			range = C.range;
			for (vector<int> c: C.moves) {
				for (int r = 1; r <= range; r++) {
					row = attacking_row + c[0] * r;
					col = attacking_col + c[1] * r;
					
					Piece piece = board.getPieceAtPosition(row, col);
					colour = piece.getColour();
					
					// There is another piece in the way
					if (colour == enemy_colour || colour == -1) break;
					
					// attacker is attacked by defending piece
					// Check if the defending piece is pinned
					if (colour == king_colour && piece.getSymbol()[0] == p.getSymbol()[0]) {
						board.setPieceAtPosition(row, col, Piece::EMPTY);
						board.setPieceAtPosition(attacking_row, attacking_col, piece);
						
						// Defending piece is pinned
						if (this->kingInCheck(king_colour)) board.setPiecePositions(piece_positions);
							// Attacking piece can be taken
						else {
							board.setPiecePositions(piece_positions);
							return false;
						}
					}
				}
			}
		}
	}
	// If check is given by pawn advance and can be taken by en passant
	if (en_passant == attacking_col) {
		int pawn_col;
		for (int i = -1; i <= 1; i += 2) {
			Piece piece = board.getPieceAtPosition(attacking_row, attacking_col + i);
			colour = piece.getColour();
			
			if (colour == -1 || colour == enemy_colour) break;
			
			if (piece.getPawn() && piece.getColour() == king_colour) {
				int j;
				j = king_colour == 1 ? -1 : 1;
				board.setPieceAtPosition(attacking_row + j, attacking_col, piece);
				board.setPieceAtPosition(attacking_row, attacking_col + i, Piece::EMPTY);
				board.setPieceAtPosition(attacking_row, attacking_col, Piece::EMPTY);
				// Defending piece is pinned
				if (this->kingInCheck(king_colour)) board.setPiecePositions(piece_positions);
					// Attacking piece can be taken
				else {
					board.setPiecePositions(piece_positions);
					return false;
				}
			}
		}
	}
	// Attacking piece is not under attack
	// Check if the attack can be blocked
	int s;
	Piece attacking_piece = board.getPieceAtPosition(attacking_row, attacking_col);
	for (const Piece::Move &C: attacking_piece.getCaptures()) {
		range = C.range;
		for (vector<int> c: C.moves) {
			for (int r = 1; r <= range; r++) {
				row = attacking_row + c[0] * r;
				col = attacking_col + c[1] * r;
				// Found the direction of the attack
				if (row == king_row && col == king_col) {
					// Checkmate: if point blank the attack cannot be blocked
					if (r == 1) return true;
					// Trace back path to see if a friendly piece can block
					int defending_row, defending_col;
					for (int d = 1; d <= r; d++) {
						defending_row = king_row - c[0] * d;
						defending_col = king_col - c[1] * d;
						
						// Checkmate since no piece can block the attack
						if (defending_row == attacking_row && defending_col == attacking_col) return true;
						
						// Check if a defending piece can block
						pieces = king_colour == 1 ? this->getWhitePieces() : this->getBlackPieces();
						for (Piece p: pieces) {
							// King cannot block itself
							if (p.getKing()) continue;
							
							for (const Piece::Move &M: p.getMoves()) {
								s = M.range;
								for (vector<int> m: M.moves) {
									for (int i = 1; i <= s; i++) {
										row = defending_row + m[0] * i;
										col = defending_col + m[1] * i;
										
										Piece piece = board.getPieceAtPosition(row, col);
										colour = piece.getColour();
										
										// Piece is not friendly
										if (colour == enemy_colour || colour == -1) break;
										
										// Found possible defender
										if (colour == king_colour && piece.getSymbol()[0] == p.getSymbol()[0]) {
											board.setPieceAtPosition(row, col, Piece::EMPTY);
											board.setPieceAtPosition(defending_row, defending_col, piece);
											
											// Check if the defending piece is pinned
											if (this->kingInCheck(king_colour))
												board.setPiecePositions(piece_positions);
												// Attacking piece can be blocked
											else {
												board.setPiecePositions(piece_positions);
												return false;
											}
										}
										// Check if the attack can be blocked by an advance
										if (p.getAdvance()) {
											vector<int> advance_rows;
											int j;
											if (king_colour == 1) {
												advance_rows = this->getWhiteAdvanceRows();
												j = 2;
											} else {
												advance_rows = this->getBlackAdvanceRows();
												j = -2;
											}
											
											if (find(advance_rows.begin(), advance_rows.end(),
											         defending_row + m[0] * j) !=
											    advance_rows.end()) {
												piece = board.getPieceAtPosition(row, col);
												
												// Found a possible defender
												if (piece.getColour() == king_colour &&
												    piece.getSymbol()[0] == p.getSymbol()[0]) {
													board.setPieceAtPosition(defending_row + m[0] * j,
													                         defending_col + m[1] * j,
													                         Piece::EMPTY);
													board.setPieceAtPosition(defending_row, defending_col, piece);
													
													// Defending piece is pinned
													if (this->kingInCheck(king_colour))
														board.setPiecePositions(piece_positions);
														// Attacking piece can be blocked
													else {
														board.setPiecePositions(piece_positions);
														return false;
													}
												}
											}
										}
									}
								}
							}
						}
					}
				}
					// This is not the square you are looking for, keep searching
				else if (board.getPieceAtPosition(row, col).getColour() != 0) break;
			}
		}
	}
	// Checkmate since the attacking piece cannot be stopped
	return true;
}

bool Chess::kingInStalemate(int king_colour) {
	int enemy_colour = (king_colour % 2) + 1;
	int row, col, range, colour;
	vector<Piece::Move> Moves, Captures;
	vector<vector<int>> moves, captures;
	vector<vector<Piece>> piece_positions = board.getPiecePositions();
	
	// Find friendly piece
	for (int i = 0; i < board.getRows(); i++) {
		for (int j = 0; j < board.getCols(); j++) {
			Piece piece = board.getPieceAtPosition(i, j);
			if (piece.getColour() == king_colour) {
				Moves = piece.getMoves();
				Captures = piece.getCaptures();
				
				// Check if the friendly piece can move or capture
				for (const Piece::Move &M: Moves) {
					range = M.range;
					moves = M.moves;
					for (vector<int> m: moves) {
						for (int r = 1; r <= range; r++) {
							row = i + m[0] * r;
							col = j + m[1] * r;
							
							Piece p = board.getPieceAtPosition(row, col);
							
							// Destination is empty or piece can be captured
							if (p.getSymbol()[0] == Piece::EMPTY_SQUARE ||
							    (Piece::CompareMoves(Moves, Captures) &&
							     p.getColour() == enemy_colour)) {
								board.setPieceAtPosition(i, j, Piece::EMPTY);
								board.setPieceAtPosition(row, col, p);
								
								// Check if this move places the king in check
								if (this->kingInCheck(king_colour)) {
									board.setPiecePositions(piece_positions);
								}
									// Move is legal
								else {
									board.setPiecePositions(piece_positions);
									return false;
								}
							}
						}
					}
				}
				// Piece captures differently than when it moves
				if (!Piece::CompareMoves(Moves, Captures)) {
					// Check if the friendly piece can capture
					for (const Piece::Move &C: Captures) {
						range = C.range;
						captures = C.moves;
						for (vector<int> c: captures) {
							for (int r = 1; r <= range; r++) {
								row = i + c[0] * r;
								col = j + c[1] * r;
								
								Piece p = board.getPieceAtPosition(row, col);
								
								// Destination has enemy piece
								if (p.getColour() == enemy_colour) {
									board.setPieceAtPosition(i, j, Piece::EMPTY);
									board.setPieceAtPosition(row, col, p);
									
									// Check if this capture places the king in check
									if (this->kingInCheck(king_colour)) {
										board.setPiecePositions(piece_positions);
									}
										// Capture is legal
									else {
										board.setPiecePositions(piece_positions);
										return false;
									}
								}
							}
						}
					}
				}
			}
		}
	}
	// Stalemate since no legal move is found
	return true;
}

bool Chess::isDraw() {
	string fen = this->getFEN(this->getHalfmove() - 1);
	
	// Dead position
	char symbol;
	int colour;
	bool white_bishop, black_bishop, white_knight, black_knight;
	int white_bishop_row, white_bishop_col, black_bishop_row, black_bishop_col;
	int counter = 0;
	for (int i = 0; i < board.getRows(); i++) {
		for (int j = 0; i < board.getCols(); j++) {
			Piece piece = board.getPieceAtPosition(i, j);
			symbol = piece.getSymbol()[0];
			colour = piece.getColour();
			if (symbol == QUEEN_SYMBOL || symbol == ROOK_SYMBOL ||
			    symbol == PAWN_SYMBOL)
				goto no_dead_position;
			else if (symbol == KNIGHT_SYMBOL) {
				if (colour == 1) {
					if (white_knight) goto no_dead_position;
					else white_knight = true;
				} else {
					if (black_knight) goto no_dead_position;
					else black_knight = true;
				}
			} else if (symbol == BISHOP_SYMBOL) {
				if (colour == 1) {
					if (white_bishop) goto no_dead_position;
					else {
						white_bishop = true;
						white_bishop_row = i;
						white_bishop_col = j;
					}
				} else {
					if (black_bishop) goto no_dead_position;
					else {
						black_bishop = true;
						black_bishop_row = i;
						black_bishop_col = j;
					}
				}
			}
		}
	}
	
	if (white_knight) counter++;
	if (black_knight) counter++;
	if (white_bishop) counter++;
	if (black_bishop) counter++;
	
	// Insufficient material for checkmate
	if (counter == 0 || counter == 1) return true;
	if (counter == 2 && white_bishop && black_bishop) {
		// Check if bishops are of same colour
		if ((white_bishop_row + white_bishop_col) % 2 ==
		    (black_bishop_row + black_bishop_col) % 2)
			return true;
	}
	// No dead position
	no_dead_position:
	// Fifty-move rule
	bool pawn = false;
	int pawn_moves = 0;
	int exp = 0;
	for (int i = fen.length() - 1; i >= 0; i--) {
		if (pawn && fen[i] != ' ') {
			pawn_moves += fen[i] * 10 ^ exp;
			exp++;
		} else if (fen[i] == ' ') {
			if (!pawn) pawn = true;
			else break;
		}
	}
	// Reached 50 non-pawn non-capture moves: draw
	if (pawn_moves == 50) return true;
	else if (pawn_moves != 0 && this->getHalfmove() > 7) {
		// Threefold repetition
		string previous_fen;
		char ch;
		bool en_pas, castling;
		counter = 1;
		for (int i = this->getHalfmove() - 3; i >= 0; i--) {
			previous_fen = this->getFEN(i);
			pawn = false;
			en_pas = false;
			castling = false;
			pawn_moves = 0;
			exp = 0;
			for (int j = previous_fen.length() - 1; j >= 0; j--) {
				ch = previous_fen[j];
				// Check for pawn moves
				if (pawn && ch != ' ' && !en_pas) {
					pawn_moves += fen[i] * 10 ^ exp;
					exp++;
				}
					// Check for castling rights
				else if (castling && ch != ' ') {
					if (ch != fen[j]) goto no_repetition;
				} else if (ch == ' ') {
					if (!pawn) pawn = true;
						// Last move was a pawn move
					else if (pawn_moves == 0) goto no_repetition;
					else if (!en_passant) en_pas = true;
					else if (!castling) castling = true;
						// Check for repetition of position
					else {
						previous_fen = this->getFEN(i);
						for (int k = 0; k <= previous_fen.length(); k++) {
							if (previous_fen[k] == ' ') {
								counter++;
								// Threefold reptition has occurred
								if (counter == 3) return true;
								break;
							}
							// No repetition this turn
							if (fen[k] != previous_fen[k]) break;
						}
					}
				}
			}
		}
	}
	// No repetition has occurred
	no_repetition:
	return false;
}

bool Chess::isEnPassant(int row, int col, int enemy_colour) {
	if (this->getEnPassant() == col) {
		int i;
		i = this->getTurn() == 1 ? 1 : -1;
		Piece piece = board.getPieceAtPosition(row + i, col);
		if (piece.getAdvance() && piece.getColour() == enemy_colour) return true;
		else return false;
	}
	return false;
}

void Chess::kingMove(const Piece &piece) {
	if (piece.getKing()) {
		if (this->getTurn() == 1) {
			this->setWhiteKingsideCastle(false);
			this->setWhiteQueensideCastle(false);
		} else {
			this->setBlackKingsideCastle(false);
			this->setBlackQueensideCastle(false);
		}
	}
}

void Chess::rookMove(Piece piece, int col) {
	if (piece.getSymbol()[0] == ROOK_SYMBOL) {
		if (col == 0 && this->getTurn() == 1) this->setWhiteQueensideCastle(false);
		else if (col == 0 && this->getTurn() == 2) this->setBlackQueensideCastle(false);
		else if (col == board.getCols() - 1 && this->getTurn() == 1) this->setWhiteKingsideCastle(false);
		else if (col == board.getCols() - 1 && this->getTurn() == 2) this->setBlackKingsideCastle(false);
	}
}

void Chess::setWhiteKingsideCastle(bool b) {
	white_kingside_castle = b;
}

void Chess::setWhiteQueensideCastle(bool b) {
	white_queenside_castle = b;
}

void Chess::setBlackKingsideCastle(bool b) {
	black_kingside_castle = b;
}

void Chess::setBlackQueensideCastle(bool b) {
	black_queenside_castle = b;
}

bool Chess::getWhiteKingsideCastle() const {
	return white_kingside_castle;
}

bool Chess::getWhiteQueensideCastle() const {
	return white_queenside_castle;
}

bool Chess::getBlackKingsideCastle() const {
	return black_kingside_castle;
}

bool Chess::getBlackQueensideCastle() const {
	return black_queenside_castle;
}

void Chess::setEnPassant(int i) {
	en_passant = i;
}

int Chess::getEnPassant() const {
	return en_passant;
}

void Chess::setRound(int i) {
	round = i;
}

int Chess::getRound() const {
	return round;
}

void Chess::incrementRound() {
	round++;
}

void Chess::setTurn(int i) {
	turn = i;
}

int Chess::getTurn() const {
	return turn;
}

void Chess::changeTurn() {
	this->setTurn((this->getTurn() % 2) + 1);
}

void Chess::setEnd(bool b) {
	end = b;
}

bool Chess::getEnd() const {
	return end;
}

void Chess::resetRounds() {
	rounds = {};
}

vector<Chess::Round> Chess::getRounds() {
	return rounds;
}

void Chess::addWhiteMove(string move) {
	rounds.push_back({this->getRound(), std::move(move), ""});
}

void Chess::addBlackMove(string move) {
	rounds[this->getRound() - 1].black_move = std::move(move);
}

void Chess::resetFEN() {
	FEN = {};
}

string Chess::getFEN(int i) {
	return FEN[i];
}

void Chess::printFEN(int i) {
	cout << this->getFEN(i) << "\n";
}

void Chess::addFEN(const string &f) {
	FEN.push_back(f);
}

void Chess::setPlayerOneColour(string c) {
	player_one_colour = std::move(c);
}

void Chess::setPlayerTwoColour(string c) {
	player_two_colour = std::move(c);
}

string Chess::getPlayerOneColour() {
	return player_one_colour;
}

string Chess::getPlayerTwoColour() {
	return player_two_colour;
}

void Chess::setWhitePieces(vector<Piece> p) {
	white_pieces = std::move(p);
}

void Chess::setBlackPieces(vector<Piece> p) {
	black_pieces = std::move(p);
}

vector<Piece> Chess::getWhitePieces() {
	return white_pieces;
}

vector<Piece> Chess::getBlackPieces() {
	return black_pieces;
}

void Chess::setWhitePromotionRows(vector<int> r) {
	white_promotion_rows = std::move(r);
}

void Chess::setBlackPromotionRows(vector<int> r) {
	black_promotion_rows = std::move(r);
}

void Chess::setWhiteAdvanceRows(vector<int> r) {
	white_advance_rows = std::move(r);
}

void Chess::setBlackAdvanceRows(vector<int> r) {
	black_advance_rows = std::move(r);
}

vector<int> Chess::getWhitePromotionRows() {
	return white_promotion_rows;
}

vector<int> Chess::getBlackPromotionRows() {
	return black_promotion_rows;
}

vector<int> Chess::getWhiteAdvanceRows() {
	return white_advance_rows;
}

vector<int> Chess::getBlackAdvanceRows() {
	return black_advance_rows;
}

void Chess::resetCaptures() {
	white_captures = {};
	black_captures = {};
}

void Chess::pushWhiteCaptures(const string &s) {
	white_captures.push_back(s);
}

void Chess::pushBlackCaptures(const string &s) {
	black_captures.push_back(s);
}

vector<string> Chess::getWhiteCaptures() {
	return white_captures;
}

vector<string> Chess::getBlackCaptures() {
	return black_captures;
}

void Chess::setHalfmove(int i) {
	halfmove = i;
}

int Chess::getHalfmove() const {
	return halfmove;
}

void Chess::incrementHalfmove() {
	halfmove++;
}

void Chess::refreshBoard() {
	clearScreen();
	this->printBlackCaptures();
	board.refreshBoard();
	this->printWhiteCaptures();
}
