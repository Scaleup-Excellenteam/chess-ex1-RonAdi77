// Chess 
#include "Chess.h"
#include "Board.h"
#include "Move.h"
#include "PriorityAlgo.h"
#include "MyExceptions.h"

#define DEPTH 2

int main()
{
    PriorityQueue<Move> priorityQueue;
    string board = "RNBQKBNRPPPPPPPP################################pppppppprnbqkbnr";
//    string board = "##########K###############################R#####q#######r#######";
    COLOR turn = WHITE;
	Chess a(board);
	int codeResponse = 0;
    Board chessBoard(board);
    chessBoard.updatePotenMoves(turn);
    // min-max algo to recommend the best move
    priorityQueue = miniMaxMain(DEPTH, turn, chessBoard);
    priorityQueue.print();
	string res = a.getInput();
    // Update all potential moves for the current player's pieces
	while (res != "exit"){
        std::pair<Box,Box> strToBox;

        // Convert user input string (e.g. "e2e4") into _source and _destination Box objects
        strToBox = stringToBox(res);
        Box source = strToBox.first;
        Box destination = strToBox.second;

        // Define pointers for the _source and _destination pieces
        std::shared_ptr<Piece> sourcePiece;
        std::shared_ptr<Piece> destinationPiece;

        // Used to skip further checks if an error is already found
        bool codeResponseFlag = false;
        try{
            // Try to get the piece at the _source box
            sourcePiece = chessBoard.getPiece(source);
        }
        catch (EmptyPiece& e){
            // If there's no piece at the _source, it's an invalid move (code 11)
            codeResponse = EMPTY_SOURCE;
            codeResponseFlag = true;
        }
        // If _source is valid, but it's not the current player's piece
        if (!codeResponseFlag && turn != sourcePiece->getColor()){
            codeResponse = OPPONENT_SOURCE;
            codeResponseFlag = true;
        }
        try{
            // Check if there's a piece at the _destination
            destinationPiece = chessBoard.getPiece(destination);
            // If it's your own piece at _destination, it's an invalid move (code 13)
            if (turn == destinationPiece->getColor()){
                codeResponse = OWN_PIECE_DESTINATION;
                codeResponseFlag = true;
            }
        }
        catch (EmptyPiece& e){
            // No piece at _destination — that's fine, continue
        }
        if (!codeResponseFlag){
            // No your own piece at _destination — proceed with move validation
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
                chessBoard.makeMove(destination,sourcePiece);
                chessBoard.updatePotenMoves(turn);
                // If this move puts the player in check
                codeResponse = chessBoard.isCheck(colorNot(turn))? CHECK_VALID_MOVE : VALID_MOVE; // code 41 or 42
                // Switch turn to the other player
                turn = colorNot(turn);
            }
		}
		a.setCodeResponse(codeResponse);
        // min-max algo to recommend the best move
        priorityQueue = miniMaxMain(DEPTH, turn, chessBoard);
        priorityQueue.print();
        res = a.getInput();
	}

	cout << endl << "Exiting " << endl;
	return 0;

}