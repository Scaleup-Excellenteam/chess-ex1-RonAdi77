// Chess 
#include "Chess.h"
#include "Board.h"
#include "Game.h"
#define THREADS 8

/**
 * @brief Entry point of the chess program.
 *
 * This function initializes the chess board and manages the game mode selection.
 * It prompts the user to choose between manual play (human vs. human) or computer play (AI vs. AI),
 * and requests the search depth for AI move calculation.
 * Depending on the chosen mode, it starts the corresponding game loop.
 *
 * The initial board setup is currently hardcoded and can be modified by uncommenting
 * and changing the `board` string variables.
 *
 * @return int Returns 0 upon successful termination.
 */
int main()
{
    string board = "RNBQKBNRPPPPPPPP################################pppppppprnbqkbnr";
//    string board = "####K##########################R####k###################Q#######";
//    string board = "R###K##R###############################k############r#######Q#b#";
    COLOR turn = WHITE;
    int mode, depth;
    std::cout << "choose mode: (0 = manual, 1 = computer): ";
    std::cin >> mode;
    std::cout << "Enter search depth: ";
    std::cin >> depth;

    if (mode == 1){
        std::cout << "Running computer game..." << std::endl;
        computerPlayGame(board, turn, depth, THREADS);
    }
    else{
        std::cout << "Running manual game..." << std::endl;
        userPlayGame(board, turn, depth, THREADS);
    }
	return 0;

}