#include "menu.h"

#define ARRIBA 'w'
#define ABAJO 's'
#define ENTER 't'
#define MAX 3
#define MIN 0

const int PARTIDAS_FACIL_MAX = 2;
const int PARTIDAS_NORMAL_MAX = 3;
const int PARTIDAS_DIFICIL_MAX = 4;
const int PARTIDAS_IMPOSIBLE_MAX = 5;

const int OBSTACULOS_OCULTOS_FACIL = 1;
const int OBSTACULOS_OCULTOS_NORMAL = 2;
const int OBSTACULOS_OCULTOS_DIFICIL = 3;
const int OBSTACULOS_OCULTOS_IMPOSIBLE = 4;

char *LOGO = "Cᴀʀʀᴇʀᴀ Pᴏᴋᴇᴍᴏɴ";
char *OBSTACULOS = "Oʙsᴛᴀᴄᴜʟᴏs\n";
char *BARRA =
	"\n----------------------------------------------------------------\n";
char *FLECHA = "->> ";
char *ESPACIO = "    ";
char *OPTION1_TEXT = "Iniciar Juego\n";
char *OPTION2_TEXT = "Seleccionar pokemon\n";
char *OPTION3_TEXT = "Modificar pista\n";
char *OPTION4_TEXT = "Salir\n";

char *DIFICIL_ = "Difícil\n";
char *NORMAL_ = "Normal\n";
char *FACIL_ = "Fácil\n";
char *IMPOSIBLE_ = "Imposible\n";

char *INSERTAR_ = "Insertar obstaculos\n";
char *ELIMINAR_ = "Eliminar obstaculos\n";
char *LIMPIAR_ = "Limpiar la pista\n";
char *VOLVER_ = "Volver al menu principal\n";

char *FUERZA_TEXTO = "Fuerza\n";
char *DESTREZA_TEXTO = "Destreza\n";
char *INTELIGENCIA_TEXTO = "Inteligencia\n";

char *ERROR_SIN_POKEMON =
	"Para iniciar el juego necesitas seleccionar un pokemon. \n";
char *ERROR_SIN_PISTA =
	"Para iniciar el juego necesitas una pista con obstáculos.\n";
char *ERROR_POKEMON_NO_PERMITIDO =
	"No puedes usar el mismo pokemon del oponente.\n";
char *ERROR_PARTIDA_INICIADA =
	"No puedes seleccionar un pokemon hasta  acabar todas las rondas.\n";
char *ERROR_SIN_OBSTACULOS = "No hay obstáculos para borrar. \n";

void sleep_ms(int milliseconds)
{
	clock_t start_time = clock();
	clock_t end_time = start_time + milliseconds * (CLOCKS_PER_SEC / 1000);
	while (clock() < end_time)
		;
}
char *string_dificultad(int dificultad)
{
	switch (dificultad) {
	case FACIL:
		return "FACIL";
		break;
	case NORMAL:
		return "NORMAL";
		break;
	case DIFICIL:
		return "DIFICIL";
		break;
	}
	return "IMPOSIBLE";
}

menu_t *menu_crear(char *pokemones, int tamanio)
{
	if (!pokemones) {
		printf("No hay pokemones");
		return NULL;
	}
	char **array_pokemones = split(pokemones, ',');
	if (!array_pokemones) {
		return NULL;
	}
	menu_t *menu = (menu_t *)calloc(1, sizeof(menu_t));

	if (!menu) {
		printf("No se pudo crear el menú \n");
		free(array_pokemones);
		return NULL;
	}
	menu->iniciado = true;
	menu->tam_pokemones = tamanio;
	menu->pokemones = array_pokemones;
	free(pokemones);
	return menu;
}
void mostrar_mensaje(char *string)
{
	printf("\n%s\n", BARRA);
	printf(ANSI_BRIGHT_YELLOW
	       "\n MENSAJE:" ANSI_COLOR_RESET ANSI_BRIGHT_WHITE
	       " %s" ANSI_COLOR_RESET,
	       string);
}
void tab()
{
	printf("\t\t\t");
}

