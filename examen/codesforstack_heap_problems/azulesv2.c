#include <stdio.h>
#include <stdlib.h>
#define MAX_VECTOR 5
typedef struct cosa_azul{
  char* letra;
  struct cosa_azul* dps_siguiente;
  struct cosa_azul* siguiente;
}cosa_azul_t;

void generar_bloques_azules(cosa_azul_t* cosa_azul, int* contador, char* abece){
  if (!cosa_azul){
    return;
  }
  cosa_azul->letra = (abece + MAX_VECTOR- 1 - *(contador));
  if(*contador < MAX_VECTOR-1){
    cosa_azul->siguiente = calloc(1, sizeof(cosa_azul_t));
    (*contador)++;
  }
  generar_bloques_azules(cosa_azul->siguiente,contador, abece);
}

void referenciar_dps_de_siguiente(cosa_azul_t* cosa_azul){
  if (!cosa_azul || !cosa_azul->siguiente || !cosa_azul->siguiente->siguiente) {
    return;
  }
  cosa_azul->dps_siguiente = cosa_azul->siguiente->siguiente;
  referenciar_dps_de_siguiente(cosa_azul->siguiente);
}

int main(){
  cosa_azul_t* cosa_azul = calloc(1,sizeof(cosa_azul_t));
  char* abece = malloc(MAX_VECTOR*sizeof(char));

  *(abece) = 'A';
  *(abece+1) = 'B';
  *(abece+2) = 'C';
  *(abece+3) = 'D';
  *(abece+4) = 'E';
  int contador = 0;
  generar_bloques_azules(cosa_azul, &contador, abece);
  referenciar_dps_de_siguiente(cosa_azul);
  return 0;
}
