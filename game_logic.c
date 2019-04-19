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

            if(board[selectedSquare][0].numTokens == minNumOfTokens){

               // printf("here\n");
                if(board[selectedSquare][0].numTokens == 0){
                    current = (token *)malloc(sizeof(token));
                    board[selectedSquare][0].stack = current;
                    board[selectedSquare][0].stack->col = players[j].col;
                    board[selectedSquare][0].stack->next = NULL;
                    print_board(board);


                }
                else{
                    current = (token *)malloc(sizeof(token));
                    current->col = players[j].col;
                    current->next = board[selectedSquare][0].stack;
                    board[selectedSquare][0].stack = current;
                    print_board(board);
                }

                board[selectedSquare][0].numTokens++;
            }



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

     int n;
     int dice = 0;
     int selectrow, selectcol;
     int sidestep;
     int winner;

     token* moving;

     while (players[0].numTokensLastCol !=3 && players[1].numTokensLastCol !=3 && players[2].numTokensLastCol !=3 && players[3].numTokensLastCol !=3 && players[4].numTokensLastCol !=3&&
             players[5].numTokensLastCol !=3)
     {
         for(int i=0;i<numPlayers;i++)
         {
             dice = (rand()%6);
             printf("Player %d. Your dice roll is : %d\n\n", i+1, dice);

             int sidestepmove=0;
             printf("Do you want to do a sidestep? Enter 1 if you want to do a sidestep. Enter 2 to skip this.\n");
             scanf("%d", &sidestep);

             if(sidestep == 1){     //ask user to perform side step

                 printf("Select your token you wish to move the up/down.\n");
                 printf("Row: ");
                 scanf("%d", &selectrow);
                 printf("Column: ");
                 scanf("%d", &selectcol);

                 while(board[selectrow][selectcol].stack->col != players[i].col){   //if selected stack doesnt have player's token on top, ask to input again
                     printf("This is not your token. Please select again.\n");
                     printf("Row: ");
                     scanf("%d", &selectrow);
                     printf("Column: ");
                     scanf("%d", &selectcol);
                     printf("token on this row is %c\n" ,print_token(board[selectrow][selectcol].stack));
                     printf("player token is %c\n" ,players[i].col);
                 }


                 printf("Token at board[%d][%d] selected. Press 1 to move down, 2 to move up a row.\n", selectrow, selectcol);
                 scanf("%d", &sidestepmove);
                 printf("sidestepmove is : %d \n", sidestepmove);

                 if(sidestepmove == 1){
                     //movement implementation
                     moving = board[selectrow][selectcol].stack;
                     board[selectrow][selectcol].stack = moving->next;
                     moving->next = board[selectrow+1][selectcol].stack;
                     board[selectrow+1][selectcol].stack = moving;
                     print_board(board);
                 }

                 else if(sidestepmove == 2){
                     moving = board[selectrow][selectcol].stack;
                     board[selectrow][selectcol].stack = moving->next;
                     moving->next = board[selectrow+1][selectcol].stack;
                     board[selectrow-1][selectcol].stack = moving;
                     print_board(board);
                     //movement implementation
                 }


             }

             else if(sidestep == 2){
                 print_board(board);
             }

             printf("Dice roll requires you to move a piece from row %d.\n", dice);
             printf("Select a token in this row token to move.\n");
             scanf("%d", &selectcol);

             while(board[dice][selectcol].stack == NULL){
                 printf("No token in this square. Please select again.\n");
                 scanf("%d", &selectcol);
             }
       /*
             int found = 0;
             for(int n = 0; found != 1; n++){
                 if(board[dice][n].stack->col == players[i].col || board[dice][n].stack == NULL){
                     found = 1;
                 }
                 else{
                     found = 0;
                 }
             }

             if(found = 0){
                 printf("None of your pieces are present in this row. Select a different token in this row token to move.\n");
                 scanf("%d", &selectcol);
             }

             else if(found = 1){
                 printf("Please select your own token in this row to move.\n");
                 scanf("%d", &selectcol);
                 while(board[dice][selectcol].stack->col != players[i].col){
                     printf("Invalid token. This is not your token. Please choose again.\n");
                     scanf("%d", &selectcol);
                 }
             }
*/
                //if selected token was in an obstacle, must check all spaces before this token, if there's no tokens before obstacle token, it can be moved
             if(board[dice][selectcol].type == OBSTACLE){
                 printf("Token selected is in an obstacle. Checking if move is valid...\n");
                 for(int x = 0; x < 6; x++){
                     for(int y = 0; y < selectcol; y++){
                         if(board[x][y].stack != NULL){
                             printf("Can't move this token. Please choose a different token.");
                             printf("Row: \n");
                             scanf("%d", &selectrow);
                             printf("Column: \n");
                             scanf("%d", &selectcol);
                         }
                     }
                 }

                 while(board[selectrow][selectcol].stack == NULL){
                     printf("No tokens in this square. Please select again.\n");
                     printf("Row: \n");
                     scanf("%d", &selectrow);
                     printf("Column: \n");
                     scanf("%d", &selectcol);
                 }

                 //movement implementaion forward
                 moving = board[selectrow][selectcol].stack;
                 board[selectrow][selectcol].stack = moving->next;
                 moving->next = board[selectrow][selectcol + 1].stack;
                 board[selectrow][selectcol + 1].stack = moving;
                 print_board(board);

                 if((selectcol + 1) == 8){
                     players[i].numTokensLastCol += 1;
                     winner = i;
                 }


             }

             else{
                 //movement implementation forward
                 moving = board[dice][selectcol].stack;
                 board[dice][selectcol].stack = moving->next;
                 moving->next = board[dice][selectcol + 1].stack;
                 board[dice][selectcol + 1].stack = moving;
                 print_board(board);

                 if((selectcol + 1) == 8){
                     players[i].numTokensLastCol += 1;
                     winner = i;
                 }

             }

         }
     }

     printf("The winner is Player %d!", winner);
}
