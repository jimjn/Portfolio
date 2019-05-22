#ifndef BOARD_H
#define BOARD_H

#include "Piece.h"
#include "Move.h"


typedef struct {
    PIECE *piece;
    int legalMovesMatrix[4][16];
} SQUARE;

typedef struct {
    SQUARE *chessBoard[8][8];
} BOARD;

SQUARE *createSquare();

BOARD *createBoard();

//Memory Management
void deleteBoard(BOARD *bd);

//Memory Management
void deleteSquare(SQUARE *sq);

//Initialize Board
void fillBoard(BOARD *bd, enum pieceColor playerColor);

//Gets type of piece in coordinate
TYPE getType(BOARD *bd, int row, int col);

//Gets type of color in coordinate
COLOR getColor(BOARD *bd, int row, int col);

//gets the canEp field
int getEp(BOARD *bd, int row, int col);

//gets the hasmoved field
int getHM(BOARD *bd, int row, int col);

//returns the number field from the piece in the coordinate
int getNumber(BOARD *bd, int row, int col);

//returns the alive field from the piece in the coordinate
int getAlive(BOARD *bd, int row, int col);

int getLMAElement(BOARD *bd, int bRow, int bCol, int aRow, int aCol);

void setLMAElement(BOARD *bd, int bRow, int bCol, int aRow, int aCol, int val);

//executes a move depending on if its a catle, en passant, or standard move, return 1 if invalid, return 0 if valid
int doMove(BOARD *bd, MOVE mv);

//sets legal markers for castling
void SetCastleMarkers(BOARD *bd);

//updates the canEp field for each piece
void updateEp(BOARD *bd);

//Moves a piece on the board struct
void movePiece(BOARD *bd, MOVE mv);

//Deletes a piece from the board structure
void deleteBoardPiece(BOARD *bd, int row, int col);

//make sure to call this after checking if move is valid, will check the type of the piece in destination of move so
//call this after moving the piece
int checkPromotion(BOARD *bd, MOVE mv);

//makes a new piece struct pointer and assigns it to the destination of the move
void doPromotion(BOARD *bd, MOVE mv, TYPE t);

void undoMove(BOARD *bd, MOVE oppMv, MOVE plrMv, PIECE *oppKill, PIECE *plrKill);

int isInCheck(BOARD *bd,COLOR side);

MOVE isInCheckMate(BOARD *bd, COLOR side);


#endif //BOARD_H