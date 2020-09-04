//
//  algorithm.h
//  reversiGame
//
//  Created by Karishma Shah on 2020-09-04.
//  Copyright © 2020 Karishma Shah. All rights reserved.
//

#ifndef algorithm_h
#define algorithm_h

//Prints out the default game board given n dimension - no moves made
void startingBoard (int n, char board [][26]);

//Prints out current game board - with moves made
void printBoard (int n, char board [][26]);

//Determines the colour of the computer and user
void whoPlaysWhichColour (char turn, char computerColour, char userColour);

//Finds the opposite colour
char findOpposite (char turn);

//Returns true if a position is within the game board, false otherwise
bool positionInBounds(int n, int row, int col);

//Checks for avaliable moves for a specific colour and stores it in a validMoves array
void avaliableMoves (int n, char board [][26], char colour, char validMoves[][3], int *numMoves);

//Returns true if a move is valid
bool checkLegalInDirection (char board[][26], int n, int row, int col, char colour, int deltaRow, int deltaCol, bool flip);

//Returns true if an entered move is valid, false otherwise
bool isValidMove (int n, char board[][26], int whiteNumMoves, int blackNumMoves, char whiteValidMoves[][3], char blackValidMoves[][3], char row, char column, char userColour);

//Flips all necessary tiles when move is made
void flipInDirection (int n, char board[][26], int row, int column, char colour, int deltaRow, int deltaCol);

//Returns true if a colour has any moves remaining
bool anyMovesLeft (char colour, int whiteNumMoves, int BlackNumMoves);

//Hypothetically places a tile on another duplicate version of the board
void flipTilesOnBoard2 (int n, char board2[][26], int row, int col, char computerColour);

//Returns a heuristic computed value for where the best position would be to place a tile
int getTileScore (int n, char board[][26], int row, int col, char computerColour);

//Returns the number of tiles occupied by the computer on current version of the board
int countBeforeFlip (int n, char board[][26], int computerColour);

//Returns number of corners that can be attained if a specific move were to be made
double numberOfCorners (int n, int row, int col);

//Returns number of sides that can be attained if a specific move were to be made
double numberOfSides (int n, int row, int col);

//Returns number of opponent moves left after a specific move were to be made
int numberOfOpponentMoves (int n, char board [][26], int row, int col, char computerColour, char opponentMoves[][3], int numOpponentMoves);

//Returns the number of tiles of the computer colour on the board after a hypothetical move is made
int countAfterFlip (int n, char board2[][26], char computerColour);

//Returns true if the board is full, false otherwise
bool isBoardFull (int n, char board[][26]);

//Function determines the game winner
char figureOutWinner(int n, char board[][26]);


#endif /* algorithm_h */
