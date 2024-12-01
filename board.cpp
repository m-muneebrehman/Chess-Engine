#include "board.h"
#include <iostream>

// Constructor: Initializes the board
Board::Board() {
    initialize();
}


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


void Board::make_move(Bitboard from, Bitboard to, Bitboard &piece) {
  // First, validate the move
    if (!is_valid_move(from, to, piece)) {
        std::cerr << "Error: Invalid move from " << from << " to " << to << std::endl;
        return;
    }

    // Check if the move is a capture
    if ((1ULL << to) & (blackPieces | whitePieces)) {
        capture_piece(to);  // Capture the piece
    }

    // Move the piece to the new location
    piece = clear_bit(piece, from);  // Clear the piece from the 'from' position
    piece = set_bit(piece, to);      // Set the piece at the 'to' position

    // Update all pieces and empty squares
    update_all();
}


void Board::capture_piece(Bitboard to) {
    // Store pointers to the bitboards for white and black pieces
    Bitboard* whitePiecesArr[16] = { &whitePawnA, &whitePawnB, &whitePawnC, &whitePawnD,
                                     &whitePawnE, &whitePawnF, &whitePawnG, &whitePawnH,
                                     &whiteKnight1, &whiteKnight2, &whiteBishop1, &whiteBishop2,
                                     &whiteRook1, &whiteRook2, &whiteQueen, &whiteKing };

    Bitboard* blackPiecesArr[16] = { &blackPawnA, &blackPawnB, &blackPawnC, &blackPawnD,
                                     &blackPawnE, &blackPawnF, &blackPawnG, &blackPawnH,
                                     &blackKnight1, &blackKnight2, &blackBishop1, &blackBishop2,
                                     &blackRook1, &blackRook2, &blackQueen, &blackKing };

    // Check if the captured piece is white
    if ((1ULL << to) & whitePieces) {
        // Iterate over the white pieces and clear the captured piece
        for (int i = 0; i < 16; ++i) {
            if ((1ULL << to) & *whitePiecesArr[i]) {
                *whitePiecesArr[i] = clear_bit(*whitePiecesArr[i], to); // Clear the captured piece
                break;
            }
        }
    }
    // Check if the captured piece is black
    else if ((1ULL << to) & blackPieces) {
        // Iterate over the black pieces and clear the captured piece
        for (int i = 0; i < 16; ++i) {
            if ((1ULL << to) & *blackPiecesArr[i]) {
                *blackPiecesArr[i] = clear_bit(*blackPiecesArr[i], to); // Clear the captured piece
                break;
            }
        }
    }

    // Update the allPieces and emptySquares bitboards after a capture
    update_all();
}



void Board::update_all() {
    // Initialize white and black pieces as 0
    whitePieces = 0ULL;
    blackPieces = 0ULL;

    // Create arrays of pointers to each piece (white and black)
    Bitboard* whitePiecesArr[16] = { &whitePawnA, &whitePawnB, &whitePawnC, &whitePawnD, 
                                     &whitePawnE, &whitePawnF, &whitePawnG, &whitePawnH, 
                                     &whiteKnight1, &whiteKnight2, &whiteBishop1, &whiteBishop2, 
                                     &whiteRook1, &whiteRook2, &whiteQueen, &whiteKing };

    Bitboard* blackPiecesArr[16] = { &blackPawnA, &blackPawnB, &blackPawnC, &blackPawnD, 
                                     &blackPawnE, &blackPawnF, &blackPawnG, &blackPawnH, 
                                     &blackKnight1, &blackKnight2, &blackBishop1, &blackBishop2, 
                                     &blackRook1, &blackRook2, &blackQueen, &blackKing };

    // Add each white piece to whitePieces if it's still in the game (not 0ULL)
    for (int i = 0; i < 16; ++i) {
        if (*whitePiecesArr[i] != 0ULL) {
            whitePieces |= *whitePiecesArr[i];
        }
    }

    // Add each black piece to blackPieces if it's still in the game (not 0ULL)
    for (int i = 0; i < 16; ++i) {
        if (*blackPiecesArr[i] != 0ULL) {
            blackPieces |= *blackPiecesArr[i];
        }
    }

    // Update allPieces and emptySquares
    allPieces = whitePieces | blackPieces;
    emptySquares = ~allPieces & 0xFFFFFFFFFFFFFFFFULL; 
}



