#include "move_generation.h"

// Generate white pawn moves
Bitboard generate_white_pawn_moves(Bitboard whitePawns, Bitboard emptySquares) {
    Bitboard moveForward = (whitePawns << 8) & emptySquares;
    Bitboard doubleMoveForward = ((whitePawns & (0xFFULL << 8)) << 16) & emptySquares & (emptySquares <<  8);
    return moveForward | doubleMoveForward;
}

// Generate black pawn moves
Bitboard generate_black_pawn_moves(Bitboard blackPawns, Bitboard emptySquares) {
    Bitboard moveForward = (blackPawns >> 8) & emptySquares;
    Bitboard doubleMoveForward = ((blackPawns & (0xFFULL << 48)) >> 16) & emptySquares & (emptySquares >> 8);
    return moveForward | doubleMoveForward;
}


// Generate knight moves
Bitboard generate_knight_moves(Bitboard knight, Bitboard allPieces) {
    Bitboard knightMoves = 0ULL;

    // Knight moves in all 8 directions with corresponding edge masks
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

// Generate sliding piece moves (rook, bishop, queen)
Bitboard generate_sliding_moves(Bitboard piece, Bitboard allPieces, int direction) {
    Bitboard moves = 0ULL;
    Bitboard ray = piece;

    // Masks to prevent wraparound at file boundaries
    const Bitboard FILE_A_MASK = 0x7F7F7F7F7F7F7F7FULL; // Clears file A
    const Bitboard FILE_H_MASK = 0xFEFEFEFEFEFEFEFEULL; // Clears file H

    // Direction handling
    const int directions[] = { 1, -1, 8, -8, 9, 7, -9, -7 }; // Right, Left, Up, Down, Up-Right, Up-Left, Down-Left, Down-Right

    for (int i = 0; i < 8; i++) {
        ray = piece;
        while (true) {
            if (directions[i] == 1) { // Right
                ray = (ray << 1) & FILE_H_MASK;
            } else if (directions[i] == -1) { // Left
                ray = (ray >> 1) & FILE_A_MASK;
            } else if (directions[i] == 8) { // Up
                ray <<= 8;
            } else if (directions[i] == -8) { // Down
                ray >>= 8;
            } else if (directions[i] == 9) { // Up-Right
                ray = (ray << 9) & FILE_H_MASK;
            } else if (directions[i] == 7) { // Up-Left
                ray = (ray << 7) & FILE_A_MASK;
            } else if (directions[i] == -9) { // Down-Left
                ray = (ray >> 9) & FILE_A_MASK;
            } else if (directions[i] == -7) { // Down-Right
                ray = (ray >> 7) & FILE_H_MASK;
            }

            if (!ray) break; // Stop if ray moves off the board
            moves |= ray; // Add valid move to the result
            if (ray & allPieces) break; // Stop if an occupied square is encountered
        }
    }

    return moves & ~allPieces;
}

// Generate king moves
Bitboard generate_king_moves(Bitboard king, Bitboard allPieces) {
    Bitboard kingMoves = 0ULL;

    // King moves in all 8 surrounding squares with appropriate edge masks
    kingMoves |= (king << 7) & 0x7F7F7F7F7F7F7F7FULL;  // Up-left
    kingMoves |= (king << 9) & 0xFEFEFEFEFEFEFEFEULL;  // Up-right
    kingMoves |= (king >> 7) & 0xFEFEFEFEFEFEFEFEULL;  // Down-right
    kingMoves |= (king >> 9) & 0x7F7F7F7F7F7F7F7FULL;  // Down-left
    kingMoves |= (king >> 1) & 0x7F7F7F7F7F7F7F7FULL;  // Left
    kingMoves |= (king << 1) & 0xFEFEFEFEFEFEFEFEULL;  // Right
    kingMoves |= (king << 8) & 0xFFFFFFFFFFFFFFFFULL;  // Up
    kingMoves |= (king >> 8) & 0xFFFFFFFFFFFFFFFFULL;  // Down

    return kingMoves & ~allPieces;  // Exclude occupied squares
}

// Generate rook moves
Bitboard generate_rook_moves(Bitboard rook, Bitboard allPieces) {
    Bitboard moves = 0ULL;
    // Rook moves in four cardinal directions: up, down, left, right
    moves |= generate_sliding_moves(rook, allPieces, 1);   // Right
    moves |= generate_sliding_moves(rook, allPieces, -1);  // Left
    moves |= generate_sliding_moves(rook, allPieces, 8);   // Up
    moves |= generate_sliding_moves(rook, allPieces, -8);  // Down

    return moves;
}

// Generate bishop moves
Bitboard generate_bishop_moves(Bitboard bishop, Bitboard allPieces) {
    Bitboard moves = 0ULL;
    // Bishop moves in four diagonal directions: up-right, up-left, down-right, down-left
    moves |= generate_sliding_moves(bishop, allPieces, 9);   // Up-Right
    moves |= generate_sliding_moves(bishop, allPieces, 7);   // Up-Left
    moves |= generate_sliding_moves(bishop, allPieces, -9);  // Down-Left
    moves |= generate_sliding_moves(bishop, allPieces, -7);  // Down-Right

    return moves;
}

// Generate queen moves
Bitboard generate_queen_moves(Bitboard queen, Bitboard allPieces) {
    Bitboard moves = 0ULL;
    // Queen combines rook and bishop moves
    moves |= generate_rook_moves(queen, allPieces);
    moves |= generate_bishop_moves(queen, allPieces);

    return moves;
}
