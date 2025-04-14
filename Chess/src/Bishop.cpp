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
        std::vector<Box> FrontRight = diagFrontRight(board, std::make_shared<Bishop>(*this));
        result.insert(result.end(),FrontRight.begin(),FrontRight.end());
        std::vector<Box> FrontLeft = diagFrontLeft(board,std::make_shared<Bishop>(*this));
        result.insert(result.end(),FrontLeft.begin(),FrontLeft.end());
        std::vector<Box> BackRight = diagBackRight(board,std::make_shared<Bishop>(*this));
        result.insert(result.end(),BackRight.begin(),BackRight.end());
        std::vector<Box> BackLeft = diagBackLeft(board,std::make_shared<Bishop>(*this));
        result.insert(result.end(),BackLeft.begin(),BackLeft.end());
    }

    catch (std::runtime_error& e) {
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


