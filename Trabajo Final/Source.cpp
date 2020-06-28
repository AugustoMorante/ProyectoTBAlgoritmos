#include <iostream>
#include <cstdlib>
#include <ctime>
#include <functional>
#include <string>
#include <vector>
#include <list>
#include <cstring>
#include <locale.h>
#include "ListaDoble.hpp"
#include "ABB.hpp"
#include "Menu.hpp"
#include "BaseDatos.hpp"
using namespace std;
typedef unsigned long long int ll;

void CrearTabla(int& columnas) {

	ofstream archEscritura("Registro.txt");
	int filas;
	string aux;

	system("cls");
	cout << "Ingrese numero de filas: " << endl;
	cin >> filas;
	cout << "Ingrese numero de columnas: " << endl;
	cin >> columnas;

	for (int i = 0; i < columnas; i++)
	{
		system("cls");
		cout << "Ingrese nombre columna " << i + 1 << ": " << endl;
		cin >> aux;
		if (i == columnas - 1)
		{
			archEscritura << aux;
		}
		else
		{
			archEscritura << aux << ";";
		}
	}
	archEscritura << endl;

	string aux2;
	for (int i = 0; i < filas; i++)
	{
		for (int f = 0; f < columnas; f++)
		{
			system("cls");
			cout << "Ingrese fila " << i + 1 << "-" << "Columna " << f + 1 << ": " << endl;
			cin >> aux2;
			if (f == columnas - 1)
			{
				archEscritura << aux2;
			}
			else
			{
				archEscritura << aux2 << ";";
			}
		}
		archEscritura << endl;
	}

	archEscritura.close();

}

void ExportarTabla(vector<vector<string>>* NuevaTabla, vector<string>* NuevosTitulos) {

	ofstream archEscritura("Resultado.txt");
	
	for (int i = 0; i < NuevosTitulos->size(); i++)
	{
		archEscritura.width(17); archEscritura << NuevosTitulos->at(i);
	}
	archEscritura << endl;

	for (size_t f = 0; f < NuevaTabla->size(); f++)
	{
		for (size_t c = 0; c < NuevaTabla->at(f).size(); c++)
		{
			archEscritura.width(17); archEscritura << NuevaTabla->at(f).at(c);
		}
		archEscritura << endl;
	}

	archEscritura.close();

}

int main() {
	setlocale(LC_ALL, "spanish");
	short opc = 0;
	BaseDatos datosDifuntos;
	int select;
	int colum;
	cout << "Desea crear una tabla o usar datos predefinidos? " << endl;
	cout << "[1] Datos predefinidos" << endl;
	cout << "[2] Crear tabla" << endl;
	cin >> select;
	if (select==2)
	{
		CrearTabla(colum);
		datosDifuntos.lectura("Registro.txt", colum);
	}
	else
	{
	datosDifuntos.lectura("Difuntos.csv", 6);
	}
	while (1)
	{
		do
		{
			menuPrincipal();
			getPOS(45, 16); cout << "Inserte opción: "; cin >> opc;
		} while (opc < 1 || opc > 5);
		switch (opc)
		{
		case 1://Mostrar
			system("cls");
			blanco();
			datosDifuntos.Ordenar();
			break;
		case 2://Filtrar
			system("cls");
			blanco();
			datosDifuntos.Filtrar();
			break;
		case 3://Insertar datos por filas
			system("cls");
			blanco();
			datosDifuntos.InsertarFilaDatos();
			break;
		case 4://Insertar nueva columna
			system("cls");
			blanco();
			datosDifuntos.InsertarColumnaDatos();
			break;
		case 5://Seleccion datos x columna
			system("cls");
			blanco();
			datosDifuntos.SeleccionarDatosXcolumnas();
			break;
		default:
			break;
		}
	}
	cin.get();
	return 0;
}