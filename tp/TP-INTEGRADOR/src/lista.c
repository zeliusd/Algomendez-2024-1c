#include "lista.h"
#include <stddef.h>
#include <stdlib.h>

typedef struct nodo {
	void *elemento;
	struct nodo *siguiente;
	struct nodo *anterior;
} nodo_t;

struct lista {
	nodo_t *nodo_inicio;
	nodo_t *nodo_ultimo;
	size_t largo;
};
struct lista_iterador {
	nodo_t *nodo_actual;
	lista_t *lista;
};

nodo_t *crear_nodo_lista(void *elemento)
{
	nodo_t *nodoNuevo = (nodo_t *)malloc(sizeof(nodo_t));
	if (!nodoNuevo)
		return NULL;
	nodoNuevo->elemento = elemento;
	nodoNuevo->siguiente = NULL;
	nodoNuevo->anterior = NULL;
	return nodoNuevo;
}

lista_t *lista_crear()
{
	lista_t *lista = (lista_t *)malloc(sizeof(lista_t));
	if (!lista)
		return NULL;
	lista->nodo_inicio = NULL;
	lista->nodo_ultimo = NULL;
	lista->largo = 0;
	return lista;
}

lista_t *lista_insertar(lista_t *lista, void *elemento)
{
	if (!lista)
		return NULL;

	nodo_t *nuevoNodo = crear_nodo_lista(elemento);
	if (!nuevoNodo)
		return NULL;
	if (lista_vacia(lista)) {
		lista->nodo_inicio = nuevoNodo;

	} else {
		lista->nodo_ultimo->siguiente = nuevoNodo;
		nuevoNodo->anterior = lista->nodo_ultimo;
	}
	lista->nodo_ultimo = nuevoNodo;
	lista->largo++;
	return lista;
}

nodo_t *buscarNodo(nodo_t *nodo, size_t pos, size_t acum)
{
	if (!nodo || acum == pos)
		return nodo;

	return buscarNodo(nodo->siguiente, pos, acum + 1);
}
lista_t *lista_insertar_en_posicion(lista_t *lista, void *elemento,
				    size_t posicion)
{
	if (!lista)
		return NULL;

	size_t tamanio = lista_tamanio(lista);
	if (posicion + 1 > tamanio) {
		lista_insertar(lista, elemento);
		return lista;
	}
	nodo_t *nuevoNodo = crear_nodo_lista(elemento);
	if (!nuevoNodo)
		return NULL;

	if (posicion == 0) {
		lista->nodo_inicio->anterior = nuevoNodo;
		nuevoNodo->siguiente = lista->nodo_inicio;
		lista->nodo_inicio = nuevoNodo;
	} else {
		nodo_t *nodo_pos = buscarNodo(lista->nodo_inicio, posicion, 0);
		nuevoNodo->siguiente = nodo_pos;
		nuevoNodo->anterior = nodo_pos->anterior;
		nuevoNodo->anterior->siguiente = nuevoNodo;
		nodo_pos->anterior = nuevoNodo;
	}
	lista->largo++;
	return lista;
}

void *lista_quitar(lista_t *lista)
{
	if (!lista || lista_vacia(lista))
		return NULL;

	void *elemento = lista->nodo_ultimo->elemento;
	if (lista->largo == 1) {
		free(lista->nodo_ultimo);
		lista->nodo_inicio = NULL;
		lista->nodo_ultimo = NULL;
	} else {
		lista->nodo_ultimo = lista->nodo_ultimo->anterior;
		free(lista->nodo_ultimo->siguiente);
		lista->nodo_ultimo->siguiente = NULL;
	}

	lista->largo--;

	return elemento;
}

