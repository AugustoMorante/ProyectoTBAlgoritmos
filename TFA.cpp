#include <iostream>
#include <cstdlib>
#include <ctime>
#include <functional>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include <list>
#include <cstring>
typedef unsigned long long int ll;

using namespace std;

template <typename def>
class NodoLD
{
public:
	def v;
	NodoLD<def>* anterior;
	NodoLD<def>* siguiente;

	NodoLD(def v1) :v(v1), anterior(nullptr), siguiente(nullptr) {}

private:

};

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

	/*void _agregar(Nodo<G>*& nodo, G valor) {

		if (nodo == nullptr)
		{
			nodo = new Nodo<G>(valor);
			cantidad++;
		}
		else if (valor >= nodo->v)
		{
			_agregar(nodo->d, valor);
		}
		else
		{
			_agregar(nodo->i, valor);
		}
	}*/

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

		if (!node)
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

	void _enOrden(Nodo<G>* nodo) {

		if (nodo != nullptr)
		{
			_enOrden(nodo->i);
			cout << nodo->v << " " << endl;
			_enOrden(nodo->d);
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


	void enOrden(function<void(G)> criterioImpresion) {

		_enOrden(raiz, criterioImpresion);
	}

	void enOrden(function<bool(G)> criterioImpresion) {

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

class BaseDatos
{
	ifstream archivo;
	string fila;
	vector<vector<string>> bd;

public:

	void lectura(string nombre) {

		archivo.open(nombre);
		while (getline(archivo, fila))
		{
			stringstream ss(fila);
			dividirColumnas(ss);
		}

	}

private:

	void dividirColumnas(istream& ss) {

		vector<string> vCol;
		string campo;

		while (getline(ss, campo, ';'))
		{
			vCol.push_back(campo);
		}
		bd.push_back(vCol);
	}

public:

	void mostrar() {

		for (size_t f = 0; f < bd.size(); f++)
		{
			for (size_t c = 0; c < bd[f].size(); c++)
			{
				cout.width(17); cout << bd[f].at(c);
			}
			cout << endl;
		}

	}

	void dimensiones() {

		cout << "Contidad de cantidad de filas " << bd.size() << endl;
		cout << "Cantidad de columnas " << bd[0].size() << endl;
	}

	int getNumFilas() {

		return bd.size();
	}

	int getNumColumnas(int i) {

		return bd[i].size();
	}

	string getDato(int f, int c) {

		string resultado;
		
		resultado = bd.at(f).at(c);
		
		return resultado;
	}

};

int main() {

	srand(time(0));

	BaseDatos datosDifuntos;
	datosDifuntos.lectura("Difuntos.csv");
	datosDifuntos.mostrar();
	datosDifuntos.dimensiones();
	cout << endl << endl;

	//Indexacion
	/////////////////////////////////////////////////////////////////////////////////

	ABB<ListaDoble<string>>* arbol = new ABB<ListaDoble<string>>();
	
	auto lambaInsercionEdad = [](ListaDoble<string> a, ListaDoble<string> b)->bool { return stoi(a.getDato(3)) > stoi(b.getDato(3)); };
	auto LambaCriterioImpresion = [](ListaDoble<string> a)->void { a.mostrar(); };

	ListaDoble<string> aux;

	//Datos Reales
	for (int i = 1; i < datosDifuntos.getNumFilas(); i++)
	{
		for (int f = 0; f < datosDifuntos.getNumColumnas(i); f++)
		{
			aux.insercionFinal(datosDifuntos.getDato(i, f));
		}
		arbol->agregar(aux, lambaInsercionEdad);
		aux.vaciar();
	}

	arbol->enOrden(LambaCriterioImpresion);
	cout << endl << endl;

	//Test
	/*vector<ListaDoble<string>> vectorListaTest;
	ListaDoble<string> aux;
	
	for (int i = 1; i < datosDifuntos.getNumFilas(); i++)
	{
		for (int f = 0; f < datosDifuntos.getNumColumnas(i); f++)
		{
			aux.insercionFinal(datosDifuntos.getDato(i, f));
		}
		vectorListaTest.push_back(aux);
		aux.vaciar();
	}

	for (int i = 0; i < vectorListaTest.size(); i++)
	{
		vectorListaTest.at(i).mostrar();
	}
	cout << endl << endl;*/

	/*ListaDoble<string> listaTest;
	
	for (int i = 0; i < datosDifuntos.getNumColumnas(1); i++)
	{
		listaTest.insercionFinal(datosDifuntos.getDato(1,i));
	}

	listaTest.mostrar();
	cout << endl << endl;
	cout << listaTest.getDato(3);*/

	cin.get();
	return 0;
}


