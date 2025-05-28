#pragma once
#include "PriorityQueue.h"
#include "ThreadManger.h"
#include "Common.h"
#include "Board.h"

#define MATE_SCORE 1000          ///< Bonus score for detecting checkmate.
#define UP_ROW_MIDDLE 'C'        ///< Upper row boundary for center control.
#define DOWN_ROW_MIDDLE 'F'     ///< Lower row boundary for center control.
#define LEFT_COL_MIDDLE 2       ///< Left column boundary for center control.
#define RIGHT_COL_MIDDLE 5      ///< Right column boundary for center control.
#define MIDDLE_SCORE 2          ///< Bonus for central control.
#define TOTAL_SCORE 1           ///< Bonus for general coverage.


/**
 * @brief Returns the base score of a piece based on its type.
 * @param type The type of the chess piece.
 * @return The integer score representing the piece's value.
 */
int pieceScore(TYPE);
/**
 * @brief Evaluates how much a weak piece is endangered by enemy attacks.
 * Adds score for each weaker attacking piece threatening this one.
 * @param color The color of the evaluated piece.
 * @param box The location of the piece being evaluated.
 * @param board The current game board.
 * @return The total danger score from weaker threats.
 */
int getScoreDangerWeakPiece(COLOR,const Box&,  Board&);
/**
 * @brief Evaluates how much the current piece threatens stronger enemy pieces.
 * Adds score for each stronger enemy piece within this piece's potential moves.
 * @param color The color of the evaluated piece.
 * @param box The location of the evaluating piece.
 * @param board The current game board.
 * @return The total threat score on stronger pieces.
 */
int getScoreThreatStrongPiece(COLOR, const Box&,  Board&);
/**
 * @brief Entry point for the minimax evaluation. Scores all legal moves and returns the top 5 in a priority queue.
 * @param depth How many levels to search ahead.
 * @param color The color of the player to move.
 * @param board The game board.
 * @return A priority queue of the top 5 scored moves.
 */
PriorityQueue<Move> miniMaxMain(int depth, COLOR color, Board &board);
/**
 * @brief Recursive minimax algorithm with alpha-beta pruning.
 * Evaluates a move and continues exploring legal options for both players.
 * @param depth Remaining depth of recursion.
 * @param move The move being evaluated at this depth.
 * @param board The game board.
 * @param maximizing The color for whom we are maximizing the score.
 * @param currentColor Whose turn it is now.
 * @param alpha Alpha value for pruning.
 * @param beta Beta value for pruning.
 * @return The evaluated score of the current move.
 */
int miniMax(int depth, Move move, Board& board, COLOR maximizing, COLOR currentColor, int alpha, int beta);
/**
 * @brief Undoes a move by restoring the source and destination pieces.
 * @param move The move to undo.
 * @param board The board to update.
 * @param sourcePiece The piece originally at the source.
 * @param destPiece The piece originally at the destination, if any.
 */
void undoMove(Move move, Board& board, const std::shared_ptr<Piece>&,const std::shared_ptr<Piece>&);
/**
 * @brief Checks whether a box is considered part of the center region.
 * @param box The board coordinate to check.
 * @return true if the box is within the center; false otherwise.
 */
bool isControlMiddle(const Box&);
/**
 * @brief Calculates how many of the given boxes are within the center region.
 * @param set A set of board positions.
 * @return The number of positions in the center.
 */
int calculateControlMiddle(const std::set<Box>&);













