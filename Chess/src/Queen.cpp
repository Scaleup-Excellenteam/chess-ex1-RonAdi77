#include "Queen.h"

/**
 * @brief Constructs a Queen at a given position with a specified color.
 * @param init The initial position of the Queen.
 * @param color The color of the Queen (WHITE or BLACK).
 */
Queen::Queen(const Box & init, COLOR color) : Piece(init,QUEEN,color){}

/**
 * @brief Computes the raw moves available to the Queen on a given board.
 * The Queen can move any number of squares in horizontal, vertical, or diagonal directions
 * as long as the path is unobstructed.
 * @param board The current state of the chess board.
 * @return A vector of valid positions the Queen can move to.
 */
std::vector<Box> Queen::getRawMoves(const Board & board) {
    std::vector<Box> result;

    try{
        // Rook-style moves
        std::vector<Box> front =  frontFreeBoxes(board, std::make_shared<Queen>(*this));
        result.insert(result.end(),front.begin(),front.end());
        std::vector<Box> back = backFreeBoxes(board,std::make_shared<Queen>(*this));
        result.insert(result.end(),back.begin(),back.end());
        std::vector<Box> right = rightFreeBoxes(board,std::make_shared<Queen>(*this));
        result.insert(result.end(),right.begin(),right.end());
        std::vector<Box> left = leftFreeBoxes(board,std::make_shared<Queen>(*this));
        result.insert(result.end(),left.begin(),left.end());

        // Bishop-style moves
        std::vector<Box> frontRight =  diagFrontRight(board, std::make_shared<Queen>(*this));
        result.insert(result.end(),frontRight.begin(),frontRight.end());
        std::vector<Box> frontLeft = diagFrontLeft(board,std::make_shared<Queen>(*this));
        result.insert(result.end(),frontLeft.begin(),frontLeft.end());
        std::vector<Box> backRight = diagBackRight(board,std::make_shared<Queen>(*this));
        result.insert(result.end(),backRight.begin(),backRight.end());
        std::vector<Box> backLeft = diagBackLeft(board,std::make_shared<Queen>(*this));
        result.insert(result.end(),backLeft.begin(),backLeft.end());
    }

    catch (std::runtime_error& e) {
        throw e;
    }

    return result;
}
/**
 * @brief Creates a shared pointer clone of the current Queen object.
 * Useful when duplicating pieces for board copying or simulations.
 * @return A shared_ptr to a copy of this Queen.
 */
std::shared_ptr<Piece> Queen::pieceSharedPtr() const {
    return std::make_shared<Queen>(*this);
}






