// Ascii chess

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <io.h>
#include <string.h>
//gcc file.c -o executable

/*
 Piece mappping for board sisplay
 white pawns 1
 white rooks 2
 white knight 3
 white bishop 4
 white queen 5
 white king 6

 black pawns 7
 black rooks 8
 black knight 9
 black bishop 10
 black queen 11
 black king 12
*/

void setup_board(int *board){
    int temp_board[64] = {
        2,3,4,5,6,4,3,2,
        1,1,1,1,1,1,1,1,
        0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,
        7,7,7,7,7,7,7,7,
        8,9,10,11,12,10,9,8};

     for (int i = 0; i < 64; i++) {
        board[i] = temp_board[i];
    }

}

int print_board(int board[], int move_next){
    int i = 0;
    const int board_length = 8;
    
    wchar_t black_square = L'□';
    wchar_t white_square = L'■';
    wchar_t white_pawn = L'♟';
    wchar_t white_rook = L'♜';
    wchar_t white_knight = L'♞';
    wchar_t white_bishop = L'♝';
    wchar_t white_queen = L'♛';
    wchar_t white_king = L'♚';
    wchar_t black_pawn = L'♙';
    wchar_t black_rook = L'♖';
    wchar_t black_knight = L'♘';
    wchar_t black_bishop = L'♗';
    wchar_t black_queen = L'♕';
    wchar_t black_king = L'♔';

    int board_code;

    for(i = board_length - 1; i >= 0; i--){
        for(int j = 0; j < board_length; j++){
            board_code = board[i * 8 + j];
            if(board_code == 1){
                wprintf(L" %lc", white_pawn);
            }else if(board_code == 2){
                wprintf(L" %lc", white_rook);
            }else if(board_code == 3){
                wprintf(L" %lc", white_knight);
            }else if(board_code == 4){
                wprintf(L" %lc", white_bishop);
            }else if(board_code == 5){
                wprintf(L" %lc", white_queen);
            }else if(board_code == 6){
                wprintf(L" %lc", white_king);
            }else if(board_code == 7){
                wprintf(L" %lc", black_pawn);
            }else if(board_code == 8){
                wprintf(L" %lc", black_rook);
            }else if(board_code == 9){
                wprintf(L" %lc", black_knight);
            }else if(board_code == 10){
                wprintf(L" %lc", black_bishop);
            }else if(board_code == 11){
                wprintf(L" %lc", black_queen);
            }else if(board_code == 12){
                wprintf(L" %lc", black_king);
            }else if(i % 2 == j % 2){
                wprintf(L" %lc", white_square);
            }else{
                wprintf(L" %lc", black_square);
            }
        }
        wprintf(L" %i \n", i + 1);
    }

    wprintf(L" ");
    for(int i = 1; i<= board_length; i++){
        wprintf(L"%c ", 'A' + i - 1);
    }
    wprintf(L"\n ");

    if(move_next){
        wprintf(L"It is blacks' go");
    }else{
        wprintf(L"It is whites' go");
    }
    wprintf(L"\n");
    fflush( stdout );
    return 0;
}

int check_path(int *board, int next_move, int current_square, int end){
    // Check if the path they try to travel is empty and the destination is valid
    // first check end is valid
    if(board[end] != 0){
        if(board[end] > 6 && next_move == 1 || board[end] < 7 && next_move == 0){
            return 0;
        }
    }

    int row_start = current_square - (current_square % 8);
    int row_end = end - (end % 8);
    int row_diff = row_end / 8 - row_start / 8;
    int column_diff = (current_square - row_start) - (end - row_end);
    // Then iterate through how it travels checking the spaces.
    while(1){
        if(column_diff > 0){
            current_square -= 1;
        }else if(column_diff < 0){
            current_square += 1;
        }
        if(row_diff > 0){
            current_square += 8;
        }else if(row_diff < 0){
            current_square -= 8;
        }
        if(current_square == end){
            return 1;
        }
        if(board[current_square] != 0){
            return 0;
        }
    }
    return 0;
}

int check_in_line(int current_square, int* temp_board, int current_move, int king_pos, int increment, int check, wchar_t check_msg[]){
    while((increment > 0 && current_square + increment < check) || (increment < 0 && current_square + increment > check)){
        current_square += increment;
        if(temp_board[current_square] == 0){
            continue;
        }else if((temp_board[current_square] < 7 && current_move == 0) || (temp_board[current_square] > 6 && current_move == 1)){
            break;
        }else if(
            temp_board[current_square] == 1 || 
            temp_board[current_square] == 3 || 
            temp_board[current_square] == 4 || 
            temp_board[current_square] == 7 || 
            temp_board[current_square] == 9 ||
            temp_board[current_square] == 10){
                break;
        }else if((temp_board[current_square] == 12 || temp_board[current_square] == 6) && current_square - king_pos != increment){
            break;
        }else{
            //wprintf(L"%ls", check_msg);
            return 0;
        }
    }
    return 1;
}

