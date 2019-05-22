#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "X11/Xlib.h"
#include "SDL/SDL.h"

typedef enum pieceType {
    noType, pawn, rook, knight, bishop, queen, king
} TYPE;
/* noType = 0
 * pawn = 1
 * rook = 2
 * knight = 3
 * bishop = 4
 * queen = 5
 * king = 6
 */

typedef enum pieceColor {
    noColor, black, white
} COLOR;
/* noColor = 0
 * black = 1
 * white = 2
 */

typedef struct {
    TYPE type;
    COLOR color;
    int alive;      //1 = alive, 0 = captured
    int number;
    int hasMoved;        //for castling, 0 = no, 1 = yes
    int canEp;            //if the piece can be en passanted, 0 = no, 1 = yes
} PIECE;

//PIECE *createPiece();
void deletePiece(PIECE *p);

PIECE *initBlank();

PIECE *initWhitePawn(int n);

PIECE *initWhiteRook(int n);

PIECE *initWhiteKnight(int n);

PIECE *initWhiteBishop(int n);

PIECE *initWhiteQueen(int n);

PIECE *initWhiteKing(void);

PIECE *initBlackPawn(int n);

PIECE *initBlackRook(int n);

PIECE *initBlackKnight(int n);

PIECE *initBlackBishop(int n);

PIECE *initBlackQueen(int n);

PIECE *initBlackKing(void);

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
void FindLegalMarker(BOARD *bd, int sRow, int sCol);

void ScanLegalMarker(BOARD *bd, COLOR color, TYPE type, int number, int bRow, int bCol);

void SetLegalMarker(BOARD *bd, COLOR color, TYPE type, int number, int bRow, int bCol);

int GetLegalMarker(BOARD *bd, int sRow, int sCol, int dRow, int dCol);

void ClearLegalMarker(BOARD *bd, int dRow, int dCol);

int CheckSafeMove(BOARD *bd, int sRow, int sCol, int dRow, int dCol);

int CheckColor(BOARD *bd, int bRow, int bCol);
typedef struct rowColumnInput{
	int row;
	int column;
	int quit;
	int ep;
	int castle;
	int promotion;

}INPUT;

int *colorPTR;
SDL_Surface *background,
		*pawnB,
		*pawnW,
		*rookB,
		*rookW,
		*kingB,
		*kingW,
		*queenB,
		*queenW,
		*bishopB,
		*bishopW,
		*knightB,
		*knightW,
		*screen,
		*highlight,
		*mainscreen;

TYPE promotionInput();
void startGUI();
void endGUI();
//void printValidMoves(BOARD *bd,int row,int column);
INPUT getMouseClicks(SDL_Event event);
void printBoard(BOARD *bd,int row,int column, int pValidMoves);
int mainscreenwindow(SDL_Event event);
int getPlayerColor();

void cleanup(BOARD *bd, FILE *log, int *colorPTR);

int main() {

    FILE *log;
    BOARD *bd;
    SDL_Event event;
    int quit =0,gameOver = 0, color;//game flow variables
    int rowSrc, columnSrc, rowDes, columnDes;//moving variables
    INPUT rowColumn;
    int turn; //turn counter: odd = player; even = AI;
    colorPTR = malloc(sizeof(int));
    if (!colorPTR) {
        printf("memory error\n");
        exit(10);
    }
    //create log/print start
    log = fopen("gamelog.txt", "w");
    //startLog(log);
    startLog(log);
    //initialize board
    bd = createBoard();
    //startGUI
    startGUI();
    //Input color from user
    color = mainscreenwindow(event);

    if (color == 1)//1 is black, 2 is white
        turn = 2;//AI starts
    else if (color == 2)
        turn = 1;//HUMAN starts


#ifdef DEBUG
    printf("color %i\n",color);
    printf("Ending mainscreen window\n");
#endif


    //fill board
    fillBoard(bd, color);
	#ifdef DEBUG	
	printf("Type: %d, Color: %d, Number: %d ERROR", getType(bd, 0,4), getColor(bd, 0,4), getNumber(bd, 0,4));
	#endif

    if (color == -1) {
        cleanup(bd, log, colorPTR);
    }


#ifdef DEBUG
    printf("Finished startGUI()\n");
#endif
    printBoard(bd,0,0,0);//print board

    //Game play loop (assume user is white right now)
    while (quit != 1 && gameOver != 1) {

        while (turn % 2 != 0) {//odd
            //User input
	    do{
            //wait for mouse click loop
            rowColumn = getMouseClicks(event);
            //get rowSrc and columnSrc from INPUT struct returned from getMouseClicks function
            rowSrc = rowColumn.row;
            columnSrc = rowColumn.column;
            if (rowColumn.quit == 1) {
                cleanup(bd, log, colorPTR);
	    }
		
	    //figure out possible moves
		ClearLegalMarker(bd,rowSrc,columnSrc);
	    FindLegalMarker(bd,rowSrc,columnSrc);
        SetCastleMarkers(bd);
            //print possible moves
            printBoard(bd,rowSrc,columnSrc,1);

            //wait for mouse click loop
            rowColumn = getMouseClicks(event);
            //get rowDes and columnDes from INPUT struct returned from getMouseClicks function
            rowDes = rowColumn.row;
            columnDes = rowColumn.column;
            if (rowColumn.quit == 1) {
                cleanup(bd, log, colorPTR);
	    }

	    }while(GetLegalMarker(bd,rowSrc,columnSrc,rowDes,columnDes)!=1);//if its not a legal move
			MOVE checkMateMove = isInCheckMate(bd, 3 - color);
			if (checkMateMove.src[0] == 100) {
			
			} else if (checkMateMove.src[0] == 50) {
				printf("incheckmate");	
				gameOver = 1;
			} else if (checkMateMove.src[0] != 50) {
				printf("player in check\n");
			} 
            //Whatever function are needed to actually do this move
            MOVE mv = createMove(rowSrc, columnSrc, rowDes, columnDes);
			
			//Log the user's move
			ConvertMove ct = convertMove(rowSrc, columnSrc, rowDes, columnDes);
			logMove(bd ,mv, ct, log, turn);	
            //deleteBoardPiece(bd,rowSrc,columnSrc);
			printf("USER MOVE (source/destination): domove: %d\n\tRow: %i Col: %i ------> Row: %i Col: %i\n",doMove(bd, mv),mv.src[0],mv.src[1],mv.dest[0],mv.dest[1]);

			
			//clear legal marker/find new legal marker
			ClearLegalMarker(bd,rowDes,columnDes);
            FindLegalMarker(bd,rowDes,columnDes);
			
			//updates en passant flag
			updateEp(bd);
            //update the board
            printBoard(bd,0,0,0);
			
			if (checkPromotion(bd, mv) == 1) {
				TYPE promoType = 0;
				promoType = promotionInput();
				printf("promotype: %d\n", promoType);
				doPromotion(bd, mv, promoType);
				FindLegalMarker(bd,rowDes,columnDes);
			}
			
			
            //increment turn
            turn ++;

        }//end of user while loop

        /*while (turn % 2 == 0) {//AI loop
			
		MOVE checkMateMove = isInCheckMate(bd, 3 - color);
		if (checkMateMove.src[0] == 100) {
	
		} else if (checkMateMove.src[0] == 50) {
			printf("incheckmate");	
			gameOver = 1;
	    } else if (checkMateMove.src[0] != 50) {
			printf("opponent in check\n");
		} 
		SetCastleMarkers(bd);
	    //AI
            //Whatever is needed to make this happen for AI
			MOVE aiMove;
//			AIBOARD aiBoard;
			int num1 = 0;
			int num2 = 0;
			int num3 = 0;
			int num4 = 0;
			int num5 = 0;
            COLOR color = 0;
			TYPE type = 0;
			if (checkMateMove.src[0] == 100) {
				aiMove = SearchMove(bd,color,type,num1,num2,num3,num4,num5);
			} else if (checkMateMove.src[0] != 50) {
				aiMove = checkMateMove;
			} else {
				break;
			}
			
			printf("aimovedone\n");
			movePiece(bd,aiMove);
			printf("AI MOVE (source/destination):\n\tRow: %i Col: %i ------> Row: %i Col: %i\n",aiMove.src[0],aiMove.src[1],aiMove.dest[0],aiMove.dest[1]);


			if (checkPromotion(bd, aiMove) == 1) {
				doPromotion(bd, aiMove, queen);
				FindLegalMarker(bd,aiMove.dest[0],aiMove.dest[1]);
			}
			
			ClearLegalMarker(bd,aiMove.dest[0],aiMove.dest[1]);
			SetCastleMarkers(bd);
            //log the AI's move
            ConvertMove ct = convertMove(aiMove.src[0],aiMove.src[1],aiMove.dest[0],aiMove.dest[1]);
			logAIMove(bd, aiMove, ct, log, turn);
            //updates en passant flag
			updateEp(bd);
            //update the board
            printBoard(bd,0,0,0);*/
            //increment turn
            turn ++;
        }//end of AI loop

    }//end game play loop
	cleanup(bd, log, colorPTR);
}


