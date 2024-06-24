#include "abb.h"
#include "abb_estructura_privada.h"
#include <stddef.h>
#include <stdlib.h>
nodo_abb_t *nodo_abb_crear(void *elemento)
{
	nodo_abb_t *nodo = (nodo_abb_t *)malloc(sizeof(nodo_abb_t));
	if (!nodo)
		return NULL;
	nodo->izquierda = NULL;
	nodo->derecha = NULL;
	nodo->elemento = elemento;
	return nodo;
}
abb_t *abb_crear(abb_comparador comparador)
{
	abb_t *abb = (abb_t *)malloc(sizeof(abb_t));
	if (!abb || !comparador) {
		free(abb);
		return NULL;
	}
	abb->comparador = comparador;
	abb->nodo_raiz = NULL;
	abb->tamanio = 0;
	return abb;
}

nodo_abb_t *nodo_abb_insertar_recursivo(abb_t *arbol, void *elemento,
					nodo_abb_t *nodo_actual)
{
	if (nodo_actual == NULL) {
		nodo_abb_t *nodoNuevo = nodo_abb_crear(elemento);
		if (!nodoNuevo)
			return NULL;
		return nodoNuevo;
	}

	int resultado = arbol->comparador(elemento, nodo_actual->elemento);

	if (resultado > 0)
		nodo_actual->derecha = nodo_abb_insertar_recursivo(
			arbol, elemento, nodo_actual->derecha);
	else
		nodo_actual->izquierda = nodo_abb_insertar_recursivo(
			arbol, elemento, nodo_actual->izquierda);

	return nodo_actual;
}
abb_t *abb_insertar(abb_t *arbol, void *elemento)
{
	if (!arbol)
		return NULL;
	arbol->nodo_raiz =
		nodo_abb_insertar_recursivo(arbol, elemento, arbol->nodo_raiz);
	arbol->tamanio++;
	return arbol;
}
nodo_abb_t *nodo_abb_padre_del_candidato_buscar(nodo_abb_t *nodoActual)
{
	if (!nodoActual->derecha) {
		return NULL;
	}
	if (!nodoActual->derecha->derecha) {
		return nodoActual;
	}
	return nodo_abb_padre_del_candidato_buscar(nodoActual->derecha);
}

nodo_abb_t *restructurar_abb(nodo_abb_t *nodoActual)
{
	// sin hijos

	if (!nodoActual->derecha && !nodoActual->izquierda) {
		return NULL;
	}

	// Dos hijos
	if (nodoActual->derecha && nodoActual->izquierda) {
		nodo_abb_t *padre_candidato =
			nodo_abb_padre_del_candidato_buscar(
				nodoActual->izquierda);
		nodo_abb_t *reemplazo;

		if (!padre_candidato) {
			reemplazo = nodoActual->izquierda;
			reemplazo->derecha = nodoActual->derecha;
			return reemplazo;
		}

		reemplazo = padre_candidato->derecha;

		if (reemplazo->izquierda) {
			padre_candidato->derecha = reemplazo->izquierda;
		} else {
			padre_candidato->derecha = NULL;
		}

		reemplazo->derecha = nodoActual->derecha;
		reemplazo->izquierda = nodoActual->izquierda;
		return reemplazo;
	}

	// Un solo hijo
	nodo_abb_t *huerfano;
	if (nodoActual->derecha) {
		huerfano = nodoActual->derecha;
	} else {
		huerfano = nodoActual->izquierda;
	}

	return huerfano;
}

