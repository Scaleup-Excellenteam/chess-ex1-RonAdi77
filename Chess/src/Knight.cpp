#include "Knight.h"
#include "Move.h"

/**
 * @brief Constructor for the Knight piece.
 * Initializes a knight with its starting position and color.
 * @param init The initial location of the knight on the board.
 * @param color The color of the knight (WHITE or BLACK).
 */
Knight::Knight(const Box & init, COLOR color) : Piece(init,KNIGHT,color){}

/**
 * @brief Computes the raw (unfiltered) moves for the knight based on the current board.
 * The knight moves in "L" shapes: two squares in one direction and then one
 * square perpendicular to that. The method delegates movement calculations
 * to directional utility functions and aggregates them.
 * @param board The current game board state.
 * @return A vector of Box objects representing all raw moves the knight can make.
 */
std::vector<Box> Knight::getRawMoves(const Board & board) {
    std::vector<Box> result;
    try{
        std::vector<Box> front =  frontKnight(board, std::make_shared<Knight>(*this));
        result.insert(result.end(),front.begin(),front.end());
        std::vector<Box> back = backKnight(board,std::make_shared<Knight>(*this));
        result.insert(result.end(),back.begin(),back.end());
        std::vector<Box> right = rightKnight(board,std::make_shared<Knight>(*this));
        result.insert(result.end(),right.begin(),right.end());
        std::vector<Box> left = leftKnight(board,std::make_shared<Knight>(*this));
        result.insert(result.end(),left.begin(),left.end());
    }
    catch (std::runtime_error& e) {
        throw e;
    }

    return result;
}
/**
 * @brief Returns a shared pointer to a new Knight object cloned from the current one.
 * Used to create a polymorphic deep copy of the knight, preserving its current state.
 * @return A shared pointer to the new Knight instance.
 */
std::shared_ptr<Piece> Knight::pieceSharedPtr() const {
    return std::make_shared<Knight>(*this);
}


