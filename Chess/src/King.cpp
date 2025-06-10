#include "King.h"

/**
 * @brief Constructs a King object with a given initial position and color.
 * Initializes the king piece by calling the base Piece constructor.
 *
 * @param init Initial position of the king.
 * @param color Color of the king (WHITE or BLACK).
 */
King::King(const Box & init, COLOR color) : Piece(init,KING,color){
    if (color == WHITE){

        _afterKCastleLocation = {'A',7};
        _afterQCastleLocation = {'A',3};
        _middleKCastleLocation = {'A',6};
        _middleQCastleLocation = {'A',4};
    }
    else{
        _afterKCastleLocation = {'H',7};
        _afterQCastleLocation = {'H',3};
        _middleKCastleLocation = {'H',6};
        _middleQCastleLocation = {'H',4};
    }
}

/**
 * @brief Computes all raw moves for the king.
 * The King can move one square in any direction: vertically, horizontally,
 * or diagonally. This function calculates those moves by checking available
 * spaces in each of the eight directions around the king's position.
 * It ensures that moves are within the boundaries of the board and return
 * the valid squares.
 * @param board The current state of the board.
 * @return A vector containing all valid squares the King can move to.
 */
std::vector<Box> King::getRawMoves(const Board & board) {
    std::vector<Box> result;

    try{
        auto moves =  frontFreeBoxes(board, std::make_shared<King>(*this));

        // bishop moves
        moves =  diagFrontRight(board, std::make_shared<King>(*this));
        if (!moves.empty()){
            result.push_back(moves.at(0));
        }
        moves = diagFrontLeft(board,std::make_shared<King>(*this));
        if (!moves.empty()){
            result.push_back(moves.at(0));
        }
        moves = diagBackRight(board,std::make_shared<King>(*this));
        if(!moves.empty()){
            result.push_back(moves.at(0));
        }
        moves = diagBackLeft(board,std::make_shared<King>(*this));
        if(!moves.empty()){
            result.push_back(moves.at(0));
        }

        // rook moves
        if (!moves.empty()){
            result.push_back(moves.at(0));
        }
        moves = backFreeBoxes(board,std::make_shared<King>(*this));
        if (!moves.empty()){
            result.push_back(moves.at(0));
        }
        std::shared_ptr<Piece> kingSideRook;
        std::shared_ptr<Piece> queenSideRook;
        if (getColor() == WHITE){
            kingSideRook = board.algoGetPiece({'A',8});
            queenSideRook = board.algoGetPiece({'A',1});
        }
        else{
            kingSideRook = board.algoGetPiece({'H',8});
            queenSideRook = board.algoGetPiece({'H',1});
        }
        moves = rightFreeBoxes(board,std::make_shared<King>(*this));
        if (!moves.empty()){
            result.push_back(moves.at(0));
            if (!isHasMoved() && kingSideRook != nullptr && !kingSideRook->isHasMoved() && !board.isOccupied(getAfterKCastleLocation())){
                result.push_back(getAfterKCastleLocation());
            }
        }
        moves = leftFreeBoxes(board,std::make_shared<King>(*this));
        if (!moves.empty()){
            result.push_back(moves.at(0));
            if (!isHasMoved() && queenSideRook != nullptr && !queenSideRook->isHasMoved() && !board.isOccupied(getAfterQCastleLocation())){
                result.push_back(getAfterQCastleLocation());
            }
        }


        setPotentialMoves(result);
        // Add castling moves (filtered for checks)
        moves = getPotenCastleMoves(board);
        result.insert(result.end(),moves.begin(),moves.end());
    }
    catch (EmptyPiece& e){
        throw e;
    }


    return result;
}
/**
 * @brief Creates a shared pointer to a copy of the King piece.
 * This method is used to return a new shared pointer that refers to a
 * copy of the current King object. It allows for polymorphic duplication
 * @return A shared pointer to a new King object.
 */
