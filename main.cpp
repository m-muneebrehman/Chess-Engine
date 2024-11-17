#include "bitboard.h"
#include "move_generation.h"
#include <iostream>

using namespace std;

int main() {
    Bitboard whitePawns = 0ULL;
    Bitboard blackPawns = 0ULL;
    Bitboard emptySquares = 0ULL;
    Bitboard allPieces = 0ULL;

    // // Initialize white pawns on row 2
    // for (int i = A2; i <= H2; ++i) {
    //     whitePawns = set_bit(whitePawns, i);
    // }

    // // Initialize black pawns on row 7
    // for (int i = A7; i <= H7; ++i) {
    //     blackPawns = set_bit(blackPawns, i);
    // }

    // Set the empty squares to be any square that does not have a piece
    allPieces = whitePawns | blackPawns;
    emptySquares = ~allPieces;

//     // 1. Test white pawn move generation
//     cout << "White Pawn Moves:" << endl;
//     Bitboard whitePawnMoves = generate_white_pawn_moves(whitePawns, emptySquares);
//     print_bitboard(whitePawnMoves);

//   // 2. Test black pawn move generation
//     cout << "Black Pawn Moves:" << endl;
//     Bitboard blackPawnMoves = generate_black_pawn_moves(blackPawns, emptySquares);
//     print_bitboard(blackPawnMoves );
    

    // // Initialize a knight at B1 
    // Bitboard knight = 0ULL;
    // knight = set_bit(knight, B1);

    // //3. Test knight move generation
    // cout << "Knight Moves from B1:" << endl;
    // Bitboard knightMoves = generate_knight_moves(knight, allPieces);
    // print_bitboard(knightMoves);
    
    // Initialize a king at E1
    Bitboard king = 0ULL;
    king = set_bit(king, C4);
 
    //4. Test king move generation
    cout << "King Moves from E1:" << endl;
    Bitboard kingMoves = generate_king_moves(king,allPieces);
    print_bitboard(kingMoves);

    // // Initialize a rook at A1 (square index 0)
    // Bitboard rook = 0ULL;
    // rook = set_bit(rook, A1);

    // // Test rook move generation
    // cout << "Rook Moves from A1:" << endl;
    // Bitboard rookMoves = generate_sliding_moves(rook, allPieces, 8);   // Up
    //          rookMoves |= generate_sliding_moves(rook, allPieces, -8);          // Down
    //          rookMoves |= generate_sliding_moves(rook, allPieces, 1);           // Right
    //          rookMoves |= generate_sliding_moves(rook, allPieces, -1);          // Left

    // print_bitboard(rookMoves);

    return 0;
}
