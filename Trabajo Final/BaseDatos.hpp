#pragma once
#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <vector>
#include <cstring>
#include "Menu.hpp"
#include "ABB.hpp"
using namespace std;

class BaseDatos
{
	ifstream archivo;
	string fila;
	vector<string>* titulos;
	vector<vector<string>*>* bd;

	ABB<ListaDoble<string>>* arbolEdades;
	int nCol;

public:

	BaseDatos() {
		nCol = 0;//Columna para indexar
		titulos = new vector<string>;
		bd = new  vector<vector<string>*>();
		arbolEdades = new ABB<ListaDoble<string>>();
	}

	void lectura(string nombre, int numColums) {

		archivo.open(nombre);
		ListaDoble<string> aux;

		for (int i = 0; i < numColums; i++)
		{
			if (i == 0)
			{
				getline(archivo, fila);
				stringstream ss(fila);
				string campo;

				while (getline(ss, campo, ';'))
				{
					titulos->push_back(campo);
				}
			}
			else
			{
				getline(archivo, fila);
				stringstream ss(fila);
				dividirColumnas(ss, aux);
				//arbolEdades->agregar(aux, lambaInsercionEdad);
				aux.vaciar();
			}
		}

	}

	void InsertarColumnaDatos() {

		string aux;

		for (int i = -1; i < getNumFilas(); i++)
		{
			if (i == -1)
			{
				cout << "Ingrese nombre de la nueva columna: " << endl;
				cin >> aux;
				titulos->push_back(aux);
			}
			else
			{
				cout << "Ingrese dato de la nuevo columna - fila " << i + 1 << ": " << endl;
				cin >> aux;
				bd->at(i)->push_back(aux);

			}

		}
	}

	void InsertarFilaDatos() {

		vector<string>* aux1 = new vector<string>;
		string aux2;

		for (int i = 0; i < getNumColumnas(0); i++)
		{
			cout << "Ingrese datos de la nueva fila -" << titulos->at(i) << ":" << endl;
			cin >> aux2;
			aux1->push_back(aux2);
		}
		bd->push_back(aux1);
	}

	void IndexarEnArbol() {

		/*Indexacion1*/
		/////////////////////////////////////////////////////////////////////////////

		auto lambaInsercionEdad = [](ListaDoble<string> a, ListaDoble<string> b)->bool { return stoi(a.getDato(3)) > stoi(b.getDato(3)); };
		auto LambaCriterioImpresion = [](ListaDoble<string> a)->void { a.mostrar(); };

		ListaDoble<string> aux;

		//Datos Reales
		for (int i = 0; i < getNumFilas(); i++)
		{
			for (int f = 0; f < getNumColumnas(i); f++)
			{
				aux.insercionFinal(getDato(i, f));
			}
			arbolEdades->agregar(aux, lambaInsercionEdad);
			aux.vaciar();
		}

		arbolEdades->enOrden(LambaCriterioImpresion);


	}

	void SeleccionarDatosXcolumnas() {

		vector<vector<string>>* NuevaTabla = new vector <vector<string>>;
		vector<string>* NuevosTitulos = new vector<string>;
		vector<string> aux;
		vector<int> columnas;
		int num;

		do
		{
			cout << "Seleccione columnas para la nueva tabla: " << endl;
			for (int i = 0; i < titulos->size(); i++)
			{
				cout << "[" << i + 1 << "] " << titulos->at(i) << endl;
			}
			cout << "[" << -1 << "] " << "Mostrar" << endl;
			cin >> num;
			if (num >= 0)
			{
				columnas.push_back(num - 1);
			}
			system("cls");
		} while (num >= 0 && columnas.size() < bd->at(0)->size());


		for (int i = 0; i < bd->size(); i++)
		{
			for (int j = 0; j < columnas.size(); j++)
			{
				aux.push_back(bd->at(i)->at(columnas.at(j)));
			}
			NuevaTabla->push_back(aux);
			aux.clear();
		}

		//Nuevo vector de Titulos
		for (int i = 0; i < columnas.size(); i++)
		{
			NuevosTitulos->push_back(titulos->at(columnas.at(i)));
		}


		//Mostrar en consola
		for (int i = 0; i < NuevosTitulos->size(); i++)
		{
			cout.width(17); cout << NuevosTitulos->at(i);
		}
		cout << endl;

		for (size_t f = 0; f < NuevaTabla->size(); f++)
		{
			for (size_t c = 0; c < NuevaTabla->at(f).size(); c++)
			{
				cout.width(17); cout << NuevaTabla->at(f).at(c);
			}
			cout << endl;
		}

		//Menu de exportacion
		int select;
		cout << endl << endl << "¿Desea exportar esta tabla?" << endl;
		cout << "[1] Si" << endl;
		cout << "[2] No (Volver al menu)" << endl;
		cin >> select;
		if (select==1)
		{
			ExportarTabla(NuevaTabla, NuevosTitulos);
		}
		system("pause");
	}

