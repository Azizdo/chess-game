//Vue-Controlleur du jeu d'échec
//La classe Board implémente l'interface et créer des élements du modèles 
// Par Aziz Doghri et Farid Bakir

#include "board.h"
#pragma warning(push, 0)
#include <QColor>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QGraphicsView>
#include <QPainter>
#include <QPixmap>
#include <QLabel>
#include <QAbstractScrollArea>
#pragma pop()
using namespace std;

Board::Board(QWidget* parent) : QMainWindow(parent) { 
	scene_ = new QGraphicsScene();
	
	setChessBoard();
	displayButtons();

	scene_->setSceneRect(-450, 0, 1500, 1000);
	setFixedSize(1900, 1200);

	connect(replay_, SIGNAL(clicked(bool)), this, SLOT(quitGame()));
	connect(*positionsChoiceList_.begin(), SIGNAL(clicked(bool)), this, SLOT(createPositionDefault()));
	connect(*(positionsChoiceList_.begin()+1), SIGNAL(clicked(bool)), this, SLOT(createPositionChoice1()));
	connect(*(positionsChoiceList_.begin()+2), SIGNAL(clicked(bool)), this, SLOT(createPositionChoice2()));
}

void Board::setChessBoard() {
	int calculX;
	int calculY;
	for (int posX = 0; posX < getSizeX(); posX++) {
		for (int posY = 0; posY < getSizeY(); posY++) {
			Position position(posX, posY);
			auto squareView = new Square(position);
			calculX = posX * squareView->measureSquare;
			calculY = posY * squareView->measureSquare;
			squareView->setRect(calculX, calculY, squareView->measureSquare, squareView->measureSquare);

			board_[posX][posY] = squareView;

			scene_->addItem(squareView);
		}
	}
}

void Board::displayButtons() {

	startView_ = new QGraphicsRectItem();
	startView_->setRect(-450, 100, 370, 50);
	startView_->setBrush(QColor("darkRed"));
	scene_->addItem(startView_);

	startText_->setPos(-450, 110);
	startText_->setPlainText("CHOOSE OPTION TO START / RESTART A GAME");
	startText_->setDefaultTextColor(Qt::white);
	scene_->addItem(startText_);

	colorTurnText_->setPos(0, -50);
	colorTurnText_->setPlainText("IT'S THE WHITES' TURN");
	colorTurnText_->setFont(QFont("times", 18, QFont::Bold, true));
	scene_->addItem(colorTurnText_);

	checkWarningText_->setPos(500, -50 );
	checkWarningText_->setPlainText("King in check, MOVE KING!");
	checkWarningText_->setFont(QFont("times", 18, QFont::Bold, true));
	checkWarningText_->setDefaultTextColor(Qt::darkBlue);

	replay_ = new QPushButton("QUIT GAME");
	replay_->setGeometry(900, 320, 200, 100);
	scene_->addWidget(replay_);

	QString txt;
	for (int i = 0; i < 3; i++) {
		if (i == 0) {
			txt = QString("Default Position ");
		}
		else {
			txt = QString("Choice Position ");
			txt.append(QString::number(i));
		}
		QPushButton* btn = new QPushButton(txt);
		positionsChoiceList_.append(btn);
		btn->move(-400, i * 150 + 200);
		btn->resize(270, 100);
		scene_->addWidget(btn);
	}
}

Color Board::colorTurn = Color::WHITE;

void Board::setColorTurn() {
	if (colorTurn == Color::WHITE) {
		colorTurn = Color::BLACK;
		colorTurnText_->setPlainText("IT'S THE BLACKS' TURN");
	}
	else {
		colorTurn = Color::WHITE;
		colorTurnText_->setPlainText("IT'S THE WHITES' TURN");
	}
}

void Board::checkWarning(bool active) {
	if (active) {
		scene_->addItem(checkWarningText_);
	}
	else
		scene_->removeItem(checkWarningText_);
}

void Board::setBkingPosition(Position position) {
	BKingPosition = position;
}
void Board::setWkingPosition(Position position) {
	WKingPosition = position;
}
Position Board::getBkingPosition() {
	return BKingPosition;                                     ////king position save
}
Position Board::getWkingPosition() {
	return WKingPosition;
}
Position Board:: getkingPosition(Color color) {
	if (color == Color::WHITE)
		return WKingPosition;
	else
		return BKingPosition;
}

