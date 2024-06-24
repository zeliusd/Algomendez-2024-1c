#include <string.h>

void swap(char *vector, int pos1, int pos2,int tamanio_un_elemento) {
  char *aux = malloc(tamanio_un_elemento);
  if (aux == NULL) {
    // Manejo de error por falta de memoria
    return;
  }
  memcpy(aux,vector+pos1*tamanio_un_elemento,(size_t)tamanio_un_elemento);
  memcpy(vector+pos1*tamanio_un_elemento,vector+pos2*tamanio_un_elemento,(size_t)tamanio_un_elemento);
  memcpy(vector+pos2*tamanio_un_elemento,aux,(size_t)tamanio_un_elemento);
  free(aux);
}

int Pivotear(char *vector, int tamanio, int (*cmp)(void *, void *), int tamanio_elemento) {

  int pivote_posicion = tamanio - 1;
  int pivote_posicion_final = 0;

  for (int i = 0; i < tamanio; i++) {

    if (cmp(vector + i*tamanio_elemento, vector + pivote_posicion*tamanio_elemento) > 0) {
      swap(vector, i, pivote_posicion_final,tamanio_elemento);
      pivote_posicion_final++;

    }
  }
  swap(vector, pivote_posicion_final, pivote_posicion,tamanio_elemento);
  return pivote_posicion_final;
}

void sort_generico(void *vector, int cant_elementos, int tamanio_un_elemento, int (*comparador)(const void *, const void*)){
  if (cant_elementos <= 1 || !comparador) {
    return;
  }
  int pivote_posicion = Pivotear(vector, cant_elementos, comparador,tamanio_un_elemento);

  sort_generico(vector, pivote_posicion,tamanio_un_elemento, comparador);
  sort_generico((char*)vector + (1+pivote_posicion)*tamanio_un_elemento,
                     cant_elementos - 1 - pivote_posicion, tamanio_un_elemento, comparador);
} 
