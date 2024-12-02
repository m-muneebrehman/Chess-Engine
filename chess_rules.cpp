// chess_rules.cpp
#include "chess_rules.h"
#include <iostream>

bool is_check(const Board& board, bool isWhite) {
    Bitboard king = isWhite ? board.whiteKing : board.blackKing;
    if(isWhite){
        return ((board.generate_Black_pieces() & king) == king);
    }
    else 
        return( (board.generate_White_pieces() & king )== king);


}

bool causes_check( Board& board, int from, int to, bool isWhite,Bitboard &piece) {
    // Simulate the move and check if the king is in check
    Board tempBoard = board; // Create a copy of the board
    //print_board(tempBoard);
        //Bitboard tempPiece = piece;
    board.make_move(from, to , piece);
    //tempBoard.make_move(from, to, isWhite ? board.whitePawnH : board.blackPawnA);  // Move piece
    return is_check(board, isWhite);  // Check if the move results in a check
}

// bool is_checkmate(const Board& board, bool isWhite) {
//     // If the king is in check and there are no valid moves to escape, it's checkmate
//     if (!is_check(board, isWhite)) {
//         return false;
//     }

//     // Generate all possible moves for the player
//     // For simplicity, you could iterate over all pieces and try to find a legal move
//     // that would remove the check. If no such move exists, it is checkmate.
//     // Implement logic to try all moves here.
//     return false;
// }

bool is_stalemate(const Board& board, bool isWhite) {
    // If the king is not in check and there are no valid moves left, it's stalemate
    if (is_check(board, isWhite)) {
        return false; // The player is in check, so it cannot be stalemate
    }

    // Check for no moves left
    // You need to check if there are no legal moves left for the player
    // Implement the logic to check for no moves here.
    return false;
}

// bool can_castle(const Board& board, bool isWhite, bool kingside) {
//     Bitboard king = isWhite ? board.whiteKing : board.blackKing;
//     Bitboard rook = isWhite ? (kingside ? board.whiteRook2 : board.whiteRook1)
//                             : (kingside ? board.blackRook2 : board.blackRook1);

//     // Make sure the king and rook are in their starting positions
//     if (kingside) {
//         if ((king != (isWhite ? board.whiteKing : board.blackKing)) ||
//             (rook != (isWhite ? board.whiteRook2 : board.blackRook2))) {
//             return false;
//         }
//     } else {
//         if ((king != (isWhite ? board.whiteKing : board.blackKing)) ||
//             (rook != (isWhite ? board.whiteRook1 : board.blackRook1))) {
//             return false;
//         }
//     }

//     // Ensure the path between the king and rook is empty
//     Bitboard path = (kingside ? 0x0E00000000000000ULL : 0x0000000000000007ULL);
//     if (board.emptySquares & path) {
//         return true;
//     }
//     return false;
// }

// bool en_passant(const Board& board, int from, int to, bool isWhite) {
//     // Implement en passant rule logic. This will need to check if:
//     // - The opponent's pawn has just moved two squares
//     // - The move is adjacent to the pawn and on the correct rank
//     return false;
// }
