#include "src/tp.h"
#include "src/menu.h"
#include <string.h>
#include <time.h>

#define FACIL_MAX 6
#define FACIL_MIN 3

#define NORMAL_MIN 6
#define NORMAL_MAX 8

#define DIFICIL_MIN 8
#define DIFICIL_MAX 10

#define IMPOSIBLE_MIN 10
#define IMPOSIBLE_MAX 15

unsigned int random_dificultad(int min, int max)
{
	return (unsigned int)(min + rand() % (max - min + 1));
}

void submenu_pista(menu_t *menu, TP *tp, int opcion)
{
	int add_obstaculo = 0;
	int posicion_seleccionada = 0;
	switch (opcion) {
	case INSERTAR:
		add_obstaculo = menu_insertar_obstaculos(menu);
		if (add_obstaculo != SALIR) {
			posicion_seleccionada = menu_posicion(menu);
			unsigned int cantidad_pista_1 = tp_agregar_obstaculo(
				tp, JUGADOR_1, add_obstaculo,
				(unsigned int)posicion_seleccionada);
			if (!menu_insertar_pista_datos(
				    menu, tp_obstaculos_pista(tp, JUGADOR_1),
				    cantidad_pista_1, (int)JUGADOR_1)) {
				return;
			}
		}

		break;
	case ELIMINAR:
		posicion_seleccionada = menu_posicion(menu);
		unsigned int cantidad_pista_1 = tp_quitar_obstaculo(
			tp, JUGADOR_1, (unsigned int)posicion_seleccionada);

		char *pista_insertar = tp_obstaculos_pista(tp, JUGADOR_1);
		menu_insertar_pista_datos(menu, pista_insertar,
					  cantidad_pista_1, (int)JUGADOR_1);
		break;
	case LIMPIAR:
		tp_limpiar_pista(tp, JUGADOR_1);
		menu_limpiar_pista(menu, (int)JUGADOR_1);
		break;
	}
	return;
}
void seleccion_dificultad(TP *juego, menu_t *menu)
{
	int dificultad = menu_dificultad(menu);
	unsigned int cantidad_obstaculos = 0;
	tp_seleccionar_pokemon(juego, JUGADOR_2, menu_random_pokemon(menu));

	switch (dificultad) {
	case FACIL:
		cantidad_obstaculos = random_dificultad(FACIL_MIN, FACIL_MAX);
		for (int i = 0; i < cantidad_obstaculos; i++) {
			tp_agregar_obstaculo(
				juego, JUGADOR_2,
				random_dificultad(OBSTACULO_FUERZA,
						  OBSTACULO_INTELIGENCIA),
				random_dificultad(0, 50));
		}
		break;
	case NORMAL:
		cantidad_obstaculos = random_dificultad(NORMAL_MIN, NORMAL_MAX);
		for (int i = 0; i < cantidad_obstaculos; i++) {
			tp_agregar_obstaculo(
				juego, JUGADOR_2,
				random_dificultad(OBSTACULO_FUERZA,
						  OBSTACULO_INTELIGENCIA),
				random_dificultad(0, 50));
		}
		break;
	case DIFICIL:
		cantidad_obstaculos =
			random_dificultad(DIFICIL_MIN, DIFICIL_MAX);
		for (int i = 0; i < cantidad_obstaculos; i++) {
			tp_agregar_obstaculo(
				juego, JUGADOR_2,
				random_dificultad(OBSTACULO_FUERZA,
						  OBSTACULO_INTELIGENCIA),
				random_dificultad(0, 50));
		}
		break;
	case IMPOSIBLE:
		cantidad_obstaculos =
			random_dificultad(IMPOSIBLE_MIN, IMPOSIBLE_MAX);
		for (int i = 0; i < cantidad_obstaculos; i++) {
			tp_agregar_obstaculo(
				juego, JUGADOR_2,
				random_dificultad(OBSTACULO_FUERZA,
						  OBSTACULO_INTELIGENCIA),
				random_dificultad(0, 50));
		}
		break;
	}
	menu_insertar_pista_datos(menu, tp_obstaculos_pista(juego, JUGADOR_2),
				  cantidad_obstaculos, (int)JUGADOR_2);
	const struct pokemon_info *pokemon_2 =
		tp_pokemon_seleccionado(juego, JUGADOR_2);
	menu_insertar_pokemon_datos(menu, pokemon_2->nombre, pokemon_2->fuerza,
				    pokemon_2->destreza,
				    pokemon_2->inteligencia, 1);
}
void inicar_juego(TP *juego, menu_t *menu)
{
	int valor = -1;
	while (menu_activo(menu)) {
		int seleccion_pista = 0;
		char *poke = NULL;
		valor = menu_principal_mostrar(menu);
		if (valor == INICIAR) {
			menu_iniciar_carrera(
				menu,
				tp_calcular_tiempo_pista(juego, JUGADOR_1),
				tp_calcular_tiempo_pista(juego, JUGADOR_2));
		} else if (valor == MODIFICAR_PISTA) {
			seleccion_pista = menu_pista(menu);
			submenu_pista(menu, juego, seleccion_pista);
		} else if (valor == SELECCION_POKEMON) {
			poke = menu_lista_pokemon_mostrar(menu);
			tp_seleccionar_pokemon(juego, JUGADOR_1, poke);
			const struct pokemon_info *pokemon_1 =
				tp_pokemon_seleccionado(juego, JUGADOR_1);
			menu_insertar_pokemon_datos(menu, pokemon_1->nombre,
						    pokemon_1->fuerza,
						    pokemon_1->destreza,
						    pokemon_1->inteligencia, 0);
		} else if (valor == SALIR) {
			menu_salir(menu);
		}
	}
}
int main(int argc, char const *argv[])
{
	TP *juego = tp_crear("ejemplo/pokemones.txt");
	if (!juego) {
		printf("Problemas de memoria o hubo un error en la lectura de archivos\n");
		return 0;
	}
	menu_t *menu = menu_crear(tp_nombres_disponibles(juego),
				  tp_cantidad_pokemon(juego));
	seleccion_dificultad(juego, menu);
	inicar_juego(juego, menu);
	menu_destruir(menu);
	tp_destruir(juego);
	return 0;
}
