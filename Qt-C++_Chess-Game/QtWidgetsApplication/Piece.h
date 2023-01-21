//Piece est une classe abstraite qui sert d'implémentation commune au classe 
//enfant : Roi, Tour et Fou.
// 
// Par Aziz Doghri et Farid Bakir

#pragma once
#include <iostream>
#include <string>
#include "Position.h"
#include "Color.h"
#include <QGraphicsItem>
using namespace std;

class Square;

class Piece : public QGraphicsPixmapItem {
public:

	Piece(Position position, Color couleur, QGraphicsItem* parent = nullptr);
	virtual ~Piece() = default;
	
	Position getPosition();
	Color getCouleur();
	void setPosition(Position position);
	virtual void move(Position position, Square* board[8][8]) = 0;
	virtual bool isMoveApproved(Position position, Square* board[8][8]) = 0;
	string getName() const { return name_; }
	int measureSquare = 100;
	int pngAdjust = 20;  

protected:
	Position position_;
	Color color_;
	string name_ = "";
};

