#include "King.h"

/**
 * @brief Constructs a King object with a given initial position and color.
 * Initializes the king piece with the provided starting position and color
 * by calling the base class constructor (Piece).
 * @param init The initial position of the king.
 * @param color The color of the king (WHITE or BLACK).
 */
King::King(const Box & init, COLOR color) : Piece(init,KING,color){}

/**
 * @brief Computes all raw moves for the king.
 * The King can move one square in any direction: vertically, horizontally,
 * or diagonally. This function calculates those moves by checking available
 * spaces in each of the eight directions around the king's position.
 * It ensures that moves are within the boundaries of the board and return
 * the valid squares.
 * @param board The current state of the board.
 * @return A vector containing all valid squares the King can move to.
 */
std::vector<Box> King::getRawMoves(const Board & board) {
    std::vector<Box> result;

    try{
        // rook moves
        auto moves =  frontFreeBoxes(board, std::make_shared<King>(*this));
        if (!moves.empty()){
            result.push_back(moves.at(0));
        }
        moves = backFreeBoxes(board,std::make_shared<King>(*this));
        if (!moves.empty()){
            result.push_back(moves.at(0));
        }
        moves = rightFreeBoxes(board,std::make_shared<King>(*this));
        if (!moves.empty()){
            result.push_back(moves.at(0));
        }
        moves = leftFreeBoxes(board,std::make_shared<King>(*this));
        if (!moves.empty()){
            result.insert(result.end(),moves.begin(),moves.end());
        }

        // bishop moves
        moves =  diagFrontRight(board, std::make_shared<King>(*this));
        if (!moves.empty()){
            result.push_back(moves.at(0));
        }
        moves = diagFrontLeft(board,std::make_shared<King>(*this));
        if (!moves.empty()){
            result.push_back(moves.at(0));
        }
        moves = diagBackRight(board,std::make_shared<King>(*this));
        if(!moves.empty()){
            result.push_back(moves.at(0));
        }
        moves = diagBackLeft(board,std::make_shared<King>(*this));
        if(!moves.empty()){
            result.push_back(moves.at(0));
        }
    }
    catch (EmptyPiece& e){
        throw e;
    }


    return result;
}
/**
 * @brief Creates a shared pointer to a copy of the King piece.
 * This method is used to return a new shared pointer that refers to a
 * copy of the current King object. It allows for polymorphic duplication
 * @return A shared pointer to a new King object.
 */
std::shared_ptr<Piece> King::pieceSharedPtr() const {
    return std::make_shared<King>(*this);
}

