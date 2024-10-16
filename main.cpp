#include "bitboard.h"
#include <iostream>

using namespace std;

int main() {
    Bitboard whitePawns = 0ULL;
    Bitboard blackPawns = 0ULL;

    // Initialize white pawns on row 2
    for (int i = A2; i <= H2; ++i) {
        whitePawns = set_bit(whitePawns, i);
    }

    // Initialize black pawns on row 7
    for (int i = A7; i <= H7; ++i) {
        blackPawns = set_bit(blackPawns, i);
    }

    cout << "White Pawns Bitboard:" << endl;
    print_bitboard(whitePawns);

    cout << "Black Pawns Bitboard:" << endl;
    print_bitboard(blackPawns);

    // Example move: Move the white pawn from A2 to A3
    whitePawns = clear_bit(whitePawns, A2);
    whitePawns = set_bit(whitePawns, A3);

    cout << "After moving A2 to A3:" << endl;
    print_bitboard(whitePawns);

    // Example move: Move the white pawn from B2 to B4
    whitePawns = clear_bit(whitePawns, B2);
    whitePawns = set_bit(whitePawns, B4);

    cout << "After moving B2 to B4:" << endl;
    print_bitboard(whitePawns);

    return 0;
}