nodo_abb_t *nodo_abb_quitar(abb_t *arbol, void *elemento,
			    nodo_abb_t *nodoActual, nodo_abb_t **liberar)
{
	if (!nodoActual)
		return NULL;

	if (!elemento) {
		*liberar = nodoActual;
		return NULL;
	}
	int resultado = arbol->comparador(elemento, nodoActual->elemento);

	if (resultado == 0) {
		*liberar = nodoActual;
		return restructurar_abb(nodoActual);
	}
	if (resultado > 0) {
		nodoActual->derecha = nodo_abb_quitar(
			arbol, elemento, nodoActual->derecha, liberar);
	} else {
		nodoActual->izquierda = nodo_abb_quitar(
			arbol, elemento, nodoActual->izquierda, liberar);
	}
	return nodoActual;
}
void *abb_quitar(abb_t *arbol, void *elemento)
{
	if (!arbol)
		return NULL;
	nodo_abb_t *liberar = NULL;
	arbol->nodo_raiz =
		nodo_abb_quitar(arbol, elemento, arbol->nodo_raiz, &liberar);

	if (!liberar)
		return NULL;

	arbol->tamanio--;
	void *elemento_liberar = liberar->elemento;
	free(liberar);
	return elemento_liberar;
}

void *nodo_abb_buscar(nodo_abb_t *nodo, void *elemento, abb_t *arbol)
{
	if (!nodo)
		return NULL;

	int resultado = arbol->comparador(elemento, nodo->elemento);

	if (resultado == 0) {
		return nodo->elemento;
	}

	if (resultado > 0) {
		return nodo_abb_buscar(nodo->derecha, elemento, arbol);
	}

	return nodo_abb_buscar(nodo->izquierda, elemento, arbol);
}

void *abb_buscar(abb_t *arbol, void *elemento)
{
	if (!arbol)
		return NULL;

	return nodo_abb_buscar(arbol->nodo_raiz, elemento, arbol);
}

bool abb_vacio(abb_t *arbol)
{
	return !(arbol && arbol->tamanio > 0);
}

size_t abb_tamanio(abb_t *arbol)
{
	return (!arbol || arbol->tamanio == 0) ? 0 : arbol->tamanio;
}

void nodo_abb_destruir(nodo_abb_t *nodo)
{
	if (!nodo)
		return;
	nodo_abb_destruir(nodo->izquierda);
	nodo_abb_destruir(nodo->derecha);
	free(nodo);
}

void destruir_nodos(nodo_abb_t *nodo, void (*destructor)(void *))
{
	if (!nodo) {
		return;
	}
	destruir_nodos(nodo->izquierda, destructor);
	destruir_nodos(nodo->derecha, destructor);
	if (destructor) {
		destructor(nodo->elemento);
	}
	free(nodo);
}

void abb_destruir(abb_t *arbol)
{
	if (!arbol)
		return;
	destruir_nodos(arbol->nodo_raiz, NULL);
	free(arbol);
}

void abb_destruir_todo(abb_t *arbol, void (*destructor)(void *))
{
	if (!arbol)
		return;
	destruir_nodos(arbol->nodo_raiz, destructor);
	free(arbol);
}

void nodo_abb_cada_elemento_preorden(nodo_abb_t *nodoActual,
				     bool (*funcion)(void *, void *), void *aux,
				     size_t *acumulador, bool *finalizar)
{
	if (!nodoActual)
		return;

	if (!(*finalizar)) {
		(*acumulador)++;
		if (!funcion(nodoActual->elemento, aux)) {
			(*finalizar) = true;
			return;
		}
		nodo_abb_cada_elemento_preorden(nodoActual->izquierda, funcion,
						aux, acumulador, finalizar);
		nodo_abb_cada_elemento_preorden(nodoActual->derecha, funcion,
						aux, acumulador, finalizar);
	}
}
void nodo_abb_cada_elemento_postorden(nodo_abb_t *nodoActual,
				      bool (*funcion)(void *, void *),
				      void *aux, size_t *acumulador,
				      bool *finalizar)
{
	if (!nodoActual)
		return;

	nodo_abb_cada_elemento_postorden(nodoActual->izquierda, funcion, aux,
					 acumulador, finalizar);

	nodo_abb_cada_elemento_postorden(nodoActual->derecha, funcion, aux,
					 acumulador, finalizar);
	if (!(*finalizar)) {
		if (!funcion(nodoActual->elemento, aux)) {
			(*finalizar) = true;
		}
		(*acumulador)++;
	}
}
void nodo_abb_cada_elemento_inorden(nodo_abb_t *nodoActual,
				    bool (*funcion)(void *, void *), void *aux,
				    size_t *acumulador, bool *finalizar)
{
	if (!nodoActual)
		return;

	nodo_abb_cada_elemento_inorden(nodoActual->izquierda, funcion, aux,
				       acumulador, finalizar);
	if (!(*finalizar)) {
		(*acumulador)++;
		if (!funcion(nodoActual->elemento, aux)) {
			(*finalizar) = true;
		}
		nodo_abb_cada_elemento_inorden(nodoActual->derecha, funcion,
					       aux, acumulador, finalizar);
	}
}

