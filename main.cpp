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
    board.make_move(D2, D4, board.whitePawnD);  
    //std::cout<<is_check(board, false)<<"\n";
    board.make_move(D1, D3,board.whiteQueen); 
    //std::cout<<is_check(board, false)<<"\n";
    board.make_move(D3, B5, board.whiteQueen); 
    //std::cout<<is_check(board, false);
     std::cout<<causes_check(board,D7,D6,false,board.blackPawnD);
    // board.make_move(D7,D6,board.blackPawnD);


     board.print_board();
    // board.print_piece(board.blackBishop2);
    // board.print_piece(board.whiteRook2);
  

    return 0;
}