	void Filtrar() {
		ABB<ListaDoble<string>>* arbolFiltro1;
		arbolFiltro1 = new ABB<ListaDoble<string>>();
		ListaDoble<string> aux;
		int num = 0;
		int opc = 0;
		string cadena = " ";
		int comp = 0;
		do
		{
			system("cls");
			cout << "Seleccione columna que desea filtrar: " << endl;
			for (int i = 0; i < titulos->size(); i++)
			{
				cout << "[" << i + 1 << "] " << titulos->at(i) << endl;
			}
			cout << ">> "; cin >> num;
		} while (num < 1 || num > bd->at(0)->size());
		num--;

		//Lambdas ordenamientos
		auto Mayor = [num](ListaDoble<string> a, ListaDoble<string> b)->bool { return (a.getDato(num).compare(b.getDato(num)) > 0); };
		auto Menor = [num](ListaDoble<string> a, ListaDoble<string> b)->bool { return (b.getDato(num).compare(a.getDato(num)) > 0); };
		auto imprimir = [](ListaDoble<string> a)->void { a.mostrar(); };
		for (int i = 0; i < getNumFilas(); i++)
		{
			for (int f = 0; f < getNumColumnas(0); f++)
			{
				aux.insercionFinal(getDato(i, f));
			}
			arbolFiltro1->agregar(aux, Mayor);
			aux.vaciar();
		}

		do
		{
			system("cls");
			cout << titulos->at(num) << endl;
			cout << "Filtro: " << endl << endl;
			cout << "1.- Mayor que (Columna Numérica)" << endl;
			cout << "2.- Menor que (Columna Numérica)" << endl;
			cout << "3.- Igual que" << endl;
			cout << "4.- Inicia con" << endl;
			cout << "5.- Finaliza con" << endl;
			cout << "6.- Está Contenido en" << endl;
			cout << "7.- No está contenido en" << endl;
			cout << ">> "; cin >> opc;
		} while (opc < 1 || opc > 7);

		//Lambdas filtros
		auto MayorQue = [&num, &comp](ListaDoble<string> a)->void {if (stoi(a.getDato(num)) > comp) a.mostrar(); };//Solo para enteros
		auto MenorQue = [&num, &comp](ListaDoble<string> a)->void {if (stoi(a.getDato(num)) < comp) a.mostrar(); };//Solo para enteros
		auto Igual = [&num, &cadena](ListaDoble<string> a)->void {if (a.getDato(num) == cadena) a.mostrar();  };
		auto IniciaCon = [&num, &cadena](ListaDoble<string> a)->void {if (a.getDato(num).at(0) == cadena.at(0)) a.mostrar(); };
		auto FinalCon = [&num, &cadena](ListaDoble<string> a)->void {if (a.getDato(num).at(a.getDato(num).length() - 1) == cadena.at(0)) a.mostrar(); };
		auto Contenido = [&num, &cadena](ListaDoble<string> a)->void {if (a.getDato(num).find(cadena) < string::npos) a.mostrar(); };
		auto NoContenido = [&num, &cadena](ListaDoble<string> a)->void {if (a.getDato(num).find(cadena) > string::npos) a.mostrar(); };

		//Lambdas filtros para Exportacion
		auto MayorQueE = [&num, &comp](ListaDoble<string> a)->bool {if (stoi(a.getDato(num)) > comp) { return true; } else { return false; } };//Solo para enteros
		auto MenorQueE = [&num, &comp](ListaDoble<string> a)->bool {if (stoi(a.getDato(num)) < comp) { return true; } else { return false; } };//Solo para enteros
		auto IgualE = [&num, &cadena](ListaDoble<string> a)->bool {if (a.getDato(num) == cadena) { return true; } else { return false; } };
		auto IniciaConE = [&num, &cadena](ListaDoble<string> a)->bool {if (a.getDato(num).at(0) == cadena.at(0)) { return true; } else { return false; } };
		auto FinalConE = [&num, &cadena](ListaDoble<string> a)->bool {if (a.getDato(num).at(a.getDato(num).length() - 1) == cadena.at(0)) { return true; } else { return false; } };
		auto ContenidoE = [&num, &cadena](ListaDoble<string> a)->bool {if (a.getDato(num).find(cadena) < string::npos) { return true; } else { return false; } };
		auto NoContenidoE = [&num, &cadena](ListaDoble<string> a)->bool {if (a.getDato(num).find(cadena) > string::npos) { return true; } else { return false; } };
		int select;

		switch (opc)
		{
		case 1:
			system("cls");
			cout << "Inserte número a comparar: "; cin >> comp;
			system("cls");
			arbolFiltro1->enOrden(MayorQue);

			//Menu Exportacion
			cout << endl << endl << "¿Desea exportar esta tabla?" << endl;
			cout << "[1] Si" << endl;
			cout << "[2] No (Volver al menu)" << endl;
			cin >> select;
			if (select == 1)
			{
				arbolFiltro1->enOrden(getNumColumnas(0), MayorQueE);
			}
			system("pause");

			break;
		case 2:
			system("cls");
			cout << "Inserte número a comparar: "; cin >> comp;
			system("cls");
			arbolFiltro1->enOrden(MenorQue);

			//Menu Exportacion
			cout << endl << endl << "¿Desea exportar esta tabla?" << endl;
			cout << "[1] Si" << endl;
			cout << "[2] No (Volver al menu)" << endl;
			cin >> select;
			if (select == 1)
			{
				arbolFiltro1->enOrden(getNumColumnas(0), MenorQueE);
			}
			system("pause");

			break;
		case 3:
			system("cls");
			cout << "Dato a comparar: "; cin >> cadena;
			system("cls");
			arbolFiltro1->enOrden(Igual);

			//Menu Exportacion
			cout << endl << endl << "¿Desea exportar esta tabla?" << endl;
			cout << "[1] Si" << endl;
			cout << "[2] No (Volver al menu)" << endl;
			cin >> select;
			if (select == 1)
			{
				arbolFiltro1->enOrden(getNumColumnas(0), IgualE);
			}
			system("pause");

			break;
		case 4:
			system("cls");
			cout << "Caracter a comparar: "; cin >> cadena;
			system("cls");
			arbolFiltro1->enOrden(IniciaCon);

			//Menu Exportacion
			cout << endl << endl << "¿Desea exportar esta tabla?" << endl;
			cout << "[1] Si" << endl;
			cout << "[2] No (Volver al menu)" << endl;
			cin >> select;
			if (select == 1)
			{
				arbolFiltro1->enOrden(getNumColumnas(0), IniciaConE);
			}
			system("pause");

			break;
		case 5:
			system("cls");
			cout << "Caracter a comparar: "; cin >> cadena;
			system("cls");
			arbolFiltro1->enOrden(FinalCon);

			//Menu Exportacion
			cout << endl << endl << "¿Desea exportar esta tabla?" << endl;
			cout << "[1] Si" << endl;
			cout << "[2] No (Volver al menu)" << endl;
			cin >> select;
			if (select == 1)
			{
				arbolFiltro1->enOrden(getNumColumnas(0), FinalConE);
			}
			system("pause");

			break;
		case 6:
			system("cls");
			cout << "Inserte palabra: "; cin >> cadena;
			arbolFiltro1->enOrden(Contenido);

			//Menu Exportacion
			cout << endl << endl << "¿Desea exportar esta tabla?" << endl;
			cout << "[1] Si" << endl;
			cout << "[2] No (Volver al menu)" << endl;
			cin >> select;
			if (select == 1)
			{
				arbolFiltro1->enOrden(getNumColumnas(0), ContenidoE);
			}
			system("pause");

			break;
		case 7:
			system("cls");
			cout << "Inserte palabra: "; cin >> cadena;
			arbolFiltro1->enOrden(NoContenido);

			//Menu Exportacion
			cout << endl << endl << "¿Desea exportar esta tabla?" << endl;
			cout << "[1] Si" << endl;
			cout << "[2] No (Volver al menu)" << endl;
			cin >> select;
			if (select == 1)
			{
				arbolFiltro1->enOrden(getNumColumnas(0), NoContenidoE);
			}
			system("pause");

			break;
		default:
			break;
		}

	}

