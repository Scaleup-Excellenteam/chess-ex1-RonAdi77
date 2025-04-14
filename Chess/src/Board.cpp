#include "Board.h"
#include "Rook.h"
#include "Bishop.h"
#include "King.h"
#include "Knight.h"
#include "Queen.h"
#include "Pawn.h"

/**
 * @brief Constructs a Board from a string representation.
 * @param strBoard A 64-character string representing the board from A1 to H8.
 */
Board::Board(const std::string& strBoard) {
    stringToBoard(strBoard);
}
/**
 * @brief Copy constructor to create a duplicate of the board.
 * Deep-copies each piece using its pieceSharedPtr function.
 * @param other Board to copy.
 */
Board::Board(const Board & other) {
    for (const auto &pair: other._board) {
        // Clone each piece to avoid shared ownership
        _board[pair.first] = pair.second->pieceSharedPtr();
    }
}
/**
 * @brief Parses a 64-character string into the internal board structure.
 * Uppercase = white, lowercase = black.
 * @param strBoard A linear 8x8 representation of the board state.
 */
void Board::stringToBoard(const std::string& strBoard) {
    if (strBoard.size() != BOARD_SIZE){
        throw std::runtime_error("ERROR: str board size is not 64");
    }
    int index = 0;
    for (char c = FIRST_ROW; c <= LAST_ROW ; c++) {
        for (int i = FIRST_COL; i <= LAST_COL; ++i) {
            Box location = {c,i};
            switch (strBoard[index]) {
                case 'R':_board[location] = std::make_shared<Rook>(location,WHITE);break;
                case 'r':_board[location] = std::make_shared<Rook>(location,BLACK);break;
                case 'N':_board[location] = std::make_shared<Knight>(location,WHITE);break;
                case 'n':_board[location] = std::make_shared<Knight>(location,BLACK);break;
                case 'Q':_board[location] = std::make_shared<Queen>(location,WHITE);break;
                case 'q':_board[location] = std::make_shared<Queen>(location,BLACK);break;
                case 'K':_board[location] = std::make_shared<King>(location,WHITE);break;
                case 'k':_board[location] = std::make_shared<King>(location,BLACK);break;
                case 'B':_board[location] = std::make_shared<Bishop>(location,WHITE);break;
                case 'b':_board[location] = std::make_shared<Bishop>(location,BLACK);break;
                case 'P':_board[location] = std::make_shared<Pawn>(location,WHITE);break;
                case 'p':_board[location] = std::make_shared<Pawn>(location,BLACK);break;
                case '#':break;
                default:throw std::runtime_error("ERROR: error in str board");
            }
            index++;
        }
    }
}

/**
 * @brief Returns the piece at a given box.
 * @param box The location to access.
 * @return A shared pointer to the piece.
 * @throws std::runtime_error if the box is empty.
 */
const std::shared_ptr<Piece>& Board::getPiece(const Box& box) const {
    try {
        return _board.at(box);
    } catch (const std::out_of_range &) {
        throw std::runtime_error("No piece in that box");
    }
}
/**
 * @brief Checks if a given piece is of the same color.
 * @param box The box to check.
 * @param color The color to compare against.
 * @return True if same color, false otherwise.
 */
bool Board::isSameColor(const Box& box, COLOR color) const {
    try{
        return getPiece(box)->getColor() == color;
    }
    catch (std::runtime_error& e){
        throw e;
    }
}
/**
 * @brief Checks if a given box is occupied.
 * @param box The box to check.
 * @return True if a piece exists at the box.
 */
bool Board::isOcuupied(const Box& box) const {
    return _board.find(box) != _board.end();
}
/**
 * @brief Adds a piece to the board.
 * @param piece Shared pointer to the piece to add.
 */
void Board::addPiece(const std::shared_ptr<Piece>& piece) {
    _board[piece->getLocation()] = piece;
}
/**
 * @brief Removes a piece from the board if present.
 * @param box The location to remove from.
 */
void Board::removePiece(const Box & box) {
    if (isOcuupied(box)){
        _board.erase(box);
    }
}
/**
 * @brief Returns the location of the king for a given color.
 * @param color The king’s color.
 * @return The box containing the king.
 */
Box Board::getKingLocation(COLOR color) const {
    for (const auto& [box,piece] : _board){
        if (piece->getType() == KING && piece->getColor() == color){
            return piece->getLocation();
        }
    }
    return {'x',-1};
}
/**
 * @brief Returns all potential moves (after legality filtering) for a color.
 * @param color Color of pieces to scan.
 * @return Set of all valid destination boxes.
 */
std::set<Box> Board::getPiecesPotenMoves(COLOR color)const {
    std::set<Box> result;
    for (const auto& [box,piece] : _board){
        if(_board.at(box)->getColor() == color){
            auto piecePotenMoves = _board.at(box)->getPotentialMoves();
            result.insert(piecePotenMoves.begin(),piecePotenMoves.end());
        }
    }
    return result;
}

/**
 * @brief Returns all raw (unfiltered) moves for all pieces of a color.
 * @param color Color of pieces.
 * @return Set of destination boxes.
 */
std::set<Box> Board::getPiecesRawMoves(COLOR color) const{
    std::set<Box> result;
    for (const auto& [box,piece] : _board){
        if(_board.at(box)->getColor() == color){
            auto piecePotenMoves = _board.at(box)->getRawMoves(*this);
            result.insert(piecePotenMoves.begin(),piecePotenMoves.end());
        }
    }
    return result;
}
/**
 * @brief Checks whether a color is in check.
 * @param color The color to check.
 * @return True if the king is attacked.
 */
bool Board::isCheck(COLOR color) const {
    return getPiecesPotenMoves(colorNot(color)).contains(getKingLocation(color));
}

/**
 * @brief Moves a piece to a destination, updates internal state.
 *
 * Does not check for move legality.
 * @param destination The box to move to.
 * @param piece The piece to move.
 * @return True if move succeeded.
 */
void Board::pieceMove(const Box& destination, const std::shared_ptr<Piece>& piece) {
    Box currentLocation = piece->getLocation();
    piece->setLocation(destination);
    piece->moved();
    addPiece(piece);
    removePiece(currentLocation);
}
/**
 * @brief Updates potential moves for all pieces on the board.
 * Protects kings by marking enemy threats first, then computing moves.
 * @param color The active player's color.
 */
void Board::updatePotenMoves(COLOR color) {
    for (const auto& [box,piece] : _board){
        piece->setIsProtected(true);
    }
    for (const auto& [box,piece] : _board){
        if (piece->getColor() != color){
            piece->updatePotentialMove(*this);
        }
    }
    for (const auto& [box,piece] : _board){
        if (piece->getColor() == color){
            piece->updatePotentialMove(*this);
        }
    }
}













