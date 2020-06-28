#pragma once
#include <string>
#include <iostream>
#include <cstring>

#include "NodoLD.hpp"
using namespace std;
typedef unsigned long long int ll;

template <typename def>
class ListaDoble {

	NodoLD<def>* inicio, * fin;
	ll tam;
	

public:
	ListaDoble() { tam = 0; inicio = fin = nullptr; }

	//InsercionInicio

	void insercionInicio(def v) {

		if (tam == 0) inicio = fin = new NodoLD<def>(v);
		else
		{
			NodoLD<def>* nuevo = new NodoLD<def>(v);
			nuevo->siguiente = inicio;
			inicio->anterior = nuevo;
			inicio = nuevo;
		}


		++tam;
	}

	//InsercionFinal

	void insercionFinal(def v) {

		if (tam == 0) inicio = fin = new NodoLD<def>(v);
		else
		{
			NodoLD<def>* nuevo = new NodoLD<def>(v);
			fin->siguiente = nuevo;
			nuevo->anterior = fin;
			fin = nuevo;
		}
		++tam;
	}

	//InsercionCualquierLugar

	void insercion(int p, def v) {

		if (p < 0)insercionInicio(v);
		else if (p > tam - 1)insercionFinal(v);
		else
		{
			NodoLD<def>* nuevo, * aux;
			aux = inicio;
			for (int i = 0; i < p - 1; i++)
			{
				aux = aux->siguiente;
			}
			nuevo = new NodoLD<def>(v);
			nuevo->siguiente = aux->siguiente;
			nuevo->siguiente->anterior = nuevo;
			aux->siguiente = nuevo;
			nuevo->anterior = aux;
			++tam;
		}
	}

	void mostrar() {

		NodoLD<def>* aux = inicio;

		for (int i = 0; i < tam; i++)
		{
			cout.width(17); cout << aux->v;
			aux = aux->siguiente;
		}
		cout << endl;

	}
	def getDato(int numColumna) {

		NodoLD<def>* aux = inicio;

		for (int i = 0; i < numColumna; i++)
		{
			aux = aux->siguiente;
		}

		return aux->v;
	}

	void vaciar() {

		this->tam = 0;
		this->inicio = this->fin = nullptr;

	}

};
