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
 * @brief Constant representing a _destination occupied by the player's own piece.
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

bool operator==(const Box&,const Box&);


// ---- Functions ----

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

/**
 * @struct Move
 * @brief Represents a move in a chess game.
 * Contains the source and destination coordinates of the move, along with a score that
 * evaluates the quality of the move, used for algorithms like minimax.
 */
struct Move{
    Box _source;        ///< The source position of the piece being moved
    Box _destination;   ///< The destination position of the piece being moved
    int _score;         ///< The score associated with the move, used for evaluating move quality
    /**
    * @brief Compares the scores of two moves.
    * Subtracts the score of the current move from that of another move. Used for sorting moves.
    * @param other The other Move object to compare to.
    * @return The difference in scores between the two moves.
    */
    int operator-(const Move& other) const{
        return _score - other._score;
    }
    /**
     * @brief Outputs a Move to an output stream.
     * Prints the source and destination of the move along with its score.
     * @param os The output stream to write to.
     * @param move The Move object to print.
     * @return The updated output stream.
     */
    friend std::ostream& operator<<(std::ostream& os,const Move& move );

    [[nodiscard]] std::string toString() const {
        return std::string(1, _source.first) + std::to_string(_source.second) +
               std::string(1, _destination.first) + std::to_string(_destination.second);
    }
};