size_t abb_con_cada_elemento(abb_t *arbol, abb_recorrido recorrido,
			     bool (*funcion)(void *, void *), void *aux)
{
	if (!arbol || !funcion)
		return 0;
	size_t acumulador = 0;
	bool finalizar = false;
	if (recorrido == INORDEN) {
		nodo_abb_cada_elemento_inorden(arbol->nodo_raiz, funcion, aux,
					       &acumulador, &finalizar);
	} else if (recorrido == POSTORDEN) {
		nodo_abb_cada_elemento_postorden(arbol->nodo_raiz, funcion, aux,
						 &acumulador, &finalizar);
	} else {
		nodo_abb_cada_elemento_preorden(arbol->nodo_raiz, funcion, aux,
						&acumulador, &finalizar);
	}
	return acumulador;
}

void abb_recorrer_inorder(nodo_abb_t *nodoActual, void **array,
			  size_t tamanio_array, size_t *acumulador)
{
	if (!nodoActual || *acumulador >= tamanio_array) {
		return;
	}

	abb_recorrer_inorder(nodoActual->izquierda, array, tamanio_array,
			     acumulador);

	if (*acumulador < tamanio_array) {
		array[(*acumulador)] = nodoActual->elemento;
		(*acumulador)++;
	}

	abb_recorrer_inorder(nodoActual->derecha, array, tamanio_array,
			     acumulador);
}

void abb_recorrer_preorder(nodo_abb_t *nodoActual, void **array,
			   size_t tamanio_array, size_t *acumulador)
{
	if (!nodoActual || *acumulador >= tamanio_array) {
		return;
	}
	if (*acumulador < tamanio_array) {
		array[(*acumulador)] = nodoActual->elemento;
		(*acumulador)++;
	}
	abb_recorrer_preorder(nodoActual->izquierda, array, tamanio_array,
			      acumulador);
	abb_recorrer_preorder(nodoActual->derecha, array, tamanio_array,
			      acumulador);
}
void abb_recorrer_postorder(nodo_abb_t *nodoActual, void **array,
			    size_t tamanio_array, size_t *acumulador)
{
	if (!nodoActual || *acumulador >= tamanio_array) {
		return;
	}

	abb_recorrer_postorder(nodoActual->izquierda, array, tamanio_array,
			       acumulador);
	abb_recorrer_postorder(nodoActual->derecha, array, tamanio_array,
			       acumulador);
	if (*acumulador < tamanio_array) {
		array[(*acumulador)] = nodoActual->elemento;
		(*acumulador)++;
	}
}
size_t abb_recorrer(abb_t *arbol, abb_recorrido recorrido, void **array,
		    size_t tamanio_array)
{
	if (!arbol || !array)
		return 0;

	size_t acumulador = 0;
	if (recorrido == INORDEN) {
		abb_recorrer_inorder(arbol->nodo_raiz, array, tamanio_array,
				     &acumulador);
	} else if (recorrido == POSTORDEN) {
		abb_recorrer_postorder(arbol->nodo_raiz, array, tamanio_array,
				       &acumulador);
	} else {
		abb_recorrer_preorder(arbol->nodo_raiz, array, tamanio_array,
				      &acumulador);
	}
	return acumulador;
}