void pista_mostrar(char *pista)
{
	printf("\n%s\n", BARRA);
	tab();
	printf(ANSI_BRIGHT_WHITE "𝙾𝚋𝚜𝚝𝚊́𝚌𝚞𝚕𝚘𝚜\n\n\n" ANSI_COLOR_RESET);
	tab();
	printf(ANSI_BRIGHT_RED " %s\n" ANSI_COLOR_RESET, pista);
}
menu_t *menu_insertar_pokemon_datos(menu_t *menu, char *nombre, int fuerza,
				    int destreza, int inteligencia,
				    enum JUGADORES jugador)
{
	if (!menu || jugador > JUGADOR2) {
		printf("Menu inválido \n");
		return NULL;
	}
	if (jugador == JUGADOR1) {
		menu->entrenador_1.pokemon.destreza = destreza;
		menu->entrenador_1.pokemon.fuerza = fuerza;
		menu->entrenador_1.pokemon.inteligencia = inteligencia;
		menu->entrenador_1.pokemon.nombre = nombre;
	} else {
		menu->entrenador_2.pokemon.destreza = destreza;
		menu->entrenador_2.pokemon.fuerza = fuerza;
		menu->entrenador_2.pokemon.inteligencia = inteligencia;
		menu->entrenador_2.pokemon.nombre = nombre;
	}
	return menu;
}

void menu_limpiar_pista(menu_t *menu, enum JUGADORES jugador)
{
	if (!menu || jugador > JUGADOR2) {
		return;
	}
	if (jugador == JUGADOR1 && menu->entrenador_1.pista) {
		free(menu->entrenador_1.pista);
		menu->entrenador_1.pista = NULL;
		menu->entrenador_1.cantidad_obstaculos = 0;
	} else if (jugador == JUGADOR2 && menu->entrenador_2.pista) {
		free(menu->entrenador_2.pista);
		menu->entrenador_2.pista = NULL;
		menu->entrenador_2.cantidad_obstaculos = 0;
	}
}

menu_t *menu_insertar_pista_datos(menu_t *menu, char *pista,
				  unsigned int cantidad, enum JUGADORES jugador)
{
	if (!menu || jugador > JUGADOR2) {
		return NULL;
	}
	if (pista && strlen(pista) >= 1 && cantidad == 0) {
		free(pista);
		return NULL;
	}

	if (jugador == JUGADOR1) {
		if (menu->entrenador_1.pista) {
			free(menu->entrenador_1.pista);
		}
		menu->entrenador_1.pista = pista;
		menu->entrenador_1.cantidad_obstaculos = cantidad;
	} else {
		if (menu->entrenador_2.pista) {
			free(menu->entrenador_2.pista);
		}
		menu->entrenador_2.pista = pista;
		menu->entrenador_2.cantidad_obstaculos = cantidad;
	}
	return menu;
}

void flecha_esta_aca(int posicion_real, int posicion_flecha)
{
	if (posicion_real == posicion_flecha) {
		printf(ANSI_BRIGHT_GREEN
		       " %s" ANSI_COLOR_RESET ANSI_BRIGHT_WHITE,
		       FLECHA);
	} else {
		printf(ANSI_COLOR_RESET);
		printf("%s", ESPACIO);
	}
}

void limpiar_pantalla()
{
	printf("\033[2J\033[H");
}

void mostrar_encabezado()
{
	limpiar_pantalla();
	tab();
	printf(ANSI_BRIGHT_WHITE "%s\n" ANSI_COLOR_RESET, LOGO);
	printf("\n%s\n", BARRA);
}

int obstaculos_ocultos(int dificultad)
{
	switch (dificultad) {
	case FACIL:
		return OBSTACULOS_OCULTOS_FACIL;
		break;
	case NORMAL:
		return OBSTACULOS_OCULTOS_NORMAL;
		break;
	case DIFICIL:
		return OBSTACULOS_OCULTOS_DIFICIL;
		break;
	}
	return OBSTACULOS_OCULTOS_IMPOSIBLE;
}

