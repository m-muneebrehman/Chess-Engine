#include "bitboard.h"
#include "move_generation.h"
#include "attack_map.h"
#include "board.h"

#include <iostream>

int main() {
    // Initialize the chessboard
    Board board;

    // Scenario 1: White Pawn captures Black Pawn
    board.make_move(H2, H4, board.whitePawnH);  
    board.make_move(G7, G5, board.blackPawnG);   
    board.make_move(H4, G5, board.whitePawnH); 
    board.make_move(H7, H6, board.blackPawnH);
    board.make_move(G5, G6, board.whitePawnH);
    board.make_move(E7, E5, board.blackPawnE);
    board.make_move(H1, H6, board.whiteRook2);
    board.make_move(F8, H6, board.blackBishop2);
    board.make_move(H6, H8, board.blackBishop2);


    board.print_board();
    board.print_piece(board.blackBishop2);
    board.print_piece(board.whiteRook2);
  

    return 0;
}
