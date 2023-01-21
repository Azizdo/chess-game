//Représentarion des cases du jeu d'échec,
//En agrégation dans le board, la classe Square fait le lien entre l'interface/le board et le modèle 
// surtout par sa fonction mousePressEvent qui appel un comportement différent à chaque clique de souris.
//La classe Board implémente l'interface et créer des élements du modèles 
// 
// Par Aziz Doghri et Farid Bakir;

#include "Square.h"
#include "board.h"
using namespace std;

extern Board* board;

Square::Square() {
	setRect(0, 0, measureSquare, measureSquare);
	setFlag(QGraphicsItem::ItemIsSelectable);
}


Square::Square(Position position) : position_(position) {
	setRect(0, 0, measureSquare, measureSquare);
	if ((position_.getPositionX() + position_.getPositionY()) % 2 == 0) {
		setBrush(QColor("darkCyan"));
		color_ = QColor("darkCyan");
	}
	else {
		setBrush(QColor("lightGray"));
		color_ = QColor("lightGray");
	}
	setFlag(QGraphicsItem::ItemIsSelectable);
}


bool Square::isFull() {
	return full_;
}

QColor Square::getColor() {
	return this->color_;
}

void Square::setColor(QColor newColor) {
	setBrush(newColor);
	currentColor_.setColor(newColor);

	if (newColor == pathColor_) {
		isMoveOn = true;
	}

	else {
		color_ = newColor;
		isMoveOn = false;
	}
}

Piece* Square::getPiece() {
	return this->piecePtr_;
}

Position Square::getPosition() const{
	return position_;
}

void Square::setPiecePtr(Piece* newPiecePtr, bool kill){
	if (piecePtr_ != nullptr && newPiecePtr != nullptr)
		killPiece(kill);
	piecePtr_ = newPiecePtr;
	full_ = (piecePtr_ != nullptr);
}

int Square::dieZoneW = 800;
int Square::dieZoneB = 800;

void Square::killPiece(bool toKill) {
	if (toKill) {
		if (piecePtr_->getCouleur() == Color::WHITE) {
			piecePtr_->setPos(dieZoneW, 500);
			piecePtr_->setPosition(Position(dieZoneW, 200));
			dieZoneW += 40;
		}
		else {
			piecePtr_->setPos(dieZoneB, 200);
			piecePtr_->setPosition(Position(dieZoneB, 200));
			dieZoneB += 40;
		}
		board->listPieceKilled.push_back(piecePtr_);
	}
}

bool Square::isDangerForKing(Position position, Color ourColor) {
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (board->board_[i][j]->isFull()) {
				if (board->board_[i][j]->getPiece()->getCouleur() != ourColor) {
					if (board->board_[i][j]->getPiece()->isMoveApproved(position, board->board_)) {
						return true;
					}
				}
			}
		}
	}
	return false;
}

bool Square::iskingInCheck(Color turn) {
	return isDangerForKing(board->getkingPosition(turn), turn);
}

void Square::mousePressEvent(QGraphicsSceneMouseEvent* ev) {

	if (isMoveOn) {
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				if (board->board_[i][j]->isClicked && board->board_[i][j]->isFull()) {
					board->board_[i][j]->isClicked = false;
					auto piecePtr = board->board_[i][j]->getPiece();
					Position init = piecePtr->getPosition();
					piecePtr->move(position_, board->board_);
					setPiecePtr(board->board_[i][j]->getPiece(), true);
					board->board_[i][j]->setPiecePtr(nullptr, true);
					
					if (piecePtr->getName() == "King") {
						if (piecePtr->getCouleur() == Color::WHITE)
							board->setWkingPosition(position_);
						else
							board->setBkingPosition(position_);
					}
				}
			}
		}
		board->setColorTurn();
		if(iskingInCheck(board->colorTurn))
			board->checkWarning(true);
		else
			board->checkWarning(false);
	}
	
	else if (isFull() && (getPiece()->getCouleur() == board->colorTurn)) {

		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				QColor originalColor = board->board_[i][j]->getColor();
				board->board_[i][j]->setColor(originalColor);
				board->board_[i][j]->isClicked = false;
			}
		}

		if (isClicked == false) {
			for (int i = 0; i < 8; i++) {
				for (int j = 0; j < 8; j++) {
					Position position(i, j);
					QColor originalColor = board->board_[i][j]->getColor();
					if (!iskingInCheck(board->colorTurn)) {
						if (getPiece()->isMoveApproved(position, board->board_)) {
							board->board_[i][j]->setColor(QColor("red"));
							isClicked = true;
							if (getPiece()->getName() == "King" && isDangerForKing(position, getPiece()->getCouleur())) {
								board->board_[i][j]->setColor(QColor(originalColor));
							}
						}
					}

					else {
						if (getPiece()->getName() == "King") {
							if (getPiece()->isMoveApproved(position, board->board_)) {
								board->board_[i][j]->setColor(QColor("red"));
								isClicked = true;
							}
							if (isDangerForKing(position, getPiece()->getCouleur())) {
								board->board_[i][j]->setColor(QColor(originalColor));
							}

						}
					}
				}
			}
		}
	}

	else {
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				QColor originalColor = board->board_[i][j]->getColor();
				board->board_[i][j]->setColor(originalColor);
				board->board_[i][j]->isClicked = false;
			}
		}
	}
	
	bool refresh = true;
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (board->board_[i][j]->isClicked)
				refresh = false;
		}
	}
	if (refresh) {
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				QColor originalColor = board->board_[i][j]->getColor();
				board->board_[i][j]->setColor(originalColor);
			}
		}
	}

	QGraphicsItem::mousePressEvent(ev);
}
