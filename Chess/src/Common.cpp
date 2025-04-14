#include "Common.h"

/**
 * @brief Compares two Box objects for equality based on their coordinates.
 * This operator returns true if both Box objects have the same `first` (row)
 * and `second` (column) values, meaning they represent the same position
 * on the chessboard.
 * @param lhs The first Box object to compare.
 * @param rhs The second Box object to compare.
 * @return true if both boxes have identical coordinates, false otherwise.
 */
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
