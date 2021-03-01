#pragma once
#include "Coords.h"
#include "Functions.h"
#include <iostream>

class Snake
{
private:
	int length;						//D�ugo�� w�a.
	int direction;					//Kierunek poruszania si� w�a.
	int foodCounter;				//Licznik jedzenia, kt�re w�� zjad�.
	Coords body[WIDTH * HEIGHT];	//Definicja cia�a w�a.
	int ground[MAX][MAX];			//Obaszr planszy, po kt�rej porusza si� w��.
public:
	void initializationOfGround();  //Inicjalizacja planszy.
	void initializationOfSnake();	//Inicjalizacja w�a.
	void updateSnake(int delay);	//Aktualizacja w�a.
	void updateFood();				//Aktualizacja jedzenia.
	void firstRandomization();		//Pierwsze losowanie.
	int  reachFoodCounter();		//Zwr�cenie warto�ci licznika jedzenia.
};

