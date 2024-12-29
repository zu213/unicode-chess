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
    const int board_length = 8;
    //int board[64] = {0};
    int i = 0;

    for(i = 0; i < 32; i++){

        if(i == 0 || i == 7){
            board[i] = 2;
        }else if(i == 1 || i == 6){
            board[i] = 3;
        }else if(i == 2 || i == 5){
            board[i] = 4;
        }else if(i == 3){
            board[i] = 5;
        }else if(i == 4){
            board[i] = 6;
        }else if(i < 16){
            board[i] = 1;
        }else if(i < 24){
            board[i + 32] = 7;
        }else if(i == 24 || i == 31){
            board[i + 32] = 8;
        }else if(i == 25 || i == 30){
            board[i + 32] = 9;
        }else if(i == 26 || i == 29){
            board[i + 32] = 10;
        }else if(i == 27){
            board[i + 32] = 11;
        }else if(i == 28){
            board[i + 32] = 12;
        }else{
            wprintf(L"Error");
        }
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

    //wprintf(L"\n");

    int board_code;
    wprintf(L"\n ");
    for(int i = 1; i<= board_length; i++){
        wprintf(L"%i ", i);
    }
    wprintf(L"\n");
    for(i = 0; i < board_length; i++){
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
    if(move_next){
        wprintf(L"it is blacks go");
    }else{
        wprintf(L"it is whites go");
    }
    fflush( stdout );
    return 0;
}

int char_to_row(char c){
    if(c == 'A'){
        return 0;
    }else if(c == 'B'){
        return 1;
    }else if(c == 'C'){
        return 2;
    }else if(c == 'D'){
        return 3;
    }else if(c == 'E'){
        return 4;
    }else if(c == 'F'){
        return 5;
    }else if(c == 'G'){
        return 6;
    }else if(c == 'H'){
        return 7;
    }else{
        wprintf(L"invalid character %c", c);
        return -1;
    }
}

int check_path(int *board, int next_move, int start, int end){
    wprintf(L"LKLK");
    if(board[end] != 0){
        if(board[end] > 6 && next_move == 1 || board[end] < 7 && next_move == 0){
            return 0;
        }
    }
    int row_start = start - (start % 8);
    int row_end = end - (end % 8);
    int row_diff = row_end / 8 - row_start / 8;
    int column_diff = (start - row_start) - (end - row_end);
    wprintf(L"MKMK %i, %i ", row_diff, column_diff);
    int current_square = start;
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
        wprintf(L"LKLK %i jj", current_square);

        if(board[current_square] != 0){
            return 0;
        }


    }
    return 0;
}

