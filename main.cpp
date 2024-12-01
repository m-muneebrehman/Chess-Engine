#include "bitboard.h"
#include "move_generation.h"
#include "attack_map.h"
#include "board.h"
#include "chess_rules.h"

#include <iostream>

int main() {
    // Initialize the chessboard
    Board board;

    // Scenario 1: White Pawn captures Black Pawn
    board.make_move(B1, C3, board.whiteKnight1);  
    std::cout<<is_check(board, false)<<"\n";
    board.make_move(C3, D5,board.whiteKnight1); 
    std::cout<<is_check(board, false)<<"\n";
    board.make_move(D5, C7, board.whiteKnight1); 
    std::cout<<is_check(board, false);


    board.print_board();
    board.print_piece(board.blackBishop2);
    board.print_piece(board.whiteRook2);
  

    return 0;
}
