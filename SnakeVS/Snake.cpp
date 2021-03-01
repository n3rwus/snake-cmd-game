#include "Snake.h"

/*
		Funkcja initializationOfGround() klasy Snake rozpoczyna swoje dzia³anie od stworzenia pustej przestrzeni
	w rozmiarze [MAX][MAX] (MAX = 100 i znajduje siê w pliku Define.h) w pierwszej pêtli for. 
	Tworzy pole kwadratu o rozmiarze 100 na 100. W nastepnych dwóch pêtlach for, rysujemy œciany planszy, po 
	której bêdzie poruszaæ siê nasz obiekt/w¹¿. 
		Zmienne WIDTH i HEIGHT zosta³y zdefiniowane w pliku nag³ówkowym tak samo jak zmienna MAX. Wartoœci
	dla wysokoœci i szerokoœci s¹ dobrane metod¹ prób i b³êdów.
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

	for (int i = 0; i <= WIDTH + 1; i++) //górna i dolna œciana
	{
		ground[0][i] = WALL;
		ground[HEIGHT + 1][i] = WALL;
	}

	for (int i = 0; i <= HEIGHT; i++)	//lewa i prawa œciana
	{
		ground[i][0] = WALL;
		ground[i][WIDTH + 1] = WALL;
	}
}

/*
		Funkcja initializationOfSnake() inicjalizuje d³ugoœæ wê¿a przy pomocy INIT_SNAKE_LENGTH z g³ow¹ wê¿a na samym œrodku planszy.
	Pocz¹tkowy kierunek wê¿a jest ustawiony na prawo dla zmiennej wejœciowej. Dane wejœciowe to zmienna globalna zdefiniowana w 
	pliku nag³ówkowym Define.h, która pobiera dane wejœciowe u¿ytkwownika w celu sterowania wê¿em. 
		W pêtli for nadajemy reszcie cia³a wê¿a okreœlone po³o¿enia, aby "stworzy³o siê". Tablice directionArray_X i directionArray_Y
	s¹ wstêpnie wype³nione wartoœciami wskazuj¹cymi na zmiannê kierunku na planszy.
	Np.: Jeœli wejœcie jest prawe ma wartoœæ 0, wiêc directionArray_X[0] wynosi 1, a directionArray_Y[0] wynosi 0.
		Przeklada siê to na ruch, który jest opisany w pliku Define.h. (1, 0) itp.
		W momencie kiedy chcemy zdefiniowaæ resztê cia³a wê¿a, odejmujemy directionArray_X i directionArray_Y od wpó³rzêdnych g³owy 
	wê¿a.
		Na koñcu musimy zaktualizowaæ planszê, aby w¹¿ siê w niej "stworzy³".
*/

void Snake::initializationOfSnake()
{
	length = INIT_SNAKE_LENGHT;

	//Ustawienie g³owy wê¿a w œrodku.
	body[0].x = WIDTH / 2;
	body[0].y = HEIGHT / 2;

	direction = input;
	foodCounter = 0;

	for (int i = 1; i < length; i++)
	{
		body[i].x = body[i - 1].x - directionArray_X[direction]; //Je¿eli porusz¹ siê w prawo cia³o bêdzie po lewej itp;
		body[i].y = body[i - 1].y - directionArray_Y[direction];
	}

	// infromacje dla ziemi/planszy o pozycji wê¿a
	for (int i = 0; i < length; i++)
		ground[body[i].y][body[i].x] = SNAKE;
}

