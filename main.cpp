#include "bitboard.h"
#include "move_generation.h"
#include "attack_map.h"
#include "board.h"

#include <iostream>

int main() {

    Board board;
    board.make_move(B1, C3, board.whiteKnight1);
    board.print_board();
    return 0;
}
