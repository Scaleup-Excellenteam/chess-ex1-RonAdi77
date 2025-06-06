#include "Game.h"


/**
 * @brief Starts a manual interactive chess game where the user plays.
 *
 * This function runs a game loop accepting user moves, validating them,
 * applying moves on the board, and providing move suggestions using minimax.
 * It also checks for game end conditions such as checkmate, stalemate, and draw.
 *
 * @param boardStr The initial board state represented as a string.
 * @param turn The player color who starts the game (WHITE or BLACK).
 * @param depth The search depth for the minimax algorithm.
 * @param numThreads Number of threads to use for move calculation.
 */
void userPlayGame(const std::string& boardStr, COLOR turn, int depth, int numThreads){
    PriorityQueue<Move> priorityQueue;
    Chess a(boardStr);
    int codeResponse = 0;
    Board chessBoard(boardStr);
    chessBoard.updatePotenMoves(turn);
    string userMove = "userMove";
    // min-max algo to recommend the best move
    priorityQueue = ThreadManger::minMaxManger(chessBoard,turn,depth,numThreads);
    priorityQueue.print();
    string res = a.getInput(true, userMove,chessBoard);
    // Update all potential moves for the current player's pieces
    while (res != "exit"){
        std::pair<Box,Box> strToBox;

        // Convert user input string (e.g. "e2e4") into _source and _destination Box objects
        strToBox = stringToBox(res);
        Box source = strToBox.first;
        Box destination = strToBox.second;

        if (checkValidateMove(source, destination, turn, chessBoard, codeResponse)) {
            applyMove(source, destination, chessBoard, turn);
            codeResponse = chessBoard.isCheck(colorNot(turn)) ? CHECK_VALID_MOVE : VALID_MOVE;
            turn = colorNot(turn);

            if (chessBoard.isMate(turn)) {
                std::cout << "\nCheckmate! " << (turn == WHITE ? "Black" : "White") << " wins!\n";
                break;
            }
            if (chessBoard.isStalemate(turn)) {
                std::cout << "\nStalemate! It's a draw.\n";
                break;
            }
            if (chessBoard.isDraw()) {
                std::cout << "\nDraw by insufficient material.\n";
                break;
            }
            if (chessBoard.isThreeFoldDraw()) {
                std::cout << "\nDraw by threefold repetition.\n";
                break;
            }
        }

        a.setCodeResponse(codeResponse);
        // min-max algo to recommend the best move
        priorityQueue = ThreadManger::minMaxManger(chessBoard,turn,depth,numThreads);
        priorityQueue.print();
        res = a.getInput(true, userMove,chessBoard);
    }

    cout << endl << "Exiting " << endl;
}
/**
 * @brief Starts a chess game session where the computer plays against the user.
 *
 * The game alternates turns between the user and the computer.
 * The computer uses a minimax algorithm with multithreading to select moves.
 * The user inputs moves via console. Game end conditions are monitored.
 *
 * @param boardStr The initial board state represented as a string.
 * @param turn The player color who starts the game (WHITE or BLACK).
 * @param depth The search depth for the minimax algorithm.
 * @param numThreads Number of threads to use for move calculation.
 */
