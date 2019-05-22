//
// Created by jingtaoz on 1/23/2018.
//
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include "Piece.h"

//we will need a better way to clear memory, very leaky right now -leo
void deletePiece(PIECE *p) {
    //assert(p);
    free(p);
}
/*
PLIST *NewPieceList(void)
{
	PLIST *l;
	l = malloc(sizeof(SLIST));
	l->Length = 32;
	l->First = NULL;
	l->Last = NULL;

	return l;
}

void DeletePieceList(PLIST *l)
{
	PENTRY *e, *n;
	PIECE *p;

	assert(l);
	while(e)
	{
		n = e->Next;
		p = deletePiece(e);
		e = n;
	}

	free(l);
}*/

PIECE *initBlank() {
    PIECE *p;
    p = malloc(sizeof(PIECE));
    p->color = noColor;
    p->hasMoved = 0;
    p->canEp = 0;
    p->type = noType;
    p->alive = 1;
    return p;
}

PIECE *initWhitePawn(int n) {
    PIECE *p;
    p = malloc(sizeof(PIECE));
    p->type = pawn;
    p->color = white;
    p->number = n;
    p->hasMoved = 0;
    p->canEp = 0;
    p->alive = 1;
    return p;
}

PIECE *initWhiteRook(int n) {
    PIECE *p;
    p = malloc(sizeof(PIECE));
    p->type = rook;
    p->color = white;
    p->number = n;
    p->hasMoved = 0;
    p->canEp = 0;
    p->alive = 1;
    return p;
}

PIECE *initWhiteKnight(int n) {
    PIECE *p;
    p = malloc(sizeof(PIECE));
    p->type = knight;
    p->color = white;
    p->number = n;
    p->hasMoved = 0;
    p->canEp = 0;
    p->alive = 1;
    return p;
}

PIECE *initWhiteBishop(int n) {
    PIECE *p;
    p = malloc(sizeof(PIECE));
    p->type = bishop;
    p->color = white;
    p->number = n;
    p->hasMoved = 0;
    p->canEp = 0;
    p->alive = 1;
    return p;
}

PIECE *initWhiteQueen(int n) {
    PIECE *p;
    p = malloc(sizeof(PIECE));
    p->type = queen;
    p->color = white;
    p->number = n;
    p->hasMoved = 0;
    p->canEp = 0;
    p->alive = 1;
    return p;
}

PIECE *initWhiteKing(void) {
    PIECE *p;
    p = malloc(sizeof(PIECE));
    p->type = king;
    p->color = white;
    p->number = 0;
    p->hasMoved = 0;
    p->canEp = 0;
    p->alive = 1;
    return p;
}

PIECE *initBlackPawn(int n) {
    PIECE *p;
    p = malloc(sizeof(PIECE));
    p->type = pawn;
    p->color = black;
    p->number = n;
    p->hasMoved = 0;
    p->canEp = 0;
    p->alive = 1;
    return p;
}

PIECE *initBlackRook(int n) {
    PIECE *p;
    p = malloc(sizeof(PIECE));
    p->type = rook;
    p->color = black;
    p->number = n;
    p->hasMoved = 0;
    p->canEp = 0;
    p->alive = 1;
    return p;
}

PIECE *initBlackKnight(int n) {
    PIECE *p;
    p = malloc(sizeof(PIECE));
    p->type = knight;
    p->color = black;
    p->number = n;
    p->hasMoved = 0;
    p->canEp = 0;
    p->alive = 1;
    return p;
}

PIECE *initBlackBishop(int n) {
    PIECE *p;
    p = malloc(sizeof(PIECE));
    p->type = bishop;
    p->color = black;
    p->number = n;
    p->hasMoved = 0;
    p->canEp = 0;
    p->alive = 1;
    return p;
}

PIECE *initBlackQueen(int n) {
    PIECE *p;
    p = malloc(sizeof(PIECE));
    p->type = queen;
    p->color = black;
    p->number = n;
    p->hasMoved = 0;
    p->canEp = 0;
    p->alive = 1;
    return p;
}

PIECE *initBlackKing(void) {
    PIECE *p;
    p = malloc(sizeof(PIECE));
    p->type = king;
    p->color = black;
    p->hasMoved = 0;
    p->canEp = 0;
    p->alive = 1;
    return p;
}
