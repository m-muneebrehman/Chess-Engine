#include "bitboard.h"
#include "move_generation.h"
#include "attack_map.h"
#include "board.h"

#include <iostream>

int main() {

    Board board;
    board.make_move(D2, D3, board.whitePawnD);
    board.make_move(G8, F6, board.blackKnight2);
    board.make_move(C1, G5, board.whiteBishop1);
    board.make_move(E7, E5, board.blackPawnE);
    board.make_move(G5, F6, board.whiteBishop1);
    board.make_move(B8, C6, board.blackKnight1);
    board.make_move(E2, E4, board.whitePawnE);
    board.make_move(D8, F6, board.blackQueen);
    board.make_move(G2, G3, board.whitePawnG);
    board.make_move(F6, E6, board.blackQueen);



    board.print_board();
    
    board.print_piece(board.blackQueen);
    board.print_piece(board.whiteBishop1);
    board.print_piece(board.blackKnight2);
    
    return 0;
}
