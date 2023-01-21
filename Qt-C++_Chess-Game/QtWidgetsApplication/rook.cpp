//Rook est une classe qui implemente une représentation d'une tour au échec.
//Elle est en mesure de verifier ses propres mouvement et
// de savoir quels sont les positions valides.
// 
// Par Aziz Doghri et Farid Bakir

#include "rook.h"
using namespace std;

Rook::Rook(Position position, Color couleur, QGraphicsItem* parent) : Piece(position, couleur, parent) {
	name_ = "Rook";

	if (couleur == Color::BLACK)
		setPixmap(QPixmap("bRook.png"));

	else
		setPixmap(QPixmap("wRook.png"));

	int calculX = (measureSquare * position.getPositionX()) + pngAdjust;
	int calculY = (measureSquare * position.getPositionY()) + pngAdjust;
	setPos(calculX, calculY);
}

void Rook::move(Position position, Square* board[8][8]) {
	this->position_.setPosition(position);

	int calculX = (measureSquare * position.getPositionX()) + pngAdjust;
	int calculY = (measureSquare * position.getPositionY()) + pngAdjust;
	setPos(calculX, calculY);
};

bool Rook::isMoveApproved(Position position, Square* board[8][8]) {
	bool approved = position.isValidPosition() && isLegalPosition(position)
		&& isSquareFree(position, board) && isPathPossible(position, board);
	return approved;
}

bool Rook::isLegalPosition(Position position) {

	bool sameValueX = this->position_.isSameX(position);
	bool sameValueY = this->position_.isSameY(position);

	return (!sameValueX && sameValueY) || (sameValueX && !sameValueY);
}

bool Rook::isSquareFree(Position position, Square* board[8][8]) {
	bool isFree = !(board[position.getPositionX()][position.getPositionY()]->isFull()
		&& board[position.getPositionX()][position.getPositionY()]
		->getPiece()->getCouleur() == this->color_);
	return isFree;
}

bool Rook::isPathPossible(Position position, Square* board[8][8]) {

	bool isPosible = true;
	Position positionTemp;
	positionTemp.setPosition(position_);
	pair<int, int> directions = direction(position);


	while (!positionTemp.isSamePosition(position)) {
		positionTemp.ajustPosition(directions.first, directions.second);


		if (!positionTemp.isSamePosition(position)
			&& board[positionTemp.getPositionX()][positionTemp.getPositionY()]->isFull()) {
			isPosible = false;
			break;
		}
	}
	return isPosible;
}


pair<int, int> Rook::direction(Position finalPosition) {
	pair<int, int> direction;
	int initialPositionX = this->position_.getPositionX();
	int initialPositionY = this->position_.getPositionY();
	int finalPositionX = finalPosition.getPositionX();
	int finalPositionY = finalPosition.getPositionY();


	if (finalPositionX < initialPositionX) {
		direction.first = -1;
		direction.second = 0;
	}
	else if (finalPositionX > initialPositionX) {
		direction.first = 1;
		direction.second = 0;
	}
	else if (finalPositionY < initialPositionY) {
		direction.first = 0;
		direction.second = -1;
	}
	else {
		direction.first = 0;
		direction.second = 1;
	}
	return direction;
}