void cleanup(BOARD *bd, FILE *log, int *colorPTR) {
	printf("CLEANING\n");
    deleteBoard(bd);
    //Closing all files/freeing all memory (we will need more)
    endLog(log);
    endGUI();
    fclose(log);
    free(colorPTR);
    exit(0);

}

/*James Nelson*/
/*1/17/2018  */
void startGUI() {
int y;
#ifdef DEBUG
    printf("Initializing window and SDL ....\n");
#endif
	y = SDL_Init(SDL_INIT_VIDEO);
    #ifdef DEBUG
    if (y != 0);
    {
	print("SDL has been init but it still says the opposite");
        printf("SDL could not be initialized. SDL_Error: %s\n  %i\n", SDL_GetError(),y);
        //	exit(1);
    }
    #endif
    screen = SDL_SetVideoMode(800/*720*/, 800/*720*/, 8, SDL_SWSURFACE);

    if (screen == NULL) {
        printf("Couldn't set screen mode\n");
        exit(1);
    }
    SDL_WM_SetCaption("Chess Game", 0/*or NULL*/);


#ifdef DEBUG
    printf("%p",screen);
    printf("Loading images ....\n");
#endif
    pawnB = SDL_LoadBMP("pawnB.bmp");
    pawnW = SDL_LoadBMP("pawnW.bmp");
    knightB = SDL_LoadBMP("knightB.bmp");
    knightW = SDL_LoadBMP("knightW.bmp");
    bishopB = SDL_LoadBMP("bishopB.bmp");
    bishopW = SDL_LoadBMP("bishopW.bmp");
    rookB = SDL_LoadBMP("rookB.bmp");
    rookW = SDL_LoadBMP("rookW.bmp");
    kingB = SDL_LoadBMP("kingB.bmp");
    kingW = SDL_LoadBMP("kingW.bmp");
    queenB = SDL_LoadBMP("queenB.bmp");
    queenW = SDL_LoadBMP("queenW.bmp");
    //background = SDL_LoadBMP("board0.bmp");
    background = SDL_LoadBMP("board0NEW.bmp");
    highlight = SDL_LoadBMP("highlight.bmp");
    mainscreen = SDL_LoadBMP("mainscreen.bmp");

    if (highlight == NULL || pawnB == NULL || pawnW == NULL || knightB == NULL || knightW == NULL || bishopB == NULL ||
        bishopW == NULL || rookB == NULL || rookW == NULL || kingB == NULL || kingW == NULL || queenB == NULL ||
        queenW == NULL || background == NULL || mainscreen ==NULL) {
        printf("ERROR loading one or more of the gui images \n\n Quitting .....\n");
        exit(10);
    }

#ifdef DEBUG
    printf("Removing background color on images .....\n");
#endif
    SDL_SetColorKey(pawnB, SDL_SRCCOLORKEY, SDL_MapRGB(pawnB->format, 0, 187, 0));
    SDL_SetColorKey(pawnW, SDL_SRCCOLORKEY, SDL_MapRGB(pawnW->format, 0, 187, 0));
    SDL_SetColorKey(knightB, SDL_SRCCOLORKEY, SDL_MapRGB(knightB->format, 0, 187, 0));
    SDL_SetColorKey(knightW, SDL_SRCCOLORKEY, SDL_MapRGB(knightW->format, 0, 187, 0));
    SDL_SetColorKey(bishopB, SDL_SRCCOLORKEY, SDL_MapRGB(bishopB->format, 0, 187, 0));
    SDL_SetColorKey(bishopW, SDL_SRCCOLORKEY, SDL_MapRGB(bishopW->format, 0, 187, 0));
    SDL_SetColorKey(rookB, SDL_SRCCOLORKEY, SDL_MapRGB(rookB->format, 0, 187, 0));
    SDL_SetColorKey(rookW, SDL_SRCCOLORKEY, SDL_MapRGB(rookW->format, 0, 187, 0));
    SDL_SetColorKey(kingB, SDL_SRCCOLORKEY, SDL_MapRGB(kingB->format, 0, 187, 0));
    SDL_SetColorKey(kingW, SDL_SRCCOLORKEY, SDL_MapRGB(kingW->format, 0, 187, 0));
    SDL_SetColorKey(queenB, SDL_SRCCOLORKEY, SDL_MapRGB(queenB->format, 0, 187, 0));
    SDL_SetColorKey(queenW, SDL_SRCCOLORKEY, SDL_MapRGB(queenW->format, 0, 187, 0));
    SDL_SetColorKey(highlight, SDL_SRCCOLORKEY, SDL_MapRGB(highlight->format, 0, 187, 0));



}
int mainscreenwindow(SDL_Event event)
{
	#ifdef DEBUG
	printf("starting mainscreenwindow\n");
	#endif
	SDL_FillRect(screen,NULL,SDL_MapRGB(screen->format,0,0,0));
	SDL_BlitSurface(mainscreen,NULL,screen,NULL);
	SDL_Flip(screen);
	int color=-1,x,y;
	int quit = 0;

		printf("Now ready for clicking\n");
	while(SDL_PollEvent(&event) || color==-1){
		
		switch(event.type){
		case SDL_QUIT:
			quit = -1;
			return quit;
			break;
		case SDL_MOUSEBUTTONDOWN://convert click to row/column
			x = (int) event.button.x;
			y = (int) event.button.y;
			if(event.button.button == SDL_BUTTON_LEFT){
				if(x>=285 && x<=344 && y>=561 && y<=620)//white
				{
					*colorPTR = 0;
					return 2;//white
				}
				else if(x>=420 && x<=479 && y>=560 && y<=620)//black
				{
					*colorPTR = 1;
					return 1;//black
				}
			}
			break;
		default:
			break;
		}
	
	}
	return 0;
}
int getPlayerColor() //white = 0, black = 1;
{
	return *colorPTR;
}
void printBoard(BOARD *bd,int row,int column, int pValidMoves) {
#ifdef DEBUG
    printf("Printing Board\n");
#endif

    SDL_Rect offset;
    offset.w = 60;
    offset.h = 60;

    /*Clear Board*/
    SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 0, 0, 0));

    /*Apply Background*/
    SDL_BlitSurface(background, NULL, screen, NULL);

    /*Apply green square to spots that are legal moves*/
    /*Apply Pieces on top*/
    for (int y = 0; y < 8; y++)
        for (int x = 0; x < 8; x++) {
            if (bd->chessBoard[y][x]->piece != NULL/* && bd->chessBoard[y][x]->piece->type !=NULL && bd->chessBoard[y][x]->piece->type != NULL*/) {
		if(pValidMoves ==1){
		#ifdef DEBUG
		if(x ==0 && y==0)
		printf("Printing Highlight on Legal moves...\n");
		#endif
                offset.x = 40 + (80 * y);
                offset.y = 40 + (80 * x);
				
		if(GetLegalMarker(bd,row,column,x,y)==1){
		    #ifdef DEBUG
	    	    printf("highlight at row: %i column: %i\n",y,x);
		    #endif
                    SDL_BlitSurface(highlight, NULL, screen, &offset);
		    //SDL_Delay(400);
		}
		}//print the highlighted spot if pValidMoves ==1

                offset.x = 50 + (80 * x);
                offset.y = 50 + (80 * y);


                if ((bd->chessBoard[y][x]->piece->type == pawn) &&
                    bd->chessBoard[y][x]->piece->color == black)// Black Pawn
                    SDL_BlitSurface(pawnB, NULL, screen, &offset);

                if ((bd->chessBoard[y][x]->piece->type == pawn) &&
                    bd->chessBoard[y][x]->piece->color == white)// White Pawn
                    SDL_BlitSurface(pawnW, NULL, screen, &offset);

                if ((bd->chessBoard[y][x]->piece->type == knight) &&
                    bd->chessBoard[y][x]->piece->color == black)// Black knight
                    SDL_BlitSurface(knightB, NULL, screen, &offset);

                if ((bd->chessBoard[y][x]->piece->type == knight) &&
                    bd->chessBoard[y][x]->piece->color == white)// White knight
                    SDL_BlitSurface(knightW, NULL, screen, &offset);

                if ((bd->chessBoard[y][x]->piece->type == bishop) &&
                    bd->chessBoard[y][x]->piece->color == black)// Black bishop
                    SDL_BlitSurface(bishopB, NULL, screen, &offset);

                if ((bd->chessBoard[y][x]->piece->type == bishop) &&
                    bd->chessBoard[y][x]->piece->color == white)// White bishop
                    SDL_BlitSurface(bishopW, NULL, screen, &offset);

                if ((bd->chessBoard[y][x]->piece->type == rook) &&
                    bd->chessBoard[y][x]->piece->color == black)// Black rook
                    SDL_BlitSurface(rookB, NULL, screen, &offset);

                if ((bd->chessBoard[y][x]->piece->type == rook) &&
                    bd->chessBoard[y][x]->piece->color == white)// White rook
                    SDL_BlitSurface(rookW, NULL, screen, &offset);

                if (bd->chessBoard[y][x]->piece->type == king &&
                    bd->chessBoard[y][x]->piece->color == black)// Black king
                    SDL_BlitSurface(kingB, NULL, screen, &offset);

                if (bd->chessBoard[y][x]->piece->type == king &&
                    bd->chessBoard[y][x]->piece->color == white)// White king
                    SDL_BlitSurface(kingW, NULL, screen, &offset);

                if (bd->chessBoard[y][x]->piece->type == queen &&
                    bd->chessBoard[y][x]->piece->color == black)// Black queen
                    SDL_BlitSurface(queenB, NULL, screen, &offset);

                if (bd->chessBoard[y][x]->piece->type == queen &&
                    bd->chessBoard[y][x]->piece->color == white)// White queen
                    SDL_BlitSurface(queenW, NULL, screen, &offset);

            }
        }


    /*update screen*/
    SDL_Flip(screen);
}