void Board::createKingOnBoard(Position position, Color color) {
	Piece* newPiece = new King(position, color);
	board_[newPiece->getPosition().getPositionX()][newPiece->getPosition().getPositionY()]->setPiecePtr(newPiece, true);
	listPieceInGame.push_back(newPiece);
	scene_->addItem(newPiece);
	if (color == Color::BLACK)
		setBkingPosition(position);
	else
		setWkingPosition(position);
}
void Board::createBishopOnBoard(Position position, Color color) {
	Piece* newPiece = new Bishop(position, color);
	board_[newPiece->getPosition().getPositionX()][newPiece->getPosition().getPositionY()]->setPiecePtr(newPiece, true);
	listPieceInGame.push_back(newPiece);
	scene_->addItem(newPiece);
}
void Board::createRookOnBoard(Position position, Color color) {
	Piece* newPiece = new Rook(position, color);
	board_[newPiece->getPosition().getPositionX()][newPiece->getPosition().getPositionY()]->setPiecePtr(newPiece, true);
	listPieceInGame.push_back(newPiece);
	scene_->addItem(newPiece);
}

///functions for slots

void Board::quitGame() {
	this->close();
}

void Board::createPositionDefault(){
	for (auto element : listPieceInGame) {
		scene_->removeItem(element);
		board_[element->getPosition().getPositionX()][element->getPosition().getPositionY()]->setPiecePtr(nullptr, true);
		Square::dieZoneW = 800;
		Square::dieZoneB = 800;
		King::setKingCounterNull();
	}
	listPieceInGame.clear();
	listPieceKilled.clear();
	colorTurn = Color::BLACK;
	setColorTurn();
	checkWarning(false);

	createRookOnBoard(Position(7, 7), Color::WHITE); 
	createRookOnBoard(Position(0, 7), Color::WHITE); 
	createRookOnBoard(Position(0, 0), Color::BLACK); 
	createRookOnBoard(Position(7, 0), Color::BLACK);

	createBishopOnBoard(Position(2, 7), Color::WHITE);
	createBishopOnBoard(Position(5, 7), Color::WHITE);
	createBishopOnBoard(Position(2, 0), Color::BLACK);
	createBishopOnBoard(Position(5, 0), Color::BLACK);

	try {
		createKingOnBoard(Position(4, 0), Color::BLACK);
		createKingOnBoard(Position(4, 7), Color::WHITE);
	}
	catch (NumberKingsError& e) {
		std::cout << e.what();
	}
}

void Board::createPositionChoice1(){
	for (auto element : listPieceInGame) {
		scene_->removeItem(element);
		board_[element->getPosition().getPositionX()][element->getPosition().getPositionY()]->setPiecePtr(nullptr, true);
		Square::dieZoneW = 800;
		Square::dieZoneB = 800;
		King::setKingCounterNull();  
	}
	listPieceInGame.clear();
	listPieceKilled.clear();
	colorTurn = Color::BLACK;
	setColorTurn();
	checkWarning(false);

	createRookOnBoard(Position(4, 6), Color::WHITE);
	createRookOnBoard(Position(5, 6), Color::WHITE);
	createRookOnBoard(Position(4, 1), Color::BLACK);
	createRookOnBoard(Position(3, 1), Color::BLACK);

	createBishopOnBoard(Position(5, 7), Color::WHITE);
	createBishopOnBoard(Position(3, 6), Color::WHITE);
	createBishopOnBoard(Position(5, 1), Color::BLACK);
	createBishopOnBoard(Position(3, 0), Color::BLACK);

	try {
		createKingOnBoard(Position(4, 0), Color::BLACK);
		createKingOnBoard(Position(4, 7), Color::WHITE);
	}
	catch (NumberKingsError& e) {
		std::cout << e.what();
	}
}

void Board::createPositionChoice2(){
	for (auto element : listPieceInGame) {
		scene_->removeItem(element);
		board_[element->getPosition().getPositionX()][element->getPosition().getPositionY()]->setPiecePtr(nullptr, true);
		Square::dieZoneW = 800;
		Square::dieZoneB = 800;
		King::setKingCounterNull();
	}
	listPieceInGame.clear();
	listPieceKilled.clear();
	colorTurn = Color::BLACK;
	setColorTurn();
	checkWarning(false);

	createRookOnBoard(Position(3, 4), Color::WHITE);
	createRookOnBoard(Position(4, 3), Color::WHITE);
	createRookOnBoard(Position(3, 3), Color::BLACK);
	createRookOnBoard(Position(4, 4), Color::BLACK);

	createBishopOnBoard(Position(5, 2), Color::WHITE);
	createBishopOnBoard(Position(4, 6), Color::WHITE);
	createBishopOnBoard(Position(4, 1), Color::BLACK);
	createBishopOnBoard(Position(5, 5), Color::BLACK);

	try {
		createKingOnBoard(Position(4, 0), Color::BLACK);
		createKingOnBoard(Position(4, 7), Color::WHITE);
	}
	catch (NumberKingsError& e) {
		std::cout << e.what();
	}
}