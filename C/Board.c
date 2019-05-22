//
// Created by jingtaoz on 1/23/2018.
//
#include <stdlib.h>
#include <stdio.h>
#include "Board.h"
#include "Piece.h"
#include "LegalMoves.h"

SQUARE *createSquare() {
    SQUARE *s;
    s = malloc(sizeof(SQUARE));
    s->piece = NULL;
    //s->bR0
    return s;
};

BOARD *createBoard() {
    BOARD *bd;
    bd = malloc(sizeof(BOARD));
    if (!bd) {
        perror("out of mem");
        exit(1);
    }
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            bd->chessBoard[i][j] = createSquare();
        }
    }
    printf("board created\n");
    return bd;
}

void deleteBoard(BOARD *bd) {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            deleteSquare(bd->chessBoard[i][j]);
        }
    }
    //free(bd->chessBoard);
    free(bd);
}

void deleteSquare(SQUARE *sq) {
    deletePiece(sq->piece);
    free(sq);
}

void fillBoard(BOARD *bd, enum pieceColor playerColor) {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            bd->chessBoard[i][j]->piece = NULL;
        }
    }

#ifdef DEBUG
    //playerColor = white;
#endif

    for (int i = 2; i < 6; i++) {
        for (int j = 0; j < 8; j++) {
            bd->chessBoard[i][j]->piece = initBlank();
        }
    }
		
    for (int i = 0; i < 8; i++) {

        bd->chessBoard[6][i]->piece = initWhitePawn(i);
        bd->chessBoard[1][i]->piece = initBlackPawn(i);
    }
    bd->chessBoard[0][0]->piece = initBlackRook(0);
    bd->chessBoard[0][7]->piece = initBlackRook(1);
    bd->chessBoard[7][0]->piece = initWhiteRook(0);
    bd->chessBoard[7][7]->piece = initWhiteRook(1);

    bd->chessBoard[0][1]->piece = initBlackKnight(0);
    bd->chessBoard[0][6]->piece = initBlackKnight(1);
    bd->chessBoard[7][1]->piece = initWhiteKnight(0);
    bd->chessBoard[7][6]->piece = initWhiteKnight(1);

    bd->chessBoard[0][2]->piece = initBlackBishop(0);
    bd->chessBoard[0][5]->piece = initBlackBishop(1);
    bd->chessBoard[7][2]->piece = initWhiteBishop(0);
    bd->chessBoard[7][5]->piece = initWhiteBishop(1);

    bd->chessBoard[0][3]->piece = initBlackQueen(0);
    bd->chessBoard[0][4]->piece = initBlackKing();
    bd->chessBoard[7][3]->piece = initWhiteQueen(0);
    bd->chessBoard[7][4]->piece = initWhiteKing();
	
    printf("board filled\n");
}

TYPE getType(BOARD *bd, int row, int col) {
    if(row<=7 && row>=0 && col <=7 &&col>=0){
    if (bd->chessBoard[row][col]->piece == NULL) {
        return noType;
    } else {
	#ifdef DEBUG
	//printf("piece type at row: %i column %i: %i\n",row,col,bd->chessBoard[row][col]->piece->type);
	#endif
        return bd->chessBoard[row][col]->piece->type;
    }}
    return noType;
}

COLOR getColor(BOARD *bd, int row, int col) {
    if(row<=7 && row>=0 && col<=7 && col>=0){
    if (bd->chessBoard[row][col]->piece == NULL) {
        return noColor;
    }
    return bd->chessBoard[row][col]->piece->color;
    }
    return noColor;
}

int getEp(BOARD *bd, int row, int col) {
    if (bd->chessBoard[row][col]->piece == NULL) {
        return 0;
    }
    return bd->chessBoard[row][col]->piece->canEp;
}

int getHM(BOARD *bd, int row, int col) {
    if (bd->chessBoard[row][col]->piece == NULL) {
        return 0;
    }
    return bd->chessBoard[row][col]->piece->hasMoved;
}

int getNumber(BOARD *bd, int row, int col) {
    if (bd->chessBoard[row][col]->piece == NULL) {
        return 0;
    }
    return bd->chessBoard[row][col]->piece->number;
}

