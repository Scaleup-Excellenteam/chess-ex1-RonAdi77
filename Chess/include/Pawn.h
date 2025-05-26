#pragma once
#include "Piece.h"
#include "Move.h"
#include "MyExceptions.h"

class Pawn : public Piece{
public:
    /**
     * @class Pawn
     * @brief A class representing the pawn piece in chess.
     * Inherits from the base Piece class and overrides necessary methods to handle pawn-specific movement.
     */
    Pawn(const Box&, COLOR);

    /**
    * @brief Computes the raw moves that the pawn can make from its current position.
    * Includes diagonal captures, one/two square forward moves, and board boundary logic.
    * @param board The current board state.
    * @return A vector of valid Box positions representing potential raw moves.
    */
    std::vector<Box> getRawMoves(const Board&) override;
    /**
    * @brief Clones the current pawn object and returns it as a shared pointer.
    * @return A shared pointer to the newly created Pawn object.
    */
    [[nodiscard]] std::shared_ptr<Piece> pieceSharedPtr() const override;

    [[nodiscard]] const std::shared_ptr<Piece> &getPromotedPiece() const;
    /**
     * @brief Checks if the pawn has reached a promotion rank and is eligible for promotion.
     * @return true if the pawn can be promoted; false otherwise.
     */
    bool canPromote();
    /**
     * @brief Prompts the user to select a piece type for pawn promotion and sets the promotedPiece accordingly.
     * @param promotionLocation The board location where the pawn is being promoted.
     */
    void userPromotionChoice(const Box&);


private:
    /**
     * @brief Holds a shared pointer to the piece this pawn was promoted to.
     * Null if the pawn has not been promoted.
     */
    std::shared_ptr<Piece> promotedPiece;
};