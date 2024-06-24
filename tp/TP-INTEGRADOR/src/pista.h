#ifndef __PISTA_H_
#define __PISTA_H_
#include "lista.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "tp.h"

#define MAX_PISTA 30
#define ELIMINAR 3
#define INVALIDO -1
#define EXITO 0
#define MAX_TAMANIO_PISTA 99
#define VALOR_MAX_OBSTACULO 10

typedef struct obstaculo {
	enum TP_OBSTACULO tipo;
	char identificador;
} obstaculo_t;

typedef struct pista {
	lista_t *lista;
} pista_t;
/*
 * Crea una pista para el jugador 
 * */
pista_t *pista_crear();

/*
 * Crea un obstaculo para la pista
* en caso de error devuelve NULL
 * */
obstaculo_t *obstaculo_crear(enum TP_OBSTACULO tipo);
/*
* Inserta en la pista y devuelve la cantidad de obstaculos en la pista.
* en caso de error devuelve 0
 * */
int pista_insertar(pista_t *pista, enum TP_OBSTACULO tipo, size_t pos);
/*
* Elimina un obstaculo de la pista y devuelve la cantidad de obstaculos en la pista.
 * en caso de error devuelve NULL
 * */
int pista_borrar(pista_t *pista, size_t posicion);
/*
 * Devuelve el tamaño de la pista, en caso de error devuelve 0*/

unsigned int pista_tamanio(pista_t *pista);
/*
 * Recibe una pista válida y los atributos del pokemon, */

unsigned int pista_calcular_tiempo(pista_t *pista, int fuerza, int destreza,
				   int inteligencia);
/*
 *Recibe una pista válida y los atributos del pokemon y devuelve todos los tiempos de los obstaculos en formato csv.
 en caso de error devuelve NULL*/
char *pista_tiempo_csv(pista_t *pista, int fuerza, int destreza,
		       int inteligencia);

/*
 * Vacia la pista*/
void pista_limpiar(pista_t *lista_pista);
/*
 * Devuelve un puntero de un string que debe ser liberado por el usuario.
 * En caso de error devuelve NULL*/
char *pista_devolver_todo(pista_t *pista);
/*
 * Destruye la pista*/
void pista_destruir(pista_t *pista);
#endif // __PISTA_H__
