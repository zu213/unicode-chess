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

int print_board(int pieces[]){
    const int board_length = 8;
    int board[64] = {0};
    int i = 0;
    int pieces_length = 32;

    for(i = 0; i < pieces_length; i++){
        //wprintf(L" %i,", pieces[i]);
        // early return
        if(pieces[i] < 0){
            continue;
        }

        if(i < 8){
            board[pieces[i]] = 1;
        }else if(i == 8 || i ==15){
            board[pieces[i]] = 2;
        }else if(i == 9 || i ==14){
            board[pieces[i]] = 3;
        }else if(i == 10 || i ==13){
            board[pieces[i]] = 4;
        }else if(i == 11){
            board[pieces[i]] = 5;
        }else if(i == 12){
            board[pieces[i]] = 6;
        }else if(i < 24){
            board[pieces[i]] = 7;
        }else if(i == 24 || i == 31){
            board[pieces[i]] = 8;
        }else if(i == 25 || i == 30){
            board[pieces[i]] = 9;
        }else if(i == 26 || i == 29){
            board[pieces[i]] = 10;
        }else if(i == 27){
            board[pieces[i]] = 11;
        }else if(i == 28){
            board[pieces[i]] = 12;
        }else{
            wprintf(L"Error");
        }
    }
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
    printf(" ♜ ♞ ♝ ♛ ♚ ♝ ♞ ♜ ");
    printf(" ♟ ♟ ♟ ♟ ♟ ♟ ♟ ♟ ");
    printf(" ♙ ♙ ♙ ♙ ♙ ♙ ♙ ♙ ");
    printf(" ♖ ♘ ♗ ♕ ♔ ♗ ♘ ♖ ");

    fflush( stdout );
    return 0;
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

    int pieces[32] = {
     8, 9, 10, 11, 12, 13, 14, 15,
     0, 1, 2, 3, 4, 5 ,6 , 7,
     48, 49, 50, 51, 52, 53, 54, 55,
     56, 57, 58, 59, 60, 61, 62, 63};

    wprintf(L"WELCOME TO CHESS, TYPE 'start' TO BEGIN OR 'exit' TO END \n");
    const wchar_t *target = L"exit";
    while(1){
        if (wscanf(L"%99[^\n]", move) == 1){
            if (wcscmp(move, L"start") == 0)
            {
                print_board(pieces);
                while(1){
                    if (wscanf(L"%99[^\n]", move) == 1){
                        wprintf(L"\033[2J\033[H");
                        wprintf(L"%ls", move);
                        print_board(pieces);
                    }
                }
            }else if(wcscmp(move,target) == 0){
                break;
            }
            wprintf(L"%s\n",move);
            
        }
    }
    
    return 0;
}



