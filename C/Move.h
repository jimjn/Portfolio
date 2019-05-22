
#ifndef MOVE_H
#define MOVE_H

typedef struct move {
    int src[2];
    int dest[2];
    //int ep;
    //int castle;
} MOVE;

typedef struct convert {
	int src1;
	char src2;
	int dest1;
	char dest2;	
} ConvertMove;

MOVE createMove(int sRow, int sCol, int dRow, int dCol);

ConvertMove convertMove(int sRow, int sCol, int dRow, int dCol);


#endif //MOVE_H
