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

  for(int i = 0; i<4; i++){
      for(int j = 0; j<numPlayers; j++){

          printf("Player %d please select a square\n", j+1);
          scanf("%d", &selectedSquare);

          if(board[selectedSquare][0].numTokens == minNumOfTokens && board[selectedSquare][0].stack->col != players[j].col){
              if(board[selectedSquare][0].numTokens == 0){
                  board[selectedSquare][0].stack->top = NULL;
                  board[selectedSquare][0].stack->curr = NULL;
              }

              board[selectedSquare][0].stack->curr = board[selectedSquare][0].stack->top;
              board[selectedSquare][0].stack->top = (token *)malloc(sizeof(token));
              board[selectedSquare][0].stack->top->col = players[j].col;
              board[selectedSquare][0].stack->top->next = board[selectedSquare][0].stack->curr;

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
     int row, move, n;
     int dice =0;
     int j=0;
     while (players[0].numTokensLastCol !=3 || players[1].numTokensLastCol !=3 || players[2].numTokensLastCol !=3|| players[3].numTokensLastCol !=3 || players[4].numTokensLastCol !=3||
             players[5].numTokensLastCol !=3)
     {
         for(int i=0;i<numPlayers;i++)
         {
             dice = 1+(rand()%6);
             printf("Player %d. Your dice roll is : %d\n\n", i+1, dice);
             printf("Select the row you wish to move the token up/down. Or enter -1 to skip this");
             scanf("%d", &row);
             if (row == -1)
             {
                 continue;
             }
             else
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

         }

     }
     }