int getAlive(BOARD *bd, int row, int col) {
    if (bd->chessBoard[row][col]->piece == NULL) {
        return 0;
    }
    return bd->chessBoard[row][col]->piece->alive;
}

int getLMAElement(BOARD *bd, int bRow, int bCol, int aRow, int aCol) {
    int q = 0;
	if(bRow<=7 && bRow >=0 && bCol <= 7 && bCol >=0)
	{
	q = bd->chessBoard[bRow][bCol]->legalMovesMatrix[aRow][aCol];

	}
    return q;
}

void setLMAElement(BOARD *bd, int bRow, int bCol, int aRow, int aCol, int val) {
    #ifdef DEBUG
    //printf("setLMAElement: bRow %i, bCol %i, aRow %i, val %i\n",bRow,bCol,aRow,aCol);
    #endif
    if(bRow<=7 && bRow >=0 && bCol <= 7 && bCol >=0)
    bd->chessBoard[bRow][bCol]->legalMovesMatrix[aRow][aCol] = val;
}

void deleteBoardPiece(BOARD *bd, int row, int col) {
    bd->chessBoard[row][col]->piece->type = noType;
    bd->chessBoard[row][col]->piece->color = noColor;
    bd->chessBoard[row][col]->piece->alive = 0;
    bd->chessBoard[row][col]->piece->number = 0;
    bd->chessBoard[row][col]->piece->hasMoved = 0;
    bd->chessBoard[row][col]->piece->canEp = 0;
}

int doMove(BOARD *bd, MOVE mv) {
    printf("doing move\n");
    int src[2] = {mv.src[0], mv.src[1]};
    int dest[2] = {mv.dest[0], mv.dest[1]};

    //checks if src and dest are in bounds
    if (src[0] > 7 || src[0] < 0 || src[1] > 7 || src[1] < 0 ||
        dest[0] > 7 || dest[0] < 0 || dest[1] > 7 || dest[1] < 0) {
        return 1;
    }

    //checks if src and dest are equal to each other
    if (src[0] == dest[0] && src[1] == dest[1]) {
        return 1;
    }

    //Castling
    //if the piece is king and hasn't moved
    if (getType(bd, src[0], src[1]) == king && getHM(bd, src[0], src[1]) == 0) {
        //for king's side castle (going to the right)
        if (dest[1] == src[1] + 2) {
            //checks if there is a rook where it's supposed to be and if it has moved or not
            if (getType(bd, src[0], src[1] + 3) == rook && getHM(bd, src[0], src[1]) == 0) {
                movePiece(bd, mv);
                MOVE rookMv = createMove(src[0], src[1] + 3, dest[0], dest[1] - 1);
                movePiece(bd, rookMv);
				return 0;
            }
        }
        //for queen's side castle (going to the left)
        if (dest[1] == src[1] - 2) {
            //checks if there is a rook where it's supposed to be and if it has moved or not
            if (getType(bd, src[0], src[1] - 4) == rook && getHM(bd, src[0], src[1]) == 0) {
                movePiece(bd, mv);
                MOVE rookMv = createMove(src[0], src[1] - 4, dest[0], dest[1] + 1);
                movePiece(bd, rookMv);
				return 0;
            }
        }        
    }

    //en passant going up
    if (dest[0] == 2) {
	#ifdef DEBUG
        printf("check1\n");
	#endif
        if (getColor(bd, dest[0] + 1, dest[1]) != getColor(bd, src[0], src[1])) {
	    #ifdef DEBUG
            printf("check2\n");
	    #endif
            if (getEp(bd, dest[0] + 1, dest[1]) > 0) {
		#ifdef DEBUG
                printf("check3\n");
		#endif
                movePiece(bd, mv);
                deleteBoardPiece(bd, dest[0] + 1, dest[1]);
				return 0;
            }
        }        
    }

    //en passant going down
    if (dest[0] == 5) {
	#ifdef DEBUG
        printf("check1\n");
	#endif
        if (getColor(bd, dest[0] - 1, dest[1]) != getColor(bd, src[0], src[1])) {
	    #ifdef DEBUG
            printf("check2\n");
	    #endif
            if (getEp(bd, dest[0] - 1, dest[1]) > 0) {
		#ifdef DEBUG
                printf("check3\n");
		#endif
                movePiece(bd, mv);
                deleteBoardPiece(bd, dest[0] - 1, dest[1]);
				return 0;
            }
        }
    }

    //if move is legal {
    movePiece(bd, mv);
    //}
    return 1;
}

