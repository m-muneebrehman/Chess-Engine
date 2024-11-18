#include "bitboard.h"
#include "move_generation.h"
#include "attack_map.h"

#include <iostream>

using namespace std;

int main() {
    // Define individual bitboards for all pieces
    Bitboard whitePawnA = 0ULL, whitePawnB = 0ULL, whitePawnC = 0ULL, whitePawnD = 0ULL;
    Bitboard whitePawnE = 0ULL, whitePawnF = 0ULL, whitePawnG = 0ULL, whitePawnH = 0ULL;
    Bitboard blackPawnA = 0ULL, blackPawnB = 0ULL, blackPawnC = 0ULL, blackPawnD = 0ULL;
    Bitboard blackPawnE = 0ULL, blackPawnF = 0ULL, blackPawnG = 0ULL, blackPawnH = 0ULL;

    Bitboard whiteKnight1 = 0ULL, whiteKnight2 = 0ULL;
    Bitboard blackKnight1 = 0ULL, blackKnight2 = 0ULL;

    Bitboard whiteBishop1 = 0ULL, whiteBishop2 = 0ULL;
    Bitboard blackBishop1 = 0ULL, blackBishop2 = 0ULL;

    Bitboard whiteRook1 = 0ULL, whiteRook2 = 0ULL;
    Bitboard blackRook1 = 0ULL, blackRook2 = 0ULL;

    Bitboard whiteQueen = 0ULL, blackQueen = 0ULL;
    Bitboard whiteKing = 0ULL, blackKing = 0ULL;

    Bitboard whitePieces = 0ULL, blackPieces = 0ULL, allPieces = 0ULL, emptySquares = 0ULL;

    // Initialize white pawns
    whitePawnA = set_bit(whitePawnA, A2);
    whitePawnB = set_bit(whitePawnB, B2);
    whitePawnC = set_bit(whitePawnC, C2);
    whitePawnD = set_bit(whitePawnD, D2);
    whitePawnE = set_bit(whitePawnE, E2);
    whitePawnF = set_bit(whitePawnF, F2);
    whitePawnG = set_bit(whitePawnG, G2);
    whitePawnH = set_bit(whitePawnH, H2);

    // Initialize black pawns
    blackPawnA = set_bit(blackPawnA, A7);
    blackPawnB = set_bit(blackPawnB, B7);
    blackPawnC = set_bit(blackPawnC, C7);
    blackPawnD = set_bit(blackPawnD, D7);
    blackPawnE = set_bit(blackPawnE, E7);
    blackPawnF = set_bit(blackPawnF, F7);
    blackPawnG = set_bit(blackPawnG, G7);
    blackPawnH = set_bit(blackPawnH, H7);

    // Initialize knights
    whiteKnight1 = set_bit(whiteKnight1, B1);
    whiteKnight2 = set_bit(whiteKnight2, G1);
    blackKnight1 = set_bit(blackKnight1, B8);
    blackKnight2 = set_bit(blackKnight2, G8);

    // Initialize bishops
    whiteBishop1 = set_bit(whiteBishop1, C1);
    whiteBishop2 = set_bit(whiteBishop2, F1);
    blackBishop1 = set_bit(blackBishop1, C8);
    blackBishop2 = set_bit(blackBishop2, F8);

    // Initialize rooks
    whiteRook1 = set_bit(whiteRook1, A1);
    whiteRook2 = set_bit(whiteRook2, H1);
    blackRook1 = set_bit(blackRook1, A8);
    blackRook2 = set_bit(blackRook2, H8);

    // Initialize queens
    whiteQueen = set_bit(whiteQueen, D1);
    blackQueen = set_bit(blackQueen, D8);

    // Initialize kings
    whiteKing = set_bit(whiteKing, E1);
    blackKing = set_bit(blackKing, E8);

    // Combine into piece groups
    whitePieces = whitePawnA | whitePawnB | whitePawnC | whitePawnD | whitePawnE | whitePawnF | whitePawnG | whitePawnH
                | whiteKnight1 | whiteKnight2 | whiteBishop1 | whiteBishop2 | whiteRook1 | whiteRook2 | whiteQueen | whiteKing;

    blackPieces = blackPawnA | blackPawnB | blackPawnC | blackPawnD | blackPawnE | blackPawnF | blackPawnG | blackPawnH
                | blackKnight1 | blackKnight2 | blackBishop1 | blackBishop2 | blackRook1 | blackRook2 | blackQueen | blackKing;

    allPieces = whitePieces | blackPieces;
    emptySquares = ~allPieces;

    // Example test: Print the bitboard for white pieces
    cout << "White Pieces:" << endl;
    print_bitboard(whitePieces);

    // Example: Testing knight move generation for whiteKnight1
    cout << "White Knight Moves from B1:" << endl;
    Bitboard knightMoves = generate_knight_moves(whiteKnight1, allPieces);
    knightMoves |= generate_knight_attacks(whiteKnight1, blackPieces);
    print_bitboard(knightMoves);











Bitboard bishop = 0ULL;
bishop = set_bit(bishop, D4);

Bitboard friendlyPieces = whitePieces;
Bitboard enemyPieces = blackPieces;

Bitboard bishopAttacks = 0ULL;

bishopAttacks |= generate_sliding_attacks(bishop, friendlyPieces, enemyPieces, 9);   // Up-Right
bishopAttacks |= generate_sliding_attacks(bishop, friendlyPieces, enemyPieces, 7);   // Up-Left
bishopAttacks |= generate_sliding_attacks(bishop, friendlyPieces, enemyPieces, -7);  // Down-Right
bishopAttacks |= generate_sliding_attacks(bishop, friendlyPieces, enemyPieces, -9);  // Down-Left
bishopAttacks |= generate_sliding_moves(bishop, allPieces, 9);   // Up-Right
bishopAttacks |= generate_sliding_moves(bishop, allPieces, 7);   // Up-Left
bishopAttacks |= generate_sliding_moves(bishop, allPieces, -7);  // Down-Right
bishopAttacks |= generate_sliding_moves(bishop, allPieces, -9);  // Down-Left

print_bitboard(bishopAttacks);

    return 0;
}
