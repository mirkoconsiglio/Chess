#include "shogi.h"

Shogi::Shogi() {
	// Initial conditions
	this->setRound(1);
	this->setHalfmove(1);
	this->setTurn(1);
	this->setEnd(false);
	
	// Define player colours
	this->setPlayerOneColour("Black");
	this->setPlayerTwoColour("White");
	
	// Define the board
	this->setBoard(9, 9);
	
	// Promotion rows
	this->setBlackPromotionRows({0, 1, 2});
	this->setWhitePromotionRows({board.getRows() - 1, board.getRows() - 2, board.getRows() - 3});
	
	// Reset
	this->resetRounds();
	this->resetCaptures();
	
	// Define piece movement
	int max_range = max(board.getCols(), board.getRows()) - 1;
	vector<Piece::Move> king_moves = {{1, {{1, 0}, {0, 1}, {-1, 0}, {0, -1}, {1, 1}, {-1, 1}, {1, -1}, {-1, -1}}}};
	vector<Piece::Move> gold_general_moves = {{1, {{1, 0}, {1, 1}, {1, -1}, {0, 1}, {0, -1}, {-1, 0}}}};
	vector<Piece::Move> silver_general_moves = {{1, {{1, 0}, {1, 1}, {1, -1}, {-1, 1}, {-1, -1}}}};
	vector<Piece::Move> knight_moves = {{1, {{1, 2}, {2, 1}, {-1, 2}, {2, -1}, {1, -2}, {-2, 1}, {-1, -2}, {-2, -1}}}};
	vector<Piece::Move> lance_moves = {{max_range, {{1, 0}}}};
	vector<Piece::Move> bishop_moves = {{max_range, {{1, 1}, {-1, 1}, {1, -1}, {-1, -1}}}};
	vector<Piece::Move> rook_moves = {{max_range, {{1, 0}, {0, 1}, {-1, 0}, {0, -1}}}};
	vector<Piece::Move> pawn_moves = {{1, {{1, 0}}}};
	
	vector<Piece::Move> dragon_king_moves = {{max_range, {{1, 0}, {0, 1}, {-1, 0}, {0, -1}}}, {1, {{1, 1}, {1, -1}, {-1, 1}, {-1, -1}}}};
	vector<Piece::Move> dragon_horse_moves = {{max_range, {{1, 1}, {-1, 1}, {1, -1}, {-1, -1}}}, {1, {{1, 0}, {0, 1}, {-1, 0}, {0, -1}}}};
	
    // Define neutral pieces
    Piece promoted_silver_general = Piece::neutralPiece(PROMOTED_SILVER_GENERAL_SYMBOL, gold_general_moves);
    Piece promoted_knight = Piece::neutralPiece(PROMOTED_KNIGHT_SYMBOL, gold_general_moves);
    Piece promoted_lance = Piece::neutralPiece(PROMOTED_LANCE_SYMBOL, gold_general_moves);
    Piece dragon_horse = Piece::neutralPiece(DRAGON_HORSE_SYMBOL, dragon_horse_moves);
    Piece dragon_king = Piece::neutralPiece(DRAGON_KING_SYMBOL, dragon_king_moves);
    Piece tokin = Piece::neutralPiece(TOKIN_SYMBOL, gold_general_moves);
    
    Piece king = Piece::neutralPiece(KING_SYMBOL, king_moves, true);
    Piece gold_general = Piece::neutralPiece(GOLD_GENERAL_SYMBOL, gold_general_moves);
    Piece silver_general = Piece::neutralPiece(SILVER_GENERAL_SYMBOL, silver_general_moves, false, false);
    silver_general.setPromoteSet({silver_general, promoted_silver_general});
    Piece knight = Piece::neutralPiece(KNIGHT_SYMBOL, knight_moves, false, false);
    knight.setPromoteSet({knight, promoted_knight});
    Piece lance = Piece::neutralPiece(LANCE_SYMBOL, lance_moves, false, false);
    lance.setPromoteSet({lance, promoted_lance});
    Piece bishop = Piece::neutralPiece(BISHOP_SYMBOL, bishop_moves, false, false);
    bishop.setPromoteSet({bishop, dragon_horse});
    Piece rook = Piece::neutralPiece(ROOK_SYMBOL, rook_moves, false, false);
    rook.setPromoteSet({rook, dragon_king});
    Piece pawn = Piece::neutralPiece(PAWN_SYMBOL, pawn_moves, false, true);
    pawn.setPromoteSet({pawn, tokin});
    
    // Define black pieces
    Piece black_promoted_silver_general = Piece::colouredPiece(promoted_silver_general, 1, "+S", "Promoted Black Silver General", false);
    Piece black_promoted_knight = Piece::colouredPiece(promoted_knight, 1, "+N", "Promoted Black Knight", false);
    Piece black_promoted_lance = Piece::colouredPiece(promoted_lance, 1, "+L", "Promoted Black Lance", false);
    Piece black_dragon_horse = Piece::colouredPiece(dragon_horse, 1, "+B", "Black Dragon Horse", false);
    Piece black_dragon_king = Piece::colouredPiece(dragon_king, 1, "+R", "Black Dragon King", false);
    Piece black_tokin = Piece::colouredPiece(tokin, 1, "+P", "Black Tokin", false);
    
    Piece black_king = Piece::colouredPiece(king, 1, " K", "Black King", false);
	Piece black_gold_general = Piece::colouredPiece(gold_general, 1, " G", "Black Gold General", false);
	Piece black_silver_general = Piece::colouredPiece(silver_general, 1, " S", "Black Silver General", false);
	black_silver_general.setPromoteSet({black_silver_general, black_promoted_silver_general});
	Piece black_knight = Piece::colouredPiece(knight, 1, " N", "Black Knight", false);
	black_knight.setPromoteSet({black_knight, black_promoted_knight});
	Piece black_lance = Piece::colouredPiece(lance, 1, " L", "Black Lance", false);
	black_lance.setPromoteSet({black_lance, black_promoted_lance});
	Piece black_bishop = Piece::colouredPiece(bishop, 1, " B", "Black Bishop", false);
    black_bishop.setPromoteSet({black_bishop, black_dragon_horse});
	Piece black_rook = Piece::colouredPiece(rook, 1, " R", "Black Rook", false);
    black_rook.setPromoteSet({black_rook, black_dragon_king});
    Piece black_pawn = Piece::colouredPiece(pawn, 1, " P", "Black Pawn", false);
    black_pawn.setPromoteSet({black_pawn, black_tokin});
	this->setBlackPieces({black_promoted_silver_general, black_promoted_knight, black_promoted_lance, black_dragon_horse,
					   black_dragon_king, black_tokin, black_king, black_gold_general, black_silver_general, black_knight,
					   black_lance, black_bishop, black_rook, black_pawn});

    // Define white pieces
    Piece white_promoted_silver_general = Piece::colouredPiece(promoted_silver_general, 2, "+s", "Promoted White Silver General", true);
    Piece white_promoted_knight = Piece::colouredPiece(promoted_knight, 2, "+n", "Promoted White Knight", true);
    Piece white_promoted_lance = Piece::colouredPiece(promoted_lance, 2, "+l", "Promoted White Lance", true);
    Piece white_dragon_horse = Piece::colouredPiece(dragon_horse, 2, "+b", "White Dragon Horse", true);
    Piece white_dragon_king = Piece::colouredPiece(dragon_king, 2, "+r", "White Dragon King", true);
    Piece white_tokin = Piece::colouredPiece(tokin, 2, "+p", "White Tokin", true);
    
    Piece white_king = Piece::colouredPiece(king, 2, " k", "White King", true);
	Piece white_gold_general = Piece::colouredPiece(gold_general, 2, " g", "White Gold General", true);
	Piece white_silver_general = Piece::colouredPiece(silver_general, 2, " s", "White Silver General", true);
	white_silver_general.setPromoteSet({white_silver_general, white_promoted_silver_general});
	Piece white_knight = Piece::colouredPiece(knight, 2, " n", "White Knight", true);
	white_knight.setPromoteSet({white_knight, white_promoted_knight});
	Piece white_lance = Piece::colouredPiece(lance, 2, " l", "White Lance", true);
    white_lance.setPromoteSet({white_lance, white_promoted_lance});
    Piece white_bishop = Piece::colouredPiece(bishop, 2, " b", "White Bishop", true);
    white_bishop.setPromoteSet({white_bishop, white_dragon_horse});
    Piece white_rook = Piece::colouredPiece(rook, 2, " r", "White Rook", true);
    white_rook.setPromoteSet({white_rook, white_dragon_king});
    Piece white_pawn = Piece::colouredPiece(pawn, 2, " p", "White Pawn", true);
	white_pawn.setPromoteSet({white_pawn, white_tokin});
    this->setWhitePieces({white_promoted_silver_general, white_promoted_knight, white_promoted_lance, white_dragon_horse,
					   white_dragon_king, white_tokin, white_king, white_gold_general, white_silver_general, white_knight,
					   white_lance, white_bishop, white_rook, white_pawn});

	// Fill in empty squares
    for (int i = 0; i < board.getRows(); i++) {
        for (int j = 0; j < board.getCols(); j++) {
            board.setPieceAtPosition(i, j, Piece::EMPTY);
        }
    }
	
    // Fill in white pieces
    board.setPieceAtPosition(0, 0, white_lance);          // a9
    board.setPieceAtPosition(0, 1, white_knight);         // b9
    board.setPieceAtPosition(0, 2, white_silver_general); // c9
    board.setPieceAtPosition(0, 3, white_gold_general);   // d9
    board.setPieceAtPosition(0, 4, white_king);           // e9
    board.setPieceAtPosition(0, 5, white_gold_general);   // f9
    board.setPieceAtPosition(0, 6, white_silver_general); // g9
    board.setPieceAtPosition(0, 7, white_knight);         // h9
    board.setPieceAtPosition(0, 8, white_lance);          // i9
    board.setPieceAtPosition(1, 1, white_rook);           // b8
    board.setPieceAtPosition(1, 7, white_bishop);         // h8

    // Fill in black pieces
    board.setPieceAtPosition(8, 0, black_lance);          // a1
    board.setPieceAtPosition(8, 1, black_knight);         // b1
    board.setPieceAtPosition(8, 2, black_silver_general); // c1
    board.setPieceAtPosition(8, 3, black_gold_general);   // d1
    board.setPieceAtPosition(8, 4, black_king);           // e1
    board.setPieceAtPosition(8, 5, black_gold_general);   // f1
    board.setPieceAtPosition(8, 6, black_silver_general); // g1
    board.setPieceAtPosition(8, 7, black_knight);         // h1
    board.setPieceAtPosition(8, 8, black_lance);          // i1
    board.setPieceAtPosition(7, 7, black_rook);           // b2
    board.setPieceAtPosition(7, 1, black_bishop);         // h2

    // Fill in pawns
    for (int i = 0; i < board.getCols(); i++) {
        board.setPieceAtPosition(2, i, white_pawn); // a7 - i7
        board.setPieceAtPosition(board.getRows() - 3, i, black_pawn); // a3 - i3
    }
	
	this->startGame();
}