	void Ordenar() {
		ABB<ListaDoble<string>>* arbolColumna;
		arbolColumna = new ABB<ListaDoble<string>>();
		

		int num = 0;
		int opc = 0;
		do
		{
			system("cls");
			cout << "Seleccione columna que desea ordenar: " << endl;
			for (int i = 0; i < titulos->size(); i++)
			{
				cout << "[" << i + 1 << "] " << titulos->at(i) << endl;
			}
			cout << ">> "; cin >> num;
		} while (num < 1 || num > bd->at(0)->size());
		num--;
		ListaDoble<string> aux;
		auto desdeMayor = [num](ListaDoble<string> a, ListaDoble<string> b)->bool { return (a.getDato(num).compare(b.getDato(num)) > 0); };
		auto desdeMenor = [num](ListaDoble<string> a, ListaDoble<string> b)->bool { return (b.getDato(num).compare(a.getDato(num)) > 0); };
		auto imprimir = [](ListaDoble<string> a)->void { a.mostrar(); };
		
		do
		{
			system("cls");
			cout << titulos->at(num) << endl;
			cout << "Seleccione con que orden lo desea ordenar: " << endl << endl;
			cout << "1.- De mayor a menor (Alfabetico)" << endl;
			cout << "2.- De menor a mayor (Inverso Alfabeticamente)" << endl;
			cout << ">> "; cin >> opc;
		} while (opc < 1 || opc > 2);
		switch (opc)
		{
		case 1:
			for (int i = 0; i < getNumFilas(); i++)
			{
				for (int f = 0; f < getNumColumnas(i); f++)
				{
					aux.insercionFinal(getDato(i, f));
				}
				arbolColumna->agregar(aux, desdeMayor);
				aux.vaciar();
			}
			break;
		case 2:
			for (int i = 0; i < getNumFilas(); i++)
			{
				for (int f = 0; f < getNumColumnas(i); f++)
				{
					aux.insercionFinal(getDato(i, f));
				}
				arbolColumna->agregar(aux, desdeMenor);
				aux.vaciar();
			}
			break;
		default:
			break;
		}
		system("cls");
		arbolColumna->enOrden(imprimir);
		
		//Menu Exportacion
		int select;
		cout << endl << endl << "¿Desea exportar esta tabla?" << endl;
		cout << "[1] Si" << endl;
		cout << "[2] No (Volver al menu)" << endl;
		cin >> select;
		if (select == 1)
		{
			arbolColumna->enOrden(getNumColumnas(0));
		}
		system("pause");
	}
private:

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

	void dividirColumnas(istream& ss, ListaDoble<string>& aux) {

		vector<string>* vCol = new vector<string>;
		string campo;

		while (getline(ss, campo, ';'))
		{
			vCol->push_back(campo);
			aux.insercionFinal(campo);
		}
		bd->push_back(vCol);

	}

	void mostrarTitulos() {

		for (int i = 0; i < titulos->size(); i++)
		{
			cout.width(17); cout << titulos->at(i);
		}
		cout << endl;

	}

public:


	void mostrar() {

		mostrarTitulos();

		for (size_t f = 0; f < bd->size(); f++)
		{
			for (size_t c = 0; c < bd->at(f)->size(); c++)
			{
				cout.width(17); cout << bd->at(f)->at(c);
			}
			cout << endl;
		}

	}

	void dimensiones() {

		cout << "Contidad de cantidad de filas " << bd->size() << endl;
		cout << "Cantidad de columnas " << bd->at(0)->size() << endl;
	}

	int getNumFilas() {

		return bd->size();
	}

	int getNumColumnas(int i) {

		return bd->at(i)->size();
	}

	string getDato(int f, int c) {

		string resultado;

		resultado = bd->at(f)->at(c);

		return resultado;
	}

 };
