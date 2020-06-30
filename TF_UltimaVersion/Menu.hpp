#pragma once
#include <iostream>
#include <windows.h>
using namespace std;
void blanco() { system("color 07"); }
void blancoB() { system("color 0F"); }
void amarillo() { system("color 0E"); }
void rojo() { system("color 0C"); }
void celes() { system("color 0B"); }

void getPOS(int x, int y)
{
	HANDLE hCon;
	hCon = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD dwPos;
	dwPos.X = x;
	dwPos.Y = y;
	SetConsoleCursorPosition(hCon, dwPos);
}

void cuadro() {
	for (short x = 0; x < 50; x++) {
		getPOS(x + 12, 3); cout << "/";
		getPOS(x + 12, 21); cout << "/";
	}
	for (short x = 50; x < 98; x++) {
		getPOS(x + 12, 3); cout << "\\";
		getPOS(x + 12, 21); cout << "\\";
	}
	for (short y = 1; y < 18; y++)
	{
		getPOS(12, y + 3); cout << "////";
		getPOS(106, y + 3); cout << "\\\\\\\\";
	}
}

void menuPrincipal() {
	system("cls");
	celes();
	cuadro();
	getPOS(50, 5); cout << "---MENU---";
	getPOS(45, 8); cout << "1.- Mostrar Tabla";
	getPOS(45, 9); cout << "2.- Filtrar datos";
	getPOS(45, 10); cout << "3.- Insertar datos";
	getPOS(45, 11); cout << "4.- Indexar Columna";
	getPOS(45, 12); cout << "5.- Selección datos por columna";
}
