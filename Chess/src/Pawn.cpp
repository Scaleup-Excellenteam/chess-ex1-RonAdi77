#include "Pawn.h"

/**
 * @brief Constructor for a Pawn.
 * Initializes a pawn with a given position and color.
 * @param init The initial box location of the pawn.
 * @param color The color of the pawn (WHITE or BLACK).
 */
Pawn::Pawn(const Box& init , COLOR color): Piece(init,PAWN,color){}

/**
 * @brief Calculates the raw legal moves available to a pawn from its current position.
 * The moves include:
 * - One square forward if unoccupied.
 * - Two squares forward if it's the pawn's first move and both squares are unoccupied.
 * - Diagonal captures (front-left and front-right) if an opposing piece is present.
 * @param board The current board state, used to evaluate move legality.
 * @return A vector containing all possible raw move destinations for the pawn.
 */
std::vector<Box> Pawn::getRawMoves(const Board & board) {
    std::vector<Box> result;
    try{
        std::vector<Box> front =  frontFreeBoxes(board, std::make_shared<Pawn>(*this));
        // Handle forward movement
        if (!isHasMoved()){
            if (!front.empty()){
                if (!board.isOcuupied(front.at(0))){
                    result.push_back(front.at(0));
                }
            }
            if (front.size() > 1){
                if (!board.isOcuupied(front.at(1))){
                    result.push_back(front.at(1));
                }
            }
        }
        else{
            if (!front.empty()){
                if (!board.isOcuupied(front.at(0))){
                    result.push_back(front.at(0));
                }
            }
        }
        // Handle diagonal captures
        std::vector<Box> frontRight =  diagFrontRight(board, std::make_shared<Pawn>(*this));
        if (!frontRight.empty()){
            if (board.isOcuupied(frontRight.at(0))){
                try{
                    if (board.getPiece(frontRight.at(0))->getColor() != getColor()){
                        result.push_back(frontRight.at(0));
                    }
                }
                catch (std::runtime_error& e){
                    throw e;
                }
            }
        }
        std::vector<Box> frontLeft = diagFrontLeft(board,std::make_shared<Pawn>(*this));
        if (!frontLeft.empty()){
            if (board.isOcuupied(frontLeft.at(0))){
                try{
                    if (board.getPiece(frontLeft.at(0))->getColor() != getColor()){
                        result.push_back(frontLeft.at(0));
                    }
                }
                catch (std::runtime_error& e){
                    throw e;
                }
            }
        }
    }

    catch (std::runtime_error& e) {
        throw e;
    }

    return result;
}

/**
 * @brief Clones the current pawn as a shared pointer to a new Pawn object.
 * Used for duplication, typically in board copies or simulation.
 * @return A shared pointer to a copy of the current pawn.
 */
std::shared_ptr<Piece> Pawn::pieceSharedPtr() const {
    return std::make_shared<Pawn>(*this);
}