void endGUI() {
#ifdef DEBUG
    printf("Freeing surfaces and quiting SDL......\n");
#endif

    SDL_FreeSurface(background);
    SDL_FreeSurface(pawnB);
    SDL_FreeSurface(pawnW);
    SDL_FreeSurface(rookB);
    SDL_FreeSurface(rookW);
    SDL_FreeSurface(knightB);
    SDL_FreeSurface(knightW);
    SDL_FreeSurface(queenB);
    SDL_FreeSurface(queenW);
    SDL_FreeSurface(kingB);
    SDL_FreeSurface(kingW);
    SDL_FreeSurface(bishopB);
    SDL_FreeSurface(bishopW);
    
    SDL_Quit();//takes care of freeing screen
}

INPUT getMouseClicks(SDL_Event event){
	#ifdef DEBUG
	printf("Starting getMouseClicks.....\n");
	#endif
	int row=-1,column=-1,quit=0;
	INPUT inputNUM;
	int x,y;
	while(SDL_PollEvent(&event) || (row ==-1 ||column==-1)){
		row =-1;
		column =-1;
		switch(event.type){
		case SDL_QUIT:
			quit = 1;
			goto ENDPOLL;
			break;
		case SDL_MOUSEBUTTONDOWN://convert click to row/column
			x = (int) event.button.x;
			y = (int) event.button.y;
			if(event.button.button == SDL_BUTTON_LEFT){
			if(x >=36 && x <= 120){//a
				column = 0;

				if(y>=36 && y <=120)//1
					row = 0;
				else if(y>=120 && y<=200)//2
					row = 1;
				else if(y >= 200 && y<=280)//3
					row = 2;
				else if (y>=280 && y<=360)//4
					row = 3;
				else if (y>=360 && y <= 440)//5
					row = 4;
				else if (y>=440 && y<=520)//6
					row = 5;
				else if (y>=520 && y<=600)//7
					row = 6;
				else if (y>=600 && y <= 680)//
					row = 7;
				else
					printf("Not a valid square");
			}
			else if(x >= 120 && x <= 200){//b
				column = 1;

				if(y>=36 && y <=120)//1
					row = 0;
				else if(y>=120 && y<=200)//2
					row = 1;
				else if(y >= 200 && y<=280)//3
					row = 2;
				else if (y>=280 && y<=360)//4
					row = 3;
				else if (y>=360 && y <= 440)//5
					row = 4;
				else if (y>=440 && y<=520)//6
					row = 5;
				else if (y>=520 && y<=600)//7
					row = 6;
				else if (y>=600 && y <= 680)//
					row = 7;
				else
					printf("Not a valid square");
			}
			else if(x >=200 && x <= 280){//c
				column = 2;
				
				if(y>=36 && y <=120)//1
					row = 0;
				else if(y>=120 && y<=200)//2
					row = 1;
				else if(y >= 200 && y<=280)//3
					row = 2;
				else if (y>=280 && y<=360)//4
					row = 3;
				else if (y>=360 && y <= 440)//5
					row = 4;
				else if (y>=440 && y<=520)//6
					row = 5;
				else if (y>=520 && y<=600)//7
					row = 6;
				else if (y>=600 && y <= 680)//
					row = 7;
				else
					printf("Not a valid square");

			}
			else if (x >= 280 && x <= 360){//d
				column = 3;

				if(y>=36 && y <=120)//1
					row = 0;
				else if(y>=120 && y<=200)//2
					row = 1;
				else if(y >= 200 && y<=280)//3
					row = 2;
				else if (y>=280 && y<=360)//4
					row = 3;
				else if (y>=360 && y <= 440)//5
					row = 4;
				else if (y>=440 && y<=520)//6
					row = 5;
				else if (y>=520 && y<=600)//7
					row = 6;
				else if (y>=600 && y <= 680)//
					row = 7;
				else
					printf("Not a valid square");


			}
			else if (x>=360 && x<= 440){//e
				column = 4;
	
				if(y>=36 && y <=120)//1
					row = 0;
				else if(y>=120 && y<=200)//2
					row = 1;
				else if(y >= 200 && y<=280)//3
					row = 2;
				else if (y>=280 && y<=360)//4
					row = 3;
				else if (y>=360 && y <= 440)//5
					row = 4;
				else if (y>=440 && y<=520)//6
					row = 5;
				else if (y>=520 && y<=600)//7
					row = 6;
				else if (y>=600 && y <= 680)//
					row = 7;
				else
					printf("Not a valid square");

			}
			else if (x>=440 && x<=520){//f
				column = 5;
	
				if(y>=36 && y <=120)//1
					row = 0;
				else if(y>=120 && y<=200)//2
					row = 1;
				else if(y >= 200 && y<=280)//3
					row = 2;
				else if (y>=280 && y<=360)//4
					row = 3;
				else if (y>=360 && y <= 440)//5
					row = 4;
				else if (y>=440 && y<=520)//6
					row = 5;
				else if (y>=520 && y<=600)//7
					row = 6;
				else if (y>=600 && y <= 680)//
					row = 7;
				else
					printf("Not a valid square");

			}
			else if(x>=520 && x<=600){//g
				column = 6;

				if(y>=36 && y <=120)//1
					row = 0;
				else if(y>=120 && y<=200)//2
					row = 1;
				else if(y >= 200 && y<=280)//3
					row = 2;
				else if (y>=280 && y<=360)//4
					row = 3;
				else if (y>=360 && y <= 440)//5
					row = 4;
				else if (y>=440 && y<=520)//6
					row = 5;
				else if (y>=520 && y<=600)//7
					row = 6;
				else if (y>=600 && y <= 680)//
					row = 7;
				else
					printf("Not a valid square");

			}
			else if (x>=600 && x <=680){//h
				column = 7;
			
				if(y>=36 && y <=120)//1
					row = 0;
				else if(y>=120 && y<=200)//2
					row = 1;
				else if(y >= 200 && y<=280)//3
					row = 2;
				else if (y>=280 && y<=360)//4
					row = 3;
				else if (y>=360 && y <= 440)//5
					row = 4;
				else if (y>=440 && y<=520)//6
					row = 5;
				else if (y>=520 && y<=600)//7
					row = 6;
				else if (y>=600 && y <= 680)//
					row = 7;
				else
					printf("Not a valid square");
			}
			}//end if left click
			break;
		default:
			#ifdef DEBUG
			//printf("NO GUI Input.....\n");	
			#endif
			break;
		}//endswitch
		if(row != -1 && column !=-1)
			goto ENDPOLL;	
	}//end of waiting for mouse click (while loop)
	
	//now we have a valid row and column number of clicked spot
		ENDPOLL: inputNUM.row = row;
		inputNUM.column = column;
		inputNUM.quit = quit;
		#ifdef DEBUG
		printf("row: %i column: %i\n",row,column);
		#endif		
			
	return inputNUM;

}

