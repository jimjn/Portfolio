/*James Nelson*/
/*1/17/2018  */
#include "gui.h"
#include <stdio.h>
#include "constants.h"
#include "Board.h"
#include "LegalMoves.h"
#include "SDL/SDL_thread.h"


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