void mostrar_datos_actuales(menu_t *menu)
{
	printf(ANSI_BRIGHT_YELLOW
	       " Dificultad: " ANSI_COLOR_RESET ANSI_BRIGHT_RED
	       "%s \n\n" ANSI_COLOR_RESET,
	       string_dificultad(menu->nivel));
	printf(ANSI_BRIGHT_YELLOW " Entrenador 1:" ANSI_COLOR_RESET
				  "\t\t\t\t" ANSI_BRIGHT_YELLOW
				  "Entrenador 2:\n" ANSI_COLOR_RESET);
	printf(ANSI_BRIGHT_YELLOW " Pokemon:" ANSI_COLOR_RESET
				  " %s\t\t\t" ANSI_BRIGHT_YELLOW
				  "Pokemon:" ANSI_COLOR_RESET " %s \n",
	       menu->entrenador_1.pokemon.nombre,
	       menu->entrenador_2.pokemon.nombre);
	printf(" F: %i, D: %i, I: %i\t\t\tF: %i, D: %i, I: %i\n",
	       menu->entrenador_1.pokemon.fuerza,
	       menu->entrenador_1.pokemon.destreza,
	       menu->entrenador_1.pokemon.inteligencia,
	       menu->entrenador_2.pokemon.fuerza,
	       menu->entrenador_2.pokemon.destreza,
	       menu->entrenador_2.pokemon.inteligencia);
	printf(ANSI_BRIGHT_YELLOW " Obstaculos:" ANSI_COLOR_RESET
				  " %i\t\t\t\t" ANSI_BRIGHT_YELLOW
				  "Obstaculos:" ANSI_COLOR_RESET " %i\n",
	       menu->entrenador_1.cantidad_obstaculos,
	       (int)menu->entrenador_2.cantidad_obstaculos -
		       obstaculos_ocultos(menu->nivel));
	printf(ANSI_BRIGHT_YELLOW " Puntaje:" ANSI_COLOR_RESET
				  " %i\t\t\t\t" ANSI_BRIGHT_YELLOW
				  "Puntaje:" ANSI_COLOR_RESET " %i\n",
	       menu->entrenador_1.puntaje, menu->entrenador_2.puntaje);
	printf(ANSI_BRIGHT_YELLOW "\n\nRonda:" ANSI_COLOR_RESET " %i-%i",
	       menu->cantidad_partidas, menu->max_partidas);
	if (menu->cantidad_partidas > 0) {
		printf(ANSI_BRIGHT_GREEN "\tPARTIDA EN CURSO" ANSI_COLOR_RESET);
	}
	printf("\n");
}

enum INDEX menu_principal_mostrar(menu_t *menu)
{
	if (!menu) {
		printf("Error al mostrar al menu\n");
		return INVALIDO;
	}

	int posicion_flecha = 0;
	int key = 0;
	int error = 0;
	bool bucle = true;

	while (bucle) {
		mostrar_encabezado();
		mostrar_datos_actuales(menu);
		if (error == 1) {
			mostrar_mensaje(ERROR_SIN_POKEMON);
		} else if (error == 2) {
			mostrar_mensaje(ERROR_SIN_PISTA);
		} else if (error == 3) {
			mostrar_mensaje(ERROR_PARTIDA_INICIADA);
		}
		printf("\n%s\n", BARRA);
		flecha_esta_aca(INICIAR, posicion_flecha);
		printf("%s", OPTION1_TEXT);
		flecha_esta_aca(SELECCION_POKEMON, posicion_flecha);
		printf("%s", OPTION2_TEXT);
		flecha_esta_aca(MODIFICAR_PISTA, posicion_flecha);
		printf("%s", OPTION3_TEXT);
		flecha_esta_aca(SALIR, posicion_flecha);
		printf("%s", OPTION4_TEXT);
		printf(ANSI_COLOR_RESET);
		pista_mostrar(menu->entrenador_1.pista);
		key = getchar();

		if (key == ABAJO && posicion_flecha < MAX) {
			posicion_flecha++;
		} else if (key == ARRIBA && posicion_flecha > MIN) {
			posicion_flecha--;
		} else if (key == ENTER) {
			error = 0;
			if (posicion_flecha == INICIAR &&
			    !menu->entrenador_1.pokemon.nombre) {
				error = 1;
			} else if (posicion_flecha == INICIAR &&
				   !menu->entrenador_1.pista) {
				error = 2;
			} else if (posicion_flecha == SELECCION_POKEMON &&
				   menu->cantidad_partidas > 0) {
				error = 3;
			} else {
				bucle = false;
			}
		}
	}
	if (menu->cantidad_partidas == menu->max_partidas) {
		menu->entrenador_1.puntaje = 0;
		menu->entrenador_2.puntaje = 0;
	}
	return posicion_flecha;
}

