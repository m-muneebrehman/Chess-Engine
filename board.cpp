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
    whitePawnA = set_bit(0ULL, A2);    whitePawnB = set_bit(0ULL, B2);   whitePawnC = set_bit(0ULL, C2);
    whitePawnD = set_bit(0ULL, D2);    whitePawnE = set_bit(0ULL, E2);   whitePawnF = set_bit(0ULL, F2);
    whitePawnG = set_bit(0ULL, G2);    whitePawnH = set_bit(0ULL, H2);

    // Initialize black pawns
    blackPawnA = set_bit(0ULL, A7);    blackPawnB = set_bit(0ULL, B7);   blackPawnC = set_bit(0ULL, C7);
    blackPawnD = set_bit(0ULL, D7);    blackPawnE = set_bit(0ULL, E7);   blackPawnF = set_bit(0ULL, F7);
    blackPawnG = set_bit(0ULL, G7);    blackPawnH = set_bit(0ULL, H7);

    // Initialize knights
    whiteKnight1 = set_bit(0ULL, B1);  whiteKnight2 = set_bit(0ULL, G1);
    blackKnight1 = set_bit(0ULL, B8);  blackKnight2 = set_bit(0ULL, G8);

    // Initialize bishops
    whiteBishop1 = set_bit(0ULL, C1);  whiteBishop2 = set_bit(0ULL, F1);
    blackBishop1 = set_bit(0ULL, C8);  blackBishop2 = set_bit(0ULL, F8);

    // Initialize rooks
    whiteRook1 = set_bit(0ULL, A1);    whiteRook2 = set_bit(0ULL, H1);
    blackRook1 = set_bit(0ULL, A8);    blackRook2 = set_bit(0ULL, H8);

    // Initialize queens
    whiteQueen = set_bit(0ULL, D1);    blackQueen = set_bit(0ULL, D8);

    // Initialize kings
    whiteKing = set_bit(0ULL, E1);     blackKing = set_bit(0ULL, E8);

    // Combine all white pieces
    whitePieces = whitePawnA | whitePawnB | whitePawnC | whitePawnD |   whitePawnE | whitePawnF | whitePawnG | whitePawnH |
                  whiteKnight1 | whiteKnight2 |   whiteBishop1 | whiteBishop2 | whiteRook1 | whiteRook2 | 
                  whiteQueen | whiteKing;

    // Combine all black pieces
    blackPieces = blackPawnA | blackPawnB | blackPawnC | blackPawnD |  blackPawnE | blackPawnF | blackPawnG | blackPawnH |
                  blackKnight1 | blackKnight2 |  blackBishop1 | blackBishop2 | blackRook1 | blackRook2 |
                  blackQueen | blackKing;

    allPieces = whitePieces | blackPieces;
    emptySquares = ~allPieces & 0xFFFFFFFFFFFFFFFFULL;
}
// Make a move from one position to another for a given piece
void Board::make_move(Bitboard from, Bitboard to, Bitboard &piece) {
    // First, validate the move
    if (!is_valid_move(from, to, piece)) {
        std::cerr << "Error: Invalid move from " << from << " to " << to << std::endl;
        return;
    }

    // Check if the move is a capture (the 'to' position is occupied by an opponent's piece)
    if (to & (blackPieces | whitePieces)) {
        // If the opponent's piece is on the 'to' square, it's a capture.
        if (to & whitePieces) {
            // Black piece is captured. Find which black piece is captured and set its bitboard to 0ULL
            if (to & whitePawnA) whitePawnA = 0ULL;
            else if (to & whitePawnB) whitePawnB = 0ULL;
            else if (to & whitePawnC) whitePawnC = 0ULL;
            else if (to & whitePawnD) whitePawnD = 0ULL;
            else if (to & whitePawnE) whitePawnE = 0ULL;
            else if (to & whitePawnF) whitePawnF = 0ULL;
            else if (to & whitePawnG) whitePawnG = 0ULL;
            else if (to & whitePawnH) whitePawnH = 0ULL;
            else if (to & whiteKnight1) whiteKnight1 = 0ULL;
            else if (to & whiteKnight2) whiteKnight2 = 0ULL;
            else if (to & whiteBishop1) whiteBishop1 = 0ULL;
            else if (to & whiteBishop2) whiteBishop2 = 0ULL;
            else if (to & whiteRook1) whiteRook1 = 0ULL;
            else if (to & whiteRook2) whiteRook2 = 0ULL;
            else if (to & whiteQueen) whiteQueen = 0ULL;
            else if (to & whiteKing) whiteKing = 0ULL;
        }
        else if (to & blackPieces) {
            // White piece is captured. Find which white piece is captured and set its bitboard to 0ULL
            if (to & blackPawnA) blackPawnA = 0ULL;
            else if (to & blackPawnB) blackPawnB = 0ULL;
            else if (to & blackPawnC) blackPawnC = 0ULL;
            else if (to & blackPawnD) blackPawnD = 0ULL;
            else if (to & blackPawnE) blackPawnE = 0ULL;
            else if (to & blackPawnF) blackPawnF = 0ULL;
            else if (to & blackPawnG) blackPawnG = 0ULL;
            else if (to & blackPawnH) blackPawnH = 0ULL;
            else if (to & blackKnight1) blackKnight1 = 0ULL;
            else if (to & blackKnight2) blackKnight2 = 0ULL;
            else if (to & blackBishop1) blackBishop1 = 0ULL;
            else if (to & blackBishop2) blackBishop2 = 0ULL;
            else if (to & blackRook1) blackRook1 = 0ULL;
            else if (to & blackRook2) blackRook2 = 0ULL;
            else if (to & blackQueen) blackQueen = 0ULL;
            else if (to & blackKing) blackKing = 0ULL;
        }
    }

    // Move the piece to the new location by clearing it from the 'from' position and setting it at the 'to' position
    piece = clear_bit(piece, from);  // Clear the piece from its current position
    piece = set_bit(piece, to);      // Set the piece at the new position
    
    // After every move, update the emptySquares and allPieces bitboards
    update_all();  // This will only update allPieces and emptySquares, not individual pieces
}


