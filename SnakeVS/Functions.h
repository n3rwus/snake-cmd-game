#pragma once
#include <Windows.h>
#include <conio.h>
#include "Define.h"
#include <process.h>

void goToXY(int column_x, int row_y);
void clearScreen();
void userIn(void* id);

int oppositeDirection(int input1, int input2);