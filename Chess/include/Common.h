#pragma once
#include <iostream>
#include <utility>


/**
 * @brief Constant representing an attempt to move from an empty square.
 */
const int EMPTY_SOURCE = 11;

/**
 * @brief Constant representing an attempt to move an opponent's piece.
 */
const int OPPONENT_SOURCE = 12;

/**
 * @brief Constant representing a destination occupied by the player's own piece.
 */
const int OWN_PIECE_DESTINATION = 13;

/**
 * @brief Constant representing a move that is not valid by the rules of the game.
 */
const int INVALID_MOVE = 21;

/**
 * @brief Constant representing a move that would leave the player's own king in check.
 */
const int OWN_CHECK = 31;

/**
 * @brief Constant representing a valid move that does not result in check.
 */
const int VALID_MOVE = 42;

/**
 * @brief Constant representing a valid move that puts the opponent in check.
 */
const int CHECK_VALID_MOVE = 41;


/**
 * @brief Constant representing the first valid column on a chess board.
 * Columns are numbered from 1 (leftmost) to 8 (rightmost).
 */
const int FIRST_COL = 1;
/**
 * @brief Constant representing the last valid column on a chess board.
 * Columns are numbered from 1 (leftmost) to 8 (rightmost).
 */
const int LAST_COL = 8;
/**
 * @brief Constant representing the first valid row on a chess board.
 * Rows are labeled from 'A' (top) to 'H' (bottom) in standard notation.
 */
const char FIRST_ROW = 'A';
/**
 * @brief Constant representing the last valid row on a chess board.
 * Rows are labeled from 'A' (top) to 'H' (bottom) in standard notation.
 */
const char LAST_ROW = 'H';

/**
 * @brief Constant representing the total number of squares on a standard chess board.
 * A standard chess board has 8 rows and 8 columns, resulting in 64 squares.
 */
const int BOARD_SIZE = 64;


/**
 * @brief Enum representing the type of chess piece.
 */
enum TYPE {
    KING,
    QUEEN,
    ROOK,
    BISHOP,
    KNIGHT,
    PAWN
};

/**
 * @brief Enum representing the color of a piece or player.
 */
enum COLOR {
    BLACK,
    WHITE
};

/**
 * @brief Represents a position on the chess board using (row, column),
 * where row is a character from 'A' to 'H', and column is an integer from 1 to 8.
 */
typedef std::pair<char, int> Box;


// ---- Functions ----
/**
 * @brief Compares two Box objects for equality.
 * This operator checks if both Box objects represent the same position
 * or state in the context of the chessboard. The exact comparison logic 
 * depends on the Box class implementation, typically comparing internal 
 * coordinates or piece data.
 * @param lhs The first Box object to compare.
 * @param rhs The second Box object to compare.
 * @return true if the boxes are equal, false otherwise.
 */
bool operator==(const Box&,const Box&);

/**
 * @brief Checks whether a box is a valid board position.
 * @param box A board coordinate.
 * @return true if within 'A'-'H' or 'a'-'h' and 1-8.
 */
bool inBoard(const Box& box);

/**
 * @brief Returns the opposite color.
 * @param color The input color.
 * @return BLACK if WHITE, or WHITE if BLACK.
 */
COLOR colorNot(COLOR color);


