#include "Move.h"

/**
 * Calculates all the free (or capturable) boxes directly in front of a given piece.
 * The direction of movement depends on the piece's color.
 * @param board The current game board instance.
 * @param piece A shared pointer to the piece whose movement is being evaluated.
 * @return A vector containing all frontward boxes that the piece can move to.
 */
std::vector<Box> frontFreeBoxes(const Board& board,const std::shared_ptr<Piece>& piece){
    bool searchEnd = false;
    int direction;
    try{
        direction = (piece->getColor() == BLACK)? -1 : 1; // black or white piece.
    }
    catch (std::runtime_error& e){
        throw e;
    }
    int moveLength = direction;
    char row = piece->getLocation().first;
    int col = piece->getLocation().second;
    std::vector<Box> result;
    while(!searchEnd){
        Box checkFree = {row+moveLength,col};
        if (!inBoard(checkFree)) break;
        if (!board.isOcuupied(checkFree)){
            result.push_back(checkFree);
        } else{
            //if this box is filled with opposite piece then add the option to eat it , else make this box protected.
            if(!board.isSameColor(checkFree,piece->getColor())){
                result.push_back(checkFree);
            }
            else{
                try{
                    board.getPiece(checkFree)->setIsProtected(true);
                }
                catch (std::runtime_error& e){
                    throw e;
                }

            }
            searchEnd = true;
        }
        moveLength += direction;
        if (piece->getType() == KING){
            searchEnd = true;
        }
    }
    return result;
}
/**
 * Calculates all the free (or capturable) boxes directly behind a given piece.
 * The direction is opposite to the usual forward direction based on color.
 * @param board The current game board instance.
 * @param piece A shared pointer to the piece whose backward movement is being evaluated.
 * @return A vector containing all backward boxes that the piece can move to.
 */
std::vector<Box> backFreeBoxes(const Board& board,const std::shared_ptr<Piece>& piece){
    bool searchEnd = false;
    int direction;
    try {
        direction = (piece->getColor() == BLACK)? 1 : -1; // black or white piece.
    }
    catch (std::runtime_error& e){
        throw e;
    }
    int moveLength = direction;
    char row = piece->getLocation().first;
    int col = piece->getLocation().second;
    std::vector<Box> result;
    while(!searchEnd){
        Box checkFree = {row+moveLength,col};
        if (!inBoard(checkFree)) break;
        if (!board.isOcuupied(checkFree)){
            result.push_back(checkFree);
        } else{
            //if this box is filled with opposite piece then add the option to eat it , else make this box protected.
            if(!board.isSameColor(checkFree,piece->getColor())){
                result.push_back(checkFree);
            }
            else{
                try{
                    board.getPiece(checkFree)->setIsProtected(true);
                }
                catch (std::runtime_error& e){
                    throw e;
                }
            }
            searchEnd = true;
        }
        moveLength += direction;
        if (piece->getType() == KING){
            searchEnd = true;
        }
    }
    return result;
}
/**
 * Calculates all the free (or capturable) boxes to the right of a given piece.
 * @param board The current game board instance.
 * @param piece A shared pointer to the piece being evaluated.
 * @return A vector containing all rightward boxes that the piece can move to.
 */
std::vector<Box> rightFreeBoxes(const Board& board,const std::shared_ptr<Piece>& piece){
    bool searchEnd = false;
    int direction = 1;
    char row = piece->getLocation().first;
    int col = piece->getLocation().second;
    std::vector<Box> result;
    while(!searchEnd){
        Box checkFree = {row,col+direction};
        if (!inBoard(checkFree)) break;
        if (!board.isOcuupied(checkFree)){
            result.push_back(checkFree);
        } else{
            //if this box is filled with opposite piece then add the option to eat it , else make this box protected.
            if(!board.isSameColor(checkFree,piece->getColor())){
                result.push_back(checkFree);
            }
            else{
                try{
                    board.getPiece(checkFree)->setIsProtected(true);
                }
                catch (std::runtime_error& e){
                    throw e;
                }
            }
            searchEnd = true;
        }
        if (piece->getType() == KING){
            searchEnd = true;
        }
        direction++;
    }
    return result;
}
/**
 * Calculates all the free (or capturable) boxes to the left of a given piece.
 * @param board The current game board instance.
 * @param piece A shared pointer to the piece being evaluated.
 * @return A vector containing all leftward boxes that the piece can move to.
 */
