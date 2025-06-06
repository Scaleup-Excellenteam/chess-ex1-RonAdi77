#pragma once

#include "Chess.h"
#include "Board.h"
#include "Move.h"
#include "PriorityAlgo.h"
#include "MyExceptions.h"
#include "ThreadManger.h"
#include <chrono>

/**
 * @brief Starts a game session where the user plays.
 *
 * @param gameName Name or identifier of the game/session.
 * @param playerColor The color the user is playing (WHITE or BLACK).
 * @param timeLimit Time limit per move or game (seconds).
 * @param maxMoves Maximum number of moves allowed in the game.
 */
void userPlayGame(const std::string&, COLOR, int, int);
/**
 * @brief Starts a game session where the computer plays automatically.
 *
 * @param gameName Name or identifier of the game/session.
 * @param computerColor The color the computer is playing.
 * @param timeLimit Time limit per move or game (seconds).
 * @param maxMoves Maximum number of moves allowed in the game.
 */
void computerPlayGame(const std::string&, COLOR, int, int);
/**
 * @brief Validates whether a proposed move from source to destination is legal.
 *
 * @param source Starting position of the piece to move.
 * @param destination Ending position where the piece should move.
 * @param turn The current player's color.
 * @param board The current game board state.
 * @param responseCode Output parameter indicating detailed validation results (e.g., illegal move, check, etc.).
 * @return True if the move is valid according to game rules, false otherwise.
 */
bool checkValidateMove(const Box& source, const Box& destination, COLOR turn, Board& board, int& responseCode);
/**
 * @brief Applies a validated move to the board, updating the game state accordingly.
 *
 * @param source Starting position of the piece to move.
 * @param destination Ending position where the piece will move.
 * @param board The current game board to be updated.
 * @param turn The current player's color making the move.
 */
void applyMove(const Box& source, const Box& destination, Board& board, COLOR turn);