/*User input of promotion*/
TYPE promotionInput()
{
	SDL_Event event;
	TYPE promotePiece = 0;
	int x,y;
	printf("use buttons on the right to input\n");
	while(SDL_PollEvent(&event) || promotePiece == 0)
	{
		//printf("in while\n");
		switch(event.type){
			case SDL_QUIT:
				printf("cannot quit in this menu\n");
			break;
			
			case SDL_MOUSEBUTTONDOWN:
			  	x = (int)event.button.x;
				y = (int)event.button.y;
				
				if(event.button.button == SDL_BUTTON_LEFT){
					if(x>=720 && x <=800){
						if(y>=36 && y<=80)//queen
							promotePiece = queen;
						else if(y>=138 && y<=180)//knight
							promotePiece = knight;
						else if(y>=250 && y<=284)//rook
							promotePiece = rook;
						else if(y>=350 && y<=390)//bishop
							promotePiece = bishop;
					}
					return promotePiece;

				}
			break;
			default:

			break;
		}//end of switch
	}//end of while

	#ifdef DEBUG
	printf("End of promotion input");
	#endif
	return promotePiece;

}

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
//
// esahaba 02/02/18
// kevin chew 1/31/18

void FindLegalMarker(BOARD *bd, int sRow, int sCol) {
    
	COLOR color;
    TYPE type;
    int number;
    int i,m,s;
    int down2, down1, right2,right1, up2, up1, left2, left1; //directions for knight movement
//    int HborderMinus; // sRow - i;
//	int HborderPlus; //= sRow + i;
//	int VborderMinus; // sCol - i;
 //   int VborderPlus; //= sCol + i;

    color = getColor(bd, sRow, sCol);
    number = getNumber(bd, sRow, sCol);
    type = getType(bd, sRow, sCol);

    switch (type) {
        
		case noType:

            return;

        case pawn:

          //  int m, s;
			if (color == white)
            {    
 		    s = -1;
            } 
		else	
            {    
			s = 1;
			}
            if (bd->chessBoard[sRow][sCol]->piece->hasMoved)
			{
			m = 1;
			}
            else
            {
			m = 2;
			}

            for (int i = 1; i <= m; i++) {
				
				if(CheckColor(bd, sRow + s * i, sCol))
				{
					break;
				}
                SetLegalMarker(bd, color, pawn, number, sRow + s * i, sCol); 
				
            }
			

            if (color != getColor(bd, sRow + s * 1, sCol + 1) && getColor(bd, sRow + s * 1, sCol + 1) != noColor) {

                SetLegalMarker(bd, color, pawn, number, sRow + s * 1, sCol + 1);

            }

            if (color != getColor(bd, sRow + s * 1, sCol - 1) && getColor(bd, sRow + s * 1, sCol - 1) != noColor) {

                SetLegalMarker(bd, color, pawn, number, sRow + s * 1, sCol - 1);

            }
			
			if (color == white && sRow == 3) {
				if (sCol < 7) {
					if (getColor(bd, sRow, sCol + 1) != getColor(bd, sRow, sCol)) {
						if (getEp(bd, sRow, sCol + 1) > 0) {
						SetLegalMarker(bd, color, pawn, number, sRow - 1, sCol + 1 );
						}
					}
				}
				if (sCol > 0) {
					if (getColor(bd, sRow, sCol - 1) != getColor(bd, sRow, sCol)) {
						if (getEp(bd, sRow, sCol - 1) > 0) {
						SetLegalMarker(bd, color, pawn, number, sRow - 1, sCol - 1);
						}
					}
				}
			}
			
			if (color == black && sRow == 4) {
				if (sCol < 7) {
					if (getColor(bd, sRow, sCol + 1) != getColor(bd, sRow, sCol)) {
						if (getEp(bd, sRow, sCol + 1) > 0) {
						SetLegalMarker(bd, color, pawn, number, sRow + 1, sCol + 1);
						}
					}
				}
				if (sCol > 0) {
					if (getColor(bd, sRow, sCol - 1) != getColor(bd, sRow, sCol)) {
						if (getEp(bd, sRow, sCol - 1) > 0) {
						SetLegalMarker(bd, color, pawn, number, sRow + 1, sCol - 1);
						}
					}
				}
			}
			
            return;

        case rook:

            for ( i = 1; (sCol + i < 8); i++) 
			{
				if(CheckColor(bd, sRow, sCol + i))
				{
					if(getColor(bd, sRow, sCol + i) != color)
					{
					
					SetLegalMarker(bd, color, rook, number, sRow, sCol + i); 
					
					}
					break;
				}
                SetLegalMarker(bd, color, rook, number, sRow, sCol + i); 
            }

            for ( i = 1; (sCol - i >= 0); i++) 
			{
				
				if(CheckColor(bd, sRow, sCol - i))
				{
					if(getColor(bd, sRow, sCol - i) != color)
					{
					
					SetLegalMarker(bd, color, rook, number, sRow, sCol - i); 
					
					}
					break;
				}
                SetLegalMarker(bd, color, rook, number, sRow, sCol - i); 
				
            }

            for ( i = 1; (sRow + i < 8); i++) {
				
				if(CheckColor(bd, sRow + i, sCol))
				{
					if(getColor(bd, sRow + i, sCol) != color)
					{
					
					SetLegalMarker(bd, color, rook, number, sRow + i, sCol); 
					
					}
					break;
				}
                SetLegalMarker(bd, color, rook, number, sRow + i, sCol); 
            }

            for ( i = 1; (sRow - i >= 0); i++) 
			{
				
				if(CheckColor(bd, sRow - i, sCol))
				{
					if(getColor(bd, sRow - i, sCol) != color)
					{
					
					SetLegalMarker(bd, color, rook, number, sRow - i, sCol); 
					
					}
					break;
				}
                SetLegalMarker(bd, color, rook, number, sRow - i, sCol);
				
            }

            return;

        case knight:

            //int i;
            //int down2, down1, right2,
                    //right1, up2, up1, left2, left1; //directions for knight movement
            down2 = sRow + 2;
            down1 = sRow + 1;
            right2 = sCol + 2;
            right1 = sCol + 1;
            up2 = sRow - 2;
            up1 = sRow - 1;
            left2 = sCol - 2;
            left1 = sCol - 1;
	    
	    if(up2 <=7 && up2 >=0 && left1 >=0 && left1 <=7)//up 2 left 1 is in bounds
	    {
		ScanLegalMarker(bd,color,knight,number,up2,left1);
	    }
	    if(up2 <=7 && up2 >=0 && right1 >=0 && right1 <=7)//up 2 right 1 is in bounds
	    {
		ScanLegalMarker(bd,color,knight,number,up2,right1);
	    }
	    if(up1 <=7 && up1 >=0 && right2 >=0 && right2 <=7)//up 1 right 2 is in bounds
	    {
		ScanLegalMarker(bd,color,knight,number,up1,right2);
	    }
 	    if(down1 <=7 && down1 >=0 && right2 >=0 && right2 <=7)//down 1 right 2 is in bounds
	    {
		ScanLegalMarker(bd,color,knight,number,down1,right2);
	    }
 	    if(down2 <=7 && down2 >=0 && right1 >=0 && right1 <=7)//down 2 right 1 is in bounds
	    {
		ScanLegalMarker(bd,color,knight,number,down2,right1);
	    }
 	    if(down2 <=7 && down2 >=0 && left1 >=0 && left1 <=7)//down 2 left 1 is in bounds
	    {
		ScanLegalMarker(bd,color,knight,number,down2,left1);
	    }
 	    if(down1 <=7 && down1 >=0 && left2 >=0 && left2 <=7)//down 1 left 2 is in bounds
	    {
		ScanLegalMarker(bd,color,knight,number,down1,left2);
	    }
 	    if(up1 <=7 && up1 >=0 && left2 >=0 && left2 <=7)//up 1 left 2 is in bounds
	    {
		ScanLegalMarker(bd,color,knight,number,up1,left2);
	    }
 

	/*
            //below checks for out of bounds for knight and applies available squares knight can play
            if ((down2 > 7) && (down1 > 7) && (right2 > 7)) //applies to initial white knight1 square 76
            {
                ScanLegalMarker(bd, color, knight, number, up2, left1);
                ScanLegalMarker(bd, color, knight, number, up2, right1);
                ScanLegalMarker(bd, color, knight, number, up1, left2);
            } else if ((down2 > 7) && (down1 > 7) && (left2 < 0)) //initial white knight0 square 71
            {
                ScanLegalMarker(bd, color, knight, number, up2, left1);
                ScanLegalMarker(bd, color, knight, number, up2, right1);
                ScanLegalMarker(bd, color, knight, number, up1, right2);
            } else if ((up2 < 0) && (up1 < 0) && (right2 > 7)) //initial black knight1 square 06
            {
                ScanLegalMarker(bd, color, knight, number, down2, left1);
                ScanLegalMarker(bd, color, knight, number, down2, right1);
                ScanLegalMarker(bd, color, knight, number, down1, left2);
            } else if ((up2 < 0) && (up1 < 0) && (left2 < 0)) //initial black knight0 square 01
            {
                ScanLegalMarker(bd, color, knight, number, down2, left1);
                ScanLegalMarker(bd, color, knight, number, down2, right1);
                ScanLegalMarker(bd, color, knight, number, down1, right2);
            }

//spacing			
            else if ((down2 > 7) && (left2 < 0) && (left1 < 0)) //square 60
            {
                ScanLegalMarker(bd, color, knight, number, up2, right1);
                ScanLegalMarker(bd, color, knight, number, up1, right2);
                ScanLegalMarker(bd, color, knight, number, down1, right2);
            } else if ((down2 > 7) && (right1 > 7) && (right2 > 7)) //square 67
            {
                ScanLegalMarker(bd, color, knight, number, up2, left1);
                ScanLegalMarker(bd, color, knight, number, up1, left2);
                ScanLegalMarker(bd, color, knight, number, down1, left2);
            } else if ((up2 < 0) && (left1 < 0) && (left2 < 0)) //square 10
            {
                ScanLegalMarker(bd, color, knight, number, down2, right1);
                ScanLegalMarker(bd, color, knight, number, down1, right2);
                ScanLegalMarker(bd, color, knight, number, up1, right2);
            } else if ((up2 < 0) && (right1 > 7) && (right2 > 7)) //square 17
            {
                ScanLegalMarker(bd, color, knight, number, down2, left1);
                ScanLegalMarker(bd, color, knight, number, down1, left2);
                ScanLegalMarker(bd, color, knight, number, up1, left2);
            }

//spacing			
            else if ((up2 < 0) && (up1 < 0) && (left2 < 0) && (left1 < 0)) //top left corner
            {

                ScanLegalMarker(bd, color, knight, number, down2, right1);
                ScanLegalMarker(bd, color, knight, number, down1, right2);
            } else if ((up2 < 0) && (up1 < 0) && (right2 > 7) && (right1 > 7)) //top right corner
            {
                ScanLegalMarker(bd, color, knight, number, down2, left1);
                ScanLegalMarker(bd, color, knight, number, down1, left2);
            } else if ((down2 > 7) && (down1 > 7) && (left2 < 0) && (left1 < 0)) //bottom left corner
            {

                ScanLegalMarker(bd, color, knight, number, up2, right1);
                ScanLegalMarker(bd, color, knight, number, up1, right2);
            } else if ((down2 > 7) && (down1 > 7) && (right2 > 7) && (right1 > 7)) //bottom right corner
            {

                ScanLegalMarker(bd, color, knight, number, up2, left1);
                ScanLegalMarker(bd, color, knight, number, up1, left2);
            }

//spacing


            else if ((up2 < 0) && (left2 < 0)) //square 11
            {
                ScanLegalMarker(bd, color, knight, number, down2, left1);
                ScanLegalMarker(bd, color, knight, number, down2, right1);
                ScanLegalMarker(bd, color, knight, number, up1, right2);
                ScanLegalMarker(bd, color, knight, number, down1, right2);
            } else if ((up2 < 0) && (right2 > 7)) //square 16
            {
                ScanLegalMarker(bd, color, knight, number, down2, left1);
                ScanLegalMarker(bd, color, knight, number, down2, right1);
                ScanLegalMarker(bd, color, knight, number, up1, left2);
                ScanLegalMarker(bd, color, knight, number, down1, left2);
            } else if ((down2 > 7) && (right2 > 7)) //square 66
            {
                ScanLegalMarker(bd, color, knight, number, up2, left1);
                ScanLegalMarker(bd, color, knight, number, up2, right1);
                ScanLegalMarker(bd, color, knight, number, up1, left2);
                ScanLegalMarker(bd, color, knight, number, down1, left2);
            } else if ((down2 > 7) && (left2 < 0)) //square 61
            {
                ScanLegalMarker(bd, color, knight, number, up2, left1);
                ScanLegalMarker(bd, color, knight, number, up2, right1);
                ScanLegalMarker(bd, color, knight, number, up1, right2);
                ScanLegalMarker(bd, color, knight, number, down1, right2);
            }

//spacing


            else if ((up2 < 0) && (up1 < 0)) //general top row
            {
                ScanLegalMarker(bd, color, knight, number, down2, left1);
                ScanLegalMarker(bd, color, knight, number, down2, right1);
                ScanLegalMarker(bd, color, knight, number, down1, left2);
                ScanLegalMarker(bd, color, knight, number, down1, right2);
            } else if ((down2 > 7) && (down1 > 7)) //general bottom row
            {
                ScanLegalMarker(bd, color, knight, number, up2, left1);
                ScanLegalMarker(bd, color, knight, number, up2, right1);
                ScanLegalMarker(bd, color, knight, number, up1, left2);
                ScanLegalMarker(bd, color, knight, number, up1, right2);
            } else if ((left2 < 0) && (left1 < 0)) //general left col
            {
                ScanLegalMarker(bd, color, knight, number, down2, right1);
                ScanLegalMarker(bd, color, knight, number, down1, right2);
                ScanLegalMarker(bd, color, knight, number, up2, right1);
                ScanLegalMarker(bd, color, knight, number, up1, right2);
            } else if ((right2 > 7) && (right1 > 0)) //general right col
            {
                ScanLegalMarker(bd, color, knight, number, down2, left1);
                ScanLegalMarker(bd, color, knight, number, down1, left2);
                ScanLegalMarker(bd, color, knight, number, up2, left1);
                ScanLegalMarker(bd, color, knight, number, up1, left2);
            }

//spacing

                //rows and cols before end rows and cols

            else if (up2 < 0) // 2nd top row
            {
                ScanLegalMarker(bd, color, knight, number, down2, left1);
                ScanLegalMarker(bd, color, knight, number, down2, right1);
                ScanLegalMarker(bd, color, knight, number, down1, left2);
                ScanLegalMarker(bd, color, knight, number, down1, right2);
                ScanLegalMarker(bd, color, knight, number, up1, left2);
                ScanLegalMarker(bd, color, knight, number, up1, right2);
            } else if (down2 > 7) // 2nd bottom row
            {
                ScanLegalMarker(bd, color, knight, number, up2, left1);
                ScanLegalMarker(bd, color, knight, number, up2, right1);
                ScanLegalMarker(bd, color, knight, number, up1, left2);
                ScanLegalMarker(bd, color, knight, number, up1, right2);
                ScanLegalMarker(bd, color, knight, number, down1, left2);
                ScanLegalMarker(bd, color, knight, number, down1, right2);
            } else if (left2 < 0) // 2nd left col
            {
                ScanLegalMarker(bd, color, knight, number, down2, left1);
                ScanLegalMarker(bd, color, knight, number, down2, right1);
                ScanLegalMarker(bd, color, knight, number, up2, left1);
                ScanLegalMarker(bd, color, knight, number, up2, right1);
                ScanLegalMarker(bd, color, knight, number, down1, right2);
                ScanLegalMarker(bd, color, knight, number, up1, right2);
            } else if (right2 > 0) // 2nd right col
            {
                ScanLegalMarker(bd, color, knight, number, down2, left1);
                ScanLegalMarker(bd, color, knight, number, down2, right1);
                ScanLegalMarker(bd, color, knight, number, up2, left1);
                ScanLegalMarker(bd, color, knight, number, up2, right1);
                ScanLegalMarker(bd, color, knight, number, down1, left2);
                ScanLegalMarker(bd, color, knight, number, up1, left2);
            }
//spacing


            else //general movement of knight, all 8 moves
            {
                ScanLegalMarker(bd, color, knight, number, down2, left1);
                ScanLegalMarker(bd, color, knight, number, down2, right1);
                ScanLegalMarker(bd, color, knight, number, down1, right2);
                ScanLegalMarker(bd, color, knight, number, down1, left2);
                ScanLegalMarker(bd, color, knight, number, up2, right1);
                ScanLegalMarker(bd, color, knight, number, up2, left1);
                ScanLegalMarker(bd, color, knight, number, up1, left2);
                ScanLegalMarker(bd, color, knight, number, up1, right2);

            }*/

            return;

        case bishop:

            for (i = 1; ((sRow + i < 8) || (sCol + i < 8)); i++) //bishop move down right
            {
				if(CheckColor(bd, sRow + i, sCol + i))
				{
					if(getColor(bd, sRow + i, sCol + i) != color)
					{
					
					SetLegalMarker(bd, color, bishop, number, sRow + i, sCol + i); 
					
					}
					break;
				}
                
				SetLegalMarker(bd, color, bishop, number, sRow + i, sCol + i); 

            } //end for

            for (i = 1; ((sRow - i > -1) || (sCol + i < 8)); i++) //bishop move up right
            {
				if(CheckColor(bd, sRow - i, sCol + i))
				{
					if(getColor(bd, sRow - i, sCol + i) != color)
					{
					
					SetLegalMarker(bd, color, bishop, number, sRow - i, sCol + i); 
					
					}
					break;
				}

                SetLegalMarker(bd, color, bishop, number, sRow - i, sCol + i);
				
            }

            for (i = 1; ((sRow - i > -1) || (sCol - i > -1)); i++) //bishop move up left
            {
				if(CheckColor(bd, sRow - i, sCol - i))
				{
					if(getColor(bd, sRow - i, sCol - i) != color)
					{
					
					SetLegalMarker(bd, color, bishop, number, sRow - i, sCol - i); 
					
					}
					break;
				}

				SetLegalMarker(bd, color, bishop, number, sRow - i, sCol - i);
            } //end for

            for (i = 1; ((sRow + i < 8) || (sCol - i > -1)); i++) //bishop move down left
            {
				
				if(CheckColor(bd, sRow + i, sCol - i))
				{
					if(getColor(bd, sRow + i, sCol - i) != color)
					{
					
					SetLegalMarker(bd, color, bishop, number, sRow + i, sCol - i); 
					
					}
					break;
				}

                SetLegalMarker(bd, color, bishop, number, sRow + i, sCol - i);
            } //end for
			

            return;

        case queen:

            for (i = 1; ((sRow + i < 8) || (sCol + i < 8)); i++) //bishop move down right
            {
				if(CheckColor(bd, sRow + i, sCol + i))
				{
					if(getColor(bd, sRow + i, sCol + i) != color)
					{
					
					SetLegalMarker(bd, color, queen, number, sRow + i, sCol + i); 
					
					}
					break;
				}
                
				SetLegalMarker(bd, color, queen, number, sRow + i, sCol + i); 

            } //end for

            for (i = 1; ((sRow - i > -1) || (sCol + i < 8)); i++) //bishop move up right
            {
				if(CheckColor(bd, sRow - i, sCol + i))
				{
					if(getColor(bd, sRow - i, sCol + i) != color)
					{
					
					SetLegalMarker(bd, color, queen, number, sRow - i, sCol + i); 
					
					}
					break;
				}

                SetLegalMarker(bd, color, queen, number, sRow - i, sCol + i);
				
            }

            for (i = 1; ((sRow - i > -1) || (sCol - i > -1)); i++) //bishop move up left
            {
				if(CheckColor(bd, sRow - i, sCol - i))
				{
					if(getColor(bd, sRow - i, sCol - i) != color)
					{
					
					SetLegalMarker(bd, color, queen, number, sRow - i, sCol - i); 
					
					}
					break;
				}

				SetLegalMarker(bd, color, queen, number, sRow - i, sCol - i);
            } //end for

            for (i = 1; ((sRow + i < 8) || (sCol - i > -1)); i++) //bishop move down left
            {
				
				if(CheckColor(bd, sRow + i, sCol - i))
				{
					if(getColor(bd, sRow + i, sCol - i) != color)
					{
					
					SetLegalMarker(bd, color, queen, number, sRow + i, sCol - i); 
					
					}
					break;
				}

                SetLegalMarker(bd, color, queen, number, sRow + i, sCol - i);
            } //end for
			
			for ( i = 1; (sCol + i < 8); i++) 
			{
				if(CheckColor(bd, sRow, sCol + i))
				{
					if(getColor(bd, sRow, sCol + i) != color)
					{
					
					SetLegalMarker(bd, color, queen, number, sRow, sCol + i); 
					
					}
					break;
				}
                SetLegalMarker(bd, color, queen, number, sRow, sCol + i); 
            }

            for ( i = 1; (sCol - i >= 0); i++) 
			{
				
				if(CheckColor(bd, sRow, sCol - i))
				{
					if(getColor(bd, sRow, sCol - i) != color)
					{
					
					SetLegalMarker(bd, color, queen, number, sRow, sCol - i); 
					
					}
					break;
				}
                SetLegalMarker(bd, color, queen, number, sRow, sCol - i); 
				
            }

            for ( i = 1; (sRow + i < 8); i++) {
				
				if(CheckColor(bd, sRow + i, sCol))
				{
					if(getColor(bd, sRow + i, sCol) != color)
					{
					
					SetLegalMarker(bd, color, queen, number, sRow + i, sCol); 
					
					}
					break;
				}
                SetLegalMarker(bd, color, queen, number, sRow + i, sCol); 
            }

            for ( i = 1; (sRow - i >= 0); i++) 
			{
				
				if(CheckColor(bd, sRow - i, sCol))
				{
					if(getColor(bd, sRow - i, sCol) != color)
					{
					
					SetLegalMarker(bd, color, queen, number, sRow - i, sCol); 
					
					}
					break;
				}
                SetLegalMarker(bd, color, queen, number, sRow - i, sCol);
				
            }

            return;

        case king:
		
			for(int i = - 1; i < 2; i++)
			{
				
				if(CheckSafeMove(bd, sRow, sCol, sRow + i, sCol - 1))
				{
					/*if(sRow +i >=0 && sRow +i <=7 && sCol -1 >=0 && sCol-1<=7){
					//do the move
					movePiece(bd,createMove(sRow,sCol,sRow+i,sCol-1));
					//update legal marker stuff
					for(int x = 0; x<8; x++)
						for(int y = 0; y<8;y++)
						{
							ClearLegalMarker(bd,x,y);
							FindLegalMarker(bd,x,y);
						}
					//call is inCheckMate returns 0 if its not check/ 1 for check/2for checkmate
					if(isInCheckMate(bd, getColor(bd,sRow+i,sCol-1)) == 0)
						ScanLegalMarker(bd, color, king, number, sRow + i, sCol - 1);
					//undo the move/reset legalmarker
					movePiece(bd,createMove(sRow+i,sCol-1,sRow,sCol));
					for(int x = 0; x<8; x++)
						for(int y = 0; y<8;y++)
						{
							ClearLegalMarker(bd,x,y);
							FindLegalMarker(bd,x,y);
						}
					//if still safe
					}
					else*/
						ScanLegalMarker(bd, color, king, number, sRow + i, sCol - 1);

					
				}
				
				if(CheckSafeMove(bd, sRow, sCol, sRow + i, sCol + 1))
				{
					
					/*if(sRow +i >=0 && sRow +i <=7){
					movePiece(bd,createMove(sRow,sCol,sRow+i,sCol+1));
					//update legal marker stuff
					for(int x = 0; x<8; x++)
						for(int y = 0; y<8;y++)
						{
							ClearLegalMarker(bd,x,y);
							FindLegalMarker(bd,x,y);
						}
					//call is inCheckMate returns 0 if its not check/ 1 for check/2for checkmate
					if(isInCheckMate(bd, getColor(bd,sRow+i,sCol+1)) == 0)
						ScanLegalMarker(bd, color, king, number, sRow + i, sCol + 1);
					//undo the move/reset legalmarker
					movePiece(bd,createMove(sRow+i,sCol+1,sRow,sCol));
					for(int x = 0; x<8; x++)
						for(int y = 0; y<8;y++)
						{
							ClearLegalMarker(bd,x,y);
							FindLegalMarker(bd,x,y);
						}
					//if still safe	
					}
					else*/
						ScanLegalMarker(bd, color, king, number, sRow + i, sCol + 1);

				}				

				if(CheckSafeMove(bd, sRow, sCol, sRow + i, sCol))
				{
					
					/*if(sRow +i >=0 && sRow +i <=7){
					movePiece(bd,createMove(sRow,sCol,sRow+i,sCol));
					//update legal marker stuff
					for(int x = 0; x<8; x++)
						for(int y = 0; y<8;y++)
						{
							ClearLegalMarker(bd,x,y);
							FindLegalMarker(bd,x,y);
						}
					//call is inCheckMate returns 0 if its not check/ 1 for check/2for checkmate
					if(isInCheckMate(bd, getColor(bd,sRow+i,sCol)) == 0)
						ScanLegalMarker(bd, color, king, number, sRow + i, sCol);
					//undo the move/reset legalmarker
					movePiece(bd,createMove(sRow+i,sCol,sRow,sCol));
					for(int x = 0; x<8; x++)
						for(int y = 0; y<8;y++)
						{
							ClearLegalMarker(bd,x,y);
							FindLegalMarker(bd,x,y);
						}
					//if still safe		
					}
					else*/
						ScanLegalMarker(bd, color, king, number, sRow + i, sCol);

				}
				
			}
			
            return;
			break;
        default:

            return;
			
    }
	
}

