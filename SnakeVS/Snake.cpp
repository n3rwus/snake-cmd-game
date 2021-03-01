#include "Snake.h"

/*
		Funkcja initializationOfGround() klasy Snake rozpoczyna swoje dzia�anie od stworzenia pustej przestrzeni
	w rozmiarze [MAX][MAX] (MAX = 100 i znajduje si� w pliku Define.h) w pierwszej p�tli for. 
	Tworzy pole kwadratu o rozmiarze 100 na 100. W nastepnych dw�ch p�tlach for, rysujemy �ciany planszy, po 
	kt�rej b�dzie porusza� si� nasz obiekt/w��. 
		Zmienne WIDTH i HEIGHT zosta�y zdefiniowane w pliku nag��wkowym tak samo jak zmienna MAX. Warto�ci
	dla wysoko�ci i szeroko�ci s� dobrane metod� pr�b i b��d�w.
*/


void Snake::initializationOfGround()
{
	for (int i = 0; i < MAX; i++)
	{
		for (int j = 0; j < MAX; j++)
		{
			ground[i][j] = 0;
		}
	}

	for (int i = 0; i <= WIDTH + 1; i++) //g�rna i dolna �ciana
	{
		ground[0][i] = WALL;
		ground[HEIGHT + 1][i] = WALL;
	}

	for (int i = 0; i <= HEIGHT; i++)	//lewa i prawa �ciana
	{
		ground[i][0] = WALL;
		ground[i][WIDTH + 1] = WALL;
	}
}

/*
		Funkcja initializationOfSnake() inicjalizuje d�ugo�� w�a przy pomocy INIT_SNAKE_LENGTH z g�ow� w�a na samym �rodku planszy.
	Pocz�tkowy kierunek w�a jest ustawiony na prawo dla zmiennej wej�ciowej. Dane wej�ciowe to zmienna globalna zdefiniowana w 
	pliku nag��wkowym Define.h, kt�ra pobiera dane wej�ciowe u�ytkwownika w celu sterowania w�em. 
		W p�tli for nadajemy reszcie cia�a w�a okre�lone po�o�enia, aby "stworzy�o si�". Tablice directionArray_X i directionArray_Y
	s� wst�pnie wype�nione warto�ciami wskazuj�cymi na zmiann� kierunku na planszy.
	Np.: Je�li wej�cie jest prawe ma warto�� 0, wi�c directionArray_X[0] wynosi 1, a directionArray_Y[0] wynosi 0.
		Przeklada si� to na ruch, kt�ry jest opisany w pliku Define.h. (1, 0) itp.
		W momencie kiedy chcemy zdefiniowa� reszt� cia�a w�a, odejmujemy directionArray_X i directionArray_Y od wp�rz�dnych g�owy 
	w�a.
		Na ko�cu musimy zaktualizowa� plansz�, aby w�� si� w niej "stworzy�".
*/

void Snake::initializationOfSnake()
{
	length = INIT_SNAKE_LENGHT;

	//Ustawienie g�owy w�a w �rodku.
	body[0].x = WIDTH / 2;
	body[0].y = HEIGHT / 2;

	direction = input;
	foodCounter = 0;

	for (int i = 1; i < length; i++)
	{
		body[i].x = body[i - 1].x - directionArray_X[direction]; //Je�eli porusz� si� w prawo cia�o b�dzie po lewej itp;
		body[i].y = body[i - 1].y - directionArray_Y[direction];
	}

	// infromacje dla ziemi/planszy o pozycji w�a
	for (int i = 0; i < length; i++)
		ground[body[i].y][body[i].x] = SNAKE;
}

/*
		Kiedy wywo�ujemy funckj� updateSnake(int delay), najpierw tworzy ona tablic�
	o nazwie prevBody[] typu Coords. Rozmiar tablicy jest inicjalizowany jako 
	WIDTH * HEIGHT, kt�ry jest maksymaln� d�ugo�ci� w�a. Tablica tworzy tymczasow� kopi�
	aktualnej pozycji w�a z tablicy body[].
		Nastepnie sprawdzamy dane wej�ciowe u�ytkownika, aby zobaczy�, czy zosta� wci�ni�ty
	klawisz ESC czy te� przeciwny do kierunku w�a.
		Ruch w�a odbywa si� poprzez aktualizacj� tablicy body[] do nowej lokalizacji. 
	prevBody[].x i prevBody[].y reprezentuj� wsp�rz�dne g�owy w�, wi�c dodajemy do nich odpowiednio
	lierunki directionArray_X[direction] i directionArray_Y[direction], aby uzyska� now� wsp�rz�dn� g�owy.
		NOTHING reprezentuje  warto�� 0, wi�c mniej ni� NOTHING oznacza warto�� ujemn�, a liczby ujemne 
	oznaczaj� GAME OVER. 
		Przypisujemy -1 do zmiennej iteam, aby powiadomi� inne funkcje i natychmiast wyj�� z funkcji update(int delay) za pomoc�
	s�owa kluczowego return;
		Je�li g�owa w�a napotka FOOD, wyd�u�y jego tu��w o jeden '#', z drugiej strony je�li w�� nic nie napotka�, musimy
	usun�� ostatni punkt w�a.
		Usuni�cie ostatniego punktu cia�a robi si� poprzez aktualizacj� ground[x][y], aby da� zna�, �e jest tam pusto.
	Funkcja goToXY(body[length - 1].x, body[length - 1].y) przenosi kursor do ostatniego punktu w�a i frukuje puste 
	miejsce, aby wymaza� punkt.
*/


