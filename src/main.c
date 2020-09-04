//  main.c
//  reversiGame
//
//  Created by Karishma Shah on 2020-03-29.
//  Copyright © 2020 Karishma Shah. All rights reserved.
 
#include <stdio.h>
#include <stdbool.h>
#include "algorithm.h"
 
int main(void) {
  
  int n;
 
  printf ("Enter the board dimension: ");
  scanf ("%d", &n);
  
  char board[n][26];
 
  char turn = 'B';
  char computerColour, userColour;
 
  printf ("Computer plays (B/W): ");
  scanf (" %c", &computerColour);
 
  if (computerColour == 'B') userColour = 'W';
  else userColour = 'B';
 
  startingBoard(n, board);
 
  char whiteValidMoves[676][3], blackValidMoves[676][3];
  int whiteNumMoves = 0, blackNumMoves = 0;
 
  bool gamePlay = true;
  
  while (gamePlay){
    if (computerColour == 'B'){
      
      whiteNumMoves = 0;
      blackNumMoves = 0;
      avaliableMoves (n, board, computerColour, blackValidMoves, &blackNumMoves);
      avaliableMoves (n, board, userColour, whiteValidMoves, &whiteNumMoves);
      
      if (turn == computerColour){
        //filling in the scores corresponding to each valid move in the 3rd column of array
        for (int i = 0; i < blackNumMoves; i++){
          blackValidMoves [i][2] = getTileScore (n, board, blackValidMoves[i][0] - 'a', blackValidMoves[i][1] - 'a', computerColour);
        }
        
        //initializing the first valid move as the highest thus far
        char highestScoreRow = blackValidMoves[0][0] , highestScoreCol = blackValidMoves [0][1];
        int highestScore = (int) blackValidMoves[0][2];
        
        //comparing the scores to find the highest one
        for (int i = 0; i < blackNumMoves; i++){
          if (blackValidMoves [i][2] > highestScore){
              highestScore = (int) blackValidMoves[i][2];
              highestScoreRow = blackValidMoves[i][0];
              highestScoreCol = blackValidMoves[i][1];
          }else{
            continue;
          }
        }
      
          board[highestScoreRow - 'a'][highestScoreCol - 'a'] = 'B';
        
          printf ("Computer places %c at %c%c.\n", computerColour, highestScoreRow, highestScoreCol);
        
          for (int deltaRow = -1; deltaRow <= 1; deltaRow++){
            for (int deltaCol = -1; deltaCol <= 1; deltaCol++){
              checkLegalInDirection(board, n, highestScoreRow - 'a', highestScoreCol - 'a', computerColour, deltaRow, deltaCol, true);
            }
          }
        
          printBoard (n, board);
          
          
        }else{
          int row, col;
            
          findSmarterMove(board, n, userColour, &row, &col);
          printf ("Testing AI move (row, col): %c%c\n", row + 'a', col + 'a');
 
          if (!isValidMove(n, board, whiteNumMoves, blackNumMoves, whiteValidMoves, blackValidMoves, row + 'a' , col + 'a' ,userColour)){
 
            printf ("Invalid move.\n");
            printf ("%c player wins.\n", computerColour);
            gamePlay = false;
            
          }else{
            printBoard (n, board);
 
          }
        }
        if (gamePlay){
          if (anyMovesLeft(findOpposite(turn), whiteNumMoves, blackNumMoves)){
            turn = findOpposite(turn);
          }else if (anyMovesLeft(turn, whiteNumMoves, blackNumMoves)){
            turn = turn;
            printf ("%c player has no valid move.\n", findOpposite(turn));
          }else{
            gamePlay = false;
            char winner = figureOutWinner(n, board);
            printf ("%c player wins.\n", winner);
          }
        }
    }else{
      
      whiteNumMoves = 0;
      blackNumMoves = 0;
      avaliableMoves (n, board, computerColour, whiteValidMoves, &whiteNumMoves);
      avaliableMoves (n, board, userColour, blackValidMoves, &blackNumMoves);
      
      if (turn == computerColour){
        for (int i = 0; i < whiteNumMoves; i++){
          whiteValidMoves [i][2] = getTileScore (n, board, whiteValidMoves[i][0] - 'a', whiteValidMoves[i][1] - 'a', computerColour);
        }
        
        //initializing the first valid move as the highest thus far
        char highestScoreRow = whiteValidMoves[0][0] , highestScoreCol = whiteValidMoves [0][1];
        int highestScore = (int) whiteValidMoves[0][2];
        
        //comparing the scores to find the highest one
        for (int i = 0; i < whiteNumMoves; i++){
          if (whiteValidMoves [i][2] > highestScore){
              highestScore = (int) whiteValidMoves[i][2];
              highestScoreRow = whiteValidMoves[i][0];
              highestScoreCol = whiteValidMoves[i][1];
          }else{
            continue;
          }
        }
          
        printf ("Computer places %c at %c%c.\n", computerColour, highestScoreRow, highestScoreCol);
        board[highestScoreRow - 'a'][highestScoreCol - 'a'] = 'W';
        
        for (int deltaRow = -1; deltaRow <= 1; deltaRow++){
          for (int deltaCol = -1; deltaCol <= 1; deltaCol++){
            checkLegalInDirection(board, n, highestScoreRow - 'a', highestScoreCol - 'a', computerColour, deltaRow, deltaCol, true);
          }
        }
        
        printBoard (n, board);
    
        }else{
          int row, col;
            
          findSmarterMove(board, n, userColour, &row, &col);
          printf ("Testing AI move (row, col): %c%c\n", row + 'a', col + 'a');
 
          if (!isValidMove(n, board, whiteNumMoves, blackNumMoves, whiteValidMoves, blackValidMoves, row + 'a' , col + 'a' ,userColour)){
            
            printf ("Invalid move.\n");
            printf ("%c player wins.\n", computerColour);
            gamePlay = false;
            
          }else{
            printBoard (n, board);
 
          }
        }
        if (gamePlay){
          if (anyMovesLeft(findOpposite(turn), whiteNumMoves, blackNumMoves)){
            turn = findOpposite(turn);
          }else if (anyMovesLeft(turn, whiteNumMoves, blackNumMoves) && (!isBoardFull(n, board))){
            turn = turn;
            printf ("%c player has no valid move.\n", findOpposite(turn));
          }else{
            gamePlay = false;
            char winner = figureOutWinner(n, board);
            printf ("%c player wins.\n", winner);
          }
        }
      }
    }
  return 0;
}
  



