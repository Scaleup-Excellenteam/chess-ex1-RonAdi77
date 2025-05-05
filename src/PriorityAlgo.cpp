#include "PriorityAlgo.h"
#include <climits>

/**
 * @brief Returns a static score for a piece type.
 * @param type The piece type (KING, QUEEN, etc.).
 * @return The predefined score for that type.
 */
int pieceScore(TYPE type){
    switch (type){
        case KING:
            return 100;
        case QUEEN:
            return 90;
        case ROOK:
            return 50;
        case KNIGHT:
        case BISHOP:
            return 30;
        case PAWN:
            return 10;
        default:
            return 0;
    }
}
/**
 * @brief Calculates the threat to a weak piece from enemy pieces with lower value.
 * @param color The color of the piece being evaluated.
 * @param box The position of the evaluated piece.
 * @param board The board state.
 * @return Total score from threats by weaker enemy pieces.
 */
int getScoreDangerWeakPiece(COLOR color, const Box & box,  Board & board) {
    int result = 0;
    board.updatePotenMoves(colorNot(color));
    int currentPieceScore = pieceScore(board.algoGetPiece(box)->getType());

    for (char c = FIRST_ROW ; c <= LAST_ROW ; c++){
        for (int i = FIRST_COL; i <= LAST_COL; ++i) {
            auto piece = board.algoGetPiece({c,i});
            if (piece == nullptr){ continue;}
            auto potentialMoves = piece->getPotentialMoves();
            int score = pieceScore(piece->getType());
            if (potentialMoves.find(box) != potentialMoves.end() && piece->getColor() != color && score < currentPieceScore){
                result += score;
            }
        }
    }
    return result;
}
/**
 * @brief Calculates how much the current piece threatens stronger enemy pieces.
 * @param color The color of the evaluated piece.
 * @param box The position of the evaluating piece.
 * @param board The board state.
 * @return Total score from threats on stronger pieces.
 */
int getScoreThreatStrongPiece(COLOR color, const Box & box,  Board & board) {
    int result = 0;
    board.updatePotenMoves(color);
    int currentPieceScore = pieceScore(board.algoGetPiece(box)->getType());
    auto potentialMoves = board.algoGetPiece(box)->getPotentialMoves();

    for (const auto& potenBox : potentialMoves){
        const auto& piece = board.algoGetPiece(potenBox);
        if (piece == nullptr){ continue;}
        int score = pieceScore(piece->getType());
        if (currentPieceScore < score){
            result += score;
        }
    }
    return result;
}
/**
 * @brief Top-level minimax driver. Evaluates all legal moves and pushes top 5 into a priority queue.
 * @param depth How many layers to search in the game tree.
 * @param color The color whose move it is.
 * @param board The current board state.
 * @return A priority queue of the 5 highest scored moves.
 */
PriorityQueue<Move> miniMaxMain(int depth, COLOR color, Board& board) {
    PriorityQueue<Move> priorityQueue;
    auto legalMoves = board.getALLLegalMoves(color);

    for(auto move : legalMoves){

        auto dest = board.algoGetPiece(move._destination);
        if (dest){
            dest = dest->pieceSharedPtr();
        }
        auto source = board.algoGetPiece(move._source)->pieceSharedPtr();
        move._score = miniMax(depth, move, board, color, color, INT_MIN, INT_MAX);
        undoMove(move,board,source,dest);
        priorityQueue.push(move);
    }

    return priorityQueue;

}
/**
 * @brief Recursively scores a move using the minimax algorithm with alpha-beta pruning.
 * @param depth Remaining search depth.
 * @param move The current move being evaluated.
 * @param board The board state.
 * @param maximizing The color that wants to maximize its score.
 * @param currentColor Whose turn it is to move.
 * @param alpha Best value the maximizer can guarantee.
 * @param beta Best value the minimizer can guarantee.
 * @return The evaluated score of the move.
 */