std::vector<Box> leftFreeBoxes(const Board& board,const std::shared_ptr<Piece>& piece){
    bool searchEnd = false;
    int direction = -1;
    char row = piece->getLocation().first;
    int col = piece->getLocation().second;
    std::vector<Box> result;
    while(!searchEnd){
        Box checkFree = {row,col+direction};
        if (!inBoard(checkFree)) break;
        if (!board.isOcuupied(checkFree)){
            result.push_back(checkFree);
        } else{
            //if this box is filled with opposite piece then add the option to eat it , else make this box protected.
            if(!board.isSameColor(checkFree,piece->getColor())){
                result.push_back(checkFree);
            }
            else{
                try{
                    board.getPiece(checkFree)->setIsProtected(true);
                }
                catch (std::runtime_error& e){
                    throw e;
                }
            }
            searchEnd = true;
        }
        if (piece->getType() == KING){
            searchEnd = true;
        }
        direction++;
    }
    return result;
}
/**
 * Calculates all the free (or capturable) boxes diagonally front-right of a given piece.
 * @param board The current game board instance.
 * @param piece A shared pointer to the piece being evaluated.
 * @return A vector containing all front-right diagonal boxes the piece can move to.
 */
std::vector<Box> diagFrontRight(const Board& board,const std::shared_ptr<Piece>& piece){
    bool searchEnd = false;
    int rowDirection;
    try {
         rowDirection = -(piece->getColor() == BLACK)? -1 : 1; // black or white piece.;
    }
    catch (std::runtime_error& e){
        throw e;
    }
    int colDirection = -1*rowDirection;
    int rowLength = rowDirection;
    int colLength = colDirection;
    char row = piece->getLocation().first;
    int col = piece->getLocation().second;
    std::vector<Box> result;
    while(!searchEnd){
        Box checkFree = {row+rowLength,col+colLength};
        if (!inBoard(checkFree)) break;
        if (!board.isOcuupied(checkFree)){
            result.push_back(checkFree);
        } else{
            //if this box is filled with opposite piece then add the option to eat it , else make this box protected.
            if(!board.isSameColor(checkFree,piece->getColor())){
                result.push_back(checkFree);
            }
            else{
                try{
                    board.getPiece(checkFree)->setIsProtected(true);
                }
                catch (std::runtime_error& e){
                    throw e;
                }
            }
            searchEnd = true;
        }
        colLength += colDirection;
        rowLength += rowDirection;
        if (piece->getType() == KING){
            searchEnd = true;
        }
    }
    return result;
}
/**
 * Calculates all the free (or capturable) boxes diagonally back-right of a given piece.
 * @param board The current game board instance.
 * @param piece A shared pointer to the piece being evaluated.
 * @return A vector containing all back-right diagonal boxes the piece can move to.
 */
std::vector<Box> diagBackRight(const Board& board,const std::shared_ptr<Piece>& piece){
    bool searchEnd = false;
    int direction;
    try {
         direction = -(piece->getColor() == BLACK)? 1 : -1; // black or white piece.;
    }
    catch (std::runtime_error& e){
        throw e;
    }
    int moveLength = direction;
    char row = piece->getLocation().first;
    int col = piece->getLocation().second;
    std::vector<Box> result;
    while(!searchEnd){
        Box checkFree = {row+moveLength,col+moveLength};
        if (!inBoard(checkFree)) break;
        if (!board.isOcuupied(checkFree)){
            result.push_back(checkFree);
        } else{
            //if this box is filled with opposite piece then add the option to eat it , else make this box protected.
            if(!board.isSameColor(checkFree,piece->getColor())){
                result.push_back(checkFree);
            }
            else{
                try{
                    board.getPiece(checkFree)->setIsProtected(true);
                }
                catch (std::runtime_error& e){
                    throw e;
                }
            }
            searchEnd = true;
        }
        moveLength += direction;
        if (piece->getType() == KING){
            searchEnd = true;
        }
    }
    return result;
}
/**
 * Calculates all the free (or capturable) boxes diagonally front-left of a given piece.
 * @param board The current game board instance.
 * @param piece A shared pointer to the piece being evaluated.
 * @return A vector containing all front-left diagonal boxes the piece can move to.
 */
