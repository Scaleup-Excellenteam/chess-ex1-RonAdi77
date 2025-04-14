#pragma one
#include "Piece.h"

#include <utility>
#include "Board.h"

/**
 * @brief Constructor for the Piece class.
 * @param init Initial location of the piece.
 * @param type Type of the piece (e.g., KING, PAWN).
 * @param color Color of the piece (WHITE or BLACK).
 */
Piece::Piece(Box  init,  TYPE type, COLOR color):  _location(std::move(init)), _type(type), _color(color)
, _hasMoved(false), _isProtected(false){}


const Box &Piece::getLocation() const {
    return _location;
}

void Piece::setLocation(const Box &location) {
    _location = location;
}

TYPE Piece::getType() const {
    return _type;
}

COLOR Piece::getColor() const {
    return _color;
}

bool Piece::isHasMoved() const {
    return _hasMoved;
}

void Piece::moved() {
    _hasMoved = true;
}

bool Piece::isIsProtected() const {
    return _isProtected;
}

void Piece::setIsProtected(bool isProtected) {
    _isProtected = isProtected;
}

const std::set<Box> &Piece::getPotentialMoves() const {
    return _potential_moves;
}

void Piece::clearMoves() {
    _potential_moves.clear();
}
/**
 * @brief Adds new moves to the potential moves set.
 * @param moves A vector of new move destinations.
 */
void Piece::addMoves(std::vector<Box> moves) {
    if(getType() == KING){
        clearMoves();
    }
    _potential_moves.insert(moves.begin(),moves.end());
}
/**
 * @brief Checks if a given move is valid.
 * @param box Destination box to check.
 * @return True if box is in raw moves.
 */
bool Piece::isValidMove(const Box& box,const Board& board) {
    std::vector<Box> rawMoves = getRawMoves(board);
    for (auto move : rawMoves){
        if (move == box){
            return true;
        }
    }
    return false;
}
/**
 * @brief Updates the potential moves based on the current board state.
 * Calls `removeOwnCheck()` to avoid moves that put the king in check.
 * @param board The current board state.
 */
void Piece::updatePotentialMove(const Board & board) {
    clearMoves();
    addMoves(removeOwnCheck(board));
}
/**
 * @brief Filters out any moves that result in own king being in check.
 * @param board The current board state.
 * @return Vector of legal moves that do not leave king in check.
 */
std::vector<Box> Piece::removeOwnCheck(const Board & board) {
    std::vector<Box> result = getRawMoves(board);

    for (auto it = result.begin(); it != result.end();){
        Box currentMove = *it;
        Board currentBoard(board);
        try{
            if(currentBoard.isOcuupied(currentMove) && getType() == KING && board.getPiece(currentMove)->isIsProtected()){
                it = result.erase(it);
                continue;
            }
        }
        catch (std::runtime_error& e){
            throw e;
        }

        currentBoard.pieceMove(currentMove, pieceSharedPtr());
        std::set<Box> temp = currentBoard.getPiecesRawMoves(colorNot(getColor()));
        if (temp.find(currentBoard.getKingLocation(getColor())) != temp.end()){
            it = result.erase(it);
        }
        else{
            ++it;
        }
    }
    return result;
}

/**
 * @brief Checks whether moving to a specific box results in own check.
 * @param  Destination box to simulate.
 * @param board The current board.
 * @return True if move results in check.
 */
bool Piece::ownCheck(const Box& destination,const Board& board) const  {
    Board currentBoard(board);

    currentBoard.pieceMove(destination, pieceSharedPtr());
    std::set<Box> opponentMoves = currentBoard.getPiecesRawMoves(colorNot(getColor()));
    Box kingLocation = currentBoard.getKingLocation(getColor());

    return opponentMoves.find(kingLocation) != opponentMoves.end();

}