int random_num(int min, int max)
{
	return min + rand() % (max - min + 1);
}
char *menu_random_pokemon(menu_t *menu)
{
	if (!menu) {
		return NULL;
	}
	srand((unsigned int)time(NULL));
	return menu->pokemones[random_num(0, menu->tam_pokemones)];
}
char *menu_lista_pokemon_mostrar(menu_t *menu)
{
	if (!menu) {
		return NULL;
	}
	int posicion_flecha = 0;
	int key = 0;
	int error = 0;
	bool bucle = true;
	char *pokemon_elegido = NULL;

	while (bucle) {
		mostrar_encabezado();
		tab();
		printf(ANSI_BRIGHT_WHITE
		       "Elige bien tu pokemon \n" ANSI_COLOR_RESET);
		tab();
		printf("     " ANSI_BRIGHT_YELLOW
		       "Ϟ(" ANSI_COLOR_RESET ANSI_BRIGHT_RED
		       "๑" ANSI_COLOR_RESET ANSI_BRIGHT_WHITE
		       "⚈" ANSI_COLOR_RESET " ․̫ " ANSI_BRIGHT_WHITE
		       "⚈" ANSI_COLOR_RESET ANSI_BRIGHT_RED
		       "๑" ANSI_COLOR_RESET ANSI_BRIGHT_YELLOW
		       ")⋆ \n" ANSI_COLOR_RESET);
		if (error == 1) {
			mostrar_mensaje(ERROR_POKEMON_NO_PERMITIDO);
		}
		printf("%s", BARRA);
		for (int i = 0; i < menu->tam_pokemones; i++) {
			flecha_esta_aca(i, posicion_flecha);
			printf("%s \n", menu->pokemones[i]);
		}
		printf(ANSI_COLOR_RESET);
		key = getchar();
		if (key == ABAJO && posicion_flecha < menu->tam_pokemones) {
			posicion_flecha++;
		} else if (key == ARRIBA && posicion_flecha > MIN) {
			posicion_flecha--;
		}
		if (key == ENTER) {
			pokemon_elegido = menu->pokemones[posicion_flecha];
			if (strcmp(pokemon_elegido,
				   menu->entrenador_2.pokemon.nombre) == 0) {
				error = 1;
			} else {
				bucle = false;
			}
		}
	}
	return pokemon_elegido;
}

int devolver_max_partidas(int dificultad)
{
	int max = 0;
	switch (dificultad) {
	case FACIL:
		max = PARTIDAS_FACIL_MAX;
		break;
	case NORMAL:
		max = PARTIDAS_NORMAL_MAX;
		break;
	case DIFICIL:
		max = PARTIDAS_DIFICIL_MAX;
		break;
	default:
		max = PARTIDAS_IMPOSIBLE_MAX;
	}
	return max;
}
void mostrar_indicaciones()
{
	printf("\n%s\n", BARRA);
	printf(ANSI_BRIGHT_WHITE
	       " Para moverte: W(ARRIBA) ↑ S(ABAJO)↓ y (t) para seleccionar\n" ANSI_COLOR_RESET);
}
enum DIFICULTAD menu_dificultad(menu_t *menu)
{
	if (!menu) {
		return INVALIDO;
	}

	int posicion_flecha = 0;
	int key = 0;
	bool tecla_presionada = false;

