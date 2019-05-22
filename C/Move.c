#include <stdlib.h>
#include <stdio.h>
#include "Move.h"
#include "Piece.h"

MOVE createMove(int sRow, int sCol, int dRow, int dCol) {
    MOVE mv;
    mv.src[0] = sRow;
    mv.src[1] = sCol;
    mv.dest[0] = dRow;
    mv.dest[1] = dCol;
    //mv.ep = ep;
    //mv.castle = castle;
    return mv;
}

ConvertMove convertMove(int sRow, int sCol, int dRow, int dCol)
{
	char newsCol,newdCol; 
	ConvertMove ct;
	ct.src1 =8 - sRow;
	
	if(sCol==0)
		newsCol='a';
    else if(sCol==1)
        newsCol='b';
    else if(sCol==2)
        newsCol='c';
    else if(sCol==3)
        newsCol='d';
	else if(sCol==4)
		newsCol='e';
	else if(sCol==5)
		newsCol='f';
	else if(sCol==6)
		newsCol='g';
	else if(sCol==7)
		newsCol='h';
	
	ct.src2 = newsCol;		
	ct.dest1 =8 - dRow;
	
    if(dCol==0)
        newdCol='a';
    else if(dCol==1)
        newdCol='b';
    else if(dCol==2)
        newdCol='c';
	else if(dCol==3)
		newdCol='d';
	else if(dCol==4)
		newdCol='e';
	else if(dCol==5)
		newdCol='f';
	else if(dCol==6)
		newdCol='g';
	else if(dCol==7)
		newdCol='h';
	
	ct.dest2 = newdCol;
	
	return ct;	
}


//checkmove for pawn rook knight