int GetLegalMarker(BOARD *bd, int sRow, int sCol, int dRow, int dCol) {

    COLOR color;
    TYPE type;
    int number;

    color = getColor(bd, sRow, sCol);
    number = getNumber(bd, sRow, sCol);
    type = getType(bd, sRow, sCol);

    for (int i = 0; i < 16; i++) {

        if (getLMAElement(bd, dRow, dCol, i, 0) == color &&
            getLMAElement(bd, dRow, dCol, i, 1) == type &&
            getLMAElement(bd, dRow, dCol, i, 2) == number &&
            getLMAElement(bd, dRow, dCol, i, 3) == 1) {

            return 1;

        }

    }

    return 0;

}

void ClearLegalMarker(BOARD *bd, int dRow, int dCol) {

    COLOR color;
    TYPE type;
    int number;

    color = getColor(bd, dRow, dCol);
    number = getNumber(bd, dRow, dCol);
    type = getType(bd, dRow, dCol);

    for (int x = 0; x < 8; x++) {

        for (int y = 0; y < 8; y++) {

            for (int i = 0; i < 16; i++) {

                if (getLMAElement(bd, x, y, i, 0) == color &&
                    getLMAElement(bd, x, y, i, 1) == type &&
                    getLMAElement(bd, x, y, i, 2) == number &&
                    getLMAElement(bd, x, y, i, 3) == 1) {

                    for (int j = 0; j < 4; j++) {

                        setLMAElement(bd, x, y, i, j, 0);

                    }

                }

            }

        }

    }

}

