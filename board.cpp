#include "board.h"
#include "attack_map.h"
#include "move_generation.h"
#include <iostream>
#include <cassert>

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
    emptySquares = ~allPieces & 0xFFFFFFFFFFFFFFFFULL;
}

void Board::make_move(Bitboard from, Bitboard to, Bitboard &piece) {
    if (!is_valid_move(from, to, piece)) {
        std::cerr << "Error: Invalid move from " << from << " to " << to << std::endl;
        return;
    }
    piece = clear_bit(piece, from);
    piece = set_bit(piece, to);
    update_all();
}


bool Board::is_valid_move(Bitboard from, Bitboard to, Bitboard &piece) const {
    // Ensure 'from' is part of the piece's current position
    if ((piece & (1ULL << from)) == 0) {
        std::cerr << "Error: 'From' position does not match the piece's current position." << std::endl;
        print_bitboard(1ULL << from);
        std::cerr << "Piece positions:" << std::endl;
        print_bitboard(piece);
        return false;
    }

    // Generate possible moves for the given piece
    Bitboard possibleMoves = generate_moves_for_piece(from, piece);

    // Check if 'to' position is within the possible moves
    if ((possibleMoves & (1ULL << to)) == 0) {
        std::cerr << "Error: Invalid move. 'To' position is not a valid destination." << std::endl;
        std::cout << "Possible moves:" << std::endl;
        print_bitboard(possibleMoves);
        std::cout << "Attempted move to: " << to << std::endl;
        print_bitboard(1ULL << to);
        return false;
    }

    // Move is valid
    return true;
}


Bitboard Board::generate_moves_for_piece(Bitboard position, Bitboard &piece) const {
    Bitboard moves = 0ULL;

    // Generate moves based on the type of the piece
    if (piece & (whitePawnA | whitePawnB | whitePawnC | whitePawnD |
                 whitePawnE | whitePawnF | whitePawnG | whitePawnH)) {
        // White pawn moves and attacks
        moves = generate_white_pawn_moves(piece, emptySquares) |
                generate_pawn_attacks(piece, true, blackPieces);
    } else if (piece & (blackPawnA | blackPawnB | blackPawnC | blackPawnD |
                        blackPawnE | blackPawnF | blackPawnG | blackPawnH)) {
        // Black pawn moves and attacks
        moves = generate_black_pawn_moves(piece, emptySquares) |
                generate_pawn_attacks(piece, false, whitePieces);
    } else if (piece & (whiteKnight1 | whiteKnight2 | blackKnight1 | blackKnight2)) {
        // Knight moves and attacks
        moves = generate_knight_moves(position, allPieces) |
                generate_knight_attacks(piece, allPieces);
    } else if (piece & (whiteBishop1 | whiteBishop2 | blackBishop1 | blackBishop2)) {
        // Bishop sliding moves and attacks
        moves = generate_sliding_moves(position, allPieces, 9) |
                generate_sliding_moves(position, allPieces, 7) |
                generate_sliding_moves(position, allPieces, -7)|
                generate_sliding_moves(position, allPieces, -9)|
                generate_sliding_attacks(piece, whitePieces | blackPieces, emptySquares, 9) |  // Up-right
                generate_sliding_attacks(piece, whitePieces | blackPieces, emptySquares, 7) |  // Up-left
                generate_sliding_attacks(piece, whitePieces | blackPieces, emptySquares, -7)| // Down-right
                generate_sliding_attacks(piece, whitePieces | blackPieces, emptySquares, -9);  // Down-left

    } else if (piece & (whiteRook1 | whiteRook2 | blackRook1 | blackRook2)) {
        // Rook sliding moves and attacks
        moves = generate_sliding_moves(position, allPieces, 1) |
                generate_sliding_moves(position, allPieces, -1)|
                generate_sliding_moves(position, allPieces, 8) |
                generate_sliding_moves(position, allPieces, -8)|
                generate_sliding_attacks(piece, whitePieces | blackPieces, emptySquares, 1) |  // Right
                generate_sliding_attacks(piece, whitePieces | blackPieces, emptySquares, -1)| // Left
                generate_sliding_attacks(piece, whitePieces | blackPieces, emptySquares, 8) |  // Up
                generate_sliding_attacks(piece, whitePieces | blackPieces, emptySquares, -8);  // Down

    } else if (piece & (whiteQueen | blackQueen)) {
        // Queen sliding moves and attacks (combines rook and bishop directions)
        moves = generate_sliding_moves(position, allPieces, 9) |
                generate_sliding_moves(position, allPieces, 7) |
                generate_sliding_moves(position, allPieces, -7)|
                generate_sliding_moves(position, allPieces, -9)|
                generate_sliding_moves(position, allPieces, 1) |
                generate_sliding_moves(position, allPieces, -1)|
                generate_sliding_moves(position, allPieces, 8) |
                generate_sliding_moves(position, allPieces, -8)|
                generate_sliding_attacks(piece, whitePieces | blackPieces, emptySquares, 9) |  // Up-right
                generate_sliding_attacks(piece, whitePieces | blackPieces, emptySquares, 7) |  // Up-left
                generate_sliding_attacks(piece, whitePieces | blackPieces, emptySquares, -7) | // Down-right
                generate_sliding_attacks(piece, whitePieces | blackPieces, emptySquares, -9) | // Down-left
                generate_sliding_attacks(piece, whitePieces | blackPieces, emptySquares, 1) |  // Right
                generate_sliding_attacks(piece, whitePieces | blackPieces, emptySquares, -1) | // Left
                generate_sliding_attacks(piece, whitePieces | blackPieces, emptySquares, 8) |  // Up
                generate_sliding_attacks(piece, whitePieces | blackPieces, emptySquares, -8);  // Down

    } else if (piece & (whiteKing | blackKing)) {
        // King moves and attacks
        moves = generate_king_moves(position, allPieces) |
                generate_king_attacks(piece, allPieces);
    }

    return moves;
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
    emptySquares = ~allPieces & 0xFFFFFFFFFFFFFFFFULL;
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
