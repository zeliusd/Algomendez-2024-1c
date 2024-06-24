#include "pa2m.h"
#include "src/tp.h"
#include <string.h>
#include <stdlib.h>
void test_crear_tp()
{
	TP *tp = tp_crear("");

	pa2m_afirmar(tp == NULL, "No se puede crear un TP sin archivo.");

	tp = tp_crear("ejemplo/pokemones.txt");

	pa2m_afirmar(tp != NULL, "Se puede crear un TP sin problemas.");
	pa2m_afirmar(tp_cantidad_pokemon(tp) == 25,
		     "Lee todos los pokemones correctamente");
	const struct pokemon_info *pokemon = tp_buscar_pokemon(tp, "pikAchu");
	pa2m_afirmar(pokemon != NULL, "Se puede buscar un pokemon por nombre");
	pa2m_afirmar(strcmp(pokemon->nombre, "Pikachu") == 0,
		     "El nombre del pokemon es el correcto");
	tp_destruir(tp);
}

void test_tp_jugador()
{
	pa2m_afirmar(tp_seleccionar_pokemon(NULL, JUGADOR_1, "pikachu") == 0,
		     "No se puede seleccionar un pokemon si el TP es NULL");
	pa2m_afirmar(
		!tp_pokemon_seleccionado(NULL, JUGADOR_1),
		"No se puede obtener el pokemon seleccionado si el TP es NULL");
	TP *tp = tp_crear("ejemplo/pokemones.txt");
	pa2m_afirmar(tp_seleccionar_pokemon(tp, JUGADOR_1, "blasToise"),
		     "Se puede seleccionar un pokemon para el jugador 1");
	const struct pokemon_info *pokemon =
		tp_pokemon_seleccionado(tp, JUGADOR_1);
	pa2m_afirmar(pokemon != NULL,
		     "Se puede obtener el pokemon seleccionado");
	pa2m_afirmar(strcmp(pokemon->nombre, "Blastoise") == 0,
		     "El pokemon seleccionado es el correcto");
	pa2m_afirmar(tp_seleccionar_pokemon(tp, JUGADOR_2, "charIzard"),
		     "Se puede seleccionar un pokemon para el jugador 2");
	pa2m_afirmar(
		!tp_seleccionar_pokemon(tp, JUGADOR_2, "charIzard"),
		"No se puede seleccionar un pokemon que ya fue seleccionado por el otro jugador");
	pokemon = tp_pokemon_seleccionado(tp, JUGADOR_2);
	pa2m_afirmar(pokemon != NULL,
		     "Se puede obtener el pokemon seleccionado");
	pa2m_afirmar(strcmp(pokemon->nombre, "Charizard") == 0,
		     "El pokemon seleccionado es el correcto");

	pa2m_afirmar(tp_seleccionar_pokemon(tp, JUGADOR_1, "pidgey"),
		     "Se puede cambiar de pokemon");
	pokemon = tp_pokemon_seleccionado(tp, JUGADOR_1);
	pa2m_afirmar(pokemon != NULL,
		     "Se puede obtener el pokemon seleccionado");
	pa2m_afirmar(strcmp(pokemon->nombre, "Pidgey") == 0,
		     "El pokemon seleccionado es el correcto");
	tp_destruir(tp);
}

