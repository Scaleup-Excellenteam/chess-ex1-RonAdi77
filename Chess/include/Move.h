#pragma once

#include "Knight.h"
#include "Board.h"

/**
 * @file Move.h
 * @brief Declares movement-related utility functions for pieces on a chess board.
 *
 * This header provides directional movement calculations for various pieces,
 * including front, back, side, and diagonal moves. It also includes knight-specific
 * L-shaped movements and a utility to convert string-based move inputs into board positions.
 */

/**
 * @brief Calculates all free or capturable boxes directly in front of a piece.
 */
std::vector<Box> frontFreeBoxes(const Board&, const std::shared_ptr<Piece>&);

/**
 * @brief Calculates all free or capturable boxes directly behind a piece.
 */
std::vector<Box> backFreeBoxes(const Board&, const std::shared_ptr<Piece>&);

/**
 * @brief Calculates all free or capturable boxes to the right of a piece.
 */
std::vector<Box> rightFreeBoxes(const Board&, const std::shared_ptr<Piece>&);

/**
 * @brief Calculates all free or capturable boxes to the left of a piece.
 */
std::vector<Box> leftFreeBoxes(const Board&, const std::shared_ptr<Piece>&);

/**
 * @brief Calculates all free or capturable boxes diagonally front-right of a piece.
 */
std::vector<Box> diagFrontRight(const Board&, const std::shared_ptr<Piece>&);

/**
 * @brief Calculates all free or capturable boxes diagonally back-right of a piece.
 */
std::vector<Box> diagBackRight(const Board&, const std::shared_ptr<Piece>&);

/**
 * @brief Calculates all free or capturable boxes diagonally front-left of a piece.
 */
std::vector<Box> diagFrontLeft(const Board&, const std::shared_ptr<Piece>&);

/**
 * @brief Calculates all free or capturable boxes diagonally back-left of a piece.
 */
std::vector<Box> diagBackLeft(const Board&, const std::shared_ptr<Piece>&);

/**
 * @brief Calculates knight's valid L-shaped moves in the forward direction.
 */
std::vector<Box> frontKnight(const Board&, const std::shared_ptr<Knight>&);

/**
 * @brief Calculates knight's valid L-shaped moves in the backward direction.
 */
std::vector<Box> backKnight(const Board&, const std::shared_ptr<Knight>&);

/**
 * @brief Calculates knight's valid L-shaped moves to the right.
 */
std::vector<Box> rightKnight(const Board&, const std::shared_ptr<Knight>&);

/**
 * @brief Calculates knight's valid L-shaped moves to the left.
 */
std::vector<Box> leftKnight(const Board&, const std::shared_ptr<Knight>&);

/**
 * @brief Converts a move string (e.g., "E2E4") into a pair of Box positions.
 */
std::pair<Box, Box> stringToBox(const std::string&);
