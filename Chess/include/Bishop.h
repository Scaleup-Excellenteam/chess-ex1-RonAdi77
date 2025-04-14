#pragma one
#include "Piece.h"
#include "Move.h"

/**
 * @class Bishop
 * @brief Represents a bishop piece on the chess board.
 * The bishop moves diagonally in all directions. Inherits from the Piece base class.
 */

class Bishop : public Piece{
public:
    /**
     * @brief Constructs a Bishop at a given location and color.
     * @param location The initial position of the bishop.
     * @param color The color of the bishop (WHITE or BLACK).
     */
    Bishop(const Box&, COLOR);

    /**
    * @brief Returns all raw diagonal moves for the bishop (not filtered for checks).
    * @param board The current board state.
    * @return A vector of Box positions that the bishop can move to.
    */
    std::vector<Box> getRawMoves(const Board&) override;
    /**
     * @brief Returns a shared pointer to a deep-copied bishop.
     * @return A std::shared_ptr pointing to a new Bishop with the same data.
     */
    [[nodiscard]] std::shared_ptr<Piece> pieceSharedPtr() const override;
};