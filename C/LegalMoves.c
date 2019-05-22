//
// esahaba 02/02/18
// kevin chew 1/31/18

#include "LegalMoves.h"

#include <stdio.h>


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