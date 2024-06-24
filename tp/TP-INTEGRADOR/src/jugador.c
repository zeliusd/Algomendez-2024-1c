#include "jugador.h"

player_t *jugador_crear(enum TP_JUGADOR id)
{
	if (id > JUGADOR_2) {
		return NULL;
	}
	player_t *jugador = (player_t *)calloc(1, sizeof(player_t));
	if (!jugador) {
		return NULL;
	}
	jugador->pista = pista_crear();
	if (!jugador->pista) {
		free(jugador);
		return NULL;
	}
	return jugador;
}

bool jugador_agregar_pokemon(player_t *jugador_a_insertar,
			     player_t *otro_jugador,
			     const struct pokemon_info *poke)
{
	if (!jugador_a_insertar || !poke || !otro_jugador) {
		return false;
	}

	if (otro_jugador->pokemon) {
		if (strcmp(otro_jugador->pokemon->nombre, poke->nombre) == 0) {
			return false;
		}
	}
	if (jugador_a_insertar->pokemon) {
		if (strcmp(jugador_a_insertar->pokemon->nombre, poke->nombre) ==
		    0) {
			return false;
		}
		jugador_a_insertar->pokemon = poke;
		return true;
	}
	jugador_a_insertar->pokemon = poke;
	return true;
}

const struct pokemon_info *jugador_ver_pokemon(player_t *jugador)
{
	return (!jugador) ? NULL : jugador->pokemon;
}

unsigned jugador_eliminar_obstaculo_pista(player_t *jugador, unsigned posicion)
{
	if (!jugador) {
		return 0;
	}
	if (pista_borrar(jugador->pista, posicion) == INVALIDO) {
		return 0;
	}
	return pista_tamanio(jugador->pista);
}

unsigned jugador_insertar_pista(player_t *jugador, enum TP_OBSTACULO obstaculo,
				unsigned posicion)
{
	if (!jugador) {
		return 0;
	}
	if (pista_insertar(jugador->pista, obstaculo, posicion) == INVALIDO) {
		return 0;
	}
	return pista_tamanio(jugador->pista);
}

char *jugador_mostrar_pista(player_t *jugador)
{
	if (!jugador) {
		return NULL;
	}
	return pista_devolver_todo(jugador->pista);
}

void jugador_limpiar_pista(player_t *jugador)
{
	if (!jugador) {
		return;
	}
	pista_limpiar(jugador->pista);
}

unsigned jugador_tamanio_pista(player_t *jugador)
{
	if (!jugador) {
		return 0;
	}
	return pista_tamanio(jugador->pista);
}

unsigned jugador_calcular_tiempo(player_t *jugador)
{
	if (!jugador || !jugador->pokemon) {
		return 0;
	}
	return pista_calcular_tiempo(jugador->pista, jugador->pokemon->fuerza,
				     jugador->pokemon->destreza,
				     jugador->pokemon->inteligencia);
}

char *jugador_tiempo_por_obstaculo(player_t *jugador)
{
	if (!jugador || !jugador->pokemon) {
		return NULL;
	}
	return pista_tiempo_csv(jugador->pista, jugador->pokemon->fuerza,
				jugador->pokemon->destreza,
				jugador->pokemon->inteligencia);
}
void jugador_destructor(player_t *jugador)
{
	if (!jugador) {
		return;
	}
	pista_destruir(jugador->pista);
	free(jugador);
}
