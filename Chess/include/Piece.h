#pragma once
#include "Common.h"
#include <set>
#include <vector>
#include <memory>


class Board;
/**
 * @class Piece
 * @brief Abstract base class representing a chess piece.
 * This class provides the common interface and shared functionality
 * for all specific chess pieces (e.g., Pawn, Knight, etc.).
 */
class Piece{
public:
    /**
     * @brief Constructor for Piece.
     * @param initLocation The initial position of the piece.
     * @param type The type of the piece (KING, QUEEN, etc.).
     * @param color The color of the piece (WHITE or BLACK).
     */
    Piece(Box , TYPE, COLOR);


    // getters & setters
    [[nodiscard]] const Box &getLocation() const;
    void setLocation(const Box &);
    [[nodiscard]] TYPE getType() const;
    [[nodiscard]] COLOR getColor() const;
    [[nodiscard]] bool isHasMoved() const;
    void moved();
    [[nodiscard]] bool isIsProtected() const;
    void setIsProtected(bool);
    [[nodiscard]] const std::set<Box> &getPotentialMoves() const;

    /**
     * @brief Checks whether a given move is in the potential moves list.
     * @param destination The destination box.
     * @return True if move is valid, false otherwise.
     */
    bool isValidMove(const Box&,const Board&);

    /**
    * @brief Removes any potential moves that would leave own king in check.
    * @param board The current board state.
    * @return Vector of legal moves.
    */
    std::vector<Box> removeOwnCheck(const Board&);

    /**
     * @brief Adds a vector of new potential moves to the piece.
     * @param moves The moves to add.
     */
    void addMoves(std::vector<Box>);

    /// Clears the potential move list
    void clearMoves();

    /**
     * @brief Updates potential moves for the piece based on current board state.
     * @param board The current board state.
     */
    void updatePotentialMove(const Board&);

    /**
    * @brief Checks whether the move results in self-check.
    * @param destination The intended destination.
    * @param board The board to simulate the move on.
    * @return True if the move leaves the king in check.
    */
    [[nodiscard]] bool ownCheck(const Box&,const Board&) const ;

    /**
   * @brief Returns a shared pointer to this piece.
   * @return Shared pointer to this piece.
   */
    [[nodiscard]] virtual std::shared_ptr<Piece> pieceSharedPtr() const = 0;

    /**
     * @brief Returns all possible raw moves (including illegal ones) based on movement rules.
     * @param board The current board state.
     * @return Vector of candidate move destinations.
     */
    virtual std::vector<Box> getRawMoves(const Board&) = 0;

private:
    Box _location;                 ///< Current location of the piece
    TYPE _type;                    ///< Type of the piece
    COLOR _color;                  ///< Color of the piece
    std::set<Box> _potential_moves;///< Set of potential moves
    bool _hasMoved;                ///< Whether the piece has moved
    bool _isProtected;             ///< Whether the piece is protected by another from eating
};
