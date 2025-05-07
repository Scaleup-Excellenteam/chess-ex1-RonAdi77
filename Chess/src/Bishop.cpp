#include "Bishop.h"


/**
 * @brief Constructs a Bishop object with an initial position and color.
 * Initializes the bishop using the base Piece constructor with type BISHOP.
 * @param init The starting position of the bishop.
 * @param color The color of the bishop (WHITE or BLACK).
 */
Bishop::Bishop(const Box & init, COLOR color): Piece(init,BISHOP,color){}

/**
 * @brief Computes all raw diagonal moves for the bishop.
 * The bishop moves diagonally in all four directions: front-right, front-left,
 * back-right, and back-left until blocked by another piece or board boundaries.
 * This function gathers all such moves without considering if the king is in check.
 * @param board The current state of the board.
 * @return A vector of legal boxes the bishop can move to, based on board occupancy.
 */
std::vector<Box> Bishop::getRawMoves(const Board & board) {
    std::vector<Box> result;

    try {
        auto moves = diagFrontRight(board, std::make_shared<Bishop>(*this));
        result.insert(result.end(),moves.begin(),moves.end());
        moves = diagFrontLeft(board,std::make_shared<Bishop>(*this));
        result.insert(result.end(),moves.begin(),moves.end());
        moves = diagBackRight(board,std::make_shared<Bishop>(*this));
        result.insert(result.end(),moves.begin(),moves.end());
        moves = diagBackLeft(board,std::make_shared<Bishop>(*this));
        result.insert(result.end(),moves.begin(),moves.end());
    }

    catch (EmptyPiece& e) {
        throw e;
    }

    return result;
}
/**
 * @brief Creates a shared pointer to a deep copy of this bishop.
 * Used to safely clone the bishop, preserving its current state.
 * @return A std::shared_ptr to a new Bishop object copied from this one.
 */
std::shared_ptr<Piece> Bishop::pieceSharedPtr() const {
    return std::make_shared<Bishop>(*this);
}


