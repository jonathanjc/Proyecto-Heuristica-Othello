#ifndef NODO_H
#define NODO_H

#include <iostream>

template <class T>
class Nodo
{
	private:
		T elemento;
		Nodo *siguiente;
		int prioridad;

	public:
		Nodo() { siguiente = NULL; prioridad = -1; }

		~Nodo() { }
		
		void SetElemento(T elemento) { this->elemento = elemento; }
		void SetSiguiente(Nodo *siguiente) {this->siguiente = siguiente; }
		void SetPrioridad(int prioridad) { this->prioridad = prioridad; }
		
		T GetElemento() { return this->elemento; }
		Nodo* GetSiguiente() {return this->siguiente; }
		int GetPrioridad() { return prioridad; }
};

#endif //NODO_H
