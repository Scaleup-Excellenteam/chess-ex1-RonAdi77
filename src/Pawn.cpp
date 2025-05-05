#include "Pawn.h"
#include "Queen.h"
#include "Knight.h"
#include "Rook.h"
#include "Bishop.h"

/**
 * @brief Constructor for a Pawn.
 * Initializes a pawn with a given position and color.
 * @param init The initial box location of the pawn.
 * @param color The color of the pawn (WHITE or BLACK).
 */
Pawn::Pawn(const Box& init , COLOR color): Piece(init,PAWN,color),promotedPiece(nullptr){}

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
        auto front =  frontFreeBoxes(board, std::make_shared<Pawn>(*this));
        // Handle forward movement
        if (!isHasMoved()){
            if (!front.empty()){
                if (!board.isOccupied(front.at(0))){
                    result.push_back(front.at(0));
                }
            }
            if (front.size() > 1){
                if (!board.isOccupied(front.at(1))){
                    result.push_back(front.at(1));
                }
            }
        }
        else{
            if (!front.empty()){
                if (!board.isOccupied(front.at(0))){
                    result.push_back(front.at(0));
                }
            }
        }
        // Handle diagonal captures
        auto frontRight =  diagFrontRight(board, std::make_shared<Pawn>(*this));
        if (!frontRight.empty()){
            if (board.isOccupied(frontRight.at(0))){
                try{
                    if (board.getPiece(frontRight.at(0))->getColor() != getColor()){
                        result.push_back(frontRight.at(0));
                    }
                }
                catch (EmptyPiece& e){
                    throw e;
                }
            }
        }
        auto frontLeft = diagFrontLeft(board,std::make_shared<Pawn>(*this));
        if (!frontLeft.empty()){
            if (board.isOccupied(frontLeft.at(0))){
                try{
                    if (board.getPiece(frontLeft.at(0))->getColor() != getColor()){
                        result.push_back(frontLeft.at(0));
                    }
                }
                catch (EmptyPiece& e){
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

/**
 * @brief Gets the piece this pawn was promoted to, if any.
 * @return Shared pointer to the promoted piece, or nullptr if not promoted.
 */
const std::shared_ptr<Piece> &Pawn::getPromotedPiece() const {
    return promotedPiece;
}
/**
 * @brief Handles user input to choose the promotion type when a pawn reaches the last rank.
 * Displays a menu for the player to select between Queen, Rook, Bishop, or Knight.
 * Throws WrongPromotionInput exception on invalid input.
 * Throws runtime_error if promotion creation fails.
 * @param promotionLocation The board location where the pawn is being promoted.
 */
void Pawn::userPromotionChoice(const Box & promotionLocation) {
    bool correctInput = false;
    std::string choice;

    while (!correctInput) {
        std::cout << "This pawn can be promoted, choose promotion type:\n";
        std::cout << "Press (1) for Queen.\n";
        std::cout << "Press (2) for Rook.\n";
        std::cout << "Press (3) for Bishop.\n";
        std::cout << "Press (4) for Knight.\n";
        std::cin >> choice;

        if (choice == "1") {
            promotedPiece = std::make_shared<Queen>(promotionLocation,  getColor());
            correctInput = true;
        } else if (choice == "2") {
            promotedPiece = std::make_shared<Rook>(promotionLocation,getColor());
            correctInput = true;
        } else if (choice == "3") {
            promotedPiece = std::make_shared<Bishop>(promotionLocation, getColor());
            correctInput = true;
        } else if (choice == "4") {
            promotedPiece = std::make_shared<Knight>(promotionLocation, getColor());
            correctInput = true;
        } else {
            throw WrongPromotionInput("Invalid input\n");
        }
    }

    if (!promotedPiece) {
        throw std::runtime_error("Promotion failed: piece is null.");
    }

}
/**
 * @brief Checks if the pawn has reached a rank where promotion is possible.
 * For white, checks if the next move would land on the last row.
 * For black, checks if the next move would land on the first row.
 * @return true if the pawn can be promoted on the next move.
 */
bool Pawn::canPromote() {
    if (getColor() == WHITE){
        return  static_cast<char>(getLocation().first + 1) == LAST_ROW;
    }
    else{
        return static_cast<char>(getLocation().first - 1) == FIRST_ROW;
    }
}



