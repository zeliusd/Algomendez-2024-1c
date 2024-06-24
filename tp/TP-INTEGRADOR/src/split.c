#include "split.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int calcularCant(const char *string, char separador)
{
	int acumulador = 0;
	int longi = (int)strlen(string);
	for (int i = 0; i < longi; i++) {
		acumulador += (string[i] == separador) ? 1 : 0;
	}
	return acumulador;
}

char **split(const char *string, char separador)
{
	if (!string) {
		return NULL;
	}
	int cantidad = calcularCant(string, separador) + 2;
	size_t longitud = strlen(string);
	int pos = 0;
	int tope = 0;
	char **salida = malloc((unsigned int)cantidad * sizeof(char *));

	if (!salida) {
		return NULL;
	}
	for (int i = 0; i < (int)longitud + 1; i++) {
		if (string[i] == separador || string[i] == '\0') {
			salida[tope] = malloc((unsigned int)(i - pos + 1) *
					      sizeof(char));
			if (!salida[tope]) {
				for (int j = 0; j < tope; j++) {
					free(salida[j]);
				}
				return NULL;
			}
			for (int j = 0; j < i - pos; j++) {
				salida[tope][j] = string[j + pos];
			}
			salida[tope][i - pos] = '\0';
			tope++;
			pos = i + 1;
		}
	}
	salida[tope] = NULL;
	return salida;
}
