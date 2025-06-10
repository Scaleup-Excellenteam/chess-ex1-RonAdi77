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
    _boardHistory.push_back(copyBoard(_board));
}
/**
 * @brief Copy constructor to create a duplicate of the board.
 * Deep-copies each piece using its pieceSharedPtr function.
 * @param other Board to copy.
 */
Board::Board(const Board & other) {
    _board = copyBoard(other._board);
    for (const auto& historicalBoard : other._boardHistory) {
        _boardHistory.push_back(copyBoard(historicalBoard));
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
 * @throws EmptyPiece if the box is empty.
 */
const std::shared_ptr<Piece>& Board::getPiece(const Box& box) const {
    try {
        return _board.at(box);
    } catch (const std::out_of_range & e) {
        throw EmptyPiece("No piece in that box");

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
    catch (EmptyPiece& e){
        throw e;
    }
}
/**
 * @brief Checks if a given box is occupied.
 * @param box The box to check.
 * @return True if a piece exists at the box.
 */
bool Board::isOccupied(const Box& box) const {
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
    if (isOccupied(box)){
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
 * @return Set of all valid _destination boxes.
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
 * @return Set of _destination boxes.
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
 * @brief Checks whether a color is in mate.
 * @param color The color to check.
 * @return True if the player is in mate.
 */
bool Board::isMate(COLOR color) const {
    return isCheck(color) && getPiecesPotenMoves(color).empty();
}

/**
 * @brief Moves a piece to a _destination, updates internal state.
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
 * @brief Moves a piece to the destination, handling special cases.
 *
 * - Handles castling if the piece is a king.
 * - Handles pawn promotion if applicable.
 * - Otherwise, performs a normal move.
 *
 * Updates board history after the move.
 *
 * @param destination Target square for the move.
 * @param piece The piece to move.
 */
void Board::makeMove(const Box& destination,const std::shared_ptr<Piece>& piece) {
    auto pieceToMove = piece;
    if (piece->getType() == KING){
        auto king = std::dynamic_pointer_cast<King>(piece);
        std::shared_ptr<Piece> kingSideRook;
        std::shared_ptr<Piece> queenSideRook;

        if (king->getColor() == WHITE){
            kingSideRook = algoGetPiece({'A',8});
            queenSideRook = algoGetPiece({'A',1});
        }
        else{
            kingSideRook = algoGetPiece({'H',8});
            queenSideRook = algoGetPiece({'H',1});
        }
        if (king->canCastleK(*this) && destination == king->getAfterKCastleLocation()){
            pieceMove(destination,king);
            pieceMove(king->getMiddleKCastleLocation(),kingSideRook);
        }
        else if (king->canCastleQ(*this) && destination == king->getAfterQCastleLocation()){
            pieceMove(destination,king);
            pieceMove(king->getMiddleQCastleLocation(),queenSideRook);
        }
        else{
            pieceMove(destination,king);
        }

    }
    else if (piece->getType() == PAWN){
        auto pawn = std::dynamic_pointer_cast<Pawn>(piece);
        if (pawn->canPromote() && pawn){
            try{
                pawn->userPromotionChoice(pawn->getLocation());
                pieceToMove = pawn->getPromotedPiece();
                addPiece(pieceToMove);
                pieceMove(destination,pieceToMove);
            }
            catch (WrongPromotionInput& e){
                std::cerr << e.what();
            }
        }
        else{
            pieceMove(destination,pawn);
        }
    }
    else{
        pieceMove(destination,pieceToMove);
    }
    _boardHistory.push_back(copyBoard(_board));
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
/**
 * @brief Retrieves all legal moves for the given color.
 * Iterates through all pieces on the board of the specified color and collects
 * their potential moves into a vector of Move objects. Each move includes
 * a source, destination, and default score (set to 0).
 * @param color The color of the pieces to generate legal moves for (WHITE or BLACK).
 * @return A vector containing all legal moves for the given color.
 */
std::vector<Move> Board::getALLLegalMoves(COLOR color)const{
    std::vector<Move> result;
    for (const auto& [box,piece] : _board){
        if (piece->getColor() != color){
            continue;
        }
        for (auto destination : piece->getPotentialMoves()){
            Move move = {box,destination,0};
            result.push_back(move);
        }
    }
    return result;
}
/**
 * @brief Retrieves a piece from a specific board coordinate.
 * Used primarily in algorithms to safely access a piece. If no piece exists
 * @param box The location on the board to check.
 * @return A const reference to a shared pointer of the piece, or null if none exists.
 */
const std::shared_ptr<Piece> &Board::algoGetPiece(const Box & box) const {
    static const std::shared_ptr<Piece> nullPiece = nullptr;
    auto it = _board.find(box);
    if (it == _board.end()) return nullPiece;
    return it->second;
}
/**
 * @brief Returns all pieces on the board of the given color.
 * @param color The color of pieces to retrieve.
 * @return Vector of shared pointers to pieces of the specified color.
 */
std::vector<std::shared_ptr<Piece>> Board::getPieces(COLOR color) {
     std::vector<std::shared_ptr<Piece>> result;
     for (auto& [box, piece] : _board){
         if ( piece->getColor() == color){
             result.push_back(piece);
         }
     }
    return result;
}
/**
 * @brief Creates a deep copy of the given board state.
 * @param sourceBoard The board state to copy.
 * @return A new map with copied pieces at the same positions.
 */
std::map<Box, std::shared_ptr<Piece>> Board::copyBoard(const std::map<Box, std::shared_ptr<Piece>> &sourceBoard) const {
    std::map<Box, std::shared_ptr<Piece>> result;
    for (const auto& pair : sourceBoard) {
        result[pair.first] = pair.second->pieceSharedPtr(); // Calls the virtual copy method
    }
    return result;
}
/**
 * @brief Checks if the current position has occurred three times (threefold repetition).
 * @return True if a threefold repetition draw can be claimed, false otherwise.
 */
bool Board::isDraw() {
    if (_board.size() == 2){
        return true;
    }
    else if (_board.size() == 3){
        bool isNotKing = false;
        for (auto& [box, piece] : _board){
            if (piece->getType() == BISHOP || piece->getType() == KNIGHT){
                isNotKing = true;
                break;
            }
        }
        return isNotKing;
    }
    return false;
}
/**
 * @brief Checks if the current position has occurred three times (threefold repetition).
 * @return True if a threefold repetition draw can be claimed, false otherwise.
 */
bool Board::isThreeFoldDraw() {
    std::unordered_map<std::string, int> boardCount;

    for (const auto& pastBoard : _boardHistory) {
        std::string boardStr;

        for (char row = FIRST_ROW; row <= LAST_ROW; ++row) {
            for (int col = FIRST_COL; col <= LAST_COL; ++col) {
                Box box = {row, col};
                auto it = pastBoard.find(box);
                if (it != pastBoard.end() && it->second != nullptr) {
                    boardStr += it->second->toChar();
                } else {
                    boardStr += '#';
                }
            }
        }

        boardCount[boardStr]++;
        if (boardCount[boardStr] == 3) {
            return true;
        }
    }

    return false;
}
/**
 * @brief Checks if the player of the given color is in stalemate.
 * @param color The player color to check.
 * @return True if the player is stalemated, false otherwise.
 */
bool Board::isStalemate(COLOR color) const {
    return !isCheck(color) && getPiecesPotenMoves(color).empty();
}
/**
 * @brief Returns a string representation of the current board state.
 * @return String encoding of the board, with pieces represented by characters and empty squares by '#'.
 */
std::string Board::boardToString() const {
    std::string currentBoardState;
    for (char c = FIRST_ROW; c <= LAST_ROW ; c++) {
        for (int i = FIRST_COL; i <= LAST_COL; ++i) {

            Box currentBox = {c,i};
            std::shared_ptr<Piece> p = algoGetPiece(currentBox);
            if (p != nullptr){
                currentBoardState += p->toChar();
            }
            else{
                currentBoardState += '#';
            }
        }
    }
    return currentBoardState;
}




