std::shared_ptr<Piece> King::pieceSharedPtr() const {
    return std::make_shared<King>(*this);
}
/**
 * @brief Returns potential castling moves if allowed and not in check.
 *
 * @param board Current board state.
 * @return Vector of potential castling move squares.
 */
std::vector<Box> King::getPotenCastleMoves(const Board & board) {
    std::vector<Box> result;
    if (board.isCheck(getColor())){
        return result;
    }
    if (canCastleK(board)){
        result.push_back(getMiddleKCastleLocation());
//        result.push_back(getAfterKCastleLocation());
    }
    if (canCastleQ(board)){
        result.push_back(getMiddleQCastleLocation());
//        result.push_back(getAfterQCastleLocation());
    }
    return result;
}

const Box &King::getAfterKCastleLocation() const {
    return _afterKCastleLocation;
}

const Box &King::getAfterQCastleLocation() const {
    return _afterQCastleLocation;
}

const Box &King::getMiddleKCastleLocation() const {
    return _middleKCastleLocation;
}

const Box &King::getMiddleQCastleLocation() const {
    return _middleQCastleLocation;
}
/**
 * @brief Checks if kingside castling is possible.
 *
 * @param board Current board state.
 * @return True if kingside castling is allowed.
 */
bool King::canCastleK(const Board & board) {
    std::shared_ptr<Piece> kingSideRook;
    try{
        if (getColor() == WHITE){
            kingSideRook = board.getPiece({'A',8});
        }
        else{
            kingSideRook = board.getPiece({'H',8});
        }

    }
    catch (EmptyPiece& e){
        return false;
    }

    if (isHasMoved() || kingSideRook->isHasMoved()){
        return false;
    }
    std::shared_ptr<Piece> currentKing = pieceSharedPtr();
    Board currentBoard(board);
    std::set<Box> potenMoves = getPotentialMoves();
    if (potenMoves.find(getMiddleKCastleLocation()) != potenMoves.end()){
        currentBoard.pieceMove(getMiddleKCastleLocation(),currentKing);
        if (currentBoard.isCheck(getColor())){
            return false;
        }
        if ( potenMoves.find(getAfterKCastleLocation()) != potenMoves.end()){
            currentBoard.pieceMove(getAfterKCastleLocation(),currentKing);
            return !currentBoard.isCheck(getColor());
        }
    }
    return false;
}
/**
 * @brief Checks if queenside castling is possible.
 *
 * @param board Current board state.
 * @return True if queenside castling is allowed.
 */
bool King::canCastleQ(const Board & board) {
    std::shared_ptr<Piece> queenSideRook;
    try{
        if (getColor() == WHITE){
            queenSideRook = board.getPiece({'A',1});
        }
        else{
            queenSideRook = board.getPiece({'H',1});
        }

    }
    catch (EmptyPiece& e){
        return false;
    }

    if (isHasMoved() || queenSideRook->isHasMoved()){
        return false;
    }
    std::shared_ptr<Piece> currentKing = pieceSharedPtr();
    Board currentBoard(board);
    std::set<Box> potenMoves = getPotentialMoves();
    if (potenMoves.find(getMiddleQCastleLocation()) != potenMoves.end()){
        currentBoard.pieceMove(getMiddleQCastleLocation(),currentKing);
        if (currentBoard.isCheck(getColor())){
            return false;
        }
        std::vector<Box> rookRaw = queenSideRook->getRawMoves(board);
        Box afterAfterCastle = {queenSideRook->getLocation().first,queenSideRook->getLocation().second+1};
        if (potenMoves.find(getAfterQCastleLocation()) != potenMoves.end() && std::find(rookRaw.begin(), rookRaw.end(),afterAfterCastle) != rookRaw.end()){
            currentBoard.pieceMove(getAfterQCastleLocation(),currentKing);
            return !currentBoard.isCheck(getColor());
        }
    }
    return false;
}
/**
 * @brief Returns the character representing the King piece.
 *
 * @return 'K' for white King, 'k' for black King.
 */
char King::toChar() {
    if (getColor() == WHITE){
        return 'K';
    }
    return 'k';
}

