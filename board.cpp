#include "board.h"
#include "attack_map.h"
#include "move_generation.h"
#include <iostream>

// Constructor: Initializes the board
Board::Board() {
    initialize();
}

// Initialize the board with all pieces in their starting positions
void Board::initialize() {
    // Initialize white pawns
    whitePawnA = set_bit(0ULL, A2);
    whitePawnB = set_bit(0ULL, B2);
    whitePawnC = set_bit(0ULL, C2);
    whitePawnD = set_bit(0ULL, D2);
    whitePawnE = set_bit(0ULL, E2);
    whitePawnF = set_bit(0ULL, F2);
    whitePawnG = set_bit(0ULL, G2);
    whitePawnH = set_bit(0ULL, H2);

    // Initialize black pawns
    blackPawnA = set_bit(0ULL, A7);
    blackPawnB = set_bit(0ULL, B7);
    blackPawnC = set_bit(0ULL, C7);
    blackPawnD = set_bit(0ULL, D7);
    blackPawnE = set_bit(0ULL, E7);
    blackPawnF = set_bit(0ULL, F7);
    blackPawnG = set_bit(0ULL, G7);
    blackPawnH = set_bit(0ULL, H7);

    // Initialize knights
    whiteKnight1 = set_bit(0ULL, B1);
    whiteKnight2 = set_bit(0ULL, G1);
    blackKnight1 = set_bit(0ULL, B8);
    blackKnight2 = set_bit(0ULL, G8);

    // Initialize bishops
    whiteBishop1 = set_bit(0ULL, C1);
    whiteBishop2 = set_bit(0ULL, F1);
    blackBishop1 = set_bit(0ULL, C8);
    blackBishop2 = set_bit(0ULL, F8);

    // Initialize rooks
    whiteRook1 = set_bit(0ULL, A1);
    whiteRook2 = set_bit(0ULL, H1);
    blackRook1 = set_bit(0ULL, A8);
    blackRook2 = set_bit(0ULL, H8);

    // Initialize queens
    whiteQueen = set_bit(0ULL, D1);
    blackQueen = set_bit(0ULL, D8);

    // Initialize kings
    whiteKing = set_bit(0ULL, E1);
    blackKing = set_bit(0ULL, E8);

    // Combine all white pieces
    whitePieces = whitePawnA | whitePawnB | whitePawnC | whitePawnD |
                  whitePawnE | whitePawnF | whitePawnG | whitePawnH |
                  whiteKnight1 | whiteKnight2 |
                  whiteBishop1 | whiteBishop2 |
                  whiteRook1 | whiteRook2 |
                  whiteQueen | whiteKing;

    // Combine all black pieces
    blackPieces = blackPawnA | blackPawnB | blackPawnC | blackPawnD |
                  blackPawnE | blackPawnF | blackPawnG | blackPawnH |
                  blackKnight1 | blackKnight2 |
                  blackBishop1 | blackBishop2 |
                  blackRook1 | blackRook2 |
                  blackQueen | blackKing;

    // Combine all pieces on the board
    allPieces = whitePieces | blackPieces;

    // Calculate empty squares
    emptySquares = ~allPieces;
}

// Make a move: Update the bitboards for the piece being moved
void Board::make_move(Bitboard from, Bitboard to, Bitboard &piece) {
    // Check if the move is valid
    if (!is_valid_move(from, to, piece)) {
        std::cerr << "Error: Invalid move from " << from << " to " << to << std::endl;
        return;
    }

    // Update the piece's bitboard
    piece = clear_bit(piece, from);
    piece = set_bit(piece, to);

    // Update all aggregate bitboards
    update_all();
}

// Validate if a move is valid according to move generation rules
bool Board::is_valid_move(Bitboard from, Bitboard to, Bitboard &piece) const {
    Bitboard possibleMoves = generate_moves_for_piece(from, piece);
    if ((possibleMoves & (1ULL << to)) == 0) {
        std::cerr << "Invalid move: From " << from << " to " << to << ". Possible moves: ";
        print_bitboard(possibleMoves);
        return false;
    }
    return true;
}

Bitboard Board::generate_moves_for_piece(Bitboard position, Bitboard &piece) const {
    // Identify the type of piece and generate moves accordingly
    if (piece & (whitePawnA | whitePawnB | whitePawnC | whitePawnD |
                 whitePawnE | whitePawnF | whitePawnG | whitePawnH)) {
        return generate_white_pawn_moves(piece, emptySquares);
    } else if (piece & (blackPawnA | blackPawnB | blackPawnC | blackPawnD |
                        blackPawnE | blackPawnF | blackPawnG | blackPawnH)) {
        return generate_black_pawn_moves(piece, emptySquares);
    } else if (piece & (whiteKnight1 | whiteKnight2 | blackKnight1 | blackKnight2)) {
        return generate_knight_moves(position, allPieces);
    } else if (piece & (whiteBishop1 | whiteBishop2 | blackBishop1 | blackBishop2)) {
        return generate_sliding_moves(position, allPieces, 9) |  // Up-right
               generate_sliding_moves(position, allPieces, 7) |  // Up-left
               generate_sliding_moves(position, allPieces, -7) | // Down-right
               generate_sliding_moves(position, allPieces, -9);  // Down-left
    } else if (piece & (whiteRook1 | whiteRook2 | blackRook1 | blackRook2)) {
        return generate_sliding_moves(position, allPieces, 1) |  // Right
               generate_sliding_moves(position, allPieces, -1) | // Left
               generate_sliding_moves(position, allPieces, 8) |  // Up
               generate_sliding_moves(position, allPieces, -8);  // Down
    } else if (piece & (whiteQueen | blackQueen)) {
        return generate_sliding_moves(position, allPieces, 9) |  // Up-right
               generate_sliding_moves(position, allPieces, 7) |  // Up-left
               generate_sliding_moves(position, allPieces, -7) | // Down-right
               generate_sliding_moves(position, allPieces, -9) | // Down-left
               generate_sliding_moves(position, allPieces, 1) |  // Right
               generate_sliding_moves(position, allPieces, -1) | // Left
               generate_sliding_moves(position, allPieces, 8) |  // Up
               generate_sliding_moves(position, allPieces, -8);  // Down
    } else if (piece & (whiteKing | blackKing)) {
        return generate_king_moves(position, allPieces);
    }

    // If no match, return an empty bitboard
    return 0ULL;
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
    whitePieces = whitePawnA | whitePawnB | whitePawnC | whitePawnD |
                  whitePawnE | whitePawnF | whitePawnG | whitePawnH |
                  whiteKnight1 | whiteKnight2 |
                  whiteBishop1 | whiteBishop2 |
                  whiteRook1 | whiteRook2 |
                  whiteQueen | whiteKing;

    blackPieces = blackPawnA | blackPawnB | blackPawnC | blackPawnD |
                  blackPawnE | blackPawnF | blackPawnG | blackPawnH |
                  blackKnight1 | blackKnight2 |
                  blackBishop1 | blackBishop2 |
                  blackRook1 | blackRook2 |
                  blackQueen | blackKing;

    allPieces = whitePieces | blackPieces;
    emptySquares = ~allPieces;
}

// Print the full board
void Board::print_board() const {
    std::cout << "Current Board State:" << std::endl;
    print_bitboard(allPieces);
}

// Print a specific piece
void Board::print_piece(Bitboard piece) const {
    print_bitboard(piece);
}
