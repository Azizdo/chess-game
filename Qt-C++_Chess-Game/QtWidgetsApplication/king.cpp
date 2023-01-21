//King est une classe qui implemente une représentation du roi au échec.
//Elle est en mesure de verifier ses propres mouvement,
// de savoir quels sont les positions valides et levé une exception s'il y a plus de 2 rois
// 
// Par Aziz Doghri et Farid Bakir


#include "king.h"
using namespace std;


King::King(Position position, Color couleur, QGraphicsItem* parent) : Piece(position, couleur, parent) {
	name_ = "King";

	KingCounter_++;
		if (KingCounter_ > 2)
			throw NumberKingsError("Number of Kings greater than 2");

	if (couleur == Color::BLACK)
		setPixmap(QPixmap("bKing.png"));

	else
		setPixmap(QPixmap("wKing.png"));
	int calculX = (measureSquare * position.getPositionX()) + pngAdjust;
	int calculY = (measureSquare * position.getPositionY()) + pngAdjust;
	setPos(calculX, calculY);
}


King::~King() {
	KingCounter_--;
}


void King::move(Position position, Square* board[8][8]) {
	this->position_.setPosition(position);
	int calculX = (measureSquare * position.getPositionX()) + pngAdjust;
	int calculY = (measureSquare * position.getPositionY()) + pngAdjust;
	setPos(calculX, calculY);
};


bool King::isMoveApproved(Position position, Square* board[8][8]) {
	return position.isValidPosition()
		&& isLegalPosition(position) && isSquareFree(position, board); 
}


int King::KingCounter_ = 0;

int King::getKingCounter(){
	return KingCounter_;
}


void King::setKingCounterNull() {
	KingCounter_ = 0;
}


bool King::isLegalPosition(Position position) {
	bool goodMove = false;
	goodMove = abs(position.getPositionX() - position_.getPositionX()) <= 1
		&& abs(position.getPositionY() - position_.getPositionY()) <= 1;
	return goodMove;
};


bool King::isSquareFree(Position position, Square* board[8][8]) {
	bool isFree = !(board[position.getPositionX()][position.getPositionY()]->isFull()
		&& board[position.getPositionX()][position.getPositionY()]
		->getPiece()->getCouleur() == this->color_);
	return isFree;
}