/*
		Kiedy wywo³ujemy funckjê updateSnake(int delay), najpierw tworzy ona tablicê
	o nazwie prevBody[] typu Coords. Rozmiar tablicy jest inicjalizowany jako 
	WIDTH * HEIGHT, który jest maksymaln¹ d³ugoœci¹ wê¿a. Tablica tworzy tymczasow¹ kopiê
	aktualnej pozycji wê¿a z tablicy body[].
		Nastepnie sprawdzamy dane wejœciowe u¿ytkownika, aby zobaczyæ, czy zosta³ wciœniêty
	klawisz ESC czy te¿ przeciwny do kierunku wê¿a.
		Ruch wê¿a odbywa siê poprzez aktualizacjê tablicy body[] do nowej lokalizacji. 
	prevBody[].x i prevBody[].y reprezentuj¹ wspó³rzêdne g³owy wê¿, wiêc dodajemy do nich odpowiednio
	lierunki directionArray_X[direction] i directionArray_Y[direction], aby uzyskaæ now¹ wspó³rzêdn¹ g³owy.
		NOTHING reprezentuje  wartoœæ 0, wiêc mniej ni¿ NOTHING oznacza wartoœæ ujemn¹, a liczby ujemne 
	oznaczaj¹ GAME OVER. 
		Przypisujemy -1 do zmiennej iteam, aby powiadomiæ inne funkcje i natychmiast wyjœæ z funkcji update(int delay) za pomoc¹
	s³owa kluczowego return;
		Jeœli g³owa wê¿a napotka FOOD, wyd³u¿y jego tu³ów o jeden '#', z drugiej strony jeœli w¹¿ nic nie napotka³, musimy
	usun¹æ ostatni punkt wê¿a.
		Usuniêcie ostatniego punktu cia³a robi siê poprzez aktualizacjê ground[x][y], aby daæ znaæ, ¿e jest tam pusto.
	Funkcja goToXY(body[length - 1].x, body[length - 1].y) przenosi kursor do ostatniego punktu wê¿a i frukuje puste 
	miejsce, aby wymazaæ punkt.
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

	//G³owa wê¿a œledzi kierunek.

	if (ground[body[0].y][body[0].x] < NOTHING)
	{
		item = -1;
		return;
	}

	if (ground[body[0].y][body[0].x] == FOOD)
	{
		length++;
		item = FOOD;

		//D³ugoœc wê¿a zwiêksza siê w momencie kiedy otrzyma po¿ywienie.
	}
	else
	{
		ground[body[length - 1].y][body[length - 1].x] = NOTHING;
		item = NOTHING;
		goToXY(body[length - 1].x, body[length - 1].y);
		std::cout << " ";

		//Je¿eli w¹¿ nie otrzyma po¿ywienia, usuñ ostatni¹ czêœæ, poniewa¿ w¹¿ siê porusza po planszy/ziemi.
	}

	for (int i = 1; i < length; i++)
	{
		body[i].x = prevBody[i - 1].x; 
		body[i].y = prevBody[i - 1].y;

		//Cia³o pod¹¿a za poprzedni¹ lokalizacj¹, z której pochodzi.
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
		Funckja updateFood() jest wywo³ywana za ka¿dym razem jak w¹¿ zje po¿ywienie w celu
	stworzenia nowego obiektu do zjedzenia.
		W pêtli do while, przy pomocy generatora liczb pseudolosowych tworzymy na planszy 
	losowe wspó³rzêdne dla jedzenia. Warunek w petli do while chroni przed nadmiernym 
	generowaniem po¿ywienia.

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
		Funckja firstRandomization() w pierwszej kolejnoœci usuwa wszystkie elementy terminala przy pomocy clearScreen(). 
	Nastêpnie przy pomocy pêtli for przegl¹damy ca³y obszar HEIGHT*WIDTH i wyœwietlamy obszar oparty o liczbê ustawion¹ wczeœniej
	w tablicy ground[][].
		Switch case wraz z pêtl¹ for obs³uguje wszystkie scenariusze, które ustaliliœym, aby narysowaæ obszar.
		Kiedy ground[i][j] = NOTHING drukujemy puste miejsce wskazuj¹c, ¿e jest to dostêpny obszar.
		Kiedy ground[i][j] = WALL drukujemy '+' dla rogów, '-' dla górnej i dolnej œciany, '|' dla lewej i prawej œciany.
		Kiedy ground[i][j] = SNAKE drukujemy '@' dla g³owy wê¿a i '#' dla reszty wê¿a.
		Cokolwiek innego na planszy staje siê automatycznie jedzeniem. 
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
						std::cout << "|";    //prawa i lewa œciana
					else
						std::cout << "-";    //górna i dolna œcian
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
	//OpóŸnienie wykorzystaæ jako mno¿nik punktów im wiêkszy tym wiêcej punktów gracz dostanie.
	return foodCounter;
}