Shogi::~Shogi() {

}

void Shogi::setBoard(int rows, int cols) {
	board = Board(rows, cols);
}

void Shogi::startGame() {
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
		}
		else if (other == "CAPTURES") this->printCaptures();
		else if (other == "PGN") this->printPGN();
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

void Shogi::endGame(string message, int winner) {
    cout << message << "\n";
    this->printCaptures();
    this->printPGN(winner);
    system("pause");
    
    this->setEnd(true);
    clearScreen();
}

void Shogi::recordMove(string move, bool pawn, bool capture, char promote) {
	int enemy_colour = (this->getTurn() % 2) + 1;
	bool check = this->kingInCheck(enemy_colour);
	bool checkmate = false;
	bool stalemate = false;
	
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
				char piece = move[0];
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
			move += "=" + promote;
		}
	
	// Check for checkmate or stalemate
	check ? checkmate = this->kingInCheckmate(enemy_colour) : stalemate = this->kingInStalemate(enemy_colour);
	
	if (checkmate) {
		move = move + "#";
	} else if (check) {
		move = move + "+";
	}
	
	this->getTurn() == 1 ? this->addBlackMove(move) : this->addWhiteMove(move);
	
	// Notify game conditions
	if (checkmate) {
		cout << "Checkmate!\n";
		this->endGame(this->getTurn() == 1 ? "Black wins!" : "White wins!", this->getTurn());
	} else if (stalemate) {
		this->endGame("Stalemate!", 0);
	} else if (check) {
		cout << "Check!\n";
	} // else if (this->isDraw()) {
	  //    this->endGame("Draw!", 0);
	  // }
}

