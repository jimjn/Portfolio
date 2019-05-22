//
// esahaba 01/31/18
// modified by Kevin Chew 1/28
#ifndef LEGALMOVES_H
#define LEGALMOVES_H

#include "Board.h"
#include "Move.h"


void FindLegalMarker(BOARD *bd, int sRow, int sCol);

void ScanLegalMarker(BOARD *bd, COLOR color, TYPE type, int number, int bRow, int bCol);

void SetLegalMarker(BOARD *bd, COLOR color, TYPE type, int number, int bRow, int bCol);

int GetLegalMarker(BOARD *bd, int sRow, int sCol, int dRow, int dCol);

void ClearLegalMarker(BOARD *bd, int dRow, int dCol);

int CheckSafeMove(BOARD *bd, int sRow, int sCol, int dRow, int dCol);

int CheckColor(BOARD *bd, int bRow, int bCol);


#endif
