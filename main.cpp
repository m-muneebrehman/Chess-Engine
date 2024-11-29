#include "bitboard.h"
#include "move_generation.h"
#include "attack_map.h"
#include "board.h"

#include <iostream>

int main() {
    Board board;

    // Make a few moves and print board after each move
    board.make_move(D2, D3, board.whitePawnD);  // White pawn moves from D2 to D3
    board.make_move(G8, F6, board.blackKnight2);  // Black knight moves from G8 to F6
    board.make_move(C1, G5, board.whiteBishop1);  // White bishop moves from C1 to G5
    board.make_move(E7, E5, board.blackPawnE);   // Black pawn moves from E7 to E5
    board.make_move(G5, F6, board.whiteBishop1);
    board.make_move(D8, F6, board.blackQueen);
    board.make_move(F6, H8, board.blackQueen);

    board.print_board();
    
    std::cout << "White Bishop 1 after capture: " << std::endl;
    board.print_piece(board.whiteBishop1);
    std::cout << "Black Knight 2 after capture: " << std::endl;
    board.print_piece(board.blackKnight2);

    board.print_board();


    return 0;
}
