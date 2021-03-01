#include <time.h>
#include <cstdlib>
#include "Snake.h"

int main() 
{
	char replay;

	int delay = 50;

	LABEL:
	srand(time(NULL)); //srand(time(NULL)) -> inicjalizuje generetor liczb pseudolosowych, które są wykorzystywane do umieszczania jedzenia w różnych miejscach na planszy.
	Snake marysia;
	marysia.initializationOfGround();
	marysia.initializationOfSnake();
	marysia.updateFood();
	marysia.firstRandomization();

	/*
			Funkcja _beginthread(userIn, 0, (void*)0) uruchamia funkcję userIn w oddzielnym wątku.
		Dzieje się tak, aby dane wejściowe użytkownika mogły być przetwarzane w dowolnym momencie,
		gdy wątek węża zapętla się ciągle.
	*/

	_beginthread(userIn, 0, (void*)0);

	do
	{
		/*
				Pętla do while porusza wężem przy pomocy funkcji updateSnake(delay) przenosi węża do następnej przestrzeni.
			Następnie zatrzymuje się na okres 50 ms (opóźnienie 50 jest przypisane do zmiennej delay). 
			Zmienna delay służy do dostosowania prędkości węża (Im mniejsze opóźnienie tym wyższy poziom trudności). 
			Po przejściu do następnego miejsca funckja upadateSnake(delay) aktualizuje zmienną globalną,, na której
			wylądowała głowa węża. 
				Jeśli zostanie wykryta wartość FOOD, zostaje wywołana funckja updateFood(), aby utworzyć nowe pożywenie.
			Pętla do while będzie działać do momentu wciśnięcia ESC albo uderzenie w ściane lub zjedzenie ogona.
		*/

		marysia.updateSnake(delay);
		if (item == FOOD)
			marysia.updateFood();

	} while (item >= 0 && input != EXIT);

	goToXY(WIDTH / 2 - 5, HEIGHT / 2 - 2);
	std::cout << " GAME OVER! ";
	goToXY(WIDTH / 2 - 8, HEIGHT / 2 + 2);
	std::cout << "Your socore is " << marysia.reachFoodCounter() - 1 << "!" << std::endl;
	goToXY(WIDTH / 2, HEIGHT / 2);

	_getch();
	clearScreen();

	goToXY(WIDTH / 3, HEIGHT / 2 - 2);
	std::cout << "Would you like to play again?";
	goToXY(WIDTH / 3, HEIGHT / 2 + 2);
	std::cout << "Press y for YES or n for NO :";
	replay = _getch();
	
	if (replay == 'y')
		goto LABEL;

	clearScreen();
	return 0;
}