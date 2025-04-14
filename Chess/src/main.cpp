// Chess 
#include "Chess.h"
#include "Board.h"
#include "Move.h"

int main()
{
	string board = "RNBQKBNRPPPPPPPP################################pppppppprnbqkbnr";
//	string board = "##########K###############################R####R##########r#r####";
	Chess a(board);
	int codeResponse = 0;
    COLOR turn = WHITE;
    Board chessBoard(board);
	string res = a.getInput();
    // Update all potential moves for the current player's pieces
    chessBoard.updatePotenMoves(turn);
	while (res != "exit"){
        std::pair<Box,Box> strToBox;

        // Convert user input string (e.g. "e2e4") into source and destination Box objects
        strToBox = stringToBox(res);


        Box  source = strToBox.first;
        Box destination = strToBox.second;

        // Define pointers for the source and destination pieces
        std::shared_ptr<Piece> sourcePiece;
        std::shared_ptr<Piece> destinationPiece;

        // Used to skip further checks if an error is already found
        bool codeResponseFlag = false;
        try{
            // Try to get the piece at the source box
            sourcePiece = chessBoard.getPiece(source);
        }
        catch (std::runtime_error& e){
            // If there's no piece at the source, it's an invalid move (code 11)
            codeResponse = EMPTY_SOURCE;
            codeResponseFlag = true;
        }
        // If source is valid, but it's not the current player's piece
        if (!codeResponseFlag && turn != sourcePiece->getColor()){
            codeResponse = OPPONENT_SOURCE;
            codeResponseFlag = true;
        }
        try{
            // Check if there's a piece at the destination
            destinationPiece = chessBoard.getPiece(destination);
            // If it's your own piece at destination, it's an invalid move (code 13)
            if (turn == destinationPiece->getColor()){
                codeResponse = OWN_PIECE_DESTINATION;
                codeResponseFlag = true;
            }
        }
        catch (std::runtime_error& e){
            // No piece at destination — that's fine, continue
        }
        if (!codeResponseFlag){
            // No your own piece at destination — proceed with move validation
            // Check if the move is even allowed by the piece's movement rules
            if (!sourcePiece->isValidMove(destination,chessBoard)){
                codeResponse = INVALID_MOVE; // code 21
            }
            // Check if move would put the player in check
            else if(sourcePiece->ownCheck(destination,chessBoard)){
                codeResponse = OWN_CHECK; // coded 31
            }
            else {
                // Perform the move
                chessBoard.pieceMove(destination,sourcePiece);
                chessBoard.updatePotenMoves(turn);
                // If this move puts the player in check
                codeResponse = chessBoard.isCheck(colorNot(turn))? CHECK_VALID_MOVE : VALID_MOVE; // code 41 or 42
                // Switch turn to the other player
                turn = colorNot(turn);
            }
		}
		a.setCodeResponse(codeResponse);
		res = a.getInput(); 
	}

	cout << endl << "Exiting " << endl; 
	return 0;
}