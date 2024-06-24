#include "tp.h"
#include "split.h"
#include "abb.h"
#include "stdio.h"
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "tp.h"
#include "jugador.h"
#include <time.h>

#define MAX 4
#define MIN 3
char DELIMITADOR = ',';
enum ATRIBUTOS { NOMBRE, FUERZA, DESTREZA, INTELIGENCIA };

struct tp {
	abb_t *abb_pokemon;
	player_t *jugador_1;
	player_t *jugador_2;
};

void destructor_pokemones(void *_pk)
{
	struct pokemon_info *pk = (struct pokemon_info *)_pk;
	free(pk->nombre);
	free(pk);
}
int cmp_pokemones(void *pk1, void *pk2)
{
	return strcmp(((struct pokemon_info *)pk1)->nombre,
		      ((struct pokemon_info *)pk2)->nombre);
}

void transformar_texto(char *string)
{
	string[0] = (char)toupper(string[0]);
	for (int i = 1; i < strlen(string); i++) {
		string[i] = (char)tolower(string[i]);
	}
}

struct pokemon_info *crear_pokemon(char *nombre, int fuerza, int destreza,
				   int inteligencia)
{
	struct pokemon_info *pokemon_nuevo =
		(struct pokemon_info *)calloc(1, sizeof(struct pokemon_info));
	if (!pokemon_nuevo) {
		return NULL;
	}
	pokemon_nuevo->nombre = (char *)malloc(strlen(nombre) + 1);
	if (!pokemon_nuevo->nombre) {
		free(pokemon_nuevo);
		return NULL;
	}
	strcpy(pokemon_nuevo->nombre, nombre);
	if (!pokemon_nuevo->nombre) {
		free(pokemon_nuevo);
		return NULL;
	}
	transformar_texto(pokemon_nuevo->nombre);
	pokemon_nuevo->fuerza = fuerza;
	pokemon_nuevo->destreza = destreza;
	pokemon_nuevo->inteligencia = inteligencia;
	return pokemon_nuevo;
}
int contar_elementos(char **array)
{
	int contador = 0;
	while (array[contador] != NULL) {
		contador++;
	}
	return contador;
}
void limpiar_memoria(char **entrada)
{
	for (int i = 0; entrada[i] != NULL; i++) {
		free(entrada[i]);
	}
	free(entrada);
}
TP *llenar_abb_pokemones(TP *juego, FILE *pokemones)
{
	char linea[256];
	char **entrada = NULL;
	while (fgets(linea, sizeof(linea), pokemones)) {
		entrada = split(linea, DELIMITADOR);
		if (!entrada) {
			return NULL;
		}
		int contador = contar_elementos(entrada);
		if (contador > MAX || contador < MIN) {
			limpiar_memoria(entrada);
			return NULL;
		}
		struct pokemon_info *pokemon = crear_pokemon(
			entrada[NOMBRE], atoi(entrada[FUERZA]),
			atoi(entrada[DESTREZA]), atoi(entrada[INTELIGENCIA]));
		if (!pokemon) {
			limpiar_memoria(entrada);

			return NULL;
		}
		abb_insertar(juego->abb_pokemon, pokemon);
		limpiar_memoria(entrada);
	}
	return juego;
}
TP *tp_crear(const char *nombre_archivo)
{
	FILE *fp = fopen(nombre_archivo, "r");
	if (!fp) {
		return NULL;
	}
	TP *juego = (TP *)calloc(1, sizeof(TP));
	if (!juego) {
		fclose(fp);
		return NULL;
	}
	juego->jugador_1 = jugador_crear(JUGADOR_1);
	if (!juego->jugador_1) {
		free(juego);
		fclose(fp);
		return NULL;
	}
	juego->jugador_2 = jugador_crear(JUGADOR_2);
	if (!juego->jugador_2) {
		jugador_destructor(juego->jugador_1);
		free(juego);
		fclose(fp);
		return NULL;
	}
	juego->abb_pokemon = abb_crear(cmp_pokemones);
	if (!juego->abb_pokemon) {
		jugador_destructor(juego->jugador_1);
		jugador_destructor(juego->jugador_2);
		free(juego);
		fclose(fp);
		return NULL;
	}
	if (!llenar_abb_pokemones(juego, fp)) {
		jugador_destructor(juego->jugador_1);
		jugador_destructor(juego->jugador_2);
		abb_destruir_todo(juego->abb_pokemon, destructor_pokemones);
		free(juego);

		fclose(fp);
		return NULL;
	}
	fclose(fp);
	return juego;
}

int tp_cantidad_pokemon(TP *tp)
{
	if (!tp) {
		return 0;
	}
	return (int)abb_tamanio(tp->abb_pokemon);
}

bool se_encuentra_pokemon(void *_pk, void *_nombre)
{
	struct pokemon_info *pk = _pk;
	char *nombre = _nombre;
	return nombre == pk->nombre;
}
const struct pokemon_info *tp_buscar_pokemon(TP *tp, const char *nombre)
{
	if (!tp || !nombre || abb_tamanio(tp->abb_pokemon) == 0) {
		return NULL;
	}
	struct pokemon_info *pokemon =
		(struct pokemon_info *)malloc(sizeof(struct pokemon_info));
	if (!pokemon) {
		return NULL;
	}
	pokemon->nombre = (char *)malloc(strlen(nombre) + 1);
	strcpy(pokemon->nombre, nombre);
	transformar_texto(pokemon->nombre);
	const struct pokemon_info *pokemon_encontrado =
		(const struct pokemon_info *)abb_buscar(tp->abb_pokemon,
							(void *)pokemon);
	free(pokemon->nombre);
	free(pokemon);
	return pokemon_encontrado;
}

