#pragma once
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