void Board::update_all() {
    // Do not recalculate whitePieces and blackPieces here. They are manually updated in the move function.
      // Manually update whitePieces and blackPieces after a move
    whitePieces = whitePawnA | whitePawnB | whitePawnC | whitePawnD | whitePawnE | whitePawnF | whitePawnG | whitePawnH |
                  whiteKnight1 | whiteKnight2 | whiteBishop1 | whiteBishop2 | whiteRook1 | whiteRook2 | whiteQueen | whiteKing;

    blackPieces = blackPawnA | blackPawnB | blackPawnC | blackPawnD | blackPawnE | blackPawnF | blackPawnG | blackPawnH |
                  blackKnight1 | blackKnight2 | blackBishop1 | blackBishop2 | blackRook1 | blackRook2 | blackQueen | blackKing;

    allPieces = whitePieces | blackPieces;
    emptySquares = ~allPieces & 0xFFFFFFFFFFFFFFFFULL;  // All squares that are not occupied by pieces
}

// Validate if the move is valid for a specific piece
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

// Generate possible moves for a given piece based on its type
Bitboard Board::generate_moves_for_piece(Bitboard position, Bitboard &piece) const {
    Bitboard moves = 0ULL;

    // Ensure that a captured piece does not generate any moves
    if (piece == 0ULL) {
        return moves;  // No moves for a captured piece
    }

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
    } else if (piece & (whiteKnight1 | whiteKnight2)) {
        // Knight moves and attacks
        moves = generate_knight_moves(piece, allPieces) |
                generate_knight_attacks(piece, blackPieces);
    } else if (piece & (blackKnight1 | blackKnight2)) {
        // Knight moves and attacks
        moves = generate_knight_moves(piece, allPieces) |
                generate_knight_attacks(piece, whitePieces);
    } else if (piece & (whiteBishop1 | whiteBishop2)) {
        // Bishop sliding moves and attacks
        moves = generate_bishop_moves(piece, allPieces) |
                generate_bishop_attacks(piece, whitePieces, blackPieces);
    } else if (piece & (blackBishop1 | blackBishop2)) {
        // Bishop sliding moves and attacks
        moves = generate_bishop_moves(piece, allPieces) |
                generate_bishop_attacks(piece, blackPieces, whitePieces);
    } else if (piece & (whiteRook1 | whiteRook2)) {
        // Rook sliding moves and attacks
        moves = generate_rook_moves(piece, allPieces) |
                generate_rook_attacks(piece, whitePieces, blackPieces);
    } else if (piece & (blackRook1 | blackRook2)) {
        // Rook sliding moves and attacks
        moves = generate_rook_moves(piece, allPieces) |
                generate_rook_attacks(piece, blackPieces, whitePieces);
    } else if (piece & (whiteQueen)) {
        // Queen sliding moves and attacks
        moves = generate_queen_moves(piece, allPieces) |
                generate_queen_attacks(piece, whitePieces, blackPieces);
    } else if (piece & (blackQueen)) {
        // Queen sliding moves and attacks
        moves = generate_queen_moves(piece, allPieces) |
                generate_queen_attacks(piece, blackPieces, whitePieces);
    } else if (piece & (whiteKing)) {
        // King moves and attacks
        moves = generate_king_moves(piece, allPieces) |
                generate_king_attacks(piece, blackPieces);
    } else if (piece & (blackKing)) {
        // King moves and attacks
        moves = generate_king_moves(piece, allPieces) |
                generate_king_attacks(piece, whitePieces);
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



// Print the full board
void Board::print_board() const {
    std::cout << "Current Board State:" << std::endl;
    print_bitboard(allPieces);
}

// Print a specific piece
void Board::print_piece(Bitboard piece) const {
    print_bitboard(piece);
}


