//Position est une classe qui mod�lise les positions que les pi�ces devront occupper
//sur l'�ch�quier. Elle poss�de les m�thode necessaire 
//pour manipuler les positions afins de s'assurer
//qu'elles restent valident.
//
// Par Aziz Doghri et Farid Bakir

#pragma once
#include <iostream>
#include <string>
using namespace std;

class Position {
public:
	Position();
	Position(int positionX, int positionY);

	int getPositionX() const;
	int getPositionY() const;
	void setPositionX(int positionX);
	void setPositionY(int positionY);
	void ajustPosition(int x, int y);
	void setPosition(Position position);
	bool isValidPosition();
	bool isSamePosition(Position position);
	bool isSameX(Position position);
	bool isSameY(Position position);
	bool isValidXY(int x, int y);

private:
	int positionX_;
	int positionY_;
};

