#ifndef __JUGADOR_H_
#define __JUGADOR_H_
#include "tp.h"
#include "pista.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
typedef struct player {
	enum TP_JUGADOR id_player;
	const struct pokemon_info *pokemon;
	pista_t *pista;
} player_t;

/*
 * Crea el TDA jugador. en caso de error devuelve NULL
 * */
player_t *jugador_crear(enum TP_JUGADOR);

/*
 * recibe los dos jugadores y un pokemon, y se guarda en el jugador jugador_a_insertar, en caso de error devuelve False */
bool jugador_agregar_pokemon(player_t *jugador_a_insertar,
			     player_t *otro_jugador,
			     const struct pokemon_info *poke);

/* Recibe un jugador válido y devuelve su pokemon, en caso de error devuelve NULL*/
const struct pokemon_info *jugador_ver_pokemon(player_t *jugador);

/* Recibe el jugador, el tipo de obstáculo y la posición a insertar, devuelve la cantidad de obstáculos en la pista*/
unsigned jugador_insertar_pista(player_t *jugador, enum TP_OBSTACULO obstaculo,
				unsigned posicion);
/*Destruye el jugador*/
void jugador_destructor(player_t *jugador);
/*Recibe un jugador válido y devuelve su pista en caso de error devuelve NULL*/
char *jugador_mostrar_pista(player_t *jugador);
/*
 * Elimina el obstaculo de la pista del jugador*/
unsigned jugador_eliminar_obstaculo_pista(player_t *jugador, unsigned posicion);
/*
 * Limpia la pista del jugador*/
void jugador_limpiar_pista(player_t *jugador);
/*Devuelve el tamaño de la pista del jugador*/
unsigned jugador_tamanio_pista(player_t *jugador);
/*Calcula el tiempo que tarda el pokemon en completar la pista*/
unsigned jugador_calcular_tiempo(player_t *jugador);
/*Devuelve en archivo csv el tiempo que tarda por cada obstaculo en la pista */
char *jugador_tiempo_por_obstaculo(player_t *jugador);

#endif // __JUGADOR_H__
