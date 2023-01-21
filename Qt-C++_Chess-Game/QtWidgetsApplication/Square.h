//Représentarion des cases du jeu d'échec,
//En agrégation dans le board, la classe Square fait le lien entre l'interface/le board et le modèle 
// surtout par sa fonction mousePressEvent qui appel un comportement différent à chaque clique de souris.
// 
// Par Aziz Doghri et Farid Bakir;

#pragma once
#include <iostream>
#include<memory>
#include <string>
#include"Piece.h"
#include "Position.h"
#include "Color.h"
#include <QColor>
#include <QGraphicsRectItem>
#include <QBrush>
#include <QGraphicsSceneMouseEvent>
using namespace std;

class Square : public QGraphicsRectItem {
public:
	Square();
	Square(Position position);
	~Square() = default;

	bool isFull();
	QColor getColor();
	void setColor(QColor color);
	Piece* getPiece();
	void setPiecePtr(Piece* newPiecePtr, bool kill);
	Position getPosition() const;
	void killPiece(bool toKill);

	bool isDangerForKing(Position position, Color ennemyColor);
	bool iskingInCheck(Color turn);
	
	int measureSquare = 100;
	static int dieZoneW;
	static int dieZoneB;

protected:
	void mousePressEvent(QGraphicsSceneMouseEvent* ev);

private:
	Piece* piecePtr_ = nullptr;
	Position position_;
	bool full_ = false;
	QColor color_;
	QColor pathColor_ = QColor("red");
	QBrush currentColor_;
	bool isMoveOn = false;	
	bool isClicked = false;
};

