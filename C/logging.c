#include <stdio.h>
#include "logging.h"

char logMove(BOARD *bd, MOVE mv, ConvertMove ct, FILE *log,int turn)

{
	//check to see if log has been openned
	if(!log)
		return 1;
	//print color
	int src[2] = {mv.src[0],mv.src[1]};
		if(turn%2 !=0){
			fprintf(log,"%s","White: ");
			if(getType(bd, src[0], src[1] == pawn)){
				fprintf(log,"%s %c%i %s %c%i\n","pawn",ct.src2,ct.src1,"to",ct.dest2,ct.dest1);
			}
			else if(bd->chessBoard[src[0]][src[1]]->piece->type==rook){
				fprintf(log,"%s %c%i %s %c%i\n","rook",ct.src2,ct.src1,"to",ct.dest2,ct.dest1);
					}
			else if(bd->chessBoard[src[0]][src[1]]->piece->type==knight){
				fprintf(log,"%s %c%i %s %c%i\n","knight",ct.src2,ct.src1,"to",ct.dest2,ct.dest1);
					}
			else if(bd->chessBoard[src[0]][src[1]]->piece->type==bishop){
				fprintf(log,"%s %c%i %s %c%i\n","bishop",ct.src2,ct.src1,"to",ct.dest2,ct.dest1);
					}
			else if(bd->chessBoard[src[0]][src[1]]->piece->type==queen){
				fprintf(log,"%s %c%i %s %c%i\n","queen",ct.src2,ct.src1,"to",ct.dest2,ct.dest1);
					}
			else if(bd->chessBoard[src[0]][src[1]]->piece->type==king){
				fprintf(log,"%s %c%i %s %c%i\n","king",ct.src2,ct.src1,"to",ct.dest2,ct.dest1);
			}
		}
	return 0;
}
char logAIMove(BOARD *bd, MOVE aiMove, ConvertMove ct, FILE *log,int turn){
	int aisrc[2]={aiMove.dest[0],aiMove.dest[1]} ;
                if(turn %2==0){
                        fprintf(log,"%s","Black: " );
			if(bd->chessBoard[aisrc[0]][aisrc[1]]->piece->type==pawn){
				fprintf(log,"%s %c%i %s %c%i\n","pawn",ct.src2,ct.src1,"to",ct.dest2,ct.dest1);
                                }
                        else if(bd->chessBoard[aisrc[0]][aisrc[1]]->piece->type==rook){
                                fprintf(log,"%s %c%i %s %c%i\n","rook",ct.src2,ct.src1,"to",ct.dest2,ct.dest1);
                                }
                        else if(bd->chessBoard[aisrc[0]][aisrc[1]]->piece->type==knight){
                                fprintf(log,"%s %c%i %s %c%i\n","knight",ct.src2,ct.src1,"to",ct.dest2,ct.dest1);
  	                        }
                        else if(bd->chessBoard[aisrc[0]][aisrc[1]]->piece->type==bishop){
                                fprintf(log,"%s %c%i %s %c%i\n","bishop",ct.src2,ct.src1,"to",ct.dest2,ct.dest1);
                                }
                        else if(bd->chessBoard[aisrc[0]][aisrc[1]]->piece->type==queen){
                                fprintf(log,"%s %c%i %s %c%i\n","queen",ct.src2,ct.src1,"to",ct.dest2,ct.dest1);
                                }
                        else if(bd->chessBoard[aisrc[0]][aisrc[1]]->piece->type==king){
                                fprintf(log,"%s %c%i %s %c%i\n","king",ct.src2,ct.src1,"to",ct.dest2,ct.dest1);
                                }
	}
	return 0;
}

int startLog(FILE *log)
{
	if(!log)
		return 1;
	fprintf(log,"%s","Chess by the ROOKies\n\n");
	fprintf(log,"%s","1: Play vs Computer\n");
	fprintf(log,"%s","2: Normal Difficulty\n");
	fprintf(log,"%s","\nBegin:\n\n");
	return 0;
}


int endLog(FILE *log)
{
	if(!log)
		return 1;
	fprintf(log,"%s", "\nGame over\n");
	return 0;
}
