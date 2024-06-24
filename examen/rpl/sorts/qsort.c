#include <stdio.h>

void swap(int *v, int a, int b) {
  int aux = v[a];
  v[a] = v[b];
  v[b] = aux;
}

int Pivotear(int *v, int tam) {

  int pivote_posicion = tam - 1;
  int pivote_final_posicion = 0;

  for (int i = 0; i < tam; i++) {
    if (v[i] > v[pivote_posicion]) {
      swap(v, i, pivote_final_posicion);
      pivote_final_posicion++;
    }
  }
  swap(v, pivote_final_posicion, pivote_posicion);
  return pivote_final_posicion;
}

void QuickSort(int *v, int tam) {
  if (tam <= 1) {
    return;
  }

  int pivote_posicion = Pivotear(v, tam);

  QuickSort(v, pivote_posicion);
  QuickSort(v + pivote_posicion + 1, tam - pivote_posicion - 1);
}

int main(void) {

  int numeros[] = {
  2, 124, 23, 5, 89, -1, 44, 643, 34};
  int tamanio = sizeof(numeros) / sizeof(*numeros);

  QuickSort(numeros, tamanio);

  for (int i = 0; i < tamanio; i++) {
    printf("%i ", numeros[i]);
  }
  return 0;
}
