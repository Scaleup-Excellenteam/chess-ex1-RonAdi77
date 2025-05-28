#pragma once

#include "Chess.h"
#include "Board.h"
#include "Move.h"
#include "PriorityAlgo.h"
#include "MyExceptions.h"
#include "ThreadManger.h"
#include <chrono>

/**
 * @brief Executes an automated chess game with a fixed number of moves.
 * The best move is chosen at each turn using a multithreaded Minimax algorithm.
 * @param boardStr The initial board configuration as a string.
 * @param turn The color of the player to start the game.
 * @param depth The depth to which the Minimax algorithm should search.
 * @param numThreads Number of threads to use for evaluation.
 */
void autoPlayGame(const std::string&, COLOR, int, int);
/**
 * @brief Starts an interactive chess game where the user plays against the computer.
 * At each turn, the engine recommends top 3 moves using the Minimax algorithm.
 * @param boardStr The initial board configuration as a string.
 * @param turn The color of the player to start the game.
 * @param depth The depth to which the Minimax algorithm should search.
 * @param numThreads Number of threads to use for evaluation.
 */
void userPlayGame(const std::string&, COLOR, int, int);