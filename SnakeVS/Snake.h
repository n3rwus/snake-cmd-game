#pragma once
#include "Coords.h"
#include "Functions.h"
#include <iostream>

class Snake
{
private:
	int length;						//D³ugoœæ wê¿a.
	int direction;					//Kierunek poruszania siê wê¿a.
	int foodCounter;				//Licznik jedzenia, które w¹¿ zjad³.
	Coords body[WIDTH * HEIGHT];	//Definicja cia³a wê¿a.
	int ground[MAX][MAX];			//Obaszr planszy, po której porusza siê w¹¿.
public:
	void initializationOfGround();  //Inicjalizacja planszy.
	void initializationOfSnake();	//Inicjalizacja wê¿a.
	void updateSnake(int delay);	//Aktualizacja wê¿a.
	void updateFood();				//Aktualizacja jedzenia.
	void firstRandomization();		//Pierwsze losowanie.
	int  reachFoodCounter();		//Zwrócenie wartoœci licznika jedzenia.
};

