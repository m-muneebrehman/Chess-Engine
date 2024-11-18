#ifndef ATTACK_MAP_H
#define ATTACK_MAP_H

#include "bitboard.h"
#include "move_generation.h"

Bitboard generate_pawn_attacks(Bitboard pawns, bool isWhite , Bitboard enemyPieces);
Bitboard generate_knight_attacks(Bitboard knights, Bitboard enemyPieces);
Bitboard generate_king_attacks(Bitboard king , Bitboard enemyPieces);
Bitboard generate_sliding_attacks(Bitboard piece, Bitboard friendlyPieces, Bitboard enemyPieces, int direction);

#endif