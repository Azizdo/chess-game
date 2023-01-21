//Vue-Controlleur du jeu d'échec
//La classe Board implémente l'interface et créer des élements du modèles 
// 
// Par Aziz Doghri et Farid Bakir

#pragma once
#include <QtWidgets/QMainWindow>
#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include "Square.h"
#include "Piece.h"
#include "Position.h"
#include "rook.h"
#include "king.h"
#include "bishop.h"
#include "Color.h"
#pragma warning(push, 0)
#include <QObject>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QColor>
#include <QPushButton>
#include <QVBoxLayout>
#pragma pop()


class Board : public QMainWindow {
	Q_OBJECT
public:
	Board(QWidget* parent = 0);
	~Board() override = default;

	void setChessBoard();
	void displayButtons();
	
	void setColorTurn();
	void checkWarning(bool active);

	void createKingOnBoard(Position position, Color color);
	void createBishopOnBoard(Position position, Color color);
	void createRookOnBoard(Position position, Color color);


	const int getSize() const { return lenght_ * height_; }
	const int getSizeX() const { return lenght_; }
	const int getSizeY() const { return height_; }
	QGraphicsScene* getScene() const{ return scene_; }
	
	void setBkingPosition(Position position);
	void setWkingPosition(Position position);
	Position getBkingPosition();                 //king save positions
	Position getWkingPosition();
	Position getkingPosition(Color color);


	Square* board_[8][8];
	static Color colorTurn;
	std::vector<Piece*> listPieceInGame; 
	std::vector<Piece*> listPieceKilled;

private slots:
	void quitGame();
	void createPositionDefault();
	void createPositionChoice1();
	void createPositionChoice2();
	

private:
	const int lenght_ = 8;
	const int height_ = 8;
	Position BKingPosition;
	Position WKingPosition;
	QGraphicsScene* scene_;
	QPushButton* replay_;
	QList <QPushButton*> positionsChoiceList_;
	QGraphicsRectItem* startView_;
	QGraphicsTextItem* startText_ = new QGraphicsTextItem();
	QGraphicsTextItem* colorTurnText_ = new QGraphicsTextItem();
	QGraphicsTextItem* checkWarningText_ = new QGraphicsTextItem();
};