void test_tp_pista()
{
	pa2m_afirmar(tp_agregar_obstaculo(NULL, JUGADOR_1, OBSTACULO_FUERZA,
					  0) == 0,
		     "No se puede insertar un obstáculo si el TP es NULL");
	pa2m_afirmar(tp_quitar_obstaculo(NULL, JUGADOR_1, 0) == 0,
		     "No se puede quitar un obstáculo si el TP es NULL");

	TP *tp = tp_crear("ejemplo/pokemones.txt");
	pa2m_afirmar(
		!tp_obstaculos_pista(tp, JUGADOR_1),
		"Obstáculos_pista debe devolver NULL si no se han agregado obstaculos");
	for (int i = 0; i < 3; i++) {
		pa2m_afirmar(tp_agregar_obstaculo(tp, JUGADOR_1, i, 0) == i + 1,
			     "Se agregó un obstáculo correctamente");
	}
	char *pista = tp_obstaculos_pista(tp, JUGADOR_1);
	pa2m_afirmar(strcmp(pista, "IDF") == 0, "La pista es la esperada");

	for (int i = 2; i >= 0; i--) {
		tp_agregar_obstaculo(tp, JUGADOR_1, i, 0);
	}
	free(pista);
	pista = tp_obstaculos_pista(tp, JUGADOR_1);
	pa2m_afirmar(strcmp(pista, "FDIIDF") == 0, "La pista es la esperada");
	pa2m_afirmar(tp_quitar_obstaculo(tp, JUGADOR_1, 4) == 5,
		     "Se quitó un obstáculo correctamente");
	free(pista);
	pista = tp_obstaculos_pista(tp, JUGADOR_1);

	pa2m_afirmar(strcmp(pista, "FDIIF") == 0, "La pista es la esperada");
	pa2m_afirmar(tp_quitar_obstaculo(tp, JUGADOR_1, 10) == 0,
		     "No se puede quitar un obstáculo que no existe");

	tp_quitar_obstaculo(tp, JUGADOR_1, 0);
	free(pista);
	pista = tp_obstaculos_pista(tp, JUGADOR_1);
	pa2m_afirmar(strcmp(pista, "DIIF") == 0,
		     "Se quitó un elemento en la posición deseada");

	pa2m_afirmar(
		tp_agregar_obstaculo(tp, JUGADOR_1, OBSTACULO_FUERZA, 1000) ==
			0,
		"No se puede insertar si es mayor o igual a 100 la posición ");

	tp_limpiar_pista(tp, JUGADOR_1);

	pa2m_afirmar(tp_quitar_obstaculo(tp, JUGADOR_1, 0) == 0,
		     "No se puede quitar un obstáculo si la pista está vacía");
	free(pista);
	pista = tp_obstaculos_pista(tp, JUGADOR_1);

	pa2m_afirmar(!pista, "Se limpia la pista correctamente");
	tp_destruir(tp);
}
void test_tp_tiempo()
{
	pa2m_afirmar(tp_calcular_tiempo_pista(NULL, JUGADOR_1) == 0,
		     "El tiempo de la pista es 0 si el TP es NULL");
	pa2m_afirmar(!tp_tiempo_por_obstaculo(NULL, JUGADOR_1),
		     "El csv devuelto es NULL");
	TP *tp = tp_crear("ejemplo/pokemones.txt");
	tp_seleccionar_pokemon(tp, JUGADOR_1, "Pikachu");

	pa2m_afirmar(!tp_tiempo_por_obstaculo(tp, JUGADOR_1),
		     "Devuelve null sino tiene pista");
	tp_agregar_obstaculo(tp, JUGADOR_1, OBSTACULO_FUERZA, 0);
	tp_agregar_obstaculo(tp, JUGADOR_1, OBSTACULO_DESTREZA, 0);
	tp_agregar_obstaculo(tp, JUGADOR_1, OBSTACULO_INTELIGENCIA, 0);
	tp_agregar_obstaculo(tp, JUGADOR_1, OBSTACULO_INTELIGENCIA, 0);
	tp_agregar_obstaculo(tp, JUGADOR_1, OBSTACULO_INTELIGENCIA, 0);
	tp_agregar_obstaculo(tp, JUGADOR_1, OBSTACULO_FUERZA, 0);
	tp_agregar_obstaculo(tp, JUGADOR_1, OBSTACULO_INTELIGENCIA, 0);

	pa2m_afirmar(tp_calcular_tiempo_pista(tp, JUGADOR_1) == 6,
		     "El tiempo de la pista es el esperado");
	char *csv = tp_tiempo_por_obstaculo(tp, JUGADOR_1);
	pa2m_afirmar(strcmp(csv, "2,0,2,1,0,1,0") == 0,
		     "El csv es el esperado");
	tp_quitar_obstaculo(tp, JUGADOR_1, 5);
	pa2m_afirmar(tp_calcular_tiempo_pista(tp, JUGADOR_1) == 5,
		     "El tiempo de la pista es el esperado");

	free(csv);
	tp_destruir(tp);
}

int main()
{
	pa2m_nuevo_grupo(
		"\n======================== TEST Crear TP ========================");
	test_crear_tp();
	pa2m_nuevo_grupo(
		"\n======================== TEST JUGADOR ========================");
	test_tp_jugador();
	pa2m_nuevo_grupo(
		"\n======================== TEST PISTA ========================");
	test_tp_pista();
	pa2m_nuevo_grupo(
		"\n======================== TEST TIEMPO ========================");
	test_tp_tiempo();
	return pa2m_mostrar_reporte();
}
