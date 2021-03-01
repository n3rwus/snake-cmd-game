#include "Functions.h"

void goToXY(int column_x, int row_y)
{
	HANDLE hStdOut; ///HANDLE jest to wskaŸnik lub indeks bez widocznego typu przypisanego do niego.
	COORD coord; ///Definiuje wspó³rzêdne komórki znakowej w buforze ekranu konsoli. Pocz¹tek uk³adu wspó³rzêdnych (0,0) znajduje siê w lewej górnej komórce buforu.

	hStdOut = GetStdHandle(STD_OUTPUT_HANDLE); ///Pobiera dojœcie do okreœlonego standardowego urz¹dzenia (standardowe wejœcie, standardowe wyjœcie lub b³¹d standardowy).
	if (hStdOut == INVALID_HANDLE_VALUE) return;

	coord.X = column_x;
	coord.Y = row_y;

	SetConsoleCursorPosition(hStdOut, coord); ///Ustawia pozycjê kursora w okreœlonym buforze ekranu konsoli 
}

///Czyszczenie ekranu konsoli przy pomocy WINDOWS API.
///Wyczyszczenie ekranu jest metod¹ wpisania aktualnego
///atrybutu znaku i znaku spacji do ka¿dej komórki na ekranie,
///a nastêpnie umieszczenia kursora na (0, 0),


void clearScreen()
{
	HANDLE hStdOut;
	CONSOLE_SCREEN_BUFFER_INFO csbi; ///csbi -> console screen buffer info. Zawiera informacje o buforze ekranu konsoli.
	DWORD count; ///unsinged int 
	DWORD cellCount;
	COORD homeCoords = { 0, 0 };

	hStdOut = GetStdHandle(STD_OUTPUT_HANDLE); ///Pobiera dojœcie do okreœlonego standardowego urz¹dzenia (standardowe wejœcie, standardowe wyjœcie lub b³¹d standardowy).
	if (hStdOut == INVALID_HANDLE_VALUE) return;

	///Uzyskaj liczbê komórek w bie¿¹cym buforze i atrybuty komórki

	if (!GetConsoleScreenBufferInfo(hStdOut, &csbi)) return; ///Zmienia rozmiar okreœlonego buforu ekranu konsoli.
	cellCount = csbi.dwSize.X * csbi.dwSize.Y; //dwSize -> Struktura COORD zawieraj¹ca rozmiar bufora ekranu konsoli, w kolumnach znakowych i wierszach.

	///Uzupe³nienie ca³ego bufora spacjami.

	if (!FillConsoleOutputCharacter(
		hStdOut,	///Uchwyt do bufora ekranu konsoli.
		(TCHAR)' ', ///Symbol wpisywany do bufora w tym przypadku jest to symbol spacji.
		cellCount,	///Iloœc komórek do nadpisania.
		homeCoords, ///Koordynaty pierwszej komórki.
		&count		///Otrzymuje liczbê wpisanych znaków.
	)) return;

	///Uzupe³nienie ca³ego bufroa z aktualnymi kolorami i atrybutami.

	if (!FillConsoleOutputAttribute(
		hStdOut,			///Uchwyt do bufora ekranu konsoli.
		csbi.wAttributes,	///Atrybuty znaków do u¿ycia. wAttributes -> Atrybuty znaków zapisanych w buforze ekranu przez funkcje WriteFile i WriteConsole lub echo do buforu ekranu przez funkcje ReadFile i ReadConsole.
		cellCount,			///Iloœæ komórek do ustawienia atrybutów.
		homeCoords,			///Koordynaty pierwszej komórki.
		&count				///Otrzymuje liczbê wpisanych znaków.
	)) return;

	///Przenieœ kursor do "domu = {0, 0}".

	SetConsoleCursorPosition(hStdOut, homeCoords);

}

/*
		Funkcja userIn czeka na dane wejœciowe u¿ytkownika, wywo³uj¹c metodê _getch()
	(je¿el _getch() zosta³by wykorzystany w main() to metoda bêdzie zatrzymywac wê¿a do
	momentu otrzymania nowej danej wejœciowej. 
		Kontrola wê¿a to WASD, a 27 to w rzeczywistoœci kod ACSII dla przycisku ESC.
*/

void userIn(void* id) // Pobieranie iformacji od u¿ytkownika, w któr¹ stronê porusza siê w¹¿.
{
	do
	{
		int button = _getch();

		switch (button)
		{
		case 'W': case 'w': input = UP;
			break;
		case 'S': case 's': input = DOWN;
			break;
		case 'D': case 'd': input = RIGHT;
			break;
		case 'A': case 'a': input = LEFT;
			break;
		case 27: input = EXIT;
			break;
		}
	} while (input != EXIT && item >= NOTHING);

	_endthread();
	return;
}


int oppositeDirection(int input1, int input2) //Sprawdzanie, czy dwa kierunki s¹ przeciwne do siebie. Nie da siê jednoczêœnie iœæ w prawo i w lewo.
{
	if (input1 == LEFT && input2 == RIGHT)
		return 1;
	if (input1 == RIGHT && input2 == LEFT)
		return 1;
	if (input1 == UP && input2 == DOWN)
		return 1;
	if (input1 == DOWN && input2 == UP)
		return 1;

	return 0;
}