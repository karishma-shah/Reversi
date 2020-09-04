//
//  algorithm.c
//  reversiGame
//
//  Created by Karishma Shah on 2020-09-04.
//  Copyright © 2020 Karishma Shah. All rights reserved.
//

#include <stdio.h>
#include <stdbool.h>
#include "algorithm.h"

//Prints out the default game board given n dimension - no moves made
void startingBoard (int n, char board [][26]){
  //print out the letters on top row
  printf ("  ");
  for (int i = 0; i < n; i ++){
    printf ("%c", 'a'+i);
  }
  for (int i = 0; i < n; i++){
    //print out letters across first column
    printf ("\n");
    printf ("%c ", 'a' + i);
    //printing starting board
    for (int j = 0; j < n; j++){
      if (((i == n/2) && (j== n/2))|| ((j == (n/2)-1) && (i == (n/2)-1))){
        board[i][j] = 'W';
      }else if (((i == (n/2)-1) && (j == n/2)) || ((j == (n/2)-1) && (i == n/2))){
        board[i][j] = 'B';
      }else{
        board[i][j] = 'U';
      }
      printf ("%c", board[i][j]);
    }
  }
  printf("\n");
}

//Prints out current game board - with moves made
void printBoard (int n, char board[][26]){
  
      printf ("  ");
      for (int i = 0; i < n; i ++){
        printf ("%c", 'a' + i);
      }
      for (int i = 0; i < n; i++){
        printf ("\n");
        printf ("%c ", 'a' + i);
        for (int j = 0; j < n; j++){
          printf ("%c", board[i][j]);
        }
      }printf ("\n");
}

//Determines the colour of the computer and user
void whoPlaysWhichColour (char turn, char computerColour, char userColour){
  if (turn == computerColour){
    computerColour = 'B';
    userColour = 'W';
  }else{
    computerColour = 'W';
    userColour = 'B';
  }
}

//Finds the opposite colour
char findOpposite (char turn){
  if (turn == 'B') return 'W';
  else return 'B';
}

//Returns true if a position is within the game board, false otherwise
bool positionInBounds(int n, int row, int col){
  if ((row >= 0) && (col >= 0) && (row < n) && (col < n)){
    return true;
  }else{
    return false;
  }
}

//Checks for avaliable moves for a specific colour and stores it in a validMoves array
void avaliableMoves (int n, char board [][26], char colour, char validMoves[][3], int *numMoves){
  //loops through entire board
  for (int i = 0; i < n; i++){
    for (int j = 0; j < n; j++){
      //tile must be unoccupied
      if (board[i][j] == 'U'){
        //checks all directions (8)
        for (int deltaRow = -1; deltaRow <= 1; deltaRow++){
          for (int deltaCol = -1; deltaCol <= 1; deltaCol ++){
            // if the move is legal, it appends the move to a validMoves array
            if(checkLegalInDirection (board, n, i, j, colour, deltaRow, deltaCol, false)){
              validMoves[*numMoves][0] = 'a'+ i;
              validMoves[*numMoves][1] = 'a'+ j;
              //next row
              *numMoves = *numMoves + 1;
            }
          }
        }
      }
    }
  }
}

//Returns true if a move is valid
bool checkLegalInDirection (char board[][26], int n, int row, int col, char colour, int deltaRow, int deltaCol, bool flip){
    
  int initialRow  = row;
  int initialCol = col;
    
  row = row + deltaRow;
  col = col + deltaCol;
 
  bool legalPosition = false;
 
  if (positionInBounds (n, row, col)){
    if (board[row][col] == 'U' || board[row][col] == colour ){
      legalPosition = false;
      
    }else{
      //increments down the line until it hits the same colour
      while (board[row][col] != 'U' && positionInBounds (n, row, col)){
        if (board[row][col] == colour){
          legalPosition = true;
          //if the function is called when wanting to flip tiles, it will call another function
          if (flip == true){
            flipInDirection (n, board, initialRow, initialCol, colour, deltaRow, deltaCol);
          }
            
          break;
        }
        row = row + deltaRow;
        col = col + deltaCol;
 
      }
    }
  }return legalPosition;
}

//Returns true if an entered move is valid, false otherwise
bool isValidMove (int n, char board[][26], int whiteNumMoves, int blackNumMoves, char whiteValidMoves[][3], char blackValidMoves[][3], char row, char column, char userColour){
  bool valid = false;
 
  if (userColour == 'W'){
    for (int j = 0; j < whiteNumMoves && !valid; j++){
      //matches entered move to the one stored in the array in avaliableMoves function
      if ((row == whiteValidMoves[j][0]) && (column == whiteValidMoves[j][1])){
        row = row - 'a';
        column = column - 'a';
        board[row][column] = userColour;
        valid = true;
 
        for (int deltaRow = -1; deltaRow <= 1; deltaRow++){
          for (int deltaCol = -1; deltaCol <= 1; deltaCol ++){
              //calling checkLegalInDirection to flip the tiles
              checkLegalInDirection(board, n, row, column, userColour, deltaRow, deltaCol, true);
          }
        }
 
        break;
      }
    }
    return valid;
 
  }else{
    for (int j = 0; j < blackNumMoves && !valid; j++){
      if ((row == blackValidMoves[j][0]) && (column == blackValidMoves[j][1])){
        row = row - 'a';
        column = column - 'a';
        board[row][column] = userColour;
        valid = true;
 
        for (int deltaRow = -1; deltaRow <= 1; deltaRow++){
          for (int deltaCol = -1; deltaCol <= 1; deltaCol ++){
              checkLegalInDirection(board, n, row, column, userColour, deltaRow, deltaCol, true);
          }
        }
        break;
      }
    }
    return valid;
  }
  
}

