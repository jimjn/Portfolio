#include "SDL/SDL.h"
#include "Board.h"
#include "X11/Xlib.h"
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
