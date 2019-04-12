/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */


#include "game_init.h"
#include <stdio.h>


/*
 * This function creates the board for the first time
 *
 * Input: board - a 6x9 array of squares
 *
 */
 void initialize_board(square board[NUM_ROWS][NUM_COLUMNS]){

     for (int i =0; i< NUM_ROWS; i++){
         for(int j =0; j < NUM_COLUMNS; j++){
             //creates an obstacle square at positions (0,3), (1,6), (2,4), (3,5), (4,2) and (5,7)
             if((i == 0 && j==3) || (i == 1 && j == 6) || (i ==2 && j ==4)
                     || (i == 3 && j ==5) || (i==4 && j==2) || (i==5 && j==7)){
                 board[i][j].type = OBSTACLE;
             } else{
                 //creates a normal square otherwise
                 board[i][j].type = NORMAL;
             }
             board[i][j].stack = NULL;
             board[i][j].numTokens = 0;
         }
     }
 }


 /*
 * This function creates players for the first time
 *
 * Input: the array of players to be initialized
 * Output: The number of players of the game
 */
int initialize_players(player players[]){
    int j;
    enum color choice;
    char playercolors[6][10] = {"RED", "BLUE", "GREEN", "YELLOW", "PINK", "ORANGE"};
    choice = RED;
    printf("Player 1: RED;\nPlayer 2: BLU;\nPlayer 3: GREEN;\nPlayer 4: YELLOW;\nPlayer 5: PINK;\nPlayer 6: ORANGE;\n");
    printf("Enter how many players are playing: ");
    scanf("%d", &j);

    int i = 0;
    while(i<j){
        printf("Enter Name for Player %d: ", i+1);
        scanf("%s",players[i].name);

        players[i].col = choice+i;
        printf("Color for Player%d, %s, is %s.\n", i+1, players[i].name, playercolors[i]);
        ++i;
    }

        return i;
    }
