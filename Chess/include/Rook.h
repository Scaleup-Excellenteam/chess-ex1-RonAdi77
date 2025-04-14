#pragma once
#include "Piece.h"
#include "Move.h"

/**
 * @class Rook
 * @brief Represents a Rook piece in a chess game.
 *
 * The Rook moves in straight lines: vertically or horizontally any number of squares.
 */

class Rook : public Piece{
public:
    /**
    * @brief Constructs a Rook at the given position with the specified color.
    *
    * @param box The initial position of the Rook.
    * @param color The color of the Rook (WHITE or BLACK).
    */
    Rook(const Box&, COLOR);


    /**
     * @brief Returns all potential raw moves for this Rook.
     * This includes all horizontally and vertically reachable positions on the board,
     * regardless of check or threat conditions.
     * @param board The current state of the board.
     * @return A vector of Box objects representing the Rook's possible destinations.
     */
    std::vector<Box> getRawMoves(const Board&) override;

    /**
     * @brief Returns a shared pointer to a clone of this Rook.
     * @return A shared_ptr containing a copy of this Rook.
     */
    [[nodiscard]] std::shared_ptr<Piece> pieceSharedPtr() const override;


};