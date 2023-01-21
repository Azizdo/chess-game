//Bishop est une classe qui implemente une représentation d'un fou au échec.
//Elle est en mesure de verifier ses propres mouvement et
// de savoir quels sont les positions valides.
//
// Par Aziz Doghri et Farid Bakir

#include "bishop.h"
using namespace std;

Bishop::Bishop(Position position, Color couleur, QGraphicsItem* parent) : Piece(position, couleur, parent){
	name_ = "Bishop";
	
	if (couleur == Color::BLACK)
		setPixmap(QPixmap("bBishop.png"));

	else
		setPixmap(QPixmap("wBishop.png"));

	int calculX = (measureSquare * position.getPositionX()) + pngAdjust;
	int calculY = (measureSquare * position.getPositionY()) + pngAdjust;
	setPos(calculX, calculY);
}

void Bishop::move(Position position, Square* board[8][8]) {
	this->position_.setPosition(position);

	int calculX = (measureSquare * position.getPositionX()) + pngAdjust;
	int calculY = (measureSquare * position.getPositionY()) + pngAdjust;
	setPos(calculX, calculY);
};

bool Bishop::isMoveApproved(Position position, Square* board[8][8]) {
	bool approved = position.isValidPosition() && isLegalPosition(position)
		&& isSquareFree(position, board) && isPathPossible(position, board);
	return approved;
}


bool Bishop::isLegalPosition(const Position& position) {
	bool isLegal = abs(position.getPositionX() - this->position_.getPositionX())
		== abs(position.getPositionY() - this->position_.getPositionY());
	return isLegal;
}

bool Bishop::isSquareFree(Position position, Square* board[8][8]) {
	bool isFree = !(board[position.getPositionX()][position.getPositionY()]->isFull()
		&& board[position.getPositionX()][position.getPositionY()]
		->getPiece()->getCouleur() == this->color_);
	return isFree;
}

bool Bishop::isPathPossible(Position positionArrival, Square* board[8][8]) {
	bool isFree = true;
	Position positionTemp;
	positionTemp.setPosition(position_);
	pair<int, int> directions = direction(positionArrival);


	while (!positionTemp.isSamePosition(positionArrival)) {
		positionTemp.ajustPosition(directions.first, directions.second);

		if (!positionTemp.isSamePosition(positionArrival)
			&& board[positionTemp.getPositionX()][positionTemp.getPositionY()]->isFull()) {
			isFree = false;
			break;
		}
	}
	return isFree;

}

pair<int, int> Bishop::direction(Position finalPosition) {
	pair<int, int> direction;
	int initialPositionX = this->position_.getPositionX();
	int initialPositionY = this->position_.getPositionY();
	int finalPositionX = finalPosition.getPositionX();
	int finalPositionY = finalPosition.getPositionY();


	if (finalPositionX < initialPositionX && finalPositionY < initialPositionY) {
		direction.first = -1;
		direction.second = -1;
	}
	else if (finalPositionX < initialPositionX && finalPositionY > initialPositionY) {
		direction.first = -1;
		direction.second = 1;
	}
	else if (finalPositionX > initialPositionX && finalPositionY < initialPositionY) {
		direction.first = 1;
		direction.second = -1;
	}
	else {
		direction.first = 1;
		direction.second = 1;
	}
	return direction;
}


