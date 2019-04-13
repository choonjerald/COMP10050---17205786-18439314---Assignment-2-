/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
*/


#include "game_init.h"
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

void printLine();

/*
 * Returns the first letter associated with the color of the token
 *
 * Input: t - pointer to a token
 * Output: initial of the color of the token
 */
char print_token(token *t){
    if((*t).col== PINK) return 'P';
    if((*t).col== RED) return 'R';
    if((*t).col== BLU) return 'B';
    if((*t).col== GREEN) return 'G';
    if((*t).col== ORANGE) return 'O';
    if((*t).col== YELLOW) return 'Y';
    return '\0';
}

/*
 * Prints the board
 *
 * Input: the board to be printed.
 */
void print_board(square board[NUM_ROWS][NUM_COLUMNS]){
    token *current = NULL;

    printf("                THE BOARD\n");
    for(int i =0; i < NUM_ROWS; i++){

        //prints an horizontal line
        printLine();
        //prints the row number
        printf(" %d ", i);
        char c = '\0' ;
        //if the square (i,j) is occupied,
        //c is assigned the initial of the color of the token that occupies the square
        for (int j = 0; j < NUM_COLUMNS; j++){
            if(board[i][j].stack != NULL){
                c = print_token(board[i][j].stack);
            }
            //if the square (i,j) is empty
            else{
                //c is assigned 'X' if the square represents an obstacle
                if(board[i][j].type == OBSTACLE)
                    c = 'X';
                //c is assigned an empty space otherwise
                else c = ' ';
            }
            printf("| %c ", c);
        }
        printf ("|\n");
    }
    printLine();
    //prints the number of the columns at the end of the board
    printf("     0   1   2   3   4   5   6   7   8\n");
}

void printLine(){
  printf("   -------------------------------------\n");
}

/*
 * Place tokens in the first column of the board
 *
 * Input: board - a 6x9 array of squares that represents the board
 *        players - the array of the players
 *        numPlayers - the number of players
 */

void place_tokens(square board[NUM_ROWS][NUM_COLUMNS], player players[], int numPlayers){
    int minNumOfTokens = 0;
    int selectedSquare = 0;


    token* current = NULL;

    for(int i = 0; i<4; i++){
        for(int j = 0; j<numPlayers; j++){

            printf("Player %d please select a square\n", j+1);
            scanf("%d", &selectedSquare);

           // printf("here4\n");
            printf("%d\n",board[selectedSquare][0].numTokens);
            if(board[selectedSquare][0].numTokens == minNumOfTokens){

               // printf("here\n");
                if(board[selectedSquare][0].numTokens == 0){
                    printf("here1\n");
                    current = (token *)malloc(sizeof(token));
                    board[selectedSquare][0].stack = current;
                    board[selectedSquare][0].stack->col = players[j].col;
                    board[selectedSquare][0].stack->next = NULL;
                    printf("%d\n", j+1);
                    print_board(board);


                }
                else{
                    printf("here2\n");
                    current = (token *)malloc(sizeof(token));
                    current->col = players[j].col;
                    current->next = board[selectedSquare][0].stack;
                    board[selectedSquare][0].stack = current;
                    //board[selectedSquare][0].top = current;
                    //board[selectedSquare][0].stack = current;
                    printf("%d\n", j+1);
                    print_board(board);
                }



                /*
                if(board[selectedSquare][0].numTokens == 0){
                    board[selectedSquare][0].stack->top = NULL;
                    board[selectedSquare][0].stack->curr = NULL;
                }

                board[selectedSquare][0].stack->curr = board[selectedSquare][0].stack->top;
                board[selectedSquare][0].stack->top = (token *)malloc(sizeof(token));
                board[selectedSquare][0].stack->top->col = players[j].col;
                board[selectedSquare][0].stack->top->next = board[selectedSquare][0].stack->curr;
                */
                // for FIFO queue
                /*
                board[selectedSquare][0].stack->last = (token *)malloc(sizeof(token));
                board[selectedSquare][0].stack->last->col = players[j].col;
                board[selectedSquare][0].stack->last->next = NULL;
                 *
                if(board[selectedSquare][0].numTokens == 0){
                    board[selectedSquare][0].stack->first->col = board[selectedSquare][0].stack->last->col;
                }
                else{
                    board[selectedSquare][0].stack->curr->next = board[selectedSquare][0].stack->last;
                }

                board[selectedSquare][0].stack->curr = board[selectedSquare][0].stack->last;
                 */
                board[selectedSquare][0].numTokens++;
            }

            //printf("here5\n");


            if(((numPlayers*i)+j+1)%NUM_ROWS==0){
                minNumOfTokens++;
            }

        }

    }


}





