#ifndef LISTA_H
#define LISTA_H

#include "Nodo.h"

template <class T>
class Lista
{
	private:
		Nodo<T> *lista;

	public:
		Lista();
		~Lista();
		void AgregarI(T);
		void AgregarO(T);
		void AgregarU(T);
		void Mostrar();
		int BuscarE(T);
		int Eliminar(T&);
		T Eliminar();
		void EliminarTodo();
		Nodo<T>* GetNodoLista();
};

template <class T>
Lista<T>::Lista()
{
	this->lista = NULL;
}

template <class T>
Lista<T>::~Lista() { }

template <class T>
void Lista<T>::AgregarI(T elemento)
{
	Nodo<T> *nuevoNodo = new Nodo<T>();
	nuevoNodo->SetElemento(elemento);

	Nodo<T> *aux = lista;

	if(lista == NULL)
		lista = nuevoNodo;
	else
	{
		nuevoNodo->SetSiguiente(lista);
		lista = nuevoNodo;
		
		while(aux == NULL)
			aux = aux->GetSiguiente();
	}
}

template <class T>
void Lista<T>::AgregarO(T elemento)
{
	Nodo<T> *nuevoNodo = new Nodo<T>();
	nuevoNodo->SetElemento(elemento);

	Nodo<T> *aux = lista;

	if(lista == NULL)
		lista = nuevoNodo;
	else
	{
		if(lista->GetElemento() > elemento)
		{
			nuevoNodo->SetSiguiente(lista);
			lista = nuevoNodo;
		}

		else
		{
			while((aux->GetSiguiente() != NULL) && (aux->GetSiguiente()->GetElemento() < elemento))
				aux = aux->GetSiguiente();
			nuevoNodo->SetSiguiente(aux->GetSiguiente());
			aux->SetSiguiente(nuevoNodo);
		}
	}
}

template <class T>
void Lista<T>::AgregarU(T elemento)
{
	Nodo<T> *nuevoNodo = new Nodo<T>();
	nuevoNodo->SetElemento(elemento);

	Nodo<T> *aux = lista;

	if(lista == NULL)
		lista = nuevoNodo;

	else
	{
		while(aux->GetSiguiente() != NULL)
			aux = aux->GetSiguiente();
		aux->SetSiguiente(nuevoNodo);
	}
}

template <class T>
void Lista<T>::Mostrar()
{
	Nodo<T> *actual = lista;

	while(actual != NULL)
	{
		std::cout << actual->GetElemento() << std::endl;
		actual = actual->GetSiguiente();
	}
}

template <class T>
int Lista<T>::BuscarE(T elemento)
{
	int cont = 0;
	Nodo<T> *actual = lista;
	bool band = false;

	while((actual != NULL) && (actual->GetElemento() <= elemento))
	{
		if(actual->GetElemento() == elemento)
			band = true;
		else
			cont ++;
		
		actual = actual->GetSiguiente();
	}

	if(band)
		return cont;
	else
		return -1;
}

template <class T>
int Lista<T>::Eliminar(T &elemento)
{
	if(lista != NULL)
	{
		Nodo<T> *auxBorrar = lista;
		Nodo<T> *anterior = NULL;

		while((auxBorrar != NULL) && (auxBorrar->GetElemento() != elemento))
		{
			anterior = auxBorrar;
			auxBorrar = auxBorrar->GetSiguiente();
		}

		if(auxBorrar == NULL)
			return -1;

		else if(anterior == NULL)
		{
			lista = lista->GetSiguiente();
			delete auxBorrar;
		}
		
		else
		{
			anterior->SetSiguiente(auxBorrar->GetSiguiente());
			delete auxBorrar;
		}
	}
	
	return 0;	
}

template <class T>
T Lista<T>::Eliminar()
{
	Nodo<T> *aux = lista;
	lista = aux->GetSiguiente();
	T auxE = aux->GetElemento();
	delete aux;
	return auxE;
}

template <class T>
void Lista<T>::EliminarTodo()
{
	while(lista != NULL)
	{
		Nodo<T> *aux = lista;
		lista = aux->GetSiguiente();
		delete aux;
	}
}

template <class T>
Nodo<T>* Lista<T>::GetNodoLista() { return this->lista; }

#endif //LISTA_H