int check_diagonal(int current_square, int* temp_board, int current_move, int king_pos, int increment, int check, int mod_check, wchar_t check_msg[]){
    while(((current_square + increment > check && increment < 0 )|| (current_square + increment < check && increment > 0)) && (current_square + increment) % 8 != mod_check){
        current_square += increment;
        if(temp_board[current_square] == 0){
            continue;
        }else if((temp_board[current_square] < 7 && current_move == 0) || (temp_board[current_square] > 6 && current_move == 1)){
            break;
        }else if(
            (temp_board[current_square] == 7 && increment < 0) || 
            (temp_board[current_square] == 1 && increment > 0) || 
            temp_board[current_square] == 2 || 
            temp_board[current_square] == 3 || 
            temp_board[current_square] == 8 || 
            temp_board[current_square] == 9){
                break;
        }else if((temp_board[current_square] == 12 || temp_board[current_square] == 6) && current_square - king_pos != increment){
            break;
        }else if((temp_board[current_square] == 1 || temp_board[current_square] == 7) && (current_square - king_pos) != increment){
            break;
        }else{
            //wprintf(L"%ls",check_msg);
            return 0;
        }
        
    }
    return 1;
}

int check_knights(int current_square, int* temp_board, int start, int end, int current_move){
    int row_start = start - (start % 8);
    int row_end = end - (end % 8);
    int row_diff = abs(row_end / 8 - row_start / 8);
    int column_diff = abs((start - row_start) - (end - row_end));
    int knight;
    if(current_move){
        knight = 3;
    }else{
        knight = 9;
    }
    int possible_knights[8] = {(current_square - 2) - 8, (current_square + 2) - 8,
     (current_square - 2) + 8, (current_square + 2) + 8, (current_square - 1) - 16,
      (current_square + 1) - 16, (current_square - 1) + 16, (current_square + 1) + 16 };

    for(int i = 0; i < 8; i++){
        if(
            temp_board[possible_knights[i]] == knight
            ){
                //wprintf(L"Can't move as kinds is checked by knight %i ", current_square);
                return 0;
            }
    }
    return 1;
}

int check_king(int board[],  int current_move, int start, int end){
    //wprintf(L"Checking king %i...", current_move);
    // Check whether the move keeps the king out of check.
    // to test this we need to find out if the king is in check.
    int temp_board[64];
    memcpy(temp_board, board, 64 * sizeof(int));

    temp_board[end] = board[start];
    temp_board[start] = 0;

    // first find the king
    int i;
    for(i = 0; i < 64; i++){
        if((temp_board[i] == 6 && current_move == 0) || (temp_board[i] == 12 && current_move == 1)){
            break;
        }
    }
    int current_square = i;

    // now check king threats
    if(!check_in_line(i, temp_board, current_move, i, 8, 64, L"Can't move as kinds is checked from below")){
        return 0;
    }
    if(!check_in_line(i, temp_board, current_move, i, -8, 0, L"Can't move as kinds is checked from above")){
        return 0;
    }
    int start_square = current_square - (current_square % 8) - 1;
    if(!check_in_line(i, temp_board, current_move, i, -1, start_square, L"Can't move as kinds is checked from the left")){
        return 0;
    }
    if(!check_in_line(i, temp_board, current_move, i, 1, start_square + 9, L"Can't move as kinds is checked from the right")){
        return 0;
    }

    // checking for knights, annoying, needs rows and columns distance
    if(!check_knights(i, temp_board, start, end, current_move)){
        return 0;
    }
    
    // now check diagonals
    if(!check_diagonal(i, temp_board, current_move, i, -9, 0, 0,L"Can't move as kinds is checked A bottom")){
        return 0;
    }
    if(!check_diagonal(i, temp_board, current_move, i, -7, 0, 7 ,L"Can't move as kinds is checked b bottom")){
        return 0;
    }
    if(!check_diagonal(i, temp_board, current_move, i, 7, 64, 7 ,L"Can't move as kinds is checked c bottom")){
        return 0;
    }
    if(!check_diagonal(i, temp_board, current_move, i, 9, 64, 0 ,L"Can't move as kinds is checked d bottom")){
        return 0;
    }

    return 1;
}

