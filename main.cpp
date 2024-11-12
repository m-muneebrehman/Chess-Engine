#include "bitboard.h"
#include "move_generation.h"
#include <iostream>

using namespace std;

int main() {
    Bitboard whitePawns = 0ULL;
    Bitboard blackPawns = 0ULL;
    Bitboard emptySquares = 0ULL;
    Bitboard allPieces = 0ULL;

    // Initialize white pawns on row 2
    for (int i = A2; i <= H2; ++i) {
        whitePawns = set_bit(whitePawns, i);
    }

    // Initialize black pawns on row 7
    for (int i = A7; i <= H7; ++i) {
        blackPawns = set_bit(blackPawns, i);
    }

    // Set the empty squares to be any square that does not have a piece
    allPieces = whitePawns | blackPawns;
    emptySquares = ~allPieces;

    // Test pawn move generation
    cout << "White Pawn Moves:" << endl;
    Bitboard whitePawnMoves = generate_white_pawn_moves(whitePawns, emptySquares, blackPawns);
    print_bitboard(whitePawnMoves);

    // Initialize a knight at B1 (square index 1)
    Bitboard knight = 0ULL;
    knight = set_bit(knight, B1);

    // Test knight move generation
    cout << "Knight Moves from B1:" << endl;
    Bitboard knightMoves = generate_knight_moves(knight, allPieces);
    print_bitboard(knightMoves);

    // Initialize a rook at A1 (square index 0)
    Bitboard rook = 0ULL;
    rook = set_bit(rook, A1);

    // Test rook move generation
    cout << "Rook Moves from A1:" << endl;
    Bitboard rookMoves = generate_sliding_moves(rook, allPieces, 8);
    print_bitboard(rookMoves);

    return 0;
}