	while (!tecla_presionada) {
		limpiar_pantalla();
		mostrar_encabezado();
		flecha_esta_aca(FACIL, posicion_flecha);
		printf("%s", FACIL_);
		flecha_esta_aca(NORMAL, posicion_flecha);
		printf("%s", NORMAL_);
		flecha_esta_aca(DIFICIL, posicion_flecha);
		printf("%s", DIFICIL_);
		flecha_esta_aca(IMPOSIBLE, posicion_flecha);
		printf("%s", IMPOSIBLE_);
		mostrar_indicaciones();

		key = getchar();

		if (key == ABAJO && posicion_flecha < MAX) {
			posicion_flecha++;
		} else if (key == ARRIBA && posicion_flecha > MIN) {
			posicion_flecha--;
		} else if (key == ENTER) {
			menu->nivel = posicion_flecha;
			menu->max_partidas =
				devolver_max_partidas(posicion_flecha);
			tecla_presionada = true;
		}
	}

	return posicion_flecha;
}
int menu_insertar_obstaculos(menu_t *menu)
{
	if (!menu) {
		return INVALIDO;
	}
	int posicion_flecha = 0;
	int key = 0;
	bool bucle = true;

	while (bucle) {
		limpiar_pantalla();
		mostrar_encabezado();
		flecha_esta_aca(OBSTACULO_FUERZA_, posicion_flecha);
		printf("%s", FUERZA_TEXTO);
		flecha_esta_aca(OBSTACULO_DESTREZA_, posicion_flecha);
		printf("%s", DESTREZA_TEXTO);
		flecha_esta_aca(OBSTACULO_INTELIGENCIA_, posicion_flecha);
		printf("%s", INTELIGENCIA_TEXTO);
		flecha_esta_aca(SALIR, posicion_flecha);
		printf("%s", VOLVER_);
		printf(ANSI_COLOR_RESET);
		key = getchar();
		if (key == ABAJO && posicion_flecha < MAX) {
			posicion_flecha++;
		} else if (key == ARRIBA && posicion_flecha > MIN) {
			posicion_flecha--;
		}
		if (key == ENTER) {
			bucle = false;
		}
	}

	return posicion_flecha;
}

int menu_pista(menu_t *menu)
{
	int posicion_flecha = 0;
	int key = 0;
	bool bucle = true;
	int error = 0;

	while (bucle) {
		limpiar_pantalla();
		mostrar_encabezado();
		if (error == 1) {
			mostrar_mensaje(ERROR_SIN_OBSTACULOS);
			printf("\n%s\n", BARRA);
		}

		flecha_esta_aca(INSERTAR, posicion_flecha);
		printf("%s", INSERTAR_);
		flecha_esta_aca(ELIMINAR, posicion_flecha);
		printf("%s", ELIMINAR_);
		flecha_esta_aca(LIMPIAR, posicion_flecha);
		printf("%s", LIMPIAR_);
		flecha_esta_aca(VOLVER, posicion_flecha);
		printf("%s", VOLVER_);
		printf(ANSI_COLOR_RESET);
		pista_mostrar(menu->entrenador_1.pista);
		key = getchar();
		if (key == ABAJO && posicion_flecha < MAX) {
			posicion_flecha++;
		} else if (key == ARRIBA && posicion_flecha > MIN) {
			posicion_flecha--;
		}
		if (key == ENTER) {
			if (menu->entrenador_1.cantidad_obstaculos == 0 &&
			    (posicion_flecha == LIMPIAR ||
			     posicion_flecha == ELIMINAR)) {
				error = 1;
			} else {
				bucle = false;
			}
		}
	}
	return posicion_flecha;
}

bool menu_activo(menu_t *menu)
{
	return menu ? menu->iniciado : false;
}

int menu_posicion(menu_t *menu)
{
	if (!menu) {
		return INVALIDO;
	}
	bool bucle = true;
	int posicion = 0;
	int error = 0;

	while (bucle) {
		limpiar_pantalla();
		mostrar_encabezado();
		tab();
		printf("%s", OBSTACULOS);
		if (error == 1) {
			mostrar_mensaje(
				"Escriba un número correcto, por favor");
			error = 0;
		}
		pista_mostrar(menu->entrenador_1.pista);
		printf("\n\nIngresa una posición válida: ");

		scanf("%i", &posicion);

		if (posicion >= 0 && posicion < 100) {
			bucle = false;
		}

		error++;
	}
	return posicion;
}
unsigned int pokemon_mas_lento(unsigned int t1, unsigned int t2)
{
	return (t1 > t2) ? t1 : t2;
}

