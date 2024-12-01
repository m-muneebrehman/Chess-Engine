#include "bitboard.h"
#include "move_generation.h"
#include "attack_map.h"
#include "board.h"

#include <iostream>

int main() {
    Board board;

board.make_move(H2, H4, board.whitePawnH); 
board.make_move(A7, A5, board.blackPawnA); 
board.make_move(H4, H5, board.whitePawnH); 
board.make_move(H5, H6, board.whitePawnH); 
board.make_move(H1, H5, board.whiteRook2);
 board.print_board();
board.make_move(G7,H6, board.blackPawnG);
 board.print_board();
    



    board.print_piece(board.whitePawnH);
    board.print_piece(board.blackPawnG);


    return 0;
}
