//Position est une classe qui modèlise les positions que les pièces devront occupper
//sur l'échéquier. Elle possède les méthode necessaire 
//pour manipuler les positions afins de s'assurer
//qu'elles restent valident.
//
// Par Aziz Doghri et Farid Bakir


#include "Position.h"
using namespace std;


Position::Position() {
	this->positionX_ = 0;
	this->positionY_ = 0;
}

Position::Position(int positionX, int positionY) {
	if (isValidXY(positionX, positionY)) {
		this->positionX_ = positionX;
		this->positionY_ = positionY;
	}
	else {
		cout << "position mauvaise donc elle est egale a : ";
		positionX_ = 0;
		positionY_ = 0;
	}
}

int Position::getPositionX() const {
	return positionX_;
}

int Position::getPositionY() const {
	return positionY_;
}

void Position::setPositionX(int positionX) {
	if (isValidXY(positionX, 0)) {
		positionX_ = positionX;
	}
	else {
		cout << "attention mauvaise position";
	}
}

void Position::setPositionY(int positionY) {
	if (isValidXY(0, positionY)) {
		positionY_ = positionY;
	}
	else {
		cout << "attention mauvaise position";
	}
}

void Position::ajustPosition(int x, int y) {

	positionX_ += x;
	positionY_ += y;
}

void Position::setPosition(Position position) {
	positionX_ = position.getPositionX();
	positionY_ = position.getPositionY();
}

bool Position::isValidPosition() {
	bool verificationX = positionX_ <= 7 && positionX_ >= 0;
	bool verificationY = positionY_ <= 7 && positionY_ >= 0;
	return verificationX && verificationY;
}

bool Position::isSamePosition(Position position) {

	return positionX_ == position.getPositionX()
		&& positionY_ == position.getPositionY();
}

bool Position::isSameX(Position position) {
	return positionX_ == position.getPositionX();
}

bool Position::isSameY(Position position) {
	return positionY_ == position.getPositionY();
}

bool Position::isValidXY(int x, int y) {
	bool isXvalid = !(x < 0 || x > 7);
	bool isYvalid = !(y < 0 || y > 7);
	return isXvalid && isYvalid;
}