int miniMax(int depth, Move move, Board &board, COLOR maximizing, COLOR currentColor, int alpha, int beta) {
    if (depth <= 0) return move._score;

    auto& sourcePiece = board.algoGetPiece(move._source);
    auto& destPiece = board.algoGetPiece(move._destination);
    auto movingPiece = board.getPiece(move._source);
    auto potenMoves = board.getPiecesPotenMoves(currentColor);
    int totalCoverBefore = static_cast<int>(potenMoves.size());
    int beforeMoveCenterCover = calculateControlMiddle(potenMoves);
    board.pieceMove(move._destination, sourcePiece);

    // Evaluate move
    if (currentColor == maximizing) {
        if (destPiece) move._score += pieceScore(destPiece->getType());
        move._score += getScoreThreatStrongPiece(currentColor, move._destination, board);
        move._score -= getScoreDangerWeakPiece(currentColor, move._destination, board);
        if (board.isMate(colorNot(currentColor))){
            move._score += MATE_SCORE;
        }
        // Bonus - control the middle and cover boxes
        potenMoves.insert(movingPiece->getPotentialMoves().begin() , movingPiece->getPotentialMoves().end());
        int totalCoverAfter = static_cast<int>(potenMoves.size());
        if (totalCoverAfter - totalCoverBefore > 0){
            move._score += TOTAL_SCORE * (totalCoverAfter - totalCoverBefore);
        }
        int afterMoveCenterCover = calculateControlMiddle(potenMoves);
        if(afterMoveCenterCover - beforeMoveCenterCover > 0){
            move._score += MIDDLE_SCORE * (afterMoveCenterCover - beforeMoveCenterCover);
        }

    } else {
        if (destPiece) move._score -= pieceScore(destPiece->getType());
        move._score -= getScoreThreatStrongPiece(currentColor, move._destination, board);
        move._score += getScoreDangerWeakPiece(currentColor, move._destination, board);
        if (board.isMate(colorNot(currentColor))){
            move._score -= MATE_SCORE;
        }
        // Bonus - control the middle and cover boxes
        potenMoves.insert(movingPiece->getPotentialMoves().begin() , movingPiece->getPotentialMoves().end());
        int totalCoverAfter = static_cast<int>(potenMoves.size());
        if (totalCoverAfter - totalCoverBefore > 0){
            move._score -= TOTAL_SCORE * (totalCoverAfter - totalCoverBefore);
        }
        int afterMoveCenterCover = calculateControlMiddle(potenMoves);
        if(afterMoveCenterCover - beforeMoveCenterCover > 0){
            move._score -= MIDDLE_SCORE * (afterMoveCenterCover - beforeMoveCenterCover);
        }
    }

    // Next recursive step
    currentColor = colorNot(currentColor);
    auto legalMoves = board.getALLLegalMoves(currentColor);

    if (legalMoves.empty()) return move._score;

    int bestScore = (currentColor == maximizing) ? INT_MIN : INT_MAX;

    for (auto& nextMove : legalMoves) {
        auto dest = board.algoGetPiece(nextMove._destination);
        if (dest){
            dest = dest->pieceSharedPtr();
        }
        auto source = board.algoGetPiece(nextMove._source)->pieceSharedPtr();
        int score = miniMax(depth - 1, nextMove, board, maximizing, currentColor, alpha, beta);
        undoMove(nextMove,board,source,dest);
        if (currentColor == maximizing) {
            bestScore = std::max(bestScore, score);
            alpha = std::max(alpha, bestScore);
        } else {
            bestScore = std::min(bestScore, score);
            beta = std::min(beta, bestScore);
        }
        if (beta <= alpha) break; 
    }
    return move._score + bestScore;
}
/**
 * @brief Restores the board to its state before a move.
 * @param move The move to undo.
 * @param board The board to revert.
 * @param sourcePiece The original piece at source.
 * @param destPiece The original piece at destination, if any.
 */
void undoMove(Move move , Board &board , const std::shared_ptr<Piece> & sourcePiece, const std::shared_ptr<Piece> & destPiece) {
    board.addPiece(sourcePiece);
    board.removePiece(move._destination);
    if (destPiece){
        board.addPiece(destPiece);
    }
}
/**
 * @brief Checks if a box is in the center 4x4 area of the board.
 * @param box The coordinate to evaluate.
 * @return true if the box is within the central area.
 */
bool isControlMiddle(const Box & box) {
    return (UP_ROW_MIDDLE <= box.first && box.first <= DOWN_ROW_MIDDLE && LEFT_COL_MIDDLE <= box.second && box.second <= RIGHT_COL_MIDDLE);
}
/**
 * @brief Counts how many boxes in a set are in the center.
 * @param set The set of boxes to evaluate.
 * @return The number of central positions.
 */
int calculateControlMiddle(const std::set<Box>& set) {
    int result = 0;
    for(auto coord : set){
        if(isControlMiddle(coord))result++;
    }
    return result;
}
