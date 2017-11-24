#ifndef PILAD_H
#define PILAD_H

#include "Nodo.h"

template <class T>
class PilaD
{
	private:
		Nodo <T> *ultimo;
		
	public:
		PilaD();
		~PilaD();
		
		void Agregar(T);
		int Eliminar(T&);
};

template <class T>
PilaD<T>::PilaD() { ultimo = NULL; }
template <class T>
PilaD<T>::~PilaD() { }

template <class T>
void PilaD<T>::Agregar(T dato)
{
	Nodo<T> *nuevoNodo = new Nodo<T>();
	nuevoNodo->SetElemento(dato);
	nuevoNodo->SetSiguiente(ultimo);
	ultimo = nuevoNodo;
}

template <class T>
int PilaD<T>::Eliminar(T &datoE)
{
	if(!ultimo) return -1;
	
	Nodo<T> *aux = ultimo;
	ultimo = aux->GetSiguiente();
	datoE = aux->GetElemento();
	
	delete aux;
	
	return 0;
}

#endif
