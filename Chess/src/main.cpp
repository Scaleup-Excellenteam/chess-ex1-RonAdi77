// Chess 
#include "Chess.h"
#include "Board.h"
#include "Game.h"


int main()
{

    string board = "RNBQKBNRPPPPPPPP################################pppppppprnbqkbnr";
//    string board = "##########K###############################R#####q#######r#######";
//    string board = "####K#########R####################Q##bk############r###########";
    COLOR turn = WHITE;
    int autoMode, depth;
    std::cout << "Enter search depth: ";
    std::cin >> depth;
    std::cout << "Auto-play mode? (0 = manual, 1 = auto): ";
    std::cin >> autoMode;

    if (autoMode == 1){
        std::cout << "Running 8-move auto-game..." << std::endl;
        for (int threads : {0, 2, 4, 8}) {
            autoPlayGame(board, turn, depth, threads);
        }
    }
    else{
        int numThreads;
        std::cout << "Running manual game..." << std::endl;
        std::cout << "Enter number of threads: ";
        std::cin >> numThreads;
        userPlayGame(board, turn, depth, numThreads);
    }
	return 0;

}