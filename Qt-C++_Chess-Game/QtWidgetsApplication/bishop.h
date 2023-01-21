//Bishop est une classe qui implemente une représentation d'un fou au échec.
//Elle est en mesure de verifier ses propres mouvement et
// de savoir quels sont les positions valides.
//
// Par Aziz Doghri et Farid Bakir

#pragma once
#include <iostream>
#include <string>
#include"Piece.h"
#include "Position.h"
#include "Color.h"
#include "Square.h"
#include <QGraphicsItem>
#include <QLabel>
using namespace std;


class Bishop : public Piece {
public:
	Bishop(Position position, Color couleur, QGraphicsItem* parent = nullptr);
	void move(Position position, Square* board[8][8]) override;
	bool isMoveApproved(Position position, Square* board[8][8]) override;

private:
	bool isLegalPosition(const Position& position);
	bool isSquareFree(Position position, Square* board[8][8]);
	bool isPathPossible(Position positionArrival, Square* board[8][8]);
	pair<int, int> direction(Position finalPosition);

};