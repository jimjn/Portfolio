//Kevin Chew 2/1/18
//2/2/18
//2/3/18

#include <stdio.h>
#include <stdlib.h>

#include "Piece.h"
#include "Board.h"
#include "Move.h"
#include "gui.h"
#include "time.h"
#include "LegalMoves.h"

/*General min max Algorithm:
1. loop through each ai color's piece, check legal marker --see if piece is moveable (any destinations, when checklegalmarker == 1)
2. if piece is not moveable, break
2b. if piece is moveable, set currentmove = destination + piece's value
2c. then set best move if function 
3. continue to loop..if new move  
*/

//may change
/*VALUE BestValue() {
	VALUE v;
	v.noTypeValue = 0;
	v.PawnValue = 0;
	v.BishopValue = 0;
	v.RookValue = 0;
	v.KnightValue = 0;	
	v.QueenValue = 0;
	v.KingValue = 0;	
	return v;
}
*/

MOVE SearchMove(BOARD *bd, /*AIBOARD AIBoard,*/ COLOR color, TYPE type, int number, int sRow, int sCol, int dRow, int dCol)
{

int i, j;
int destRow, destCol; //evaluation of best move from AI variables
int currentmove = 0;
int bestmove = 0;

int AIBoard[8][8];
int row,col;
//randomizes board values for AI selection; calls AIBOARD struct
srand(time(NULL));
int random = rand();
for(i=0;i<8;i++) {
for(j=0;j<8;j++) {
	AIBoard[i][j] = random;
	
}
} //end for
#ifdef DEBUG
printf("player/AI: %d,%d\n",getPlayerColor(),!getPlayerColor());
#endif
//for(sRow = 0; sRow <= 7; sRow++)
//	for(sCol = 0;sCol <= 7; sCol++)
//	{

	for(int x = 0; x<=7;x++)
		for(int y = 0; y<=7;y++){
			ClearLegalMarker(bd,x,y);
			FindLegalMarker(bd,x,y);
		}

	/*while(1)
	{
		sRow = rand() % 8;
		sCol = rand() % 8;
		row = rand() % 8;
		col = rand() % 8;
		if(getPlayerColor() != getColor(bd,sRow,sCol) && getColor(bd,sRow,sCol) != white)
		{
			if(GetLegalMarker(bd,sRow,sCol,row,col)==1)										return createMove(sRow,sCol,row,col);

		}
	}*/
	if(getPlayerColor() == 1)//player is black AI is white
	{
	while(1)
	{	
		sRow = rand() % 8;
		sCol = rand() % 8;
		//printf("sRow: %i  sCol %i",sRow,sCol);
		if(getColor(bd,sRow,sCol) == noType)
			continue;
		#ifdef DEBUG
		printf("playercolor %i    piece color: %i",getPlayerColor(),getColor(bd,sRow,sCol));
		#endif
		if(getColor(bd,sRow,sCol) == white)
		{
	//	FindLegalMarker(bd,sRow,sCol);//get the possible moves for piece at sRow sCol
		for(row = 0; row <= 7; row++)
			for(col = 0;col <= 7; col++)
			{
			//	printf("sRow: %i  sCol %i  legalMarker: %i\n",sRow,sCol,GetLegalMarker(bd,sRow,sCol,row,col));

				if(GetLegalMarker(bd,sRow,sCol,row,col) ==1 /*&& getColor(bd,sRow,sCol) ==black && getType(bd,sRow,sCol)>=1 && getType(bd,sRow,sCol)<=6*/)//if its a legal move
				{
					#ifdef DEBUG
					printf("433333333333333333333333333333333 type: %i color:%i\n",getType(bd,sRow,sCol),getColor(bd,sRow,sCol));
					#endif
					
					if(getColor(bd,sRow,sCol) != getColor(bd,row,col))
						return createMove(sRow,sCol,row,col);
				}
				else{
					#ifdef DEBUG
					printf("Legal marker is 000\n");
					#endif
				}

			}
		}
//	scanf("%i",&j);
	}//end of while(1)
	}
	//if(getPlayerColor() == 2)//player is white AI is black
	else
	{
	while(1)
	{	
		sRow = rand() % 8;
		sCol = rand() % 8;
		//printf("sRow: %i  sCol %i",sRow,sCol);
		if(getColor(bd,sRow,sCol) == noType)
			continue;
		#ifdef DEBUG
		printf("playercolor %i    piece color: %i",getPlayerColor(),getColor(bd,sRow,sCol));
		#endif
		if(getColor(bd,sRow,sCol) == black)
		{
		for(row = 0; row <= 7; row++)
			for(col = 0;col <= 7; col++)
			{
			//	printf("sRow: %i  sCol %i  legalMarker: %i\n",sRow,sCol,GetLegalMarker(bd,sRow,sCol,row,col));

				if(GetLegalMarker(bd,sRow,sCol,row,col) ==1 && getColor(bd,sRow,sCol) ==black && getType(bd,sRow,sCol)>=1 && getType(bd,sRow,sCol)<=6)//if its a legal move
				{
					#ifdef DEBUG
					printf("FOound piece type: %i color:%i sRow: %i sCol: %i\n",getType(bd,sRow,sCol),getColor(bd,sRow,sCol),sRow,sCol);
					#endif
					
					if(getColor(bd,sRow,sCol) != getColor(bd,row,col))
						return createMove(sRow,sCol,row,col);
				}
				else {
					
				}
					//printf("Legal marker is 000\n");
			}
		}
	
	}//end of while(1)
	}







//	}
//universal code -- works for black or white
for(sRow=0;sRow<8;sRow++) {
for(sCol=0;sCol<8;sCol++) {



/*-----------------------------------------PAWN------------------------------------*/
	
		//check pawn scenario
		if(getType(bd, sRow, sCol) == pawn)
		{
			//check based on location of the pawn	
			switch(getNumber(bd, sRow, sCol))
				{
				case 0:
					
					//new loop to go through available legal positions 
					for(dRow=0;dRow<8;dRow++) {
					for(dCol=0;dCol<8;dCol++) {	 
				
						//GetLegalMarker checks legal moves, if destination != 1, means no legal moves available; break
						//GetLegalMarker assumes only the possible moves for the piece can be made (e.g. pawn 2 spaces, 1 space, diagonal)
				
							if(GetLegalMarker(bd, sRow, sCol, dRow, dCol) != 1)
							{
							break;
							}
							
							if(GetLegalMarker(bd, sRow, sCol, dRow, dCol) == 1) 
							{
							//if valid then set current move equal to value of AIBoard's random #
							currentmove = AIBoard[dRow][dCol];
							
								//update value of best move for every iteration
								if(currentmove > bestmove)
								{	
								bestmove = currentmove;
								destRow = dRow;
								destCol = dCol;
								}						
							
							}	
					} 
					} //end destination loop 
					
				//returns move (which takes source and destination) to main 
				return createMove(sRow, sCol, destRow, destCol);			
						
						
				case 1:
					
					//new loop to go through available legal positions 
					for(dRow=0;dRow<8;dRow++) {
					for(dCol=0;dCol<8;dCol++) {	 
				
						//GetLegalMarker checks legal moves, if destination != 1, means no legal moves available; break
						//GetLegalMarker assumes only the possible moves for the piece can be made (e.g. pawn 2 spaces, 1 space, diagonal)
				
							if(GetLegalMarker(bd, sRow, sCol, dRow, dCol) != 1)
							{
							break;
							}
							
							if(GetLegalMarker(bd, sRow, sCol, dRow, dCol) == 1) 
							{
							//if valid then set current move equal to value of AIBoard's random #
							currentmove = AIBoard[dRow][dCol];
							
								//update value of best move for every iteration
								if(currentmove > bestmove)
								{	
								bestmove = currentmove;
								destRow = dRow;
								destCol = dCol;
								}						
							
							}	
					} 
					} //end destination loop 
					
				//returns move (which takes source and destination) to main 
				return createMove(sRow, sCol, destRow, destCol);
					
				case 2:
					
					//new loop to go through available legal positions 
					for(dRow=0;dRow<8;dRow++) {
					for(dCol=0;dCol<8;dCol++) {	 
				
						//GetLegalMarker checks legal moves, if destination != 1, means no legal moves available; break
						//GetLegalMarker assumes only the possible moves for the piece can be made (e.g. pawn 2 spaces, 1 space, diagonal)
				
							if(GetLegalMarker(bd, sRow, sCol, dRow, dCol) != 1)
							{
							break;
							}
							
							if(GetLegalMarker(bd, sRow, sCol, dRow, dCol) == 1) 
							{
							//if valid then set current move equal to value of AIBoard's random #
							currentmove = AIBoard[dRow][dCol];
							
								//update value of best move for every iteration
								if(currentmove > bestmove)
								{	
								bestmove = currentmove;
								destRow = dRow;
								destCol = dCol;
								}						
							
							}	
					} 
					} //end destination loop 
					
				//returns move (which takes source and destination) to main 
				return createMove(sRow, sCol, destRow, destCol);
				
				case 3:
					
					//new loop to go through available legal positions 
					for(dRow=0;dRow<8;dRow++) {
					for(dCol=0;dCol<8;dCol++) {	 
				
						//GetLegalMarker checks legal moves, if destination != 1, means no legal moves available; break
						//GetLegalMarker assumes only the possible moves for the piece can be made (e.g. pawn 2 spaces, 1 space, diagonal)
				
							if(GetLegalMarker(bd, sRow, sCol, dRow, dCol) != 1)
							{
							break;
							}
							
							if(GetLegalMarker(bd, sRow, sCol, dRow, dCol) == 1) 
							{
							//if valid then set current move equal to value of AIBoard's random #
							currentmove = AIBoard[dRow][dCol];
							
								//update value of best move for every iteration
								if(currentmove > bestmove)
								{	
								bestmove = currentmove;
								destRow = dRow;
								destCol = dCol;
								}						
							
							}	
					} 
					} //end destination loop 
					
				//returns move (which takes source and destination) to main 
				return createMove(sRow, sCol, destRow, destCol);


				case 4:
					
					//new loop to go through available legal positions 
					for(dRow=0;dRow<8;dRow++) {
					for(dCol=0;dCol<8;dCol++) {	 
				
						//GetLegalMarker checks legal moves, if destination != 1, means no legal moves available; break
						//GetLegalMarker assumes only the possible moves for the piece can be made (e.g. pawn 2 spaces, 1 space, diagonal)
				
							if(GetLegalMarker(bd, sRow, sCol, dRow, dCol) != 1)
							{
							break;
							}
							
							if(GetLegalMarker(bd, sRow, sCol, dRow, dCol) == 1) 
							{
							//if valid then set current move equal to value of AIBoard's random #
							currentmove = AIBoard[dRow][dCol];
							
								//update value of best move for every iteration
								if(currentmove > bestmove)
								{	
								bestmove = currentmove;
								destRow = dRow;
								destCol = dCol;
								}						
							
							}	
					} 
					} //end destination loop 
					
				//returns move (which takes source and destination) to main 
				return createMove(sRow, sCol, destRow, destCol);


				case 5:
					
					//new loop to go through available legal positions 
					for(dRow=0;dRow<8;dRow++) {
					for(dCol=0;dCol<8;dCol++) {	 
				
						//GetLegalMarker checks legal moves, if destination != 1, means no legal moves available; break
						//GetLegalMarker assumes only the possible moves for the piece can be made (e.g. pawn 2 spaces, 1 space, diagonal)
				
							if(GetLegalMarker(bd, sRow, sCol, dRow, dCol) != 1)
							{
							break;
							}
							
							if(GetLegalMarker(bd, sRow, sCol, dRow, dCol) == 1) 
							{
							//if valid then set current move equal to value of AIBoard's random #
							currentmove = AIBoard[dRow][dCol];
							
								//update value of best move for every iteration
								if(currentmove > bestmove)
								{	
								bestmove = currentmove;
								destRow = dRow;
								destCol = dCol;
								}						
							
							}	
					} 
					} //end destination loop 
					
				//returns move (which takes source and destination) to main 
				return createMove(sRow, sCol, destRow, destCol);


				case 6:
					
					//new loop to go through available legal positions 
					for(dRow=0;dRow<8;dRow++) {
					for(dCol=0;dCol<8;dCol++) {	 
				
						//GetLegalMarker checks legal moves, if destination != 1, means no legal moves available; break
						//GetLegalMarker assumes only the possible moves for the piece can be made (e.g. pawn 2 spaces, 1 space, diagonal)
				
							if(GetLegalMarker(bd, sRow, sCol, dRow, dCol) != 1)
							{
							break;
							}
							
							if(GetLegalMarker(bd, sRow, sCol, dRow, dCol) == 1) 
							{
							//if valid then set current move equal to value of AIBoard's random #
							currentmove = AIBoard[dRow][dCol];
							
								//update value of best move for every iteration
								if(currentmove > bestmove)
								{	
								bestmove = currentmove;
								destRow = dRow;
								destCol = dCol;
								}						
							
							}	
					} 
					} //end destination loop 
					
				//returns move (which takes source and destination) to main 
				return createMove(sRow, sCol, destRow, destCol);


				case 7:
					
					//new loop to go through available legal positions 
					for(dRow=0;dRow<8;dRow++) {
					for(dCol=0;dCol<8;dCol++) {	 
				
						//GetLegalMarker checks legal moves, if destination != 1, means no legal moves available; break
						//GetLegalMarker assumes only the possible moves for the piece can be made (e.g. pawn 2 spaces, 1 space, diagonal)
				
							if(GetLegalMarker(bd, sRow, sCol, dRow, dCol) != 1)
							{
							break;
							}
							
							if(GetLegalMarker(bd, sRow, sCol, dRow, dCol) == 1) 
							{
							//if valid then set current move equal to value of AIBoard's random #
							currentmove = AIBoard[dRow][dCol];
							
								//update value of best move for every iteration
								if(currentmove > bestmove)
								{	
								bestmove = currentmove;
								destRow = dRow;
								destCol = dCol;
								}						
							
							}	
					} 
					} //end destination loop 
					
				//returns move (which takes source and destination) to main 
				return createMove(sRow, sCol, destRow, destCol);
	
			} //end switch
	
		} //end pawn if
		

/*--------------------BISHOP, KNIGHT, ROOK----------------------------------*/	
		
		if(getType(bd, sRow, sCol) == bishop)
		{
			//check based on location of the bishop	
			switch(getNumber(bd, sRow, sCol))
			{
				case 0:
					
					//new loop to go through available legal positions 
					for(dRow=0;dRow<8;dRow++) {
					for(dCol=0;dCol<8;dCol++) {	 
				
						//GetLegalMarker checks legal moves, if destination != 1, means no legal moves available; break
						//GetLegalMarker assumes only the possible moves for the piece can be made (e.g. pawn 2 spaces, 1 space, diagonal)
				
							if(GetLegalMarker(bd, sRow, sCol, dRow, dCol) != 1)
							{
							break;
							}
							
							if(GetLegalMarker(bd, sRow, sCol, dRow, dCol) == 1) 
							{
							//if valid then set current move equal to value of AIBoard's random #
							currentmove = AIBoard[dRow][dCol];
							
								//update value of best move for every iteration
								if(currentmove > bestmove)
								{	
								bestmove = currentmove;
								destRow = dRow;
								destCol = dCol;
								}						
							
							}	
					} 
					} //end destination loop 
					
				//returns move (which takes source and destination) to main 
				return createMove(sRow, sCol, destRow, destCol);			
				
				
				case 1:
				
					//new loop to go through available legal positions 
					for(dRow=0;dRow<8;dRow++) {
					for(dCol=0;dCol<8;dCol++) {	 
				
						//GetLegalMarker checks legal moves, if destination != 1, means no legal moves available; break
						//GetLegalMarker assumes only the possible moves for the piece can be made (e.g. pawn 2 spaces, 1 space, diagonal)
				
							if(GetLegalMarker(bd, sRow, sCol, dRow, dCol) != 1)
							{
							break;
							}
							
							if(GetLegalMarker(bd, sRow, sCol, dRow, dCol) == 1) 
							{
							//if valid then set current move equal to value of AIBoard's random #
							currentmove = AIBoard[dRow][dCol];
							
								//update value of best move for every iteration
								if(currentmove > bestmove)
								{	
								bestmove = currentmove;
								destRow = dRow;
								destCol = dCol;
								}						
							
							}	
					} 
					} //end destination loop 
					
				//returns move (which takes source and destination) to main 
				return createMove(sRow, sCol, destRow, destCol);		
	
	
				//extra from promotion
				case 8:
				
					//new loop to go through available legal positions 
					for(dRow=0;dRow<8;dRow++) {
					for(dCol=0;dCol<8;dCol++) {	 
				
						//GetLegalMarker checks legal moves, if destination != 1, means no legal moves available; break
						//GetLegalMarker assumes only the possible moves for the piece can be made (e.g. pawn 2 spaces, 1 space, diagonal)
				
							if(GetLegalMarker(bd, sRow, sCol, dRow, dCol) != 1)
							{
							break;
							}
							
							if(GetLegalMarker(bd, sRow, sCol, dRow, dCol) == 1) 
							{
							//if valid then set current move equal to value of AIBoard's random #
							currentmove = AIBoard[dRow][dCol];
							
								//update value of best move for every iteration
								if(currentmove > bestmove)
								{	
								bestmove = currentmove;
								destRow = dRow;
								destCol = dCol;
								}						
							
							}	
					} 
					} //end destination loop 
					
				//returns move (which takes source and destination) to main 
				return createMove(sRow, sCol, destRow, destCol);	
				
				
				//extra from promotion
				case 9:
				
					//new loop to go through available legal positions 
					for(dRow=0;dRow<8;dRow++) {
					for(dCol=0;dCol<8;dCol++) {	 
				
						//GetLegalMarker checks legal moves, if destination != 1, means no legal moves available; break
						//GetLegalMarker assumes only the possible moves for the piece can be made (e.g. pawn 2 spaces, 1 space, diagonal)
				
							if(GetLegalMarker(bd, sRow, sCol, dRow, dCol) != 1)
							{
							break;
							}
							
							if(GetLegalMarker(bd, sRow, sCol, dRow, dCol) == 1) 
							{
							//if valid then set current move equal to value of AIBoard's random #
							currentmove = AIBoard[dRow][dCol];
							
								//update value of best move for every iteration
								if(currentmove > bestmove)
								{	
								bestmove = currentmove;
								destRow = dRow;
								destCol = dCol;
								}						
							
							}	
					} 
					} //end destination loop 
					
				//returns move (which takes source and destination) to main 
				return createMove(sRow, sCol, destRow, destCol);	
	
			} //end switch

		} //end bishop if


		if(getType(bd, sRow, sCol) == knight)
		{
			//check based on location of the knight	
			switch(getNumber(bd, sRow, sCol))
			{
				case 0:
					
					//new loop to go through available legal positions 
					for(dRow=0;dRow<8;dRow++) {
					for(dCol=0;dCol<8;dCol++) {	 
				
						//GetLegalMarker checks legal moves, if destination != 1, means no legal moves available; break
						//GetLegalMarker assumes only the possible moves for the piece can be made (e.g. pawn 2 spaces, 1 space, diagonal)
				
							if(GetLegalMarker(bd, sRow, sCol, dRow, dCol) != 1)
							{
							break;
							}
							
							if(GetLegalMarker(bd, sRow, sCol, dRow, dCol) == 1) 
							{
							//if valid then set current move equal to value of AIBoard's random #
							currentmove = AIBoard[dRow][dCol];
							
								//update value of best move for every iteration
								if(currentmove > bestmove)
								{	
								bestmove = currentmove;
								destRow = dRow;
								destCol = dCol;
								}						
							
							}	
					} 
					} //end destination loop 
					
				//returns move (which takes source and destination) to main 
				return createMove(sRow, sCol, destRow, destCol);			
				
				
				case 1:
				
					//new loop to go through available legal positions 
					for(dRow=0;dRow<8;dRow++) {
					for(dCol=0;dCol<8;dCol++) {	 
				
						//GetLegalMarker checks legal moves, if destination != 1, means no legal moves available; break
						//GetLegalMarker assumes only the possible moves for the piece can be made (e.g. pawn 2 spaces, 1 space, diagonal)
				
							if(GetLegalMarker(bd, sRow, sCol, dRow, dCol) != 1)
							{
							break;
							}
							
							if(GetLegalMarker(bd, sRow, sCol, dRow, dCol) == 1) 
							{
							//if valid then set current move equal to value of AIBoard's random #
							currentmove = AIBoard[dRow][dCol];
							
								//update value of best move for every iteration
								if(currentmove > bestmove)
								{	
								bestmove = currentmove;
								destRow = dRow;
								destCol = dCol;
								}						
							
							}	
					} 
					} //end destination loop 
					
				//returns move (which takes source and destination) to main 
				return createMove(sRow, sCol, destRow, destCol);		
	
	
				//extra from promotion
				case 8:
				
					//new loop to go through available legal positions 
					for(dRow=0;dRow<8;dRow++) {
					for(dCol=0;dCol<8;dCol++) {	 
				
						//GetLegalMarker checks legal moves, if destination != 1, means no legal moves available; break
						//GetLegalMarker assumes only the possible moves for the piece can be made (e.g. pawn 2 spaces, 1 space, diagonal)
				
							if(GetLegalMarker(bd, sRow, sCol, dRow, dCol) != 1)
							{
							break;
							}
							
							if(GetLegalMarker(bd, sRow, sCol, dRow, dCol) == 1) 
							{
							//if valid then set current move equal to value of AIBoard's random #
							currentmove = AIBoard[dRow][dCol];
							
								//update value of best move for every iteration
								if(currentmove > bestmove)
								{	
								bestmove = currentmove;
								destRow = dRow;
								destCol = dCol;
								}						
							
							}	
					} 
					} //end destination loop 
					
				//returns move (which takes source and destination) to main 
				return createMove(sRow, sCol, destRow, destCol);	
				
				
				//extra from promotion
				case 9:
				
					//new loop to go through available legal positions 
					for(dRow=0;dRow<8;dRow++) {
					for(dCol=0;dCol<8;dCol++) {	 
				
						//GetLegalMarker checks legal moves, if destination != 1, means no legal moves available; break
						//GetLegalMarker assumes only the possible moves for the piece can be made (e.g. pawn 2 spaces, 1 space, diagonal)
				
							if(GetLegalMarker(bd, sRow, sCol, dRow, dCol) != 1)
							{
							break;
							}
							
							if(GetLegalMarker(bd, sRow, sCol, dRow, dCol) == 1) 
							{
							//if valid then set current move equal to value of AIBoard's random #
							currentmove = AIBoard[dRow][dCol];
							
								//update value of best move for every iteration
								if(currentmove > bestmove)
								{	
								bestmove = currentmove;
								destRow = dRow;
								destCol = dCol;
								}						
							
							}	
					} 
					} //end destination loop 
					
				//returns move (which takes source and destination) to main 
				return createMove(sRow, sCol, destRow, destCol);	
	
			} //end switch

		} //end knight if		
		
		
		if(getType(bd, sRow, sCol) == rook)
		{
			//check based on location of the rook	
			switch(getNumber(bd, sRow, sCol))
			{
				case 0:
					
					//new loop to go through available legal positions 
					for(dRow=0;dRow<8;dRow++) {
					for(dCol=0;dCol<8;dCol++) {	 
				
						//GetLegalMarker checks legal moves, if destination != 1, means no legal moves available; break
						//GetLegalMarker assumes only the possible moves for the piece can be made (e.g. pawn 2 spaces, 1 space, diagonal)
				
							if(GetLegalMarker(bd, sRow, sCol, dRow, dCol) != 1)
							{
							break;
							}
							
							if(GetLegalMarker(bd, sRow, sCol, dRow, dCol) == 1) 
							{
							//if valid then set current move equal to value of AIBoard's random #
							currentmove = AIBoard[dRow][dCol];
							
								//update value of best move for every iteration
								if(currentmove > bestmove)
								{	
								bestmove = currentmove;
								destRow = dRow;
								destCol = dCol;
								}						
							
							}	
					} 
					} //end destination loop 
					
				//returns move (which takes source and destination) to main 
				return createMove(sRow, sCol, destRow, destCol);			
				
				
				case 1:
				
					//new loop to go through available legal positions 
					for(dRow=0;dRow<8;dRow++) {
					for(dCol=0;dCol<8;dCol++) {	 
				
						//GetLegalMarker checks legal moves, if destination != 1, means no legal moves available; break
						//GetLegalMarker assumes only the possible moves for the piece can be made (e.g. pawn 2 spaces, 1 space, diagonal)
				
							if(GetLegalMarker(bd, sRow, sCol, dRow, dCol) != 1)
							{
							break;
							}
							
							if(GetLegalMarker(bd, sRow, sCol, dRow, dCol) == 1) 
							{
							//if valid then set current move equal to value of AIBoard's random #
							currentmove = AIBoard[dRow][dCol];
							
								//update value of best move for every iteration
								if(currentmove > bestmove)
								{	
								bestmove = currentmove;
								destRow = dRow;
								destCol = dCol;
								}						
							
							}	
					} 
					} //end destination loop 
					
				//returns move (which takes source and destination) to main 
				return createMove(sRow, sCol, destRow, destCol);		
	
	
				//extra from promotion
				case 8:
				
					//new loop to go through available legal positions 
					for(dRow=0;dRow<8;dRow++) {
					for(dCol=0;dCol<8;dCol++) {	 
				
						//GetLegalMarker checks legal moves, if destination != 1, means no legal moves available; break
						//GetLegalMarker assumes only the possible moves for the piece can be made (e.g. pawn 2 spaces, 1 space, diagonal)
				
							if(GetLegalMarker(bd, sRow, sCol, dRow, dCol) != 1)
							{
							break;
							}
							
							if(GetLegalMarker(bd, sRow, sCol, dRow, dCol) == 1) 
							{
							//if valid then set current move equal to value of AIBoard's random #
							currentmove = AIBoard[dRow][dCol];
							
								//update value of best move for every iteration
								if(currentmove > bestmove)
								{	
								bestmove = currentmove;
								destRow = dRow;
								destCol = dCol;
								}						
							
							}	
					} 
					} //end destination loop 
					
				//returns move (which takes source and destination) to main 
				return createMove(sRow, sCol, destRow, destCol);	
				
				
				//extra from promotion
				case 9:
				
					//new loop to go through available legal positions 
					for(dRow=0;dRow<8;dRow++) {
					for(dCol=0;dCol<8;dCol++) {	 
				
						//GetLegalMarker checks legal moves, if destination != 1, means no legal moves available; break
						//GetLegalMarker assumes only the possible moves for the piece can be made (e.g. pawn 2 spaces, 1 space, diagonal)
				
							if(GetLegalMarker(bd, sRow, sCol, dRow, dCol) != 1)
							{
							break;
							}
							
							if(GetLegalMarker(bd, sRow, sCol, dRow, dCol) == 1) 
							{
							//if valid then set current move equal to value of AIBoard's random #
							currentmove = AIBoard[dRow][dCol];
							
								//update value of best move for every iteration
								if(currentmove > bestmove)
								{	
								bestmove = currentmove;
								destRow = dRow;
								destCol = dCol;
								}						
							
							}	
					} 
					} //end destination loop 
					
				//returns move (which takes source and destination) to main 
				return createMove(sRow, sCol, destRow, destCol);	
	
			} //end switch

		} //end rook if		
	
	
/*-----------------------------------QUEEN------------------------------*/

		if(getType(bd, sRow, sCol) == queen)
		{
			//check based on location of the queen
			switch(getNumber(bd, sRow, sCol))
			{
				case 0:
					
					//new loop to go through available legal positions 
					for(dRow=0;dRow<8;dRow++) {
					for(dCol=0;dCol<8;dCol++) {	 
				
						//GetLegalMarker checks legal moves, if destination != 1, means no legal moves available; break
						//GetLegalMarker assumes only the possible moves for the piece can be made (e.g. pawn 2 spaces, 1 space, diagonal)
				
							if(GetLegalMarker(bd, sRow, sCol, dRow, dCol) != 1)
							{
							break;
							}
							
							if(GetLegalMarker(bd, sRow, sCol, dRow, dCol) == 1) 
							{
							//if valid then set current move equal to value of AIBoard's random #
							currentmove = AIBoard[dRow][dCol];
							
								//update value of best move for every iteration
								if(currentmove > bestmove)
								{	
								bestmove = currentmove;
								destRow = dRow;
								destCol = dCol;
								}						
							
							}	
					} 
					} //end destination loop 
					
				//returns move (which takes source and destination) to main 
				return createMove(sRow, sCol, destRow, destCol);			
				
				
				//extra from promotion
				case 8:
				
					//new loop to go through available legal positions 
					for(dRow=0;dRow<8;dRow++) {
					for(dCol=0;dCol<8;dCol++) {	 
				
						//GetLegalMarker checks legal moves, if destination != 1, means no legal moves available; break
						//GetLegalMarker assumes only the possible moves for the piece can be made (e.g. pawn 2 spaces, 1 space, diagonal)
				
							if(GetLegalMarker(bd, sRow, sCol, dRow, dCol) != 1)
							{
							break;
							}
							
							if(GetLegalMarker(bd, sRow, sCol, dRow, dCol) == 1) 
							{
							//if valid then set current move equal to value of AIBoard's random #
							currentmove = AIBoard[dRow][dCol];
							
								//update value of best move for every iteration
								if(currentmove > bestmove)
								{	
								bestmove = currentmove;
								destRow = dRow;
								destCol = dCol;
								}						
							
							}	
					} 
					} //end destination loop 
					
				//returns move (which takes source and destination) to main 
				return createMove(sRow, sCol, destRow, destCol);	
				
				
				//extra from promotion
				case 9:
				
					//new loop to go through available legal positions 
					for(dRow=0;dRow<8;dRow++) {
					for(dCol=0;dCol<8;dCol++) {	 
				
						//GetLegalMarker checks legal moves, if destination != 1, means no legal moves available; break
						//GetLegalMarker assumes only the possible moves for the piece can be made (e.g. pawn 2 spaces, 1 space, diagonal)
				
							if(GetLegalMarker(bd, sRow, sCol, dRow, dCol) != 1)
							{
							break;
							}
							
							if(GetLegalMarker(bd, sRow, sCol, dRow, dCol) == 1) 
							{
							//if valid then set current move equal to value of AIBoard's random #
							currentmove = AIBoard[dRow][dCol];
							
								//update value of best move for every iteration
								if(currentmove > bestmove)
								{	
								bestmove = currentmove;
								destRow = dRow;
								destCol = dCol;
								}						
							
							}	
					} 
					} //end destination loop 
					
				//returns move (which takes source and destination) to main 
				return createMove(sRow, sCol, destRow, destCol);	
	
			} //end switch

		} //end queen if		
		
/*----------------------------------------KING--------------------------------*/

	
		if(getType(bd, sRow, sCol) == king)
		{
			//new loop to go through available legal positions 
			for(dRow=0;dRow<8;dRow++) {
			for(dCol=0;dCol<8;dCol++) {	 
		
				//GetLegalMarker checks legal moves, if destination != 1, means no legal moves available; break
				//GetLegalMarker assumes only the possible moves for the piece can be made (e.g. pawn 2 spaces, 1 space, diagonal)
		
				if(GetLegalMarker(bd, sRow, sCol, dRow, dCol) != 1)
				{
				break;
				}
				
				if(GetLegalMarker(bd, sRow, sCol, dRow, dCol) == 1) 
				{
				//if valid then set current move equal to value of AIBoard's random #
				currentmove = AIBoard[dRow][dCol];
				
					//update value of best move for every iteration
					if(currentmove > bestmove)
					{	
					bestmove = currentmove;
					destRow = dRow;
					destCol = dCol;
					}						
				
				}	
			} 
			} //end destination loop 
			
		//returns move (which takes source and destination) to main 
		return createMove(sRow, sCol, destRow, destCol);			
		} //end king if
		

	}
	} //end source for loops

	return createMove(0,0,1,1);//you need a return in a non void function
} //end search move function