void SetLegalMarker(BOARD *bd, COLOR color, TYPE type, int number, int bRow, int bCol) {

    int eRow;

    for (int i = 0; i < 16; i++) {

        if (getLMAElement(bd, bRow, bCol, i, 0) == 0 &&
            getLMAElement(bd, bRow, bCol, i, 1) == 0 &&
            getLMAElement(bd, bRow, bCol, i, 2) == 0 &&
            getLMAElement(bd, bRow, bCol, i, 3) == 0) {
            eRow = i;
			//printf("eRow = %d\n", eRow);
            break;
        }

    }



	setLMAElement(bd, bRow, bCol, eRow, 0, color);
	setLMAElement(bd, bRow, bCol, eRow, 1, type);
	setLMAElement(bd, bRow, bCol, eRow, 2, number);
	setLMAElement(bd, bRow, bCol, eRow, 3, 1);



    /* if (color == white)
        setLMAElement(bd, bRow, bCol, eRow, 0, 2);
    else if (color == black)
        setLMAElement(bd, bRow, bCol, eRow, 0, 1);
    else
        return;

    switch (type) {

        case noType:
            return;

        case pawn:
            setLMAElement(bd, bRow, bCol, eRow, 1, 1);
            break;

        case rook:
            setLMAElement(bd, bRow, bCol, eRow, 1, 2);
            break;

        case knight:
            setLMAElement(bd, bRow, bCol, eRow, 1, 3);
            break;

        case bishop:
            setLMAElement(bd, bRow, bCol, eRow, 1, 4);
            break;

        case queen:
            setLMAElement(bd, bRow, bCol, eRow, 1, 5);
            break;

        case king:
            setLMAElement(bd, bRow, bCol, eRow, 1, 6);
            break;
        default:
            return;


    }

    setLMAElement(bd, bRow, bCol, eRow, 2, number);

    setLMAElement(bd, bRow, bCol, eRow, 3, 1);
 */
}