void SetCastleMarkers(BOARD *bd) {
	#ifdef DEBUG
	printf("settign casle markers\n");
	#endif
	//castle for white
	if (getType(bd, 0, 4) == king && getHM(bd, 0, 4) == 0) {       
        if (getType(bd, 0,5) == 0 && getType(bd, 0,6) == 0 && getType(bd, 0,7) == rook && getHM(bd, 0,7) == 0) {
			SetLegalMarker(bd, black, king, 56, 0, 6);
        }
		if (getType(bd, 0,1) == 0 && getType(bd, 0,2) == 0 && getType(bd,0,3) == 0 && getType(bd, 0,0) == rook && getHM(bd, 0,0) == 0) {
			SetLegalMarker(bd, black, king, 56, 0, 2);
        }
	}
	
	//castle for black
	if (getType(bd, 7, 4) == king && getHM(bd, 7, 4) == 0) {
        if (getType(bd, 7,5) == 0 && getType(bd, 7,6) == 0 && getType(bd, 7,7) == rook && getHM(bd, 7,7) == 0) {
				SetLegalMarker(bd, white, king, 0, 7, 6);
        }
		if (getType(bd, 7,1) == 0 && getType(bd, 7,2) == 0 && getType(bd,7,3) == 0 && getType(bd, 7,0) == rook && getHM(bd, 7,0) == 0) {
				SetLegalMarker(bd, white, king, 0, 7, 2);
        }
	}
}

/* On the turn that a turn becomes EPable, (i.e your turn), canEp is set to 2. At the end of each turn, updateEp is
 * called which divides the canEp value of each piece by 2. So on the turn that someone is able to EP, the piece will
 * have a canEp value of 1, and on the turn after that it will be 0.
 */
void updateEp(BOARD *bd) {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            bd->chessBoard[i][j]->piece->canEp /= 2;
        }
    }
}

void movePiece(BOARD *bd, MOVE mv) {
    int dest[2] = {mv.dest[0], mv.dest[1]};
    int src[2] = {mv.src[0], mv.src[1]};

    PIECE *temp = bd->chessBoard[src[0]][src[1]]->piece;

    //checking to set en passant
    if (temp->type == pawn && temp->hasMoved == 0) {
        if (src[0] == 1 && dest[0] == 3) {
            temp->canEp = 2;
        } else if (src[0] == 6 && dest[0] == 4) {
            temp->canEp = 2;
        }
    }
    #ifdef DEBUG	
	printf("src %i %i    dest %i %i\n",src[0],src[1],dest[0],dest[1]);
    if(bd->chessBoard[dest[0]][dest[1]]->piece == NULL)
	printf("dest piece is null\n");
    if(bd->chessBoard[dest[0]][dest[1]]->piece == NULL)
	printf("dest piece type is null\n");
    if(temp == NULL)
	printf("temp is null\n");
    #endif
    bd->chessBoard[dest[0]][dest[1]]->piece->type = temp->type;
    bd->chessBoard[dest[0]][dest[1]]->piece->color = temp->color;
    bd->chessBoard[dest[0]][dest[1]]->piece->alive = temp->alive;
    bd->chessBoard[dest[0]][dest[1]]->piece->number = temp->number;
    bd->chessBoard[dest[0]][dest[1]]->piece->canEp = temp->canEp;
    bd->chessBoard[dest[0]][dest[1]]->piece->hasMoved = 1;

    temp->type = noType;
    temp->color = noColor;
    temp->alive = 0;
    temp->number = 0;
    temp->hasMoved = 0;
    temp->canEp = 0;
#ifdef DEBUG
    printf("Type: %i Color: %i\n",bd->chessBoard[dest[0]][dest[1]]->piece->type,bd->chessBoard[dest[0]][dest[1]]->piece->color);
#endif
}

int checkPromotion(BOARD *bd, MOVE mv) {
    //int src[2] = {mv.src[0], mv.src[1]};
    int dest[2] = {mv.dest[0], mv.dest[1]};

    //if piece moving is pawn
    if (getType(bd, dest[0], dest[1]) == pawn) {
        //if its going to first or last row
        if (dest[0] == 0 || dest[0] == 7) {
            return 1;
        }
    }
    return 0;
}

