#include "Functions.h"

void goToXY(int column_x, int row_y)
{
	HANDLE hStdOut; ///HANDLE jest to wska�nik lub indeks bez widocznego typu przypisanego do niego.
	COORD coord; ///Definiuje wsp�rz�dne kom�rki znakowej w buforze ekranu konsoli. Pocz�tek uk�adu wsp�rz�dnych (0,0) znajduje si� w lewej g�rnej kom�rce buforu.

	hStdOut = GetStdHandle(STD_OUTPUT_HANDLE); ///Pobiera doj�cie do okre�lonego standardowego urz�dzenia (standardowe wej�cie, standardowe wyj�cie lub b��d standardowy).
	if (hStdOut == INVALID_HANDLE_VALUE) return;

	coord.X = column_x;
	coord.Y = row_y;

	SetConsoleCursorPosition(hStdOut, coord); ///Ustawia pozycj� kursora w okre�lonym buforze ekranu konsoli 
}

///Czyszczenie ekranu konsoli przy pomocy WINDOWS API.
///Wyczyszczenie ekranu jest metod� wpisania aktualnego
///atrybutu znaku i znaku spacji do ka�dej kom�rki na ekranie,
///a nast�pnie umieszczenia kursora na (0, 0),


void clearScreen()
{
	HANDLE hStdOut;
	CONSOLE_SCREEN_BUFFER_INFO csbi; ///csbi -> console screen buffer info. Zawiera informacje o buforze ekranu konsoli.
	DWORD count; ///unsinged int 
	DWORD cellCount;
	COORD homeCoords = { 0, 0 };

	hStdOut = GetStdHandle(STD_OUTPUT_HANDLE); ///Pobiera doj�cie do okre�lonego standardowego urz�dzenia (standardowe wej�cie, standardowe wyj�cie lub b��d standardowy).
	if (hStdOut == INVALID_HANDLE_VALUE) return;

	///Uzyskaj liczb� kom�rek w bie��cym buforze i atrybuty kom�rki

	if (!GetConsoleScreenBufferInfo(hStdOut, &csbi)) return; ///Zmienia rozmiar okre�lonego buforu ekranu konsoli.
	cellCount = csbi.dwSize.X * csbi.dwSize.Y; //dwSize -> Struktura COORD zawieraj�ca rozmiar bufora ekranu konsoli, w kolumnach znakowych i wierszach.

	///Uzupe�nienie ca�ego bufora spacjami.

	if (!FillConsoleOutputCharacter(
		hStdOut,	///Uchwyt do bufora ekranu konsoli.
		(TCHAR)' ', ///Symbol wpisywany do bufora w tym przypadku jest to symbol spacji.
		cellCount,	///Ilo�c kom�rek do nadpisania.
		homeCoords, ///Koordynaty pierwszej kom�rki.
		&count		///Otrzymuje liczb� wpisanych znak�w.
	)) return;

	///Uzupe�nienie ca�ego bufroa z aktualnymi kolorami i atrybutami.

	if (!FillConsoleOutputAttribute(
		hStdOut,			///Uchwyt do bufora ekranu konsoli.
		csbi.wAttributes,	///Atrybuty znak�w do u�ycia. wAttributes -> Atrybuty znak�w zapisanych w buforze ekranu przez funkcje WriteFile i WriteConsole lub echo do buforu ekranu przez funkcje ReadFile i ReadConsole.
		cellCount,			///Ilo�� kom�rek do ustawienia atrybut�w.
		homeCoords,			///Koordynaty pierwszej kom�rki.
		&count				///Otrzymuje liczb� wpisanych znak�w.
	)) return;

	///Przenie� kursor do "domu = {0, 0}".

	SetConsoleCursorPosition(hStdOut, homeCoords);

}

/*
		Funkcja userIn czeka na dane wej�ciowe u�ytkownika, wywo�uj�c metod� _getch()
	(je�el _getch() zosta�by wykorzystany w main() to metoda b�dzie zatrzymywac w�a do
	momentu otrzymania nowej danej wej�ciowej. 
		Kontrola w�a to WASD, a 27 to w rzeczywisto�ci kod ACSII dla przycisku ESC.
*/

void userIn(void* id) // Pobieranie iformacji od u�ytkownika, w kt�r� stron� porusza si� w��.
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


int oppositeDirection(int input1, int input2) //Sprawdzanie, czy dwa kierunki s� przeciwne do siebie. Nie da si� jednocz�nie i�� w prawo i w lewo.
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