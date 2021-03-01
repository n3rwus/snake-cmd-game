#pragma once

///Predefiniowanie zmiennych

#define MAX 100
#define WIDTH 77
#define HEIGHT 26
#define INIT_SNAKE_LENGHT 4
#define FOOD 1

///Warto�ci ujemne reprezentuj� obszary, kt�rych gracz nie mo�e dotkn�� inaczej GAME OVER.

#define WALL -2
#define SNAKE -1
#define NOTHING 0

#define RIGHT 0
#define UP 1
#define LEFT 2
#define DOWN 3
#define EXIT -1

///Tablica kierunk�w, do u�ytku ze sta�ymi RIGHT, UP, LEFT, DOWN

static int directionArray_X[5] = { 1, 0, -1, 0 };
static int directionArray_Y[5] = { 0, -1, 0, 1 };

///(1, 0) to RIGHT
///(0, -1) to UP, poniewa� rz�d liczb ro�nie od g�ry do do�u 
///(-1, 0) to LEFT
///(0, 1) to DOWN  

///Zmienne globalne do przyj�cia danych wej�ciowych u�ytkownika
__declspec(selectany) int input = RIGHT; //__declspec(selectany) -> Nakazuje konsolidatorowi wybranie jednej definicji do u�ycia przez wszystkie odwo�ania zewn�trzne i odrzucenie reszty.
__declspec(selectany) int item = NOTHING;