void Shogi::printCaptures() {
	cout << "Black captured: ";
    this->printBlackCaptures();
	
    cout << "White captured: ";
    this->printWhiteCaptures();
}

void Shogi::printPGN(int winner) {
	for (Round r : this->getRounds()) {
		cout << r.round << ". " + r.black_move + " " + r.white_move + " ";
	}
	if (winner == 0) cout << "1/2-1/2";
	else if (winner == 1) cout << "1-0";
	else if (winner == 2) cout << "0-1";
	cout << "\n";
}

char Shogi::canPromote(Piece piece, int row, int col) {
    vector<int> prs;
    char prom;
    prs = this->getTurn() == 1 ? this->getBlackPromotionRows() : this->getWhitePromotionRows();
    if (!piece.getPromoteSet().empty() &&
        find(prs.begin(), prs.end(), row) != prs.end()) {
        piece = piece.promotePiece();
        board.setPieceAtPosition(row, col, piece);
        prom = piece.getSymbol()[0];
    } prom = Piece::NONE_SQUARE;
    return prom;
}

string Shogi::isValid(string move) {
	int len = move.length();
	
	// General initial condition checks
	for (int i = 0; i < len; i++) {
		if (!(isalnum(move[i]) || move[i] == '-' || move[i] == '+')) return "Move contains non-alphanumeric characters";
	}
	if ((islower(move[0]) && !(len == 2 || (len == 4 && move[1] == 'x'))) || len > 6 ||
	    (isupper(move[0]) && (len < 3 || (move[1] == 'x' && len < 4))) ||
	    !isalpha(move[0])) {
		return "Entered invalid move";
	}
	
	int new_row = board.toX(move[len - 1]);
	int new_col = board.toY(move[len - 2]);
	int new_colour = board.getPieceAtPosition(new_row, new_col).getColour();
	
	// Cannot move onto a friendly piece
	if (new_colour == this->getTurn()) return "Cannot move onto a friendly piece";
	// Destination is either empty or has an enemy piece
	else {
		int enemy_colour = (this->getTurn() % 2) + 1;
		bool upper = isupper(move[0]);
		bool capture;
		vector<Piece> pieces = this->getTurn() == 1 ? this->getBlackPieces() : this->getWhitePieces();
		for (Piece p : pieces) {
			if ((upper && move[0] == p.getSymbol()[0]) || (!upper && p.getPawn())) {
				if (new_colour == enemy_colour) capture = true;
				return this->findPiece(move, new_row, new_col, p, this->getTurn(), capture);
			}
		}
	}
	return "Entered invalid move";
}

