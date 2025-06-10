#include "Rook.h"


/**
 * @brief Rook constructor.
 * Initializes the Rook at a given position and color.
 * @param init The initial position of the Rook.
 * @param color The color of the Rook (WHITE or BLACK).
 */
Rook::Rook(const Box & init, COLOR color): Piece(init,ROOK,color) {}


/**
 * @brief Calculates the raw moves for the Rook.
 * This includes all possible moves along the ranks and files until blocked by another piece or the board edge.
 * @param board The current state of the board.
 * @return std::vector<Box> A list of boxes the Rook can move to.
 */
std::vector<Box> Rook::getRawMoves(const Board & board) {
    std::vector<Box> result;
    try{
        auto moves =  frontFreeBoxes(board, std::make_shared<Rook>(*this));
        result.insert(result.end(),moves.begin(),moves.end());
        moves = backFreeBoxes(board,std::make_shared<Rook>(*this));
        result.insert(result.end(),moves.begin(),moves.end());
        moves = rightFreeBoxes(board,std::make_shared<Rook>(*this));
        result.insert(result.end(),moves.begin(),moves.end());
        moves = leftFreeBoxes(board,std::make_shared<Rook>(*this));
        result.insert(result.end(),moves.begin(),moves.end());
    }
    catch (EmptyPiece& e) {
        throw e;
    }

    return result;
}

/**
 * @brief Returns a shared pointer to a copy of the current Rook.
 * Useful for polymorphic operations where a clone of the piece is required.
 * @return std::shared_ptr<Piece> A shared pointer to the cloned Rook.
 */
std::shared_ptr<Piece> Rook::pieceSharedPtr() const {
    return std::make_shared<Rook>(*this);
}

char Rook::toChar() {
    if (getColor() == WHITE){
        return 'R';
    }
    return 'r';
}