void mostrar_carrera(entrenador_t entrenador, int fin)
{
	printf("\n\n");
	for (int i = 0; i < entrenador.cantidad_obstaculos; i++) {
		printf(ANSI_COLOR_CYAN " | " ANSI_COLOR_RESET);
		if (fin == i) {
			printf(ANSI_COLOR_YELLOW "%s" ANSI_COLOR_RESET,
			       entrenador.pokemon.nombre);
		} else {
			printf(ANSI_BRIGHT_RED "%c" ANSI_COLOR_RESET,
			       entrenador.pista[i]);
		}
	}
}

unsigned int puntaje(int tiempo_1, int tiempo_2)
{
	unsigned int resta_tiempos = (unsigned int)(tiempo_1 - tiempo_2);
	int suma_tiempos = tiempo_1 + tiempo_2;
	int division = (int)resta_tiempos / suma_tiempos;
	return (unsigned int)(100 - 100 * division);
}
void menu_iniciar_carrera(menu_t *menu, unsigned int jugador1_tiempo,
			  unsigned int jugador2_tiempo)
{
	int fin = 0;
	unsigned int mayor_tiempo =
		pokemon_mas_lento(menu->entrenador_1.cantidad_obstaculos,
				  menu->entrenador_2.cantidad_obstaculos);

	while (fin < mayor_tiempo) {
		limpiar_pantalla();
		mostrar_encabezado();

		mostrar_datos_actuales(menu);

		if (fin == mayor_tiempo - 1) {
			if (jugador1_tiempo > jugador2_tiempo) {
				menu->entrenador_2.puntaje +=
					puntaje((int)jugador1_tiempo,
						(int)jugador2_tiempo);

				printf(ANSI_BRIGHT_YELLOW
				       "\n Mensaje:" ANSI_COLOR_RESET
					       ANSI_BRIGHT_WHITE
				       " el ganador es %s con un tiempo de %i " ANSI_COLOR_RESET,
				       menu->entrenador_2.pokemon.nombre,
				       jugador2_tiempo);
			} else if (jugador1_tiempo < jugador2_tiempo) {
				menu->entrenador_1.puntaje +=
					puntaje((int)jugador1_tiempo,
						(int)jugador2_tiempo);
				printf(ANSI_BRIGHT_YELLOW
				       "\n Mensaje:" ANSI_COLOR_RESET
					       ANSI_BRIGHT_WHITE
				       " el ganador es %s con un tiempo de %i" ANSI_COLOR_RESET,
				       menu->entrenador_1.pokemon.nombre,
				       jugador1_tiempo);
			} else {
				printf(ANSI_BRIGHT_YELLOW
				       "\n Mensaje: " ANSI_COLOR_RESET
					       ANSI_BRIGHT_WHITE
				       "Empate." ANSI_COLOR_RESET);
			}
		}
		printf("\n%s\n", BARRA);
		tab();
		printf("Entrenador 1:\n");
		mostrar_carrera(menu->entrenador_1, fin);
		printf("\n\n");
		tab();
		printf("Entrenador 2:\n");
		mostrar_carrera(menu->entrenador_2, fin);

		printf("\n");

		printf("\n%s\n", BARRA);
		fin++;
		sleep_ms(1500);
	}

	printf(" \t \nLa carrera finalizó \n");

	sleep_ms(3500);
	menu->cantidad_partidas++;
	if (menu->cantidad_partidas == menu->max_partidas) {
		menu->cantidad_partidas = 0;
	}
}
void menu_salir(menu_t *menu)
{
	menu->iniciado = false;
}
void menu_destruir(menu_t *menu)
{
	if (!menu)
		return;
	for (int i = 0; i < menu->tam_pokemones; i++) {
		free(menu->pokemones[i]);
	}
	free(menu->pokemones);
	free(menu->entrenador_1.pista);
	free(menu->entrenador_2.pista);
	free(menu);
}
