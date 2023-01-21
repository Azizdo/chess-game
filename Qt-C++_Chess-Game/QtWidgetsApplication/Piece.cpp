//Piece est une classe abstraite qui sert d'implémentation commune au classe 
//enfant : Roi, Tour et Fou.
// 
// Par Aziz Doghri et Farid Bakir

#include "Piece.h"
using namespace std;


Piece::Piece(Position position, Color couleur, QGraphicsItem* parent)
	: position_(position), color_(couleur), QGraphicsPixmapItem(parent) {}

Position Piece::getPosition() {
	return this->position_;
}

Color Piece::getCouleur() {
	return this->color_;
}

void Piece::setPosition(Position position) {
	this->position_.setPosition(position);
}

