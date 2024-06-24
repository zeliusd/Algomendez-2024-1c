#include "stdio.h"
#include <string.h>

// complejidad O(nlogn)
void Merge(int *v1, int *v2, int *m, int c1, int c2) {
  int i1 = 0, i2 = 0, i3 = 0;
  while (c1 > i1 && c2 > i2) {
    if(v1[i1] >= v2[i2]){
      m[i3] = v2[i2];
      i2++;
    }else{
      m[i3] = v1[i1];
      i1++;
    }
    i3++;
  }
  while(c1 > i1){
    m[i3] = v1[i1];
    i3++;
    i1++;
  }
  while(c2 > i2){
    m[i3] = v2[i2];
    i3++;
    i2++;
  }

  
}

void MergeSort(int *v, int tam) {
  if(tam <= 1){
    return;
  }
  int cantidad1 = tam / 2;
  int cantidad2 = tam - cantidad1;

  int* v1 = v;
  int* v2 = v + cantidad1;

  MergeSort(v1, cantidad1);
  MergeSort(v2, cantidad2);

  int mezclado[tam];

  Merge(v1, v2, mezclado, cantidad1, cantidad2);
  memcpy(v, mezclado, tam * sizeof(int));
}

int main() { 
  int numeros[] = {3, 4, 1, 5, 6, 7, 8, 9, 2};
  int tamanio = sizeof(numeros) / sizeof(*numeros);

  MergeSort(numeros, tamanio);

  for (int i = 0; i < tamanio; i++) {
    printf("%i ", numeros[i]);
  }
  return 0;
 }