void doPromotion(BOARD *bd, MOVE mv, TYPE t) {
    //int src[2] = {mv.src[0], mv.src[1]};
    int dest[2] = {mv.dest[0], mv.dest[1]};
    static int num = 8;

    //PIECE *p = NULL;

    if (getColor(bd, dest[0], dest[1]) == black) {
        switch (t) {
            case pawn:
                bd->chessBoard[dest[0]][dest[1]]->piece->type = pawn;
                bd->chessBoard[dest[0]][dest[1]]->piece->number = num;
                break;
            case rook:
                bd->chessBoard[dest[0]][dest[1]]->piece->type = rook;
                bd->chessBoard[dest[0]][dest[1]]->piece->number = num;
                break;
            case knight:
                bd->chessBoard[dest[0]][dest[1]]->piece->type = knight;
                bd->chessBoard[dest[0]][dest[1]]->piece->number = num;
                break;
            case bishop:
                bd->chessBoard[dest[0]][dest[1]]->piece->type = bishop;
                bd->chessBoard[dest[0]][dest[1]]->piece->number = num;
                break;
            case queen:
                bd->chessBoard[dest[0]][dest[1]]->piece->type = queen;
                bd->chessBoard[dest[0]][dest[1]]->piece->number = num;
                break;
            default:
                printf("something went wrong\n");
                return;
        }
    } else if (getColor(bd, dest[0], dest[1]) == white) {
        switch (t) {
            case pawn:
                bd->chessBoard[dest[0]][dest[1]]->piece->type = pawn;
                bd->chessBoard[dest[0]][dest[1]]->piece->number = num;
                break;
            case rook:
                bd->chessBoard[dest[0]][dest[1]]->piece->type = rook;
                bd->chessBoard[dest[0]][dest[1]]->piece->number = num;
                break;
            case knight:
                bd->chessBoard[dest[0]][dest[1]]->piece->type = knight;
                bd->chessBoard[dest[0]][dest[1]]->piece->number = num;
                break;
            case bishop:
                bd->chessBoard[dest[0]][dest[1]]->piece->type = bishop;
                bd->chessBoard[dest[0]][dest[1]]->piece->number = num;
                break;
            case queen:
                bd->chessBoard[dest[0]][dest[1]]->piece->type = queen;
                bd->chessBoard[dest[0]][dest[1]]->piece->number = num;
                break;
            default:
                printf("something went wrong\n");
                return;
        }
    }
    num++;
}

void undoMove(BOARD *bd, MOVE oppMv, MOVE plrMv, PIECE *oppKill, PIECE *plrKill) {
    MOVE revOppMv = createMove(oppMv.dest[0], oppMv.dest[1], oppMv.src[0], oppMv.src[1]);
    movePiece(bd, revOppMv);
    bd->chessBoard[oppMv.dest[0]][oppMv.dest[1]]->piece->type = oppKill->type;
    bd->chessBoard[oppMv.dest[0]][oppMv.dest[1]]->piece->number = oppKill->number;
    bd->chessBoard[oppMv.dest[0]][oppMv.dest[1]]->piece->color = oppKill->color;
    bd->chessBoard[oppMv.dest[0]][oppMv.dest[1]]->piece->alive = oppKill->alive;
    bd->chessBoard[oppMv.dest[0]][oppMv.dest[1]]->piece->hasMoved = oppKill->hasMoved;
    bd->chessBoard[oppMv.dest[0]][oppMv.dest[1]]->piece->canEp = oppKill->canEp;
    
    MOVE revPlrMv = createMove(plrMv.dest[0], plrMv.dest[1], plrMv.src[0], plrMv.src[1]);
    movePiece(bd, revPlrMv);
    bd->chessBoard[plrMv.dest[0]][plrMv.dest[1]]->piece->type = plrKill->type;
    bd->chessBoard[plrMv.dest[0]][plrMv.dest[1]]->piece->number = plrKill->number;
    bd->chessBoard[plrMv.dest[0]][plrMv.dest[1]]->piece->color = plrKill->color;
    bd->chessBoard[plrMv.dest[0]][plrMv.dest[1]]->piece->alive = plrKill->alive;
    bd->chessBoard[plrMv.dest[0]][plrMv.dest[1]]->piece->hasMoved = plrKill->hasMoved;
    bd->chessBoard[plrMv.dest[0]][plrMv.dest[1]]->piece->canEp = plrKill->canEp;
    
}

