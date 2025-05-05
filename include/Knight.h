#pragma once
#include "Piece.h"

/**
 * @class Knight
 * @brief Represents the knight piece in a chess game.
 *
 * The Knight class inherits from the Piece class and provides the specific
 * movement logic for the knight piece. The knight moves in an "L" shape:
 * two squares in one direction (vertical or horizontal) and one square in
 * a perpendicular direction.
 */
class Knight : public Piece{
public:
    /**
    * @brief Constructs a Knight object with a given initial position and color.
    *
    * Initializes the knight piece with the provided starting position
    * and color by calling the base class constructor (Piece).
    *
    * @param init The initial position of the knight.
    * @param color The color of the knight (WHITE or BLACK).
    */
    Knight(const Box&, COLOR);

    /**
    * @brief Computes all raw moves for the knight.
    *
    * The knight moves in an "L" shape: two squares in one direction (horizontal
    * or vertical) and one square in a perpendicular direction. This function
    * calculates the valid squares the knight can move to based on its current position.
    *
    * @param board The current state of the board.
    * @return A vector containing all valid squares the knight can move to.
    */
    std::vector<Box> getRawMoves(const Board&) override;
    /**
    * @brief Creates a shared pointer to a copy of the Knight piece.
    *
    * This method is used to return a new shared pointer that refers to a
    * copy of the current Knight object. It allows for polymorphic duplication
    * of the piece for various game operations.
    *
    * @return A shared pointer to a new Knight object.
    */
    [[nodiscard]] std::shared_ptr<Piece> pieceSharedPtr() const override;

};
