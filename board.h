#ifndef BOARD_H
#define BOARD_H

#include "bitboard.h"
#include <iostream>

class Board {
public:
    // Bitboards for each piece
    Bitboard whitePawns, blackPawns;
    Bitboard whiteKnights, blackKnights;
    Bitboard whiteBishops, blackBishops;
    Bitboard whiteRooks, blackRooks;
    Bitboard whiteQueens, blackQueens;
    Bitboard whiteKing, blackKing;

    Bitboard blackPieces, whitePieces;
    Bitboard allPieces, emptySquares;

    // Constructor
    Board();

    // Methods for board management
    void initialize(); // Set up the board
    void make_move(Bitboard from, Bitboard to, Bitboard &piece); // Move a piece
    void remove_piece(Bitboard square, Bitboard &piece); // Remove a piece
    bool is_square_empty(Bitboard square) const; // Check if a square is empty
    void update_all(); // Update aggregate bitboards
    void print_board() const; // Print the full board
};

#endif