int check_king(int board[],  int current_move, int start, int end){
    int size = 64;
    
    int temp_board[64];
    memcpy(temp_board, board, size * sizeof(int));

    temp_board[end] = board[start];
    temp_board[start] = 0;

    // first find the king
    int i;
    for(i = 0; i < 64; i++){
        if((temp_board[i] == 6 && current_move == 0) || (temp_board[i] == 12 && current_move == 1)){
            break;
        }
    }

    // now check king threats
    // CHECKING DOWN
    int current_square = i;
    while(current_square + 8 < 64){
        current_square += 8;
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
        }else if((temp_board[current_square] == 12 || temp_board[current_square] == 6) && current_square - end != 8){
            wprintf(L"testytesty AA %i bb %i ads ", current_square, end);
            break;
        }else{
            wprintf(L"%i dUP",current_square);
            return 0;
        }
        
    }

    // checking up
    current_square = i;
    while(current_square - 8 > 0){
        current_square -= 8;
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
        }else if((temp_board[current_square] == 12 || temp_board[current_square] == 6) && current_square - end != -8){
            wprintf(L"testytesty AA %i bb %i ads ", current_square, end);
            break;
        }else{
            wprintf(L"%i DOWN",current_square);
            return 0;
        }
    }

    // check left
    current_square = i;
    int start_square = current_square - (current_square % 8) - 1;
    while(current_square - 1 > start_square){
        current_square -= 1;
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
        }else if((temp_board[current_square] == 12 || temp_board[current_square] == 6) && current_square - end != -1){
            break;
        }else{
            wprintf(L"%i left",current_square);
            return 0;
        }
    }

    //check right
    current_square = i;
    int end_square = start_square + 9;
    while(current_square + 1 < end_square){
        current_square += 1;
        wprintf(L" %i n",temp_board[current_square]);
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
        }else if((temp_board[current_square] == 12 || temp_board[current_square] == 6) && current_square - end != 1){
            wprintf(L"testytesty");
            break;
        }else{
            wprintf(L"%i right",current_square);
            return 0;
        }
    }

    // checking for knights, annoying
    current_square = i;
    int row_start = start - (start % 8);
    int row_end = end - (end % 8);
    int row_diff = abs(row_end / 8 - row_start / 8);
    int column_diff = abs((start - row_start) - (end - row_end));
    int knight;
    if(current_move == 0){
        knight = 9;
    }else{
        knight = 3;
    }
    if(
        temp_board[(current_square - 2) - 8] == knight ||
        temp_board[(current_square - 2) + 8] == knight ||
        temp_board[(current_square + 2) - 8] == knight ||
        temp_board[(current_square + 2) + 8] == knight ||
        temp_board[(current_square - 1) - 16] == knight ||
        temp_board[(current_square - 1) + 16] == knight ||
        temp_board[(current_square + 1) - 16] == knight ||
        temp_board[(current_square + 1) + 16] == knight 
        ){
            return 0;
        }
    
    // now check diagonals

    // top left
    current_square = i;
    while(current_square - 9 > 0 && current_square % 8 != 0){
        current_square -= 9;
        if(temp_board[current_square] == 0){
            continue;
        }else if((temp_board[current_square] < 7 && current_move == 0) || (temp_board[current_square] > 6 && current_move == 1)){
            break;
        }else if(
            temp_board[current_square] == 7 || 
            temp_board[current_square] == 2 || 
            temp_board[current_square] == 3 || 
            temp_board[current_square] == 8 || 
            temp_board[current_square] == 9){
                break;
        }else if((temp_board[current_square] == 12 || temp_board[current_square] == 6) && current_square - end != -9){
            break;
        }else if((temp_board[current_square] == 1) && (current_square - end) != -9){
            break;
        }else{
            wprintf(L"%i top left",current_square);
            return 0;
        }
        
    }

    // checking top right
     current_square = i;
    while(current_square - 7 > 0 && current_square % 8 != 0){
        current_square -= 7;
        if(temp_board[current_square] == 0){
            continue;
        }else if((temp_board[current_square] < 7 && current_move == 0) || (temp_board[current_square] > 6 && current_move == 1)){
            break;
        }else if(
            temp_board[current_square] == 7 || 
            temp_board[current_square] == 2 || 
            temp_board[current_square] == 3 || 
            temp_board[current_square] == 8 || 
            temp_board[current_square] == 9){
                break;
        }else if((temp_board[current_square] == 12 || temp_board[current_square] == 6) && current_square - end != -7){
            break;
        }else if((temp_board[current_square] == 1) && (current_square - end) != -7){
            break;
        }else{
            wprintf(L"%i top right",current_square);
            return 0;
        }
    }

        // checking bottom left
     current_square = i;
    while(current_square + 7 < 64 && current_square % 8 != 7){
        current_square += 7;
        if(temp_board[current_square] == 0){
            continue;
        }else if((temp_board[current_square] < 7 && current_move == 0) || (temp_board[current_square] > 6 && current_move == 1)){
            break;
        }else if(
            temp_board[current_square] == 1 || 
            temp_board[current_square] == 2 || 
            temp_board[current_square] == 3 || 
            temp_board[current_square] == 8 || 
            temp_board[current_square] == 9){
                break;
        }else if((temp_board[current_square] == 12 || temp_board[current_square] == 6) && current_square - end != 7){
            break;
        }else if((temp_board[current_square] == 7) && (current_square - end) != 7){
            break;
        }else{
            wprintf(L"%i bottom left ",current_square);
            return 0;
        }
    }

        // checking top right
     current_square = i;
    while(current_square + 9 > 0 && current_square % 8 != 7){
        current_square += 9;
        if(temp_board[current_square] == 0){
            continue;
        }else if((temp_board[current_square] < 7 && current_move == 0) || (temp_board[current_square] > 6 && current_move == 1)){
            break;
        }else if(
            temp_board[current_square] == 1 || 
            temp_board[current_square] == 2 || 
            temp_board[current_square] == 3 || 
            temp_board[current_square] == 8 || 
            temp_board[current_square] == 9){
                break;
        }else if((temp_board[current_square] == 12 || temp_board[current_square] == 6) && current_square - end != 9){
            break;
        }else if((temp_board[current_square] == 7) && (current_square - end) != 9){
            break;
        }else{
            wprintf(L"%i top right",current_square);
            return 0;
        }
    }

    return 1;
}

