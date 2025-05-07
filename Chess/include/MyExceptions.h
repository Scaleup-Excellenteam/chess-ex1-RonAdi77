#pragma once
#include <iostream>
#include <utility>

/**
 * @class WrongPromotionInput
 * @brief Exception thrown when an invalid input is provided for pawn promotion.
 *
 * Inherits from std::exception and stores an explanatory message.
 */
class WrongPromotionInput : public std::exception {
public:
    /**
     * @brief Constructs a WrongPromotionInput exception with a specific error message.
     * @param msg The error message to be associated with this exception.
     */
    explicit WrongPromotionInput(std::string  msg) : _message(std::move(msg)){}
    /**
     * @brief Returns the error message describing the cause of the exception.
     * @return A C-style string containing the error message.
     */
    [[nodiscard]] const char* what() const noexcept override {
        return _message.c_str();
    }

private:
    std::string _message;
};

/**
 * @class EmptyPiece
 * @brief Exception thrown when an operation is attempted on an empty or null piece.
 *
 * Inherits from std::exception and stores an explanatory message.
 */
class EmptyPiece : public std::exception {
public:
    /**
     * @brief Constructs an EmptyPiece exception with a specific error message.
     * @param msg The error message to be associated with this exception.
     */
    explicit EmptyPiece(std::string  msg) : _message(std::move(msg)){}
    /**
     * @brief Returns the error message describing the cause of the exception.
     * @return A C-style string containing the error message.
     */
    [[nodiscard]] const char* what() const noexcept override {
        return _message.c_str();
    }

private:
    std::string _message;
};