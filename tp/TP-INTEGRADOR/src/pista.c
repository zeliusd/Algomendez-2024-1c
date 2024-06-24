#include "pista.h"

void resetear_valores(int *v1, int *v2)
{
	*v1 = 0;
	*v2 = 0;
}
obstaculo_t *obstaculo_crear(enum TP_OBSTACULO tipo)
{
	if (tipo < OBSTACULO_FUERZA || tipo > OBSTACULO_INTELIGENCIA) {
		return NULL;
	}
	obstaculo_t *obs = (obstaculo_t *)calloc(1, sizeof(obstaculo_t));
	if (!obs) {
		return NULL;
	}

	switch (tipo) {
	case OBSTACULO_FUERZA:
		obs->identificador = IDENTIFICADOR_OBSTACULO_FUERZA;
		break;
	case OBSTACULO_DESTREZA:
		obs->identificador = IDENTIFICADOR_OBSTACULO_DESTREZA;
		break;
	case OBSTACULO_INTELIGENCIA:
		obs->identificador = IDENTIFICADOR_OBSTACULO_INTELIGENCIA;
		break;
	}
	obs->tipo = tipo;
	return obs;
}
pista_t *pista_crear()
{
	pista_t *pista = (pista_t *)calloc(1, sizeof(pista_t));
	if (!pista) {
		return NULL;
	}
	pista->lista = lista_crear();
	return pista;
}
int calcular_tiempo(int anteriores, int atributo_valor)
{
	return ((anteriores - atributo_valor) < 0) ?
		       0 :
		       anteriores - atributo_valor;
}
unsigned int pista_calcular_tiempo(pista_t *pista, int fuerza, int destreza,
				   int inteligencia)
{
	if (!pista || lista_vacia(pista->lista)) {
		return 0;
	}
	lista_iterador_t *iterador = lista_iterador_crear(pista->lista);
	if (!iterador) {
		return 0;
	}
	int valor_fuerza = 0, valor_destreza = 0, valor_inteligencia = 0;

	unsigned int tiempo = 0;
	for (obstaculo_t *actual =
		     (obstaculo_t *)lista_iterador_elemento_actual(iterador);
	     lista_iterador_tiene_siguiente(iterador);
	     lista_iterador_avanzar(iterador)) {
		actual =
			(obstaculo_t *)lista_iterador_elemento_actual(iterador);
		switch (actual->tipo) {
		case OBSTACULO_FUERZA:
			resetear_valores(&valor_destreza, &valor_inteligencia);
			tiempo += (unsigned int)calcular_tiempo(
				VALOR_MAX_OBSTACULO - valor_fuerza, fuerza);
			valor_fuerza++;
			break;
		case OBSTACULO_DESTREZA:
			resetear_valores(&valor_inteligencia, &valor_fuerza);
			tiempo += (unsigned int)calcular_tiempo(
				VALOR_MAX_OBSTACULO - valor_destreza, destreza);
			valor_destreza++;
			break;
		case OBSTACULO_INTELIGENCIA:
			resetear_valores(&valor_fuerza, &valor_destreza);
			tiempo += (unsigned int)calcular_tiempo(
				VALOR_MAX_OBSTACULO - valor_inteligencia,
				inteligencia);
			valor_inteligencia++;
			break;
		}
	}
	lista_iterador_destruir(iterador);
	return tiempo;
}
char *pista_tiempo_csv(pista_t *pista, int fuerza, int destreza,
		       int inteligencia)
{
	if (lista_vacia(pista->lista)) {
		return NULL;
	}
	lista_iterador_t *iterador = lista_iterador_crear(pista->lista);
	if (!iterador) {
		return NULL;
	}
	size_t buffer = 1;
	char *csv = (char *)malloc(sizeof(buffer));
	if (!csv) {
		return NULL;
	}
	csv[0] = '\0';
	int valor_fuerza = 0, valor_destreza = 0, valor_inteligencia = 0,
	    tiempo = 0;
	char str[12];
	size_t new_size = 0;

	for (obstaculo_t *actual =
		     (obstaculo_t *)lista_iterador_elemento_actual(iterador);
	     lista_iterador_tiene_siguiente(iterador);
	     lista_iterador_avanzar(iterador)) {
		actual =
			(obstaculo_t *)lista_iterador_elemento_actual(iterador);
		switch (actual->tipo) {
		case OBSTACULO_FUERZA:
			resetear_valores(&valor_destreza, &valor_inteligencia);
			tiempo = calcular_tiempo(
				VALOR_MAX_OBSTACULO - valor_fuerza, fuerza);
			valor_fuerza++;
			break;
		case OBSTACULO_DESTREZA:
			resetear_valores(&valor_fuerza, &valor_inteligencia);
			tiempo = calcular_tiempo(
				VALOR_MAX_OBSTACULO - valor_destreza, destreza);
			valor_destreza++;
			break;
		case OBSTACULO_INTELIGENCIA:
			resetear_valores(&valor_fuerza, &valor_destreza);
			tiempo = calcular_tiempo(VALOR_MAX_OBSTACULO -
							 valor_inteligencia,
						 inteligencia);
			valor_inteligencia++;
		}
		snprintf(str, sizeof(str), "%d,", tiempo);
		new_size = buffer + strlen(str);
		char *temp = (char *)realloc(csv, new_size);
		if (!temp) {
			free(csv);
			lista_iterador_destruir(iterador);
			return NULL;
		}
		csv = temp;
		strcat(csv, str);
		buffer = new_size;
	}
	if (buffer > 1) {
		csv[buffer - 2] = '\0';
	}
	lista_iterador_destruir(iterador);
	return csv;
}

