#pragma once
#include <iostream>
#include <functional>
#include <string>
#include <cstring>
#include <fstream>

using namespace std;

template<class G>
class AVL
{
	template<class G>
	class Nodo
	{
	public:

		G v;
		Nodo<G>* i;
		Nodo<G>* d;
		int altura;
		Nodo(G v) {

			this->v = v;
			i = d = nullptr;
			altura = 0;
		}
	};

	Nodo<G>* raiz;
	int cantidad;

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

	void _rotarIzq(Nodo<G>* x, Nodo<G>* y, Nodo<G>*& p) {

		p = y;
		x->d = y->i;
		x->altura = _altura(x);
		y->i = x;
		y->altura = _altura(p);
	}

	void _rotarDer(Nodo<G>* x, Nodo<G>* y, Nodo<G>*& p) {

		p = x;
		y->i = x->d;
		y->altura = _altura(y);
		x->d = y;
		x->altura = _altura(p);
	}

	int _altura(Nodo<G>* nodo) {

		if (nodo == nullptr)
		{
			return -1;
		}

		int hi = _altura(nodo->i);
		int hd = _altura(nodo->d);

		return 1 + (hi > hd ? hi : hd);

	}

	void _agregar(Nodo<G>*& node, const G& value, function<bool(G, G)> crit) {

		if (node == nullptr)
		{
			node = new Nodo<G>(value);
			cantidad += 1;
		}
		else if (crit(value, node->v))
		{
			_agregar(node->i, value, crit);
		}
		else
		{
			_agregar(node->d, value, crit);
		}

		//como AVL
		int hi = _altura(node->i);
		int hd = _altura(node->d);
		int dif = hd - hi;

		if (dif > 1) //pesado derecha
		{
			int hdd = _altura(node->d->d);
			int hdi = _altura(node->d->i);
			if (hdi > hdd) //zigzag
			{
				_rotarDer(node->d->i, node->d, node->d);//aplica en zigzag
			}
			_rotarIzq(node, node->d, node);//aplica para los 2 casos
		}
		else if (dif < -1)
		{
			int hid = _altura(node->i->d);
			int hii = _altura(node->i->i);
			if (hid > hii) //zigzag
			{
				_rotarIzq(node->i, node->i->d, node->i);//aplica en zigzag
			}
			_rotarDer(node->i, node, node);//aplica para los 2 casos
		}
		node->altura = _altura(node);
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

public:

	void agregar(G value, function<bool(G, G)> crit) {

		_agregar(raiz, value, crit);
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

	void Ordenado(function<bool(void)>criterioImpresion) {

		_Ordenado(raiz, criterioImpresion);

	}

	int altura() {
		return _altura(raiz);
	}

	AVL() {
		raiz = nullptr;
		cantidad = 0;
	}

};