/*
//returns highest valued move
int EvaluateMove(BOARD *bd, enum PieceType, VALUE v, int Row, int Col)
{
	
	

if(getColor(bd, sRow, sCol) == white)

{
//if player is white, ai is black and bottom row will be most valued (negative)
if (getPlayerColor() == 0)
{
	int AI_value = 10000000;
	int i,j;
	
	//loop through board to determine values for pieces
	for(i=5;i<7;i++) {
	for(j=0;j<7;j++) {

		if(getColor(bd, i, j) == white)
		{
			if(getType(bd, i, j) == noType)
			{v.noTypeValue = -1000;}

			else if (getType(bd, i, j) == pawn)
			{v.PawnValue = -500;}

			else if(getType(bd, i, j) == rook)
			{v.RookValue = -1500;}

			else if(getType(bd, i, j) == knight)
			{v.KnightValue = -2500;}

			else if(getType(bd, i, j) == bishop)
			{v.BishopValue = -2500;}

			else if(getType(bd, i, j) == queen)
			{v.QueenValue = -5000;}

			else if(getType(bd, i, j) == king)
			{v.KingValue = -10000;}
		} //end if
 
	}
	} //end fors
	
}//end if player is white




//if player is black, ai is white and top row will be most valued (most positive)
if (getPlayerColor() = 1)
{
	int AI_value = -10000000;
	int i,j;
	
	//loop through board to determine values for pieces
	for(i=0;i<3;i++) {
	for(j=0;j<7;j++) {

		if(getColor(bd, i, j) == black)
		{
			if(getType(bd, i, j) == noType)
			{v.noTypeValue = 1000;}

			else if (getType(bd, i, j) == pawn)
			{v.PawnValue = 500;}

			else if(getType(bd, i, j) == rook)
			{v.RookValue = 1500;}

			else if(getType(bd, i, j) == knight)
			{v.KnightValue = 2500;}

			else if(getType(bd, i, j) == bishop)
			{v.BishopValue = 2500;}

			else if(getType(bd, i, j) == queen)
			{v.QueenValue = 5000;}

			else if(getType(bd, i, j) == king)
			{v.KingValue = 10000;}
		} //end if
  
    }
	} //end fors
}//end if player is black



//feeds best value into function which will execute move









} //end eval move

*/