bool Board::is_valid_move(Bitboard from, Bitboard to, Bitboard &piece) const {
   
    if (to < 0 || to >= 64) {
        std::cout << "Error: Invalid move. 'To' position is not a valid destination." << std::endl;
        return false;
    }

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


void Board::remove_piece(Bitboard square, Bitboard &piece) {
    piece = clear_bit(piece, square);
    update_all();
}


bool Board::is_square_empty(Bitboard square) const {
    return (emptySquares & (1ULL << square)) != 0;
}


void Board::print_board() const {
    std::cout << "Current Board State:" << std::endl;
    print_bitboard(allPieces);
}


void Board::print_piece(Bitboard piece) const {
    print_bitboard(piece);
}

// Generate all white pieces' legal moves
Bitboard Board::generate_White_pieces() const{
    return (
        generate_king_moves(whiteKing, emptySquares) |        // King moves
        generate_queen_moves(whiteQueen, emptySquares) |      // Queen moves
        generate_bishop_moves(whiteBishop1, emptySquares) |   // Bishop 1 moves
        generate_bishop_moves(whiteBishop2, emptySquares) |   // Bishop 2 moves
        generate_knight_moves(whiteKnight1, emptySquares) |   // Knight 1 moves
        generate_knight_moves(whiteKnight2, emptySquares) |   // Knight 2 moves
        generate_rook_moves(whiteRook1, emptySquares) |       // Rook 1 moves
        generate_rook_moves(whiteRook2, emptySquares) |       // Rook 2 moves
        generate_white_pawn_moves(whitePawnA, emptySquares) | // White Pawn A moves
        generate_white_pawn_moves(whitePawnB, emptySquares) | // White Pawn B moves
        generate_white_pawn_moves(whitePawnC, emptySquares) | // White Pawn C moves
        generate_white_pawn_moves(whitePawnD, emptySquares) | // White Pawn D moves
        generate_white_pawn_moves(whitePawnE, emptySquares) | // White Pawn E moves
        generate_white_pawn_moves(whitePawnF, emptySquares) | // White Pawn F moves
        generate_white_pawn_moves(whitePawnG, emptySquares) | // White Pawn G moves
        generate_white_pawn_moves(whitePawnH, emptySquares)   // White Pawn H moves
    );
}

// Generate all black pieces' legal moves
Bitboard Board::generate_Black_pieces() const{
    return (
        generate_king_moves(blackKing, emptySquares) |        // King moves
        generate_queen_moves(blackQueen, emptySquares) |      // Queen moves
        generate_bishop_moves(blackBishop1, emptySquares) |   // Bishop 1 moves
        generate_bishop_moves(blackBishop2, emptySquares) |   // Bishop 2 moves
        generate_knight_moves(blackKnight1, emptySquares) |   // Knight 1 moves
        generate_knight_moves(blackKnight2, emptySquares) |   // Knight 2 moves
        generate_rook_moves(blackRook1, emptySquares) |       // Rook 1 moves
        generate_rook_moves(blackRook2, emptySquares) |       // Rook 2 moves
        generate_black_pawn_moves(blackPawnA, emptySquares) | // Black Pawn A moves
        generate_black_pawn_moves(blackPawnB, emptySquares) | // Black Pawn B moves
        generate_black_pawn_moves(blackPawnC, emptySquares) | // Black Pawn C moves
        generate_black_pawn_moves(blackPawnD, emptySquares) | // Black Pawn D moves
        generate_black_pawn_moves(blackPawnE, emptySquares) | // Black Pawn E moves
        generate_black_pawn_moves(blackPawnF, emptySquares) | // Black Pawn F moves
        generate_black_pawn_moves(blackPawnG, emptySquares) | // Black Pawn G moves
        generate_black_pawn_moves(blackPawnH, emptySquares)   // Black Pawn H moves
    );
}