void ScanLegalMarker(BOARD *bd, COLOR color, TYPE type, int number, int bRow, int bCol) {

    if(getColor(bd, bRow, bCol) != noColor)
	{
		if(getColor(bd, bRow, bCol) != color)
		{
			SetLegalMarker(bd, color, type, number, bRow, bCol);
		}
		else
		{
			return;
		}
	}
    
	SetLegalMarker(bd, color, type, number, bRow, bCol);

}

int CheckSafeMove(BOARD *bd, int sRow, int sCol, int dRow, int dCol)
{
	
	COLOR color;
	COLOR opponent;
	color = getColor(bd, sRow, sCol);
	if(color == 1)
		opponent = 2;
	else
		opponent = 1;
    /*for (int i = 0; i < 16; i++) {

        if (getLMAElement(bd, dRow, dCol, i, 0) != color) {

            return 1;

        }

    }*/

	for(int x = 0; x < 8; x++)
		for(int y = 0; y < 8; y++)
		{
			if(getColor(bd,x,y) == opponent)
				if(GetLegalMarker(bd,x,y,dRow,dCol) == 1)//opponent piece can kill if the king moves here
				{
					return 0;
				}	
		}

	for(int x = 0; x < 8; x++)
		for(int y = 0; y < 8; y++)
		{
				//if(getColor(bd,x,y) == opponent)
				//{
				//	if(GetLegalMarker(bd,x,y,dRow,dCol) == 1)//opponent piece can kill if the king moves here
				//	{
						if(getType(bd,dRow +2,dCol) ==pawn && color ==1)
						{
							//is safe
						}
						else if(getType(bd,dRow-2,dCol)==pawn && color == 2)
						{
							//is safe
						}
						//else
						//return 0;//not safe
					//}

				//}
					if(color == 1)//black
					{
						if(getType(bd,dRow+1,dCol-1) == pawn && getColor(bd,dRow+1,dCol-1) == white)
						{
							return 0;//not safe
						}
						if(getType(bd,dRow+1,dCol+1) == pawn && getColor(bd,dRow+1,dCol-1) == white)
							return 0;
					}
					if(color == 2)//white
					{
						if(getType(bd,dRow-1,dCol-1) == pawn && getColor(bd,dRow-1,dCol-1) == black)
							return 0;
						if(getType(bd,dRow-1,dCol+1) ==pawn && getColor(bd,dRow-1,dCol+1) == black)
							return 0;

					}	
			
			
		}
	
	return 1;//safe
	
}

int CheckColor(BOARD *bd, int bRow, int bCol){

	if(getColor(bd, bRow, bCol) != noColor){
		return 1;
	}

	return 0;
}
//
// Created by jingtaoz on 1/23/2018.
//

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


