#include "board.h"


// Constructor: Initializes the board
Board::Board() {
    initialize();
}

// Initialize the board with all pieces in their starting positions
void Board::initialize() {
    // White pawns
    whitePawns = set_bit(0ULL, A2) | set_bit(0ULL, B2) | set_bit(0ULL, C2) |
                 set_bit(0ULL, D2) | set_bit(0ULL, E2) | set_bit(0ULL, F2) |
                 set_bit(0ULL, G2) | set_bit(0ULL, H2);

    // Black pawns
    blackPawns = set_bit(0ULL, A7) | set_bit(0ULL, B7) | set_bit(0ULL, C7) |
                 set_bit(0ULL, D7) | set_bit(0ULL, E7) | set_bit(0ULL, F7) |
                 set_bit(0ULL, G7) | set_bit(0ULL, H7);

    // Knights
    whiteKnights = set_bit(0ULL, B1) | set_bit(0ULL, G1);
    blackKnights = set_bit(0ULL, B8) | set_bit(0ULL, G8);

    // Bishops
    whiteBishops = set_bit(0ULL, C1) | set_bit(0ULL, F1);
    blackBishops = set_bit(0ULL, C8) | set_bit(0ULL, F8);

    // Rooks
    whiteRooks = set_bit(0ULL, A1) | set_bit(0ULL, H1);
    blackRooks = set_bit(0ULL, A8) | set_bit(0ULL, H8);

    // Queens
    whiteQueens = set_bit(0ULL, D1);
    blackQueens = set_bit(0ULL, D8);

    // Kings
    whiteKing = set_bit(0ULL, E1);
    blackKing = set_bit(0ULL, E8);

    // Combine all pieces for white and black
    whitePieces = whitePawns | whiteKnights | whiteBishops | whiteRooks | whiteQueens | whiteKing;
    blackPieces = blackPawns | blackKnights | blackBishops | blackRooks | blackQueens | blackKing;

    // Combine all pieces on the board
    allPieces = whitePieces | blackPieces;

    // Calculate empty squares
    emptySquares = ~allPieces;
}

// Make a move: Update the bitboards for the piece being moved
void Board::make_move(Bitboard from, Bitboard to, Bitboard &piece) {
    piece = clear_bit(piece, from);
    piece = set_bit(piece, to);
    update_all();
}

// Remove a piece from the board
void Board::remove_piece(Bitboard square, Bitboard &piece) {
    piece = clear_bit(piece, square);
    update_all();
}

// Check if a square is empty
bool Board::is_square_empty(Bitboard square) const {
    return (emptySquares & (1ULL << square)) != 0;
}

// Update aggregate bitboards (allPieces and emptySquares)
void Board::update_all() {
    whitePieces = whitePawns | whiteKnights | whiteBishops | whiteRooks | whiteQueens | whiteKing;
    blackPieces = blackPawns | blackKnights | blackBishops | blackRooks | blackQueens | blackKing;
    allPieces = whitePieces | blackPieces;
    emptySquares = ~allPieces;
}

// Print the full board
void Board::print_board() const {
    std::cout << "Current Board State:" << std::endl;
    print_bitboard(allPieces); // Print all pieces
    std::cout << "White Pieces:" << std::endl;
    print_bitboard(whitePieces); // Print white pieces
    std::cout << "Black Pieces:" << std::endl;
    print_bitboard(blackPieces); // Print black pieces
}