int valid_move_for_piece(int piece, int start, int end, int end_occupied){
    // Check if the piece can move in that way
    if(end < 0 || end > 63 || end == start){
        return 0;
    }

    int row_start = start - (start % 8);
    int row_end = end - (end % 8);
    int row_diff = abs(row_end / 8 - row_start / 8);
    int column_diff = abs((start - row_start) - (end - row_end));
    if(piece == 1){
        // White pawn
        if(((end - start) == 8 && !end_occupied) ||
         (((end - start) == 7 || (end - start) == 9) && end_occupied) ||
          (start < 16 && (end - start) == 16 && !end_occupied)){
            return 1;
        }
    }else if(piece == 7){
        // black pawn
        if(
            ((end - start) == -8 && !end_occupied) ||
            (((end - start) == -7 || (end - start) == -9) && end_occupied) ||
            (start > 47 && (end - start) == -16 && !end_occupied)){
                return 1;
        }
    }else if(piece == 2 || piece == 8){
        // Rooks
        if(column_diff == 0 || row_diff == 0){
            return 1;
        }
    }else if(piece == 3 || piece == 9){
        // Knights
        if((row_diff == 2 && column_diff == 1) || (row_diff == 1 && column_diff == 2)){
            return 1;
        }
    }else if(piece == 4 || piece == 10){
        // Bishops
        if(row_diff == column_diff){
            return 1;
        }
    }else if(piece == 5 || piece == 11){
        // Queens
        if(row_diff == column_diff || column_diff == 0 || row_diff == 0){
            return 1;
        }
    }else if(piece == 6 || piece == 12){
        //Kings
        if(row_diff < 2 && column_diff < 2){
            return 1;
        }
    }
    return 0;
}

int move_piece(int *board, int move_row, int move_column, int result_row, int result_column, int *next_move){
    int valid_move = 0;
    int start_pos = move_row * 8 + move_column;
    int end_pos = result_row * 8 + result_column;
    int piece = board[start_pos];

    if(piece == 0 || (*next_move == 0 && piece > 6) || (*next_move == 1 && piece < 7)){
        return 0;
    }
    int end_occupied = board[end_pos] != 0;

    // Main check on if move is possible

    if(valid_move_for_piece(piece, start_pos, end_pos, end_occupied)){
        if(piece == 3 || piece == 9 || check_path(board, *next_move, start_pos, end_pos)){
            if(check_king(board, *next_move, start_pos, end_pos)){ // Check if they need to move out of check
                valid_move = 1;
            }
        }
    }

    if(valid_move){
        board[move_row * 8 + move_column] = 0;
        board[result_row * 8 + result_column] = piece;
        *next_move = *next_move * -1 + 1;
        return 1;
    }
    return 0;

}

int process_move(int *board, wchar_t move[], int *next_move){
    // Disassemble entry string nad try to move piece
    int move_column = move[0] - 'A';
    int move_row = (int)move[1] - '0' - 1;
    int result_column = move[4] - 'A';
    int result_row = (int)move[5]- '0' - 1;
    move_piece(board, move_row, move_column, result_row, result_column, next_move);
}

// This function is a bit brute force atm
int check_mate(int board[], int next_move){
    // Check if the king has been mated
    int temp_board[64];
    for(int i = 0; i < 64; i++){
        temp_board[i] = board[i];
    }

    for(int i = 0; i< 8; i++){
        for(int j = 0; j < 8; j++){
            for(int k = 0; k < 8; k++){
                for(int l = 0; l < 8; l++){
                    if(move_piece(temp_board, i,j,k,l, &next_move)){
                        //wprintf(L"%i, %i, %i vv %i ", i, j, k, l);
                        return 0;
                    }
                }
            }
        }
    }
    return 1;
}

int main(){
    _setmode(_fileno(stdout), 0x00020000);
    wchar_t move[50];
    int board[64] = {0};
    int next_move; // who has the next move
    int started = 0;
    int record = 0;
    setup_board(board);

    wprintf(L"WELCOME TO CHESS, TYPE 'start' TO BEGIN, 'start-record' TO PLAY WITH MOVE HISTORY OR 'exit' TO END \n");

    // main loop wait for input
    while(1){
        if (wscanf(L"%99[^\n]", move) == 1){
            while (getwchar() != '\n');

            if ((wcscmp(move, L"start") == 0 || wcscmp(move, L"start-record") == 0) && !started){
                if(wcscmp(move, L"start-record") == 0){
                    record = 1;
                }
                // Start game
                started = 1;
                next_move = 0;
                wprintf(L"To move a piece 'PIECE LOCATION->PIECE DESTINATION', (e.g. A2->A3 on whites first turn) and press enter\n");
                print_board(board, next_move);
            }else if(wcscmp(move,L"end") == 0){
                // End game
                int started = 0;
                setup_board(board);
            }else if(started){
                // make a move
                if(record == 0){
                    system("cls");
                }
                process_move(board, move, &next_move);
                if(!check_king(board, next_move, 0, 0)){
                    if(check_mate(board,next_move)){
                        wprintf(L"Checkmate \n", move);
                        started = 0;
                        continue;
                    }
                }
                wprintf(L"%ls \n", move);
                print_board(board, next_move);
            }else if(wcscmp(move,L"exit") == 0){
                break;
            }
        }
    }
    return 0;
}
