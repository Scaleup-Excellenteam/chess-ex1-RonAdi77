#pragma one
#include "Piece.h"
#include "Move.h"

/**
 * @class King
 * @brief Represents a King chess piece.
 * Inherits from the Piece class. Implements logic specific to the king,
 * such as computing its raw (non-check-filtered) moves, including one-step
 * moves in all directions.
 */
class King : public Piece{
public:
    /**
     * @brief Constructs a King object with a given starting location and color.
     *
     * @param init The initial position of the king.
     * @param color The color of the king (WHITE or BLACK).
     */
    King(const Box&, COLOR);

    /**
    * @brief Gets all raw moves for the king.
    * Returns all possible one-step moves (not filtered for checks).
    * @param board The current state of the board.
    * @return A vector of potential move positions.
    */
    std::vector<Box> getRawMoves(const Board&) override;
    /**
   * @brief Creates a shared pointer to a copy of the king.
   * Used for polymorphic duplication of the king piece.
   * @return A shared pointer to a new King object.
   */
    [[nodiscard]] std::shared_ptr<Piece> pieceSharedPtr() const override;
};