#include "Game.h"


void autoPlayGame(const std::string& boardStr, COLOR turn, int depth, int numThreads){
    Board board(boardStr);
    board.updatePotenMoves(turn);
    PriorityQueue<Move> priorityQueue;

    auto start = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < 8; ++i) {
        board.updatePotenMoves(turn);
        priorityQueue = ThreadManger::minMaxManger(board, turn, depth, numThreads);

        Move bestMove = priorityQueue.pull();
        Box source = bestMove._source;
        Box dest = bestMove._destination;

        std::shared_ptr<Piece> sourcePiece;
        std::shared_ptr<Piece> destinationPiece;


        try {
            sourcePiece = board.getPiece(source);
        } catch (EmptyPiece&) {
            std::cout << "[Auto " << i + 1 << "] there is not piece at the _source\n";
            continue;
        }

        if (turn != sourcePiece->getColor()) {
            std::cout << "[Auto " << i + 1 << "] the piece in the _source is piece of your opponent\n";
            continue;
        }

        try {
            destinationPiece = board.getPiece(dest);
            if (turn == destinationPiece->getColor()) {
                std::cout << "[Auto " << i + 1 << "] there one of your pieces at the _destination\n";
                continue;
            }
        } catch (EmptyPiece&) {
            // No piece at _destination — that's fine, continue
        }

        if (!sourcePiece->isValidMove(dest, board)) {
            std::cout << "[Auto " << i + 1 << "] illegal movement of that piece\n";
            continue;
        }

        if (sourcePiece->ownCheck(dest, board)) {
            std::cout << "[Auto " << i + 1 << "] this movement will cause you checkmate\n";
            continue;
        }

        board.makeMove(dest, sourcePiece);
        board.updatePotenMoves(turn);

        if (board.isCheck(colorNot(turn))) {
            std::cout << "[Auto " << i + 1 << "] the last movement was legal and cause check: " << bestMove << "\n";
        } else {
            std::cout << "[Auto " << i + 1 << "] the last movement was legal: " << bestMove << "\n";
        }

        turn = colorNot(turn);

    }
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = duration_cast<std::chrono::seconds>(end - start);
    std::cout << "Threads: " << numThreads << ", Time: " << duration.count() << "s\n";
}

void userPlayGame(const std::string& boardStr, COLOR turn, int depth, int numThreads){
    PriorityQueue<Move> priorityQueue;
    Chess a(boardStr);
    int codeResponse = 0;
    Board chessBoard(boardStr);
    chessBoard.updatePotenMoves(turn);
    // min-max algo to recommend the best move
    priorityQueue = ThreadManger::minMaxManger(chessBoard,turn,depth,numThreads);
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
        priorityQueue = ThreadManger::minMaxManger(chessBoard,turn,depth,numThreads);
        priorityQueue.print();
        res = a.getInput();
    }

    cout << endl << "Exiting " << endl;
}

