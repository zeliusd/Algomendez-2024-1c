#ifndef __MENU_H_
#define __MENU_H_

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include "split.h"
#include <limits.h>

#define INVALIDO -1

#define ANSI_COLOR_RED "\033[0;31m"
#define ANSI_COLOR_GREEN "\033[0;32m"
#define ANSI_COLOR_YELLOW "\033[0;33m"
#define ANSI_COLOR_BLUE "\033[0;34m"
#define ANSI_COLOR_MAGENTA "\033[0;35m"
#define ANSI_COLOR_CYAN "\033[0;36m"
#define ANSI_COLOR_RESET "\033[0m"

// Definición de códigos de escape ANSI para colores brillantes en negrita
#define ANSI_BRIGHT_RED "\033[1;31m"
#define ANSI_BRIGHT_GREEN "\033[1;32m"
#define ANSI_BRIGHT_YELLOW "\033[1;33m"
#define ANSI_BRIGHT_BLUE "\033[1;34m"
#define ANSI_BRIGHT_MAGENTA "\033[1;35m"
#define ANSI_BRIGHT_CYAN "\033[1;36m"
#define ANSI_BRIGHT_WHITE "\033[1;37m"

enum OBSTACULOS {
	OBSTACULO_FUERZA_,
	OBSTACULO_DESTREZA_,
	OBSTACULO_INTELIGENCIA_
};

enum PISTA_OPCIONES { INSERTAR, ELIMINAR, LIMPIAR, VOLVER };

enum DIFICULTAD { FACIL, NORMAL, DIFICIL, IMPOSIBLE };

enum JUGADORES { JUGADOR1, JUGADOR2 };
enum INDEX {
	INICIAR,
	SELECCION_POKEMON,
	MODIFICAR_PISTA,
	SALIR,
};

typedef struct pokemon {
	char *nombre;
	int fuerza, destreza, inteligencia;
} pokemon_t;

typedef struct entrenador {
	pokemon_t pokemon;
	char *pista;
	unsigned int cantidad_obstaculos;
	unsigned int puntaje;
} entrenador_t;

typedef struct menu {
	bool iniciado;
	char **pokemones;
	int tam_pokemones;
	int nivel;
	int cantidad_partidas;
	int max_partidas;
	entrenador_t entrenador_1;
	entrenador_t entrenador_2;
} menu_t;

menu_t *menu_crear(char *pokemones, int tamanio);

int menu_posicion(menu_t *menu);
char *menu_random_pokemon(menu_t *menu);
enum INDEX menu_principal_mostrar(menu_t *menu);
int menu_insertar_obstaculos(menu_t *menu);
menu_t *menu_insertar_pokemon_datos(menu_t *menu, char *nombre, int fuerza,
				    int destreza, int inteligencia,
				    enum JUGADORES jugador);
menu_t *menu_insertar_pista_datos(menu_t *menu, char *pista,
				  unsigned int cantidad,
				  enum JUGADORES jugador);
int menu_pista(menu_t *menu);
void menu_limpiar_pista(menu_t *menu, enum JUGADORES jugador);
char *menu_lista_pokemon_mostrar(menu_t *menu);
bool menu_activo(menu_t *menu);
enum DIFICULTAD menu_dificultad(menu_t *menu);
void menu_salir(menu_t *menu);
void menu_iniciar_carrera(menu_t *menu, unsigned int jugador1_tiempo,
			  unsigned int jugador2_tiempo);
void menu_destruir(menu_t *menu);

#endif // __MENU_H__
