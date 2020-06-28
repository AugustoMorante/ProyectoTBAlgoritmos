#pragma once
#include <iostream>
#include <functional>
#include <string>
#include <cstring>
#include <fstream>

using namespace std;

template<class G>
class ABB
{
	template<class G>
	class Nodo
	{
	public:

		G v;
		Nodo<G>* i;
		Nodo<G>* d;
		Nodo(G v) {

			this->v = v;
			i = d = nullptr;
		}
	};

	Nodo<G>* raiz;
	int cantidad;

	void _Contar(Nodo<G>* nodo, function<bool(G)>criterioContar, int& contador) {

		if (nodo != nullptr)
		{
			_Contar(nodo->i, criterioContar, contador);
			if (criterioContar(nodo->v))
			{
				contador += 1;
			}
			_Contar(nodo->d, criterioContar, contador);
		}
	}

	void _agregar(Nodo<G>*& node, const G& value, function<bool(G, G)> crit) {

		if (node == nullptr)
		{
			node = new Nodo<G>(value);
			cantidad += 1;
		}
		else if (crit(value, node->v))
		{
			_agregar(node->d, value, crit);
		}
		else
		{
			_agregar(node->i, value, crit);
		}
	}



	void _Sumar(Nodo<G>* nodo, function<int(G)> crit, int& find) {

		if (nodo != nullptr)
		{
			_Sumar(nodo->i, crit, find);
			find += crit(nodo->v);
			_Sumar(nodo->d, crit, find);
		}
	}

	void _enOrden(Nodo<G>* nodo, ofstream& archEscritura, int numColum) {

		if (nodo != nullptr)
		{
			_enOrden(nodo->i, archEscritura, numColum);

			for (int i = 0; i < numColum; i++)
			{
				archEscritura.width(17); archEscritura << nodo->v.getDato(i);

			}
			archEscritura << endl;

			
			_enOrden(nodo->d, archEscritura, numColum);
		}
	}

	void _enOrden(Nodo<G>* nodo, ofstream& archEscritura, int numColum, function<bool(G)>criterioImpresion) {

		if (nodo != nullptr)
		{
			_enOrden(nodo->i, archEscritura, numColum, criterioImpresion);

			if (criterioImpresion(nodo->v))
			{
			for (int i = 0; i < numColum; i++)
			{
				archEscritura.width(17); archEscritura << nodo->v.getDato(i);

			}
			archEscritura << endl;

			}

			_enOrden(nodo->d, archEscritura, numColum, criterioImpresion);
		}
	}

	void _enOrden(Nodo<G>* nodo, function<void(G)>criterioImpresion) {

		if (nodo != nullptr)
		{
			_enOrden(nodo->i, criterioImpresion);
			criterioImpresion(nodo->v);
			_enOrden(nodo->d, criterioImpresion);
		}
	}

	void _Rango(Nodo<G>* nodo, function<bool(G)>criterioImpresion) {

		if (nodo != nullptr)
		{
			_Rango(nodo->i, criterioImpresion);
			if (criterioImpresion(nodo->v))
			{
				cout << nodo->v << " " << endl;
			}
			_Rango(nodo->d, criterioImpresion);
		}
	}

	void _Ordenado(Nodo<G>* nodo, function<bool(void)>criterioImpresion) {

		if (nodo != nullptr)
		{
			if (criterioImpresion())
			{
				_Ordenado(nodo->i, criterioImpresion);
			}
			else
			{
				_Ordenado(nodo->d, criterioImpresion);
			}
			cout << nodo->v << " " << endl;
			if (criterioImpresion())
			{
				_Ordenado(nodo->d, criterioImpresion);
			}
			else
			{
				_Ordenado(nodo->i, criterioImpresion);
			}
		}
	}

	void _preOrden(Nodo<G>* nodo) {

		if (nodo != nullptr)
		{
			cout << nodo->v << " ";
			_preOrden(nodo->i);
			_preOrden(nodo->d);
		}

	}

	void _postOrden(Nodo<G>* nodo) {

		if (nodo != nullptr)
		{
			_postOrden(nodo->i);
			_postOrden(nodo->d);
			cout << nodo->v << " ";
		}

	}

	void _buscar(Nodo<G>* nodo, G valor, bool& find) {

		if (nodo == nullptr)
		{
			find = false;
		}
		else
		{
			if (valor == nodo->v) {
				find = true;
				return;
			}
			else if (valor > nodo->v) {

				_buscar(nodo->d, valor, find);
			}
			else
			{
				_buscar(nodo->i, valor, find);
			}
		}
	}

	void _buscar(Nodo<G>* nodo, G valor, function<char(G, G)> crit, bool& find) {

		if (nodo == nullptr)
		{
			find = false;
		}
		else
		{
			if (crit(valor, nodo->v) == 'E') {
				find = true;
				return;
			}
			else if (crit(valor, nodo->v) == 'R') {

				_buscar(nodo->d, valor, crit, find);
			}
			else
			{
				_buscar(nodo->i, valor, crit, find);
			}
		}
	}

	void _buscar(Nodo<G>* nodo, function<char(G, G)> crit, int& find) {

		if (nodo == nullptr)
		{
			find = 0;
		}
		else
		{
			if (crit(nodo->v, nodo->d->v) == 'E')
			{
				find = nodo->v;
				return;
			}
			else if (crit(nodo->v, nodo->d->v) == 'N')
			{
				if (nodo->d->d != nullptr)
				{
					_buscar(nodo->d, crit, find);
				}
				else
				{
					find = nodo->d->v;
					return;
				}
			}
		}
	}

public:

	int getCantidad() {

		return cantidad;
	}

	void agregar(G value, function<bool(G, G)> crit) {

		_agregar(raiz, value, crit);
	}

	void agregar(G v) {

		_agregar(raiz, v);
	}

	void enOrden() {

		_enOrden(raiz);
	}

	void enOrden(int numColum) {

		ofstream archEscritura("Resultado.txt");
		_enOrden(raiz, archEscritura, numColum);
		archEscritura.close();
	}

	void enOrden(int numColum, function<bool(G)> criterioImpresion) {

		ofstream archEscritura("Resultado.txt");
		_enOrden(raiz, archEscritura, numColum, criterioImpresion);
		archEscritura.close();
	}

	void enOrden(function<void(G)> criterioImpresion) {

		_enOrden(raiz, criterioImpresion);
	}

	bool buscar(G valor, function<char(G, G)> crit) {

		bool find = false;
		_buscar(raiz, valor, crit, find);
		return find;
	}

	int buscarMayor(function<char(G, G)> crit) {

		int find;
		_buscar(raiz, crit, find);
		return find;
	}

	int Sumar(function<int(G)> crit) {

		int find = 0;
		_Sumar(raiz, crit, find);
		return find;
	}

	void Rango(function<bool(G)>criterioImpresion) {

		_Rango(raiz, criterioImpresion);

	}

	void Ordenado(function<bool(void)>criterioImpresion) {

		_Ordenado(raiz, criterioImpresion);

	}

	int Contar(function<bool(G)>criterioContar) {

		int contador = 0;
		_Contar(raiz, criterioContar, contador);
		return contador;
	}

	ABB() {
		raiz = nullptr;
		cantidad = 0;
	}

};
