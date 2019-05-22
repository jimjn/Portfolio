//Kevin Chew 2/1/18
//2/2/18
//2/3/18

#include "Piece.h"
#include "Board.h"
#include "Move.h"

#ifndef AI_H
#define AI_H

typedef struct{
	int AIBoard[8][8];
} AIBOARD;
MOVE SearchMove(BOARD *bd,/* AIBOARD AIBoard,*/ COLOR color, TYPE type, int number, int sRow, int sCol, int dRow, int dCol);
/*
int EvaluateMove(BOARD *bd, enum PieceType, int sRow, int sCol);

typedef struct {
	int noTypeValue;
	int PawnValue;
	int BishopValue;
	int KnightValue;
	int RookValue;
	int QueenValue;
	int KingValue;
} VALUE;

*/



#endif