int valid_move_for_piece(int piece, int start, int end, int end_occupied){
    if(end < 0 || end > 63 || end == start){
        return 0;
    }

    int row_start = start - (start % 8);
    int row_end = end - (end % 8);
    int row_diff = abs(row_end / 8 - row_start / 8);
    int column_diff = abs((start - row_start) - (end - row_end));

    if(piece == 1){
        // White pawn
        if(((end - start) == 8) ||
         (((end - start) == 7 || (end - start) == 9) && end_occupied) ||
          (start < 16 && (end - start) == 16)){
            return 1;
        }
    }else if(piece == 7){
        // black pawn
        wprintf(L" %i ", end-start);
        if(
            ((end - start) == -8) ||
            (((end - start) == -7 || (end - start) == -9) && end_occupied) ||
            (start > 47 && (end - start) == -16)){
                return 1;
        }
    }else if(piece == 2 || piece == 8){
        // Rooks
        int row_start = start - (start % 8);
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
        //Kinds
        if(row_diff < 2 && column_diff < 2){
            return 1;
        }
    }
    return 0;
}

void move_piece(int *board, wchar_t move[], int *next_move){
    int move_row = char_to_row(move[0]);
    int move_column = (int)move[1] - '0' - 1;
    int result_row = char_to_row(move[4]);
    int result_column = (int)move[5]- '0' - 1;
    int piece;
    int pinned = 0;
    int valid_move = 0;

    if(!pinned){
        piece = board[move_row * 8 + move_column];
        wprintf(L"%i",piece);
        if(piece == 0 || (*next_move == 0 && piece > 6) || (*next_move == 1 && piece < 7)){
            return;
        }
        int end_occupied = board[result_row * 8 + result_column] != 0;
        if(valid_move_for_piece(piece, move_row * 8 + move_column, result_row * 8 + result_column, end_occupied)){

            if(piece == 3 || piece == 9 || check_path(board, *next_move, move_row * 8 + move_column, result_row * 8 + result_column)){
                wprintf(L" aaVaa ");
                if(check_king(board, *next_move, move_row * 8 + move_column, result_row * 8 + result_column)){
                    valid_move = 1;
                }
            }
        }
        
        if(valid_move){
            board[move_row * 8 + move_column] = 0;
            wprintf(L"%i ccc %i DDDD",piece, move_column);
            board[result_row * 8 + result_column] = piece;
            *next_move = *next_move * -1 + 1;
            wprintf(L"%i ccc %i DDDD",piece, board[result_row * 8 + result_column]);
        }
    }

}
/*
 Piece mappping for list storage
 white pawns 0-7
 white rooks 8, 15
 white knight 9, 14
 white bishop 10, 13
 white queen 11
 white king 12

 black pawns 16-23
 black rooks 24, 31
 black knight 25, 30
 black bishop 26, 29
 black queen 27
 black king 28
*/

int main(){
    _setmode(_fileno(stdout), 0x00020000);
    wchar_t move[50];
    int board[64] = {0};
    int next_move;
    int started = 0;
    setup_board(board);

    wprintf(L"WELCOME TO CHESS, TYPE 'start' TO BEGIN OR 'exit' TO END \n");
    const wchar_t *target = L"exit";
    while(1){
        if (wscanf(L"%99[^\n]", move) == 1){
            while (getwchar() != '\n');

            if (wcscmp(move, L"start") == 0 && !started)
            {
                started = 1;
                next_move = 0;
                print_board(board, next_move);
            }else if(started){
                move_piece(board, move, &next_move);
                wprintf(L"%ls", move);
                print_board(board, next_move);
                wprintf(L"%i",board[0]);
            }else if(wcscmp(move,L"end") == 0){
                int started = 0;
                setup_board(board);
            }else if(wcscmp(move,L"exit") == 0){
                break;
            }
            wprintf(L"%s\n",move);
        }
    }
    
    return 0;
}



