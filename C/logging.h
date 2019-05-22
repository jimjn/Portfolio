#include "Move.h"
#include "Board.h"
#include "Piece.h"
char logMove(BOARD *bd, MOVE mv,  ConvertMove ct,  FILE *log, int turn);

char logAIMove(BOARD *bd, MOVE aiMove,  ConvertMove ct, FILE *log, int turn);

int startLog(FILE *log);

int endLog(FILE *log);

