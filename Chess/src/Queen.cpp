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
        auto moves =  frontFreeBoxes(board, std::make_shared<Queen>(*this));
        result.insert(result.end(),moves.begin(),moves.end());
        moves = backFreeBoxes(board,std::make_shared<Queen>(*this));
        result.insert(result.end(),moves.begin(),moves.end());
        moves = rightFreeBoxes(board,std::make_shared<Queen>(*this));
        result.insert(result.end(),moves.begin(),moves.end());
        moves = leftFreeBoxes(board,std::make_shared<Queen>(*this));
        result.insert(result.end(),moves.begin(),moves.end());

        // Bishop-style moves
        moves =  diagFrontRight(board, std::make_shared<Queen>(*this));
        result.insert(result.end(),moves.begin(),moves.end());
        moves = diagFrontLeft(board,std::make_shared<Queen>(*this));
        result.insert(result.end(),moves.begin(),moves.end());
        moves = diagBackRight(board,std::make_shared<Queen>(*this));
        result.insert(result.end(),moves.begin(),moves.end());
        moves = diagBackLeft(board,std::make_shared<Queen>(*this));
        result.insert(result.end(),moves.begin(),moves.end());
    }

    catch (EmptyPiece& e) {
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

char Queen::toChar() {
    if (getColor() == WHITE){
        return 'Q';
    }
    return 'q';
}






