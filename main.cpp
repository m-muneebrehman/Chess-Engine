#include "bitboard.h"
#include "move_generation.h"
#include "attack_map.h"
#include "board.h"

#include <iostream>

int main() {
    Board board;

    // Make a few moves and print board after each move
    board.make_move(D2, D3, board.whitePawnD);
    board.make_move(G8, F6, board.blackKnight2);
    board.make_move(C1, G5, board.whiteBishop1);
    board.make_move(E7, E5, board.blackPawnE);
    board.make_move(G5, F6, board.whiteBishop1);
    board.make_move(F6, H8, board.whiteBishop1);

    board.print_board();
    // Print the state of each specific piece
    board.print_piece(board.whiteBishop1);
    board.print_piece(board.blackKnight2);

    return 0;
}
