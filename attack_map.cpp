#include "attack_map.h"

Bitboard generate_pawn_attacks(Bitboard pawns, bool isWhite, Bitboard enemyPieces){
     Bitboard attacks = 0ULL;

    if (isWhite) {
        attacks |= ((pawns << 7) & enemyPieces) & 0x7F7F7F7F7F7F7F7FULL;
        attacks |= ((pawns << 9) & enemyPieces) & 0xFEFEFEFEFEFEFEFEULL;
    } else {
        attacks |= ((pawns >> 9) & enemyPieces) & 0x7F7F7F7F7F7F7F7FULL;
        attacks |= ((pawns >> 7) & enemyPieces) & 0xFEFEFEFEFEFEFEFEULL;
    }

    return attacks;
}
Bitboard generate_knight_attacks(Bitboard knight, Bitboard enemyPieces) {
    Bitboard attack = 0ULL;

  
    attack |= (knight << 17) & 0xFEFEFEFEFEFEFEFEULL; // Up two, right one
    attack |= (knight << 15) & 0x7F7F7F7F7F7F7F7FULL; // Up two, left one
    attack |= (knight >> 17) & 0x7F7F7F7F7F7F7F7FULL; // Down two, left one
    attack |= (knight >> 15) & 0xFEFEFEFEFEFEFEFEULL; // Down two, right one
    attack |= (knight << 10) & 0xFCFCFCFCFCFCFCFCULL; // Right two, up one
    attack |= (knight << 6)  & 0x3F3F3F3F3F3F3F3FULL; // Left two, up one
    attack |= (knight >> 10) & 0x3F3F3F3F3F3F3F3FULL; // Left two, down one
    attack |= (knight >> 6)  & 0xFCFCFCFCFCFCFCFCULL; // Right two, down one

    return attack & enemyPieces;
}

Bitboard generate_king_attacks(Bitboard king, Bitboard enemyPieces){
    Bitboard attack = 0ULL;

    attack |= (king << 7) & 0x7F7F7F7F7F7F7F7FULL; // Up-left
    attack |= (king << 9) & 0xFEFEFEFEFEFEFEFEULL; // Up-right
    attack |= (king >> 7) & 0xFEFEFEFEFEFEFEFEULL; // Down-right
    attack |= (king >> 9) & 0x7F7F7F7F7F7F7F7FULL; // Down-left
    attack |= (king >> 1) & 0x7F7F7F7F7F7F7F7FULL; // Left
    attack |= (king << 1) & 0xFEFEFEFEFEFEFEFEULL; // Right
    attack |= (king << 8) & 0xFFFFFFFFFFFFFFFFULL; // Up
    attack |= (king >> 8) & 0xFFFFFFFFFFFFFFFFULL; // Down

    return attack & enemyPieces;
}



Bitboard generate_sliding_attacks(Bitboard piece, Bitboard friendlyPieces, Bitboard enemyPieces, int direction) {
    Bitboard attacks = 0ULL;
    Bitboard ray = piece;

    // Edge masks to prevent wraparound
    const Bitboard NOT_FILE_A =  0x7F7F7F7F7F7F7F7FULL; 
    const Bitboard NOT_FILE_H =  0xFEFEFEFEFEFEFEFEULL; 

    while (true) {
        // Shift in the specified direction
        if (direction == 1) { // Right
            ray = (ray << 1) & NOT_FILE_H;
        } else if (direction == -1) { // Left
            ray = (ray >> 1) & NOT_FILE_A;
        } else if (direction == 8) { // Up
            ray <<= 8;
        } else if (direction == -8) { // Down
            ray >>= 8;
        } else if (direction == 9) { // Up-Right
            ray = (ray << 9) & NOT_FILE_H;
        } else if (direction == 7) { // Up-Left
            ray = (ray << 7) & NOT_FILE_A;
        } else if (direction == -9) { // Down-Left
            ray = (ray >> 9) & NOT_FILE_A;
        } else if (direction == -7) { // Down-Right
            ray = (ray >> 7) & NOT_FILE_H;
        } else {
            break; // Invalid direction
        }

        if (!ray) break; // Ray has moved off the board

        if (ray & friendlyPieces) {
            break;
        }

        if (ray & enemyPieces) {
             attacks |= ray;
            break;
        }

    }

    return attacks;
}
