#include <iostream>
#include <bitset>
#include <cstdint>

typedef uint64_t Bitboard;

using namespace std;

enum Square {
    A1 = 0, B1, C1, D1, E1, F1, G1, H1,
    A2, B2, C2, D2, E2, F2, G2, H2,
    A3, B3, C3, D3, E3, F3, G3, H3,
    A4, B4, C4, D4, E4, F4, G4, H4,
    A5, B5, C5, D5, E5, F5, G5, H5,
    A6, B6, C6, D6, E6, F6, G6, H6,
    A7, B7, C7, D7, E7, F7, G7, H7,
    A8, B8, C8, D8, E8, F8, G8, H8
};

#define SET_BIT(bb, square) (bb |= (1ULL << square))
#define CLEAR_BIT(bb, square) (bb &= ~(1ULL << square))
#define IS_BIT_SET(bb, square) (bb & (1ULL << square))

void print_bitboard(Bitboard bb) {
    for (int rank = 7; rank >= 0; --rank) {
        for (int file = 0; file < 8; ++file) {
            int square = rank * 8 + file;
            cout << (IS_BIT_SET(bb, square) ? "1 " : "0 ");
        }
        cout << endl;
    }
    cout << endl;
}

int main() {
    Bitboard whitePawns = 0ULL;
    Bitboard blackPawns = 0ULL;

    // Initialize white pawns on row 2
    for (int i = A2; i <= H2; ++i) {
        SET_BIT(whitePawns, i);
    }

    // Initialize black pawns on row 7
    for (int i = A7; i <= H7; ++i) {
        SET_BIT(blackPawns, i);
    }

    cout << "White Pawns Bitboard:" << endl;
    print_bitboard(whitePawns);

    cout << "Black Pawns Bitboard:" << endl;
    print_bitboard(blackPawns);

    // Example move: Move the white pawn from A2 to A3
    CLEAR_BIT(whitePawns, A2);
    SET_BIT(whitePawns, A3);

    cout << "After moving A2 to A3:" << endl;
    print_bitboard(whitePawns);

    // Example move: Move the white pawn from B2 to B4
    CLEAR_BIT(whitePawns, B2);
    SET_BIT(whitePawns, B4);

    cout << "After moving B2 to B4:" << endl;
    print_bitboard(whitePawns);
    return 0;
}