string Shogi::findPiece(string move, int new_row, int new_col, Piece piece, int friendly_colour, bool capture) {
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
	for (Piece::Move M : Moves) {
		range = M.range;
		for (vector<int> m : M.moves) {
			for (int r = 1; r <= range; r++) {
				row = new_row + m[0] * r;
				col = new_col + m[1] * r;
				
				Piece p = board.getPieceAtPosition(row, col);
				colour = p.getColour();
				
				// Non-eligible piece
				if (colour == -1 || colour == enemy_colour ||
				    (colour == friendly_colour && symbol != p.getSymbol()[0]))
					break;
				
				// Found a relevant piece
				if (symbol == p.getSymbol()[0] && colour == friendly_colour) {
					counter++;
					if (counter == 3) { // more than two pieces are eligible
						old_row = board.toX(move[2]);
						old_col = board.toY(move[1]);
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
			x = board.toY(move[0]);
			b = 1;
		} else {
			if (isdigit(move[1])) {
				x = board.toX(move[1]);
				b = 0;
			} else {
				x = board.toY(move[1]);
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
			move[1] = board.toCol(positions[index][1]);
		}
		
		old_row = positions[index][0];
		old_col = positions[index][1];
		piece = board.getPieceAtPosition(old_row, old_col);
		return this->makeMove(move, old_row, old_col, new_row, new_col, piece, capture);
	}
}

string Shogi::makeMove(string move, int old_row, int old_col, int new_row, int new_col, Piece piece,
                       bool capture) {
	vector<vector<Piece>> piece_positions = board.getPiecePositions();
	string captured_piece_label = board.getPieceAtPosition(new_row, new_col).getLabel();
	
	// Update board
	board.setPieceAtPosition(old_row, old_col, Piece::EMPTY);
	board.setPieceAtPosition(new_row, new_col, piece);
	
	// Cannot put the king in check
	if (this->kingInCheck(this->getTurn())) {
		board.setPiecePositions(piece_positions);
		return "Illegal move: would place the king in check";
	}
	
	// Check for promotion
	char prom = this->canPromote(piece, new_row, new_col);
	
	// Record captured piece
	if (capture) this->getTurn() == 1 ? this->pushBlackCaptures(captured_piece_label) : this->pushWhiteCaptures(captured_piece_label);
	
	this->recordMove(move, piece.getPawn(), capture, prom);
	
	return "VALID";
}

bool Shogi::positionInCheck(int pos_colour, int pos_row, int pos_col) {
	int row, col, range, colour;
	int enemy_colour = (pos_colour % 2) + 1;
	vector<Piece> pieces = enemy_colour == 1 ? this->getWhitePieces() : this->getBlackPieces();
	vector<Piece::Move> Moves;
	
	for (Piece p : pieces) {
		Moves = p.getCaptures();
		for (Piece::Move M: Moves) {
			range = M.range;
			for (vector<int> c : M.moves) {
				for (int r = 1; r <= range; r++) {
					row = pos_row + c[0] * r;
					col = pos_col + c[1] * r;
					
					Piece piece = board.getPieceAtPosition(row, col);
					colour = piece.getColour();
					
					// piece is friendly
					if (colour == pos_colour || colour == -1) break;
					// found enemy piece
					else if (colour == enemy_colour && piece.getSymbol()[0] == p.getSymbol()[0]) return true;
				}
			}
		}
	}
	return false;
}

bool Shogi::kingInCheck(int king_colour) {
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

bool Shogi::kingInCheckmate(int king_colour) {
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
	for (Piece::Move M : Moves) {
		range = M.range;
		for (vector<int> m : M.moves) {
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
		for (Piece::Move C : Captures) {
			range = C.range;
			for (vector<int> c : C.moves) {
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
	for (Piece p : pieces) {
		// Opponent's king cannot be an attacker
		if (p.getKing()) continue;
		
		for (Piece::Move C :  p.getCaptures()) {
			range = C.range;
			for (vector<int> c : C.moves) {
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
	for (Piece p : pieces) {
		for (Piece::Move C : p.getCaptures()) {
			range = C.range;
			for (vector<int> c : C.moves) {
				for (int r = 1; r <= range; r++) {
					row = attacking_row + c[0] * r;
					col = attacking_col + c[1] * r;
					
					Piece piece = board.getPieceAtPosition(row, col);
					colour = piece.getColour();
					
					// There is another piece in the way
					if (colour == enemy_colour || colour == -1)	break;
					
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
	// Attacking piece is not under attack
	// Check if the attack can be blocked
	int s;
	Piece attacking_piece = board.getPieceAtPosition(attacking_row, attacking_col);
	for (Piece::Move C : attacking_piece.getCaptures()) {
		range = C.range;
		for (vector<int> c : C.moves) {
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
						for (Piece p : pieces) {
							// King cannot block itself
							if (p.getKing()) continue;
							
							for (Piece::Move M : p.getMoves()) {
								s = M.range;
								for (vector<int> m : M.moves) {
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
											if (this->kingInCheck(king_colour)) board.setPiecePositions(piece_positions);
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
				// This is not the square you are looking for, keep searching
				else if (board.getPieceAtPosition(row, col).getColour() != 0) break;
			}
		}
	}
	// Checkmate since the attacking piece cannot be stopped
	return true;
}

bool Shogi::kingInStalemate(int king_colour) {
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
				for (Piece::Move M : Moves) {
					range = M.range;
					moves = M.moves;
					for (vector<int> m : moves) {
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
					for (Piece::Move C : Captures) {
						range = C.range;
						captures = C.moves;
						for (vector<int> c : captures) {
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

//TODO: draw

//TODO: drop

void Shogi::setRound(int i) {
	round = i;
}

int Shogi::getRound() {
	return round;
}

void Shogi::incrementRound() {
	round++;
}

void Shogi::setTurn(int i) {
	turn = i;
}

int Shogi::getTurn() {
	return turn;
}

void Shogi::changeTurn() {
	this->setTurn((this->getTurn() % 2) + 1);
}

void Shogi::setEnd(bool b) {
	end = b;
}

bool Shogi::getEnd() {
	return end;
}

void Shogi::resetRounds() {
	rounds = {};
}

vector<Shogi::Round> Shogi::getRounds() {
	return rounds;
}

void Shogi::addBlackMove(string move) {
	rounds.push_back({this->getRound(), move, ""});
}

void Shogi::addWhiteMove(string move) {
	rounds[this->getRound() - 1].white_move = move;
}

void Shogi::setPlayerOneColour(string c) {
	player_one_colour = c;
}

void Shogi::setPlayerTwoColour(string c) {
	player_two_colour = c;
}

string Shogi::getPlayerOneColour() {
	return player_one_colour;
}

string Shogi::getPlayerTwoColour() {
	return player_two_colour;
}

void Shogi::setWhitePieces(vector<Piece> p) {
	white_pieces = p;
}

void Shogi::setBlackPieces(vector<Piece> p) {
	black_pieces = p;
}

vector<Piece> Shogi::getWhitePieces() {
	return white_pieces;
}

vector<Piece> Shogi::getBlackPieces() {
	return black_pieces;
}

void Shogi::setWhitePromotionRows(vector<int> r) {
	white_promotion_rows = r;
}

void Shogi::setBlackPromotionRows(vector<int> r) {
	black_promotion_rows = r;
}

vector<int> Shogi::getWhitePromotionRows() {
	return white_promotion_rows;
}

vector<int> Shogi::getBlackPromotionRows() {
	return black_promotion_rows;
}

void Shogi::resetCaptures() {
	white_captures = {};
	black_captures = {};
}

void Shogi::pushWhiteCaptures(string s) {
	white_captures.push_back(s);
}

void Shogi::pushBlackCaptures(string s) {
	black_captures.push_back(s);
}

vector<string> Shogi::getWhiteCaptures() {
	return white_captures;
}

vector<string> Shogi::getBlackCaptures() {
	return black_captures;
}

void Shogi::printWhiteCaptures() {
	vector<string> captures = this->getWhiteCaptures();
    for (int i = 0; i < captures.size(); i++) {
        cout << captures[i] << " ";
    }
    cout << "\n";
}

void Shogi::printBlackCaptures() {
	vector<string> captures = this->getBlackCaptures();
    for (int i = 0; i < captures.size(); i++) {
        cout << captures[i] << " ";
    }
    cout << "\n";
}

void Shogi::setHalfmove(int i) {
	halfmove = i;
}

int Shogi::getHalfmove() {
	return halfmove;
}

void Shogi::incrementHalfmove() {
	halfmove++;
}

void Shogi::refreshBoard() {
	clearScreen();
	this->printWhiteCaptures();
	board.refreshBoard();
	this->printBlackCaptures();
}
