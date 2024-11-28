#include "bitboard.h"
#include "move_generation.h"
#include "attack_map.h"
#include "board.h"

#include <iostream>

int main() {

    Board board;
    board.make_move(B2, B3, board.whitePawnB);
    board.print_board();
    board.make_move(A2, A4, board.whitePawnA);
    board.print_board();
    
    return 0;
}
