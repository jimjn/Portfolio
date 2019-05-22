//
// Created by jingtaoz on 1/23/2018.
//

#ifndef PIECE_H
#define PIECE_H

/*
typedef struct PieceList PLIST;
typedef struct PieceEntry PENTRY;

struct PieceList
{
	int Length;
	PENTRY *First;
	PENTRY *Last;
};

struct PieceEntry
{
	PLIST *List;
	PENTRY *Next;
	PENTRY *Prev;
	PIECE *Piece;
};

PLIST *NewPieceList(void);

void DeletePieceList(PLIST *l);
*/
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

#endif //PIECE_H
