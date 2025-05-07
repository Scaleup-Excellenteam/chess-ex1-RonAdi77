#include "Common.h"


bool operator==(const Box& lhs,const Box& rhs){
    return (lhs.first == rhs.first && lhs.second == rhs.second);
}

/**
 * @brief Checks if a given box (chessboard coordinate) is within the boundaries of a standard 8x8 chess board.
 * Accepts both uppercase ('A'-'H') and lowercase ('a'-'h') characters for columns.
 * Valid rows are from 1 to 8.
 * @param box The coordinate on the board to validate.
 * @return true if the box is within valid board boundaries; false otherwise.
 */
bool inBoard(const Box& box){
    return (((('A' <= box.first) && (box.first <= 'H')) || (('a' <= box.first) && (box.first <= 'h'))) && ((1 <= box.second ) && (box.second <= 8)));
}

/**
 * @brief Returns the opposite color of the given player.
 * Useful for alternating turns or checking opponent pieces.
 * @param color The current color (BLACK or WHITE).
 * @return The opposing color.
 */
COLOR colorNot(COLOR color){
    return (color == BLACK)? WHITE:BLACK;
}
/**
 * @brief Outputs a Move object to an output stream.
 * This function formats the move by printing the source and destination coordinates
 * of the move. The source and destination are represented as the combination of
 * row and column (e.g., "A2" to "A4").
 * @param os The output stream to write the move to (e.g., std::cout).
 * @param move The Move object to be printed.
 * @return The updated output stream after printing the move.
 */
std::ostream& operator<<(std::ostream &os, const Move &move) {
    os << move._source.first << move._source.second << " " << move._destination.first << move._destination.second;
    return os;
}