//Flips all necessary tiles when move is made
void flipInDirection (int n, char board[][26], int row, int column, char colour, int deltaRow, int deltaCol){
    
    row += deltaRow;
    column += deltaCol;
    
    //incrementing row and col until you hit the same colour tile and changing the board accordingly
    do{
      board[row][column] = colour;
      row += deltaRow;
      column += deltaCol;
      
    }while (board[row][column] != colour);
    
}

//Returns true if a colour has any moves remaining
bool anyMovesLeft (char colour, int whiteNumMoves, int blackNumMoves){
  if (colour == 'W'){
    if (whiteNumMoves == 0){
      return false;
    }else{
      return true;
    }
  }else{
    if (blackNumMoves == 0){
      return false;
    }else{
      return true;
    }
  }
}

//Hypothetically places a tile on another duplicate version of the board
void flipTilesOnBoard2 (int n, char board2[][26], int row, int col, char computerColour){
  
  board2[row][col] = computerColour;
  
  for (int i = 0; i < n; i++){
    for (int j = 0; j < n; j++){
      for (int deltaRow = -1; deltaRow <=1; deltaRow++){
        for (int deltaCol = -1; deltaCol <=1; deltaCol++){
          //flipping tiles on board2
          checkLegalInDirection(board2, n, row, col, computerColour, deltaRow, deltaCol, true);
          
        }
      }
    }
  }
}

//Returns a heuristic computed value for where the best position would be to place a tile
int getTileScore (int n, char board[][26], int row, int col, char computerColour){
  
  int initialCount, flipCount, opponentMovesCount, score;
  double numCorners, numSides;
  
  initialCount = countBeforeFlip(n, board, computerColour);
  
  //PUT IN COPY BOARD FXN
  char board2 [26][26];
  for (int i = 0; i < n; i++){
    for (int j = 0; j < n; j++){
      board2[i][j] = board[i][j];
    }
  }
 
  flipTilesOnBoard2 (n, board2, row, col, computerColour);
  flipCount = countAfterFlip (n, board2, computerColour);
  
  numCorners = numberOfCorners(n, row, col);
  numSides = numberOfSides (n, row, col);
  
  char opponentMoves [676][3];
  int numOpponentMoves = 0;
  
  opponentMovesCount = numberOfOpponentMoves(n, board, row, col, computerColour, opponentMoves, numOpponentMoves);
  
  //score = a * #flips + b * #corners + c* #sides + e*number of opponentMoves
  score = (70*(flipCount - initialCount - 1)) + (100*numCorners) + (20*numSides) - (50*opponentMovesCount);
 
  return score;
}

//Returns the number of tiles occupied by the computer on current version of the board
int countBeforeFlip (int n, char board[][26], int computerColour){
  int count = 0;
  
  //counting number of computerColour tiles initially before flip
  for (int i = 0; i < n; i++){
    for (int j = 0; j < n; j++){
      if (board[i][j] == computerColour){
        count++;
      }
    }
  }
  return count;
}

//Returns number of corners that can be attained if a specific move were to be made
double numberOfCorners (int n, int row, int col){
  double numCorners = 0;
  
  if ((row == 0 && col == 0) || (row == n-1 && col == n-1) || (row == 0 && col == n -1) || (row == n-1 && col == 0)){
    numCorners = 1;
  } else{
    numCorners = 0;
  }
  
  return numCorners;
}
 
//Returns number of sides that can be attained if a specific move were to be made
double numberOfSides (int n, int row, int col){
  double numSides = 0;
  
  if ((row == 0 || col == 0 || row == n-1 || col == n-1)){
    numSides =  1;
  }else{
    numSides = 0;
  }
  
  return numSides;
}
 
//Returns number of opponent moves left after a specific move were to be made
int numberOfOpponentMoves (int n, char board [][26], int row, int col, char computerColour, char opponentMoves[][3], int numOpponentMoves){
  
  char board2 [26][26];
  for (int i = 0; i < n; i++){
    for (int j = 0; j < n; j++){
      board2[i][j] = board[i][j];
    }
  }
  //theoretical flip on copy board
  flipTilesOnBoard2 (n, board2, row, col, computerColour);
  
  //find how many moves for opponent
  avaliableMoves(n, board2, findOpposite(computerColour), opponentMoves, &numOpponentMoves);
  
  return numOpponentMoves;
}

//Returns the number of tiles of the computer colour on the board after a hypothetical move is made
int countAfterFlip (int n, char board2[][26], char computerColour){
  int count = 0;
  //counting number of computerColour tiles initially before flip
  for (int i = 0; i < n; i++){
    for (int j = 0; j < n; j++){
      if (board2[i][j] == computerColour){
        count++;
      }
    }
  }
  return count;
}

//Returns true if the board is full, false otherwise
bool isBoardFull (int n, char board[][26]){
  for (int i = 0; i < n; i++){
    for (int j = 0; j < n; j++){
      if (board[i][j] == 'U'){
        return false;
      }
    }
  }
  return true;
}

//Function determines the game winner
char figureOutWinner(int n, char board[][26]){
  int spacesOccupiedByWhite = 0;
  int spacesOccupiedByBlack = 0;
  
  for (int i = 0; i < n; i++){
    for (int j = 0; j < n; j++){
      if (board[i][j] == 'W'){
        spacesOccupiedByWhite++;
      }else{
        spacesOccupiedByBlack++;
      }
    }
  }
  if (spacesOccupiedByBlack > spacesOccupiedByWhite){
    return 'B';
  }else{
    return 'W';
  }
}