std::vector<Box> diagFrontLeft(const Board& board,const std::shared_ptr<Piece>& piece){
    bool searchEnd = false;
    int direction;
    try {
         direction = -(piece->getColor() == BLACK)? -1 : 1; // black or white piece.;
    }
    catch (std::runtime_error& e){
        throw e;
    }
    int moveLength = direction;
    char row = piece->getLocation().first;
    int col = piece->getLocation().second;
    std::vector<Box> result;
    while(!searchEnd){
        Box checkFree = {row+moveLength,col+moveLength};
        if (!inBoard(checkFree)) break;
        if (!board.isOcuupied(checkFree)){
            result.push_back(checkFree);
        } else{
            //if this box is filled with opposite piece then add the option to eat it , else make this box protected.
            if(!board.isSameColor(checkFree,piece->getColor())){
                result.push_back(checkFree);
            }
            else{
                try{
                    board.getPiece(checkFree)->setIsProtected(true);
                }
                catch (std::runtime_error& e){
                    throw e;
                }
            }
            searchEnd = true;
        }
        moveLength += direction;
        if (piece->getType() == KING){
            searchEnd = true;
        }
    }
    return result;
}
/**
 * Calculates all the free (or capturable) boxes diagonally back-left of a given piece.
 * @param board The current game board instance.
 * @param piece A shared pointer to the piece being evaluated.
 * @return A vector containing all back-left diagonal boxes the piece can move to.
 */
std::vector<Box> diagBackLeft(const Board& board,const std::shared_ptr<Piece>& piece){
    bool searchEnd = false;
    int rowDirection;
    try{
         rowDirection = -(piece->getColor() == BLACK)? 1 : -1; // black or white piece.;
    }
    catch (std::runtime_error& e){
        throw e;
    }
    int colDirection = -1*rowDirection;
    int rowLength = rowDirection;
    int colLength = colDirection;
    char row = piece->getLocation().first;
    int col = piece->getLocation().second;
    std::vector<Box> result;
    while(!searchEnd){
        Box checkFree = {row+rowLength,col+colLength};
        if (!inBoard(checkFree)) break;
        if (!board.isOcuupied(checkFree)){
            result.push_back(checkFree);
        } else{
            //if this box is filled with opposite piece then add the option to eat it , else make this box protected.
            if(!board.isSameColor(checkFree,piece->getColor())){
                result.push_back(checkFree);
            }
            else{
                try{
                    board.getPiece(checkFree)->setIsProtected(true);
                }
                catch (std::runtime_error& e){
                    throw e;
                }
            }
            searchEnd = true;
        }
        colLength += colDirection;
        rowLength += rowDirection;
        if (piece->getType() == KING){
            searchEnd = true;
        }
    }
    return result;
}
/**
 * Calculates the forward move options (free or capturable) for a knight.
 * Unique to knight due to its L-shaped movement.
 * @param board The current game board instance.
 * @param knight A shared pointer to the knight.
 * @return A vector containing valid forward moves for the knight.
 */
std::vector<Box> frontKnight(const Board& board,const  std::shared_ptr<Knight>& knight){
    std::vector<Box> result;
    char row = knight->getLocation().first;
    int col = knight->getLocation().second;
    int direction;
    try {
         direction = (knight->getColor() == BLACK)? -2 : 2;
    }
    catch (std::runtime_error& e){
        throw e;
    }
    Box checkRight = {row + direction,col + 1};
    Box  checkLeft = {row + direction,col - 1};
    std::vector<Box> help = {checkLeft,checkRight};
    for (Box box : help){
        if (inBoard(box)){
            if (!board.isOcuupied(box)){
                result.push_back(box);
            }
            else{
                if (!board.isSameColor(box,knight->getColor())){
                    result.push_back(box);
                }
                else{
                    try{
                        board.getPiece(box)->setIsProtected(true);
                    }
                    catch (std::runtime_error& e){
                        throw e;
                    }
                }
            }
        }
    }
    return result;
}