int pista_borrar(pista_t *pista, size_t posicion)
{
	if (!pista || lista_vacia(pista->lista) ||
	    posicion > pista_tamanio(pista))
		return INVALIDO;
	obstaculo_t *borrado =
		(obstaculo_t *)lista_quitar_de_posicion(pista->lista, posicion);
	int tipo = borrado->tipo;
	free(borrado);
	return tipo;
}
int pista_insertar(pista_t *pista, enum TP_OBSTACULO tipo, size_t pos)
{
	if (!pista) {
		return INVALIDO;
	}

	if (pos >= MAX_TAMANIO_PISTA || tipo > OBSTACULO_INTELIGENCIA) {
		return INVALIDO;
	}
	obstaculo_t *obstaculo = obstaculo_crear(tipo);
	if (!obstaculo) {
		return INVALIDO;
	}
	if (!lista_insertar_en_posicion(pista->lista, obstaculo, pos)) {
		free(obstaculo);
		return INVALIDO;
	}
	return EXITO;
}
bool mostrar(void *elemento, void *texto_)
{
	char **texto = (char **)texto_;
	size_t tamanio_nuevo = strlen(*texto) + 1;
	char *temp = (char *)realloc(*texto, tamanio_nuevo + 1);
	if (!temp) {
		return false;
	}
	*texto = temp;
	(*texto)[tamanio_nuevo - 1] = ((obstaculo_t *)elemento)->identificador;
	(*texto)[tamanio_nuevo] = '\0';
	return true;
}
unsigned int pista_tamanio(pista_t *pista)
{
	if (!pista || lista_vacia(pista->lista)) {
		return 0;
	}
	return (unsigned int)lista_tamanio(pista->lista);
}
char *pista_devolver_todo(pista_t *pista)
{
	if (!pista || lista_vacia(pista->lista)) {
		return NULL;
	}
	char *pista_texto = (char *)malloc(1);
	if (!pista_texto) {
		return NULL;
	}
	pista_texto[0] = '\0';
	size_t tam =
		lista_con_cada_elemento(pista->lista, mostrar, &pista_texto);

	if (!pista_texto || tam != lista_tamanio(pista->lista)) {
		free(pista_texto);
		return NULL;
	}
	return pista_texto;
}
void pista_limpiar(pista_t *pista)
{
	if (!pista || lista_vacia(pista->lista)) {
		return;
	}
	while (!lista_vacia(pista->lista)) {
		free(lista_quitar(pista->lista));
	}
}

void pista_destruir(pista_t *pista)
{
	if (!pista) {
		return;
	}
	lista_destruir_todo(pista->lista, free);
	free(pista);
}