char *tp_nombres_disponibles(TP *tp)
{
	if (!tp) {
		return NULL;
	}
	size_t buffer = 1;
	char *salida = (char *)malloc(sizeof(buffer));
	if (!salida) {
		return NULL;
	}
	size_t cantidad = (size_t)tp_cantidad_pokemon(tp);
	struct pokemon_info **pokemones_array =
		malloc(cantidad * sizeof(struct pokemon_info *));
	if (!pokemones_array) {
		free(salida);
		return NULL;
	}
	salida[0] = '\0';
	abb_recorrer(tp->abb_pokemon, 0, (void **)pokemones_array, cantidad);

	for (int i = 0; i < cantidad; i++) {
		size_t new_size =
			buffer + strlen(pokemones_array[i]->nombre) + 1;
		char *temp = (char *)realloc(salida, new_size);
		if (!temp) {
			free(pokemones_array);
			free(salida);
			return NULL;
		}
		salida = temp;
		strcat(salida, pokemones_array[i]->nombre);
		strcat(salida, ",");
		buffer = new_size;
	}
	if (buffer > 1) {
		salida[buffer - 2] = '\0';
	}
	free(pokemones_array);
	return salida;
}

bool tp_seleccionar_pokemon(TP *tp, enum TP_JUGADOR jugador, const char *nombre)
{
	if (!tp || !nombre || jugador > JUGADOR_2) {
		return false;
	}

	const struct pokemon_info *poke = tp_buscar_pokemon(tp, nombre);

	if (jugador == JUGADOR_2) {
		return jugador_agregar_pokemon(tp->jugador_2, tp->jugador_1,
					       poke);
	}
	return jugador_agregar_pokemon(tp->jugador_1, tp->jugador_2, poke);
}

const struct pokemon_info *tp_pokemon_seleccionado(TP *tp,
						   enum TP_JUGADOR jugador)
{
	if (!tp || jugador > JUGADOR_2) {
		return NULL;
	}
	if (jugador == JUGADOR_1) {
		return jugador_ver_pokemon(tp->jugador_1);
	}
	return jugador_ver_pokemon(tp->jugador_2);
}

unsigned tp_agregar_obstaculo(TP *tp, enum TP_JUGADOR jugador,
			      enum TP_OBSTACULO obstaculo, unsigned posicion)
{
	if (!tp || jugador > JUGADOR_2 || obstaculo > OBSTACULO_INTELIGENCIA) {
		return 0;
	}
	player_t *jugador_ = tp->jugador_1;
	if (jugador == JUGADOR_2) {
		jugador_ = tp->jugador_2;
	}
	return jugador_insertar_pista(jugador_, obstaculo, posicion);
}

unsigned tp_quitar_obstaculo(TP *tp, enum TP_JUGADOR jugador, unsigned posicion)
{
	if (jugador > JUGADOR_2 || !tp) {
		return 0;
	}
	player_t *jugador_ = tp->jugador_1;
	if (jugador == JUGADOR_2) {
		jugador_ = tp->jugador_2;
	}
	return jugador_eliminar_obstaculo_pista(jugador_, posicion);
}

char *tp_obstaculos_pista(TP *tp, enum TP_JUGADOR jugador)
{
	if (!tp || jugador > JUGADOR_2) {
		return NULL;
	}
	player_t *jugador_ = tp->jugador_1;
	if (jugador == JUGADOR_2) {
		jugador_ = tp->jugador_2;
	}

	if (jugador_tamanio_pista(jugador_) == 0) {
		return NULL;
	}
	return jugador_mostrar_pista(jugador_);
}

void tp_limpiar_pista(TP *tp, enum TP_JUGADOR jugador)
{
	if (!tp || jugador > JUGADOR_2) {
		return;
	}
	player_t *jugador_ = tp->jugador_1;
	if (jugador == JUGADOR_2) {
		jugador_ = tp->jugador_2;
	}
	jugador_limpiar_pista(jugador_);
}

unsigned tp_calcular_tiempo_pista(TP *tp, enum TP_JUGADOR jugador)
{
	if (!tp || jugador > JUGADOR_2 ||
	    !tp_pokemon_seleccionado(tp, jugador)) {
		return 0;
	}

	player_t *jugador_ = tp->jugador_1;
	if (jugador == JUGADOR_2) {
		jugador_ = tp->jugador_2;
	}
	if (jugador_tamanio_pista(jugador_) == 0) {
		return 0;
	}
	return jugador_calcular_tiempo(jugador_);
}

char *tp_tiempo_por_obstaculo(TP *tp, enum TP_JUGADOR jugador)
{
	if (!tp) {
		return NULL;
	}
	player_t *jugador_ = tp->jugador_1;
	char *csv_obst = NULL;
	if (jugador == JUGADOR_2) {
		jugador_ = tp->jugador_2;
	}
	if (!jugador_->pokemon) {
		return NULL;
	}
	csv_obst = jugador_tiempo_por_obstaculo(jugador_);
	return csv_obst;
}

void tp_destruir(TP *tp)
{
	abb_destruir_todo(tp->abb_pokemon, destructor_pokemones);
	jugador_destructor(tp->jugador_1);
	jugador_destructor(tp->jugador_2);
	free(tp);
	return;
}