/**
 * Calculates the backward move options (free or capturable) for a knight.
 * Unique to knight due to its L-shaped movement.
 * @param board The current game board instance.
 * @param knight A shared pointer to the knight.
 * @return A vector containing valid backward moves for the knight.
 */
std::vector<Box> backKnight(const Board& board,const std::shared_ptr<Knight>& knight){
    std::vector<Box> result;
    char row = knight->getLocation().first;
    int col = knight->getLocation().second;
    int direction;
    try {
         direction = (knight->getColor() == BLACK)? 2 : -2;
    }
    catch (std::runtime_error& e){
        throw e;
    }
    Box checkRight = {row + direction,col + 1};
    Box  checkLeft = {row + direction,col - 1};
    std::vector<Box> help = {checkLeft,checkRight};
    for (Box box : help){
        if (inBoard(box)){
            if (!board.isOcuupied(box)){
                result.push_back(box);
            }
            else{
                if (!board.isSameColor(box,knight->getColor())){
                    result.push_back(box);
                }
                else{
                    try{
                        board.getPiece(box)->setIsProtected(true);
                    }
                    catch (std::runtime_error& e){
                        throw e;
                    }
                }
            }
        }
    }
    return result;
}
/**
 * Calculates the rightward move options (free or capturable) for a knight.
 * Unique to knight due to its L-shaped movement.
 * @param board The current game board instance.
 * @param knight A shared pointer to the knight.
 * @return A vector containing valid rightward moves for the knight.
 */
std::vector<Box> rightKnight(const Board& board, const std::shared_ptr<Knight>& knight){
    std::vector<Box> result;
    char row = knight->getLocation().first;
    int col = knight->getLocation().second;
    int direction;
    try {
         direction = (knight->getColor() == BLACK)? 2 : -2;
    }
    catch (std::runtime_error& e){
        throw e;
    }
    Box checkRight = {row + 1,col + direction};
    Box  checkLeft = {row - 1,col + direction};
    std::vector<Box> help = {checkLeft,checkRight};
    for (Box box : help){
        if (inBoard(box)){
            if (!board.isOcuupied(box)){
                result.push_back(box);
            }
            else{
                if (!board.isSameColor(box,knight->getColor())){
                    result.push_back(box);
                }
                else{
                    try{
                        board.getPiece(box)->setIsProtected(true);
                    }
                    catch (std::runtime_error& e){
                        throw e;
                    }
                }
            }
        }
    }
    return result;
}
/**
 * Calculates the leftward move options (free or capturable) for a knight.
 * Unique to knight due to its L-shaped movement.
 * @param board The current game board instance.
 * @param knight A shared pointer to the knight.
 * @return A vector containing valid leftward moves for the knight.
 */
std::vector<Box> leftKnight(const Board& board, const std::shared_ptr<Knight>& knight){
    std::vector<Box> result;
    char row = knight->getLocation().first;
    int col = knight->getLocation().second;
    int direction;
    try {
         direction = (knight->getColor() == BLACK)? -2 : 2;
    }
    catch (std::runtime_error& e){
        throw e;
    }

    Box checkRight = {row + 1,col + direction};
    Box  checkLeft = {row - 1,col + direction};
    std::vector<Box> help = {checkLeft,checkRight};
    for (Box box : help){
        if (inBoard(box)){
            if (!board.isOcuupied(box)){
                result.push_back(box);
            }
            else{
                if (!board.isSameColor(box,knight->getColor())){
                    result.push_back(box);
                }
                else{
                    try{
                        board.getPiece(box)->setIsProtected(true);
                    }
                    catch (std::runtime_error& e){
                        throw e;
                    }
                }
            }
        }
    }
    return result;
}
/**
 * Parses a string input representing a move (e.g. "E2E4") and converts it into source and destination Box objects.
 * @param input A string of 4 characters where the first two represent the source and the last two the destination.
 * @return A pair of Box objects representing the source and destination positions on the board.
 */
std::pair<Box,Box> stringToBox(const std::string& input){
    Box source = {std::toupper(input[0]),input[1] - '0'};
    Box destination = {std::toupper(input[2]),input[3] - '0'};
    return {source,destination};
}