int isInCheck(BOARD *bd,COLOR side)
{
	int rowKING,colKING;

	/*get the position of the king of COLOR side*/
	for(int x = 0; x <= 7; x++)
		for(int y = 0; y <= 7; y++)
		{
			if(getColor(bd,x,y) == side && getType(bd,x,y) == king)
			{
				rowKING = x;
				colKING = y;
			}
		}

	/*Check whether another piece can move where the king is*/
	for(int x = 0; x <= 7; x++)
		for(int y = 0; y <= 7; y++)
		{
			/*if the piece is on the other teamm*/
			if(getColor(bd,x,y) != side)
			{
				/*Check if it can kill the king*/
				if(GetLegalMarker(bd,x,y,rowKING,colKING)==1)
					return 1;

			}

		}

	return 0;

}


MOVE isInCheckMate(BOARD *bd, COLOR side)
{
	int rowKING,colKING, check = 0;//check: 0 is safe, 1 is check, 2 is checkmate
	MOVE rightMove;
	/*get the position of the king of COLOR side*/
	for(int x = 0; x <= 7; x++)
		for(int y = 0; y <= 7; y++)
		{
			if(getColor(bd,x,y) == side && getType(bd,x,y) == king)
			{
				rowKING = x;
				colKING = y;
			}
		}
	
	check = isInCheck(bd,side);
	if(check == 0) {
		rightMove = createMove(100,100,100,100);
		return rightMove;
	}
		
	else{	
	/*assume its in checkmate*/
	check = 2;
	PIECE *p = initBlank();
	for(int x = 0; x <= 7; x++)
		for(int y = 0; y <= 7; y++)
		{
			/*if its the same color as the king*/
			if(getColor(bd,x,y) == side)
			{
				FindLegalMarker(bd,x,y);
				#ifdef DEBUG
				printf("ERROR check 1\n");
				#endif
				/*Do all possible moves for that piece*/
				for(int row = 0; row <= 7; row++)
					for(int col = 0; col <= 7; col++)
					{
						//printf("test %d\n", row * col);
						/*if this piece has a valid move*/
						#ifdef DEBUG
						printf("x: %d, y: %d, row: %d, col: %d, LM: %d\n", x, y, row, col, GetLegalMarker(bd, x, y, row, col));
						#endif
						if(GetLegalMarker(bd,x,y,row,col) == 1)
						{
							/*do the move*/
							/*check if its in check still*/
								//if it got out of check
								//check =1;
							/*undo the move*/
							#ifdef DEBUG
							printf("ERROR ERROR in loop\n");
							#endif
							int toReturn = 0;

							MOVE mv = createMove(x, y, row, col);
							
							p->type = getType(bd, row, col);
							p->number = getNumber(bd, row, col);
							p->color = getColor(bd, row, col);
							p->alive = getAlive(bd, row, col);
							p->hasMoved = getHM(bd, row, col);
							p->canEp = getEp(bd, row, col);
							
							movePiece(bd, mv);
							
							if (isInCheck(bd, side) != 1) {
								check = 1;
								rightMove = createMove(x, y, row, col);
								toReturn = 1;
								//return rightMove;
								//return 1;
							}
							//undoing move
							mv = createMove(row, col, x, y);
							movePiece(bd, mv);
							bd->chessBoard[row][col]->piece->type = p->type;
							bd->chessBoard[row][col]->piece->number = p->number;
							bd->chessBoard[row][col]->piece->color = p->color;
							bd->chessBoard[row][col]->piece->alive = p->alive;
							bd->chessBoard[row][col]->piece->hasMoved = p->hasMoved;
							bd->chessBoard[row][col]->piece->canEp = p->canEp;
							if (toReturn == 1) {
								deletePiece(p);
								return rightMove;
							}
						}
						
					}
					
			}
			
		}
	deletePiece(p);
	}//end of else

	rightMove = createMove(50,50,50,50);
	return rightMove;
}

