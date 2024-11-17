#include "move_generation.h"

// Implementation of move generation functions

Bitboard generate_white_pawn_moves(Bitboard whitePawns, Bitboard emptySquares) {
    Bitboard moveForward = (whitePawns << 8) & emptySquares;
    Bitboard doubleMoveForward = ((whitePawns & (0xFFULL << 8)) << 16) & emptySquares;
    return moveForward | doubleMoveForward ;
}

Bitboard generate_black_pawn_moves(Bitboard blackPawns, Bitboard emptySquares) {
    Bitboard moveForward = (blackPawns >> 8) & emptySquares;
    Bitboard doubleMoveForward = ((blackPawns & (0xFFULL << 48)) >> 16) & emptySquares;
    return moveForward | doubleMoveForward ;
}


Bitboard generate_knight_moves(Bitboard knight, Bitboard allPieces) {
    Bitboard knightMoves = 0ULL;
    knightMoves |= (knight << 17) & 0xFEFEFEFEFEFEFEFEULL; // Up two, right one
    knightMoves |= (knight << 15) & 0x7F7F7F7F7F7F7F7FULL; // Up two, left one
    knightMoves |= (knight >> 17) & 0x7F7F7F7F7F7F7F7FULL; // Down two, left one
    knightMoves |= (knight >> 15) & 0xFEFEFEFEFEFEFEFEULL; // Down two, right one
    knightMoves |= (knight << 10) & 0xFCFCFCFCFCFCFCFCULL; // Right two, up one
    knightMoves |= (knight << 6) & 0x3F3F3F3F3F3F3F3FULL;  // Left two, up one
    knightMoves |= (knight >> 10) & 0x3F3F3F3F3F3F3F3FULL; // Left two, down one
    knightMoves |= (knight >> 6) & 0xFCFCFCFCFCFCFCFCULL;  // Right two, down one
    return knightMoves & ~allPieces;
}

Bitboard generate_sliding_moves(Bitboard piece, Bitboard allPieces, int direction) {
    Bitboard moves = 0ULL;
    Bitboard ray = piece;
    while (ray) {
        ray <<= direction; // Move in the specified direction (left, right, up, or down)
        if (ray & allPieces) break; // Stop at the first occupied square
        moves |= ray; // Add the move to the list
    }
    return moves;
}


Bitboard generate_king_moves(Bitboard king, Bitboard allPieces) {
    Bitboard kingMoves = 0ULL;
    kingMoves |= (king << 7) & 0x7F7F7F7F7F7F7F7FULL; // Up-left
    kingMoves |= (king << 9) & 0xFEFEFEFEFEFEFEFEULL; // Up-right
    kingMoves |= (king >> 7) & 0xFEFEFEFEFEFEFEFEULL; // Down-right
    kingMoves |= (king >> 9) & 0x7F7F7F7F7F7F7F7FULL; // Down-left
    kingMoves |= (king >> 1) & 0x7F7F7F7F7F7F7F7FULL; // Left
    kingMoves |= (king << 1) & 0xFEFEFEFEFEFEFEFEULL; // Right
    kingMoves |= (king << 8) & 0xFFFFFFFFFFFFFFFFULL; // Mask all bits (optional)
    kingMoves |= (king >> 8) & 0xFFFFFFFFFFFFFFFFULL; // Mask all bits (optional)

    return kingMoves & ~allPieces; // Exclude occupied squares
}
