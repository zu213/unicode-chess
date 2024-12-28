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

int print_board(int board[]){
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
        wprintf(L" a \n");

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

int check_path(int start, int end){

}

int valid_move_for_piece(int piece, int start, int end){
    if(end < 0 || end > 63 || end == start){
        return 0;
    }
    if(piece == 1){
        if((((end - start) > 6 && (end - start) < 9) || (start < 16 && (end - start) == 16)) && (end - start) > 0){
            return 1;
        }
    }else if(piece == 2){
        int row_start = start - (start % 8);
        if(end % 8 == start % 8 || (end - row_start < 8 && end - row_start > 0)){
            return 1;
        }
    }else if(piece == 3){
        int row_start = start - (start % 8);
        if(end % 8 == start % 8 || (end - row_start < 8 && end - row_start > 0)){
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
        if(piece == 0 || (*next_move == 0 && piece > 7) || (*next_move == 1 && piece < 8)){
            return;
        }
        if(valid_move_for_piece(piece, move_row * 8 + move_column, result_row * 8 + result_column)){
            if(piece == 3 || piece == 9 || check_path(move_row * 8 + move_column, result_row * 8 + result_column)){
                valid_move = 1;
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
                print_board(board);
            }else if(started){
                move_piece(board, move, &next_move);
                wprintf(L"%ls", move);
                print_board(board);
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