void *lista_quitar_de_posicion(lista_t *lista, size_t posicion)
{
	if (!lista || lista_vacia(lista))
		return NULL;

	void *elemento;
	nodo_t *nodoLiberar;
	if (posicion + 1 > lista->largo) {
		return lista_quitar(lista);
	} else if (posicion == 0) {
		nodoLiberar = lista->nodo_inicio;
		elemento = lista->nodo_inicio->elemento;
		lista->nodo_inicio = lista->nodo_inicio->siguiente;
		if (lista->nodo_inicio)
			lista->nodo_inicio->anterior = NULL;
	} else {
		nodo_t *penultimo =
			buscarNodo(lista->nodo_inicio, posicion - 1, 0);
		nodoLiberar = penultimo->siguiente;
		elemento = penultimo->siguiente->elemento;
		penultimo->siguiente = nodoLiberar->siguiente;
		if (penultimo->siguiente)
			penultimo->siguiente->anterior = penultimo;
	}
	free(nodoLiberar);
	lista->largo--;
	return elemento;
}
void *lista_elemento_en_posicion(lista_t *lista, size_t posicion)
{
	if (!lista || lista_vacia(lista) || lista->largo < posicion + 1)
		return NULL;

	return buscarNodo(lista->nodo_inicio, posicion, 0)->elemento;
}

void *lista_buscar_elemento(lista_t *lista, int (*comparador)(void *, void *),
			    void *contexto)
{
	if (!lista || !comparador)
		return NULL;
	for (nodo_t *nodoActual = lista->nodo_inicio; nodoActual != NULL;
	     nodoActual = nodoActual->siguiente) {
		if (comparador(nodoActual->elemento, contexto) == 0) {
			return nodoActual->elemento;
		}
	}
	return NULL;
}
void *lista_primero(lista_t *lista)
{
	if (!lista || lista_vacia(lista)) {
		return NULL;
	}
	return lista->nodo_inicio->elemento;
}

void *lista_ultimo(lista_t *lista)
{
	return (!lista || lista_vacia(lista)) ? NULL :
						lista->nodo_ultimo->elemento;
}

bool lista_vacia(lista_t *lista)
{
	return (!lista || lista->largo == 0) ? true : false;
}

size_t lista_tamanio(lista_t *lista)
{
	return (!lista) ? 0 : lista->largo;
}

void lista_destruir(lista_t *lista)
{
	if (!lista)
		return;
	while (!lista_vacia(lista)) {
		lista_quitar(lista);
	}
	free(lista);
}

void lista_destruir_todo(lista_t *lista, void (*funcion)(void *))
{
	if (!lista)
		return;

	while (!lista_vacia(lista)) {
		void *elemento = lista_quitar(lista);
		if (elemento && funcion) {
			funcion(elemento);
		}
	}
	free(lista);
}
lista_iterador_t *lista_iterador_crear(lista_t *lista)
{
	if (!lista)
		return NULL;
	lista_iterador_t *iterador =
		(lista_iterador_t *)malloc(sizeof(lista_iterador_t));
	if (!iterador)
		return NULL;
	iterador->nodo_actual = lista->nodo_inicio;
	iterador->lista = lista;
	return iterador;
}

bool lista_iterador_tiene_siguiente(lista_iterador_t *iterador)
{
	return (iterador) ? (iterador->nodo_actual) : false;
}

bool lista_iterador_avanzar(lista_iterador_t *iterador)
{
	if (lista_iterador_tiene_siguiente(iterador)) {
		iterador->nodo_actual = iterador->nodo_actual->siguiente;
		if (iterador->nodo_actual) {
			return true;
		}
	}
	return false;
}

void *lista_iterador_elemento_actual(lista_iterador_t *iterador)
{
	return (iterador && iterador->nodo_actual) ?
		       iterador->nodo_actual->elemento :
		       NULL;
}

void lista_iterador_destruir(lista_iterador_t *iterador)
{
	if (!iterador)
		return;
	free(iterador);
}

size_t lista_con_cada_elemento(lista_t *lista, bool (*funcion)(void *, void *),
			       void *contexto)
{
	if (!lista || !funcion)
		return 0;

	size_t acum = 0;
	for (nodo_t *actual = lista->nodo_inicio; actual != NULL;
	     actual = actual->siguiente) {
		acum++;
		if (!funcion(actual->elemento, contexto)) {
			return acum;
		}
	}
	return acum;
}
