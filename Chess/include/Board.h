#pragma once
#include "Piece.h"
#include <map>
#include <memory>

/**
* @brief Represents a chess board and its operations.
*
* Manages the current state of the board, piece placement, move validation,
* check/mate detection, and board simulation for move testing.
*/
class Board{
public:
    /**
     * @brief Constructs a Board from a string representation.
     *
     * The string should represent the board from top-left to bottom-right.
     * @param board String of 64 characters representing the board layout.
     */
    explicit Board(const std::string&);
    // copy constructor and assignment , destructor
    Board(const Board&);
    Board& operator=(const Board&) = default;
    ~Board() = default;

    /**
     * @brief Adds a piece to the board at its location.
     * @param piece Shared pointer to the piece to add.
     */
    void addPiece(const std::shared_ptr<Piece>&);
    /**
    * @brief Removes a piece from the specified location.
    * @param location Board coordinate to remove from.
    */
    void removePiece(const Box&);
    /**
     * @brief Returns the location of the king for a given color.
     * @param color The color of the king.
     * @return The box where the king is located.
     */
    [[nodiscard]] Box getKingLocation(COLOR) const;
    /**
     * @brief Returns the piece at the given box.
     * @param location The box to look up.
     * @return Shared pointer to the piece at the given box.
     * @throws std::runtime_error if no piece is found.
     */
    [[nodiscard]] const std::shared_ptr<Piece>& getPiece(const Box&) const;
    /**
    * @brief Gets all valid (post-check-filtered) potential moves for a color.
    * @param color Color of pieces to gather moves for.
    * @return Set of legal destination boxes for all pieces of that color.
    */
    [[nodiscard]] std::set<Box> getPiecesPotenMoves(COLOR) const;
    /**
     * @brief Gets all raw (unfiltered) moves for a color.
     *
     * Includes moves that may result in self-check.
     * @param color Color of the pieces.
     * @return Set of all raw destination boxes.
     */
    [[nodiscard]] std::set<Box> getPiecesRawMoves(COLOR) const;
    /**
    * @brief Checks if a given box contains a piece of the same color.
    * @param location The box to check.
    * @param color The color to compare.
    * @return True if the box is occupied by a piece of the same color.
    */
    [[nodiscard]] bool isSameColor(const Box&, COLOR) const ;
    /**
    * @brief Checks whether a given box is occupied by any piece.
    * @param location The box to check.
    * @return True if a piece exists at that location.
    */
    [[nodiscard]] bool isOcuupied(const Box&) const;
    /**
    * @brief Checks whether a given color is in check.
    * @param color The color to test for check.
    * @return True if that player's king is under attack.
    */
    [[nodiscard]] bool isCheck(COLOR)const;

    /**
    * @brief Moves a piece to a destination, handling capturing.
    * Updates the board and the piece's internal state.
    * @param destination The destination to move to.
    * @param piece The piece to move (shared pointer).
    */
    void pieceMove(const Box&,const std::shared_ptr<Piece>&);
    /**
    * @brief Updates potential moves for all pieces of a given color.
    * Should be called before checking for check or making a move.
    * @param color The color to update moves for.
    */
    void updatePotenMoves(COLOR);

    // This functions for further implementation
    //    [[nodiscard]] bool isMate(COLOR)const;
    //    bool isDraw()const;
    //    bool isThreeFoldDraw()const;
    //    bool isStalemate()const;



private:
    std::map<Box,std::shared_ptr<Piece>> _board;

    /**
    * @brief Helper to parse a string representation of the board.
    * Fills the board map with pieces according to the input string.
    * @param board String of 64 characters representing piece layout.
    */
    void stringToBoard(const std::string& board);
};
