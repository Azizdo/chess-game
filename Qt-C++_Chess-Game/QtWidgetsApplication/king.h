//King est une classe qui implemente une représentation du roi au échec.
//Elle est en mesure de verifier ses propres mouvement,
// de savoir quels sont les positions valides et levé une exception s'il y a plus de 2 rois
// 
// Par Aziz Doghri et Farid Bakir

#pragma once
#include <iostream>
#include <string>
#include "Position.h"
#include "Piece.h"
#include "Color.h"
#include "Square.h"
#include <QGraphicsItem>
#include <QPixmap>
#include <QLabel>
using namespace std;

class NumberKingsError : public std::logic_error {
	using std::logic_error::logic_error;
};

class King : public Piece { 
public:
	King(Position position, Color couleur, QGraphicsItem* parent = nullptr);
	~King();
	void move(Position position, Square* board[8][8]) override;
	bool isMoveApproved(Position position, Square* board[8][8]) override;
	static int getKingCounter();
	static void setKingCounterNull();

private:
	bool isLegalPosition(Position position);
	bool isSquareFree(Position position, Square* board[8][8]);
	static int KingCounter_;
};

