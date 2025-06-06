#pragma one
#include "Piece.h"
#include "Move.h"
#include <set>

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
    /**
     * @brief Gets potential castling moves for the King.
     *
     * @param board Current state of the board.
     * @return Vector of potential castling move positions.
     */
    std::vector<Box> getPotenCastleMoves(const Board&);

    /**
     * @brief Checks if the King can castle kingside.
     *
     * @param board Current state of the board.
     * @return True if kingside castling is possible, false otherwise.
     */
    bool canCastleK(const Board&);
    /**
     * @brief Checks if the King can castle queenside.
     *
     * @param board Current state of the board.
     * @return True if queenside castling is possible, false otherwise.
     */
    bool canCastleQ(const Board&);
    /**
     * @brief Gets the King's position after kingside castling.
     *
     * @return Box representing the King's final position after kingside castle.
     */
    [[nodiscard]] const Box &getAfterKCastleLocation() const;
    /**
     * @brief Gets the King's position after queenside castling.
     *
     * @return Box representing the King's final position after queenside castle.
     */
    [[nodiscard]] const Box &getAfterQCastleLocation() const;
    /**
     * @brief Gets the intermediate square the King crosses during kingside castling.
     *
     * @return Box representing the square between the King's start and end squares during kingside castle.
     */
    [[nodiscard]] const Box &getMiddleKCastleLocation() const;
    /**
     * @brief Gets the intermediate square the King crosses during queenside castling.
     *
     * @return Box representing the square between the King's start and end squares during queenside castle.
     */
    [[nodiscard]] const Box &getMiddleQCastleLocation() const;
    /**
     * @brief Returns the character representation of the King piece.
     *
     * @return Character representing the King (e.g., 'K' or 'k').
     */
    char toChar() override;

private:
    Box _afterKCastleLocation;
    Box _afterQCastleLocation;
    Box _middleKCastleLocation;
    Box _middleQCastleLocation;
};