void computerPlayGame(const std::string& boardStr, COLOR turn , int depth , int numThreads){
    PriorityQueue<Move> priorityQueue;
    Chess a(boardStr);
    int codeResponse = 0;
    Board chessBoard(boardStr);
    chessBoard.updatePotenMoves(turn);
    std::string res;
    while (true){
        if (turn == WHITE){
            priorityQueue = ThreadManger::minMaxManger(chessBoard, turn, depth, numThreads);
            priorityQueue.print();
            string userMove = "userMove";
            res = a.getInput(true, userMove,chessBoard);
            if (res == "exit"){
                break;
            }

            std::pair<Box, Box> strToBox = stringToBox(res);
            Box source = strToBox.first;
            Box destination = strToBox.second;

            if (checkValidateMove(source, destination, turn, chessBoard, codeResponse)) {
                applyMove(source, destination, chessBoard, turn);
                codeResponse = chessBoard.isCheck(colorNot(turn)) ? CHECK_VALID_MOVE : VALID_MOVE;
                turn = colorNot(turn);

                if (chessBoard.isMate(turn)) {
                    std::cout << "\nCheckmate! " << (turn == WHITE ? "Black" : "White") << " wins!\n";
                    break;
                }
                if (chessBoard.isStalemate(turn)) {
                    std::cout << "\nStalemate! It's a draw.\n";
                    break;
                }
                if (chessBoard.isDraw()) {
                    std::cout << "\nDraw by insufficient material.\n";
                    break;
                }
                if (chessBoard.isThreeFoldDraw()) {
                    std::cout << "\nDraw by threefold repetition.\n";
                    break;
                }
            }
            a.setCodeResponse(codeResponse);
        }

        else{
            std::cout << "\nComputer is thinking...\n";
            priorityQueue = ThreadManger::minMaxManger(chessBoard, turn, depth, numThreads);

            std::optional<Move> maybeMove = priorityQueue.pull();
            if (!maybeMove.has_value()) {
                std::cout << "Computer found no valid moves.\n";
                if (chessBoard.isMate(turn)) {
                    std::cout << "\nCheckmate! " << (turn == WHITE ? "Black" : "White") << " wins!\n";
                } else {
                    std::cout << "\nStalemate! It's a draw.\n";
                }
                break;
            }

            Move bestMove = maybeMove.value();
            string move = bestMove.toString();
            res = a.getInput(false, move ,chessBoard);
            Box source = bestMove._source;
            Box destination = bestMove._destination;


            if (!checkValidateMove(source, destination, turn, chessBoard, codeResponse)) {
                std::cout << "Computer attempted illegal move. Skipping.\n";
                turn = colorNot(turn);
                continue;
            }
            applyMove(source, destination, chessBoard, turn);

            std::cout << "Computer played: " << bestMove;
            if (chessBoard.isCheck(colorNot(turn))) {
                std::cout << " — Check!";
            }
            std::cout << "\n";

            turn = colorNot(turn);

            if (chessBoard.isMate(turn)) {
                std::cout << "\nCheckmate! " << (turn == WHITE ? "Black" : "White") << " wins!\n";
                break;
            }
            if (chessBoard.isStalemate(turn)) {
                std::cout << "\nStalemate! It's a draw.\n";
                break;
            }
            if (chessBoard.isDraw()) {
                std::cout << "\nDraw by insufficient material.\n";
                break;
            }
            if (chessBoard.isThreeFoldDraw()) {
                std::cout << "\nDraw by threefold repetition.\n";
                break;
            }
            a.setCodeResponse(codeResponse);
        }

    }
}

/**
 * @brief Validates whether a move from source to destination is legal.
 *
 * This function checks:
 * - Source box contains a piece belonging to the current player.
 * - Destination box does not contain a piece of the same color.
 * - The move is valid according to piece movement rules.
 * - The move does not leave the player’s king in check.
 *
 * @param source The source box of the move.
 * @param destination The destination box of the move.
 * @param turn The current player color.
 * @param board The current state of the board.
 * @param responseCode Reference to an int to store the validation result code.
 * @return true if the move is valid, false otherwise.
 */
bool checkValidateMove(const Box& source, const Box& destination, COLOR turn, Board& board, int& responseCode){
    std::shared_ptr<Piece> sourcePiece;
    std::shared_ptr<Piece> destinationPiece;

    try {
        sourcePiece = board.getPiece(source);
    } catch (EmptyPiece&) {
        responseCode = EMPTY_SOURCE;
        return false;
    }

    if (!sourcePiece || sourcePiece->getColor() != turn) {
        responseCode = OPPONENT_SOURCE;
        return false;
    }

    try {
        destinationPiece = board.getPiece(destination);
        if (destinationPiece && destinationPiece->getColor() == turn) {
            responseCode = OWN_PIECE_DESTINATION;
            return false;
        }
    } catch (EmptyPiece&) {
        // destination is empty — that's okay
    }

    if (!sourcePiece->isValidMove(destination, board)) {
        responseCode = INVALID_MOVE;
        return false;
    }

    if (sourcePiece->ownCheck(destination, board)) {
        responseCode = OWN_CHECK;
        return false;
    }

    responseCode = VALID_MOVE;
    return true;

}
/**
 * @brief Applies a validated move on the board.
 *
 * Moves the piece from source to destination and updates potential moves for the opponent.
 *
 * @param source The source box of the move.
 * @param destination The destination box of the move.
 * @param board The current state of the board.
 * @param turn The current player color.
 */
void applyMove(const Box& source, const Box& destination, Board& board, COLOR turn){
    std::shared_ptr<Piece> piece = board.getPiece(source);
    board.makeMove(destination, piece);
    board.updatePotenMoves(colorNot(turn));
}