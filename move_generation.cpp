#include "move_generation.h"

// Implementation of move generation functions

Bitboard generate_white_pawn_moves(Bitboard whitePawns, Bitboard emptySquares, Bitboard blackPieces) {
    Bitboard moveForward = (whitePawns << 8) & emptySquares;
    Bitboard doubleMoveForward = ((whitePawns & (0xFFULL << 8)) << 16) & emptySquares;
    Bitboard attackLeft = (whitePawns << 7) & blackPieces & ~(0x0101010101010101ULL);
    Bitboard attackRight = (whitePawns << 9) & blackPieces & ~(0x8080808080808080ULL);
    return moveForward | doubleMoveForward | attackLeft | attackRight;
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
        ray = (ray << direction) & ~allPieces;
        moves |= ray;
        if (ray & allPieces) break;
    }
    return moves;
}

Bitboard generate_king_moves(Bitboard king, Bitboard allPieces) {
    Bitboard moves = 0ULL;
    moves |= (king << 8);  // Up
    moves |= (king >> 8);  // Down
    moves |= (king << 1);  // Right
    moves |= (king >> 1);  // Left
    moves |= (king << 7);  // Up-left
    moves |= (king << 9);  // Up-right
    moves |= (king >> 7);  // Down-right
    moves |= (king >> 9);  // Down-left
    return moves & ~allPieces;
}
