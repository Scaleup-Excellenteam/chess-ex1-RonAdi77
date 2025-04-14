#pragma once
#include "Piece.h"
#include "Move.h"


/**
 * @class Queen
 * @brief Represents a queen piece in the game of chess.
 * Inherits from the Piece class and provides specific implementations
 * for queen movement, copying, and cloning.
 */
class Queen : public Piece{
public:
    /**
     * @brief Constructs a Queen object with a position and color.
     * @param box The initial position of the queen on the board.
     * @param color The color of the queen (WHITE or BLACK).
     */
    Queen(const Box&, COLOR);

    /**
     * @brief Returns all raw possible moves of the queen based on the current board state.
     * Combines the movement abilities of both the rook and bishop.
     * @param board The current state of the board.
     * @return A vector of potential destination boxes.
     */

    std::vector<Box> getRawMoves(const Board&) override;
    /**
     * @brief Clones the queen as a shared pointer.
     * Useful for deep copying board states.
     * @return A shared pointer to a copy of the current queen.
     */
    [[nodiscard]] std::shared_ptr<Piece> pieceSharedPtr() const override;

};