void Snake::updateSnake(int delay)
{
	Coords prevBody[WIDTH * HEIGHT]{};

	for (int i = 0; i < length; i++)
	{
		prevBody[i].x = body[i].x;
		prevBody[i].y = body[i].y;
	}

	if (input != EXIT && !oppositeDirection(direction, input))
		direction = input;
	
	body[0].x = prevBody[0].x + directionArray_X[direction];
	body[0].y = prevBody[0].y + directionArray_Y[direction];

	//G�owa w�a �ledzi kierunek.

	if (ground[body[0].y][body[0].x] < NOTHING)
	{
		item = -1;
		return;
	}

	if (ground[body[0].y][body[0].x] == FOOD)
	{
		length++;
		item = FOOD;

		//D�ugo�c w�a zwi�ksza si� w momencie kiedy otrzyma po�ywienie.
	}
	else
	{
		ground[body[length - 1].y][body[length - 1].x] = NOTHING;
		item = NOTHING;
		goToXY(body[length - 1].x, body[length - 1].y);
		std::cout << " ";

		//Je�eli w�� nie otrzyma po�ywienia, usu� ostatni� cz��, poniewa� w�� si� porusza po planszy/ziemi.
	}

	for (int i = 1; i < length; i++)
	{
		body[i].x = prevBody[i - 1].x; 
		body[i].y = prevBody[i - 1].y;

		//Cia�o pod��a za poprzedni� lokalizacj�, z kt�rej pochodzi.
	}

	goToXY(body[1].x, body[1].y);
	std::cout << "#";
	goToXY(body[0].x, body[0].y);
	std::cout << "@";

	for (int i = 0; i < length; i++)
	{
		ground[body[i].y][body[i].x] = SNAKE;
	}

	Sleep(delay);

	return;
}

/*
		Funckja updateFood() jest wywo�ywana za ka�dym razem jak w�� zje po�ywienie w celu
	stworzenia nowego obiektu do zjedzenia.
		W p�tli do while, przy pomocy generatora liczb pseudolosowych tworzymy na planszy 
	losowe wsp�rz�dne dla jedzenia. Warunek w petli do while chroni przed nadmiernym 
	generowaniem po�ywienia.

*/

void Snake::updateFood()
{
	int x, y;

	do {
		x = rand() % WIDTH + 1;
		y = rand() % HEIGHT + 1;
	} while (ground[y][x] != NOTHING); 

	ground[y][x] = FOOD;
	foodCounter++;
	goToXY(x, y);
	std::cout << "Q";  //symbol jedzenia 
}

/*
		Funckja firstRandomization() w pierwszej kolejno�ci usuwa wszystkie elementy terminala przy pomocy clearScreen(). 
	Nast�pnie przy pomocy p�tli for przegl�damy ca�y obszar HEIGHT*WIDTH i wy�wietlamy obszar oparty o liczb� ustawion� wcze�niej
	w tablicy ground[][].
		Switch case wraz z p�tl� for obs�uguje wszystkie scenariusze, kt�re ustalili�ym, aby narysowa� obszar.
		Kiedy ground[i][j] = NOTHING drukujemy puste miejsce wskazuj�c, �e jest to dost�pny obszar.
		Kiedy ground[i][j] = WALL drukujemy '+' dla rog�w, '-' dla g�rnej i dolnej �ciany, '|' dla lewej i prawej �ciany.
		Kiedy ground[i][j] = SNAKE drukujemy '@' dla g�owy w�a i '#' dla reszty w�a.
		Cokolwiek innego na planszy staje si� automatycznie jedzeniem. 
*/

void Snake::firstRandomization()
{
	clearScreen();
	int i, j;
	for (i = 0; i <= HEIGHT + 1; i++)
	{
		for (j = 0; j <= WIDTH + 1; j++)
		{
			switch (ground[i][j])
			{
			case NOTHING:
				std::cout << " "; break;
			case WALL:
				if ((i == 0 && j == 0)
					|| (i == 0 && j == WIDTH + 1)
					|| (i == HEIGHT + 1 && j == 0)
					|| (i == HEIGHT + 1 && j == WIDTH + 1))
					std::cout << "+";    //rogi planszy
				else
					if (j == 0 || j == WIDTH + 1)
						std::cout << "|";    //prawa i lewa �ciana
					else
						std::cout << "-";    //g�rna i dolna �cian
				break;
			case SNAKE:
				if (i == body[0].y && j == body[0].x)
					std::cout << "@";
				else
					std::cout << "#";
				break;
			default:				
				std::cout << "Q";	//jedzenie 
			}
		}
		std::cout << std::endl;
	}
}

int Snake::reachFoodCounter()
{

	//TO DO
	//Op�nienie wykorzysta� jako mno�nik punkt�w im wi�kszy tym wi�cej punkt�w gracz dostanie.
	return foodCounter;
}