/*
 * Place tokens in the first column of the board
 *
 * Input: board - a 6x9 array of squares that represents the board
 *        players - the array of the players
 *        numPlayers - the number of players
 */

void play_game(square board[NUM_ROWS][NUM_COLUMNS], player players[], int numPlayers){
  //TO BE IMPLEMENTED
     srand(time(NULL));

     for(int i = 0; i< NUM_ROWS; i++){
         token *curr = board[i][0].stack;

        while(curr != NULL){
            printf("Token color col %d is %c\n", i, print_token(curr));
            curr = curr->next;
        }

     }

     int sidestepmove, n;
     int dice = 0;
     int selectrow, selectcol;
     int sidestep;

     token* moving;

     while (players[0].numTokensLastCol !=3 || players[1].numTokensLastCol !=3 || players[2].numTokensLastCol !=3|| players[3].numTokensLastCol !=3 || players[4].numTokensLastCol !=3||
             players[5].numTokensLastCol !=3)
     {
         for(int i=0;i<numPlayers;i++)
         {
             dice = 1+(rand()%6);
             printf("Player %d. Your dice roll is : %d\n\n", i+1, dice);

             printf("Do you want to do a sidestep? Enter 1 if you want to do a sidestep. Enter 2 to skip this.\n");
             scanf("%d", &sidestep);

             if(sidestep == 1){

                 printf("Select your token you wish to move the up/down.\n");
                 printf("Row: ");
                 scanf("%d", &selectrow);
                 printf("Column: ");
                 scanf("%d", &selectcol);

                 while(board[selectrow][selectcol].stack->col != players[i].col){
                     printf("This is not your token. Please select again.\n");
                     printf("Row: ");
                     scanf("%d", &selectrow);
                     printf("Column: ");
                     scanf("%d", &selectcol);
                 }


                 printf("Token at board[%d][%d] selected. Press 1 to move down, 2 to move up a row.\n", selectrow, selectcol);
                 scanf("%d", &sidestepmove);

                 if(sidestepmove == 1){
                     //movement implementation
                 }

                 else if(sidestepmove == 2){
                     //movement implementation
                 }


             }

             else if(sidestep == 2){
                 continue;
             }

             printf("Dice roll requires you to move a piece from row %d.\n", dice);

             for(int x = 0; x < 9; x++){
                 if(board[dice-1][x].stack->col != players[i].col){
                     printf("None of your pieces are present in this row. Select a different token in this row token to move.\n");
                     scanf("%d", &selectcol);
                 }

                 else{
                     printf("Please select your own token in this row to move.\n");
                     scanf("%d", &selectcol);
                 }


             }

             if(board[dice-1][selectcol].type == OBSTACLE){
                 printf("Token selected is in an obstacle. Checking if move is valid...");
                 for(int x = 0; x < 6; x++){
                     for(int y = 0; y < selectcol; y++){
                         if(board[x][y].stack != NULL){
                             printf("Can't move this token. Please a different token.");
                             scanf("%d", &selectcol);
                             break;
                         }
                     }
                 }

                 //movement implementaion forward
             }

             else{
                 //movement implementation forward
             }




         }
     }
}



            /*
             if (row == -1)
             {
                  printf("\nPress 0 to move down, 1 to move up a row.");
                 scanf("%d", &move);
                 if (move == 0)
                 {
                     n = row+1;
                     board[n][0] = board[row][0];
                 }
                 else if(move == 1)
                 {
                     n= n-1;
                     board[n][0] = board[row][0];
                 }

                 if ( board[n][0].stack->col == players[i].col )
                 {
                     board[n][1] = board[n][0];
                 }

             }

             */
