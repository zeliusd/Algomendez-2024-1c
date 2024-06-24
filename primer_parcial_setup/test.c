#include <stdio.h>
#include <stdbool.h>
#define MAX_VECTOR 5
void swap(int *vector, int pos1, int pos2){
    int aux = vector[pos1];
    vector[pos1] = vector[pos2];
    vector[pos2] = aux;
}

void bubble_sort_recursivo2(int vector_desordenado[MAX_VECTOR], int vector_ordenado[MAX_VECTOR], int tope, bool ascendente, int *contador1, int* contador2){
    if((*contador2) >= tope - (*contador1) - 1){
        return;
    }
    if(ascendente){
        if(vector_desordenado[(*contador2)] > vector_desordenado[(*contador2)+1]) swap(vector_desordenado, (*contador2), (*contador2)+1);
    }else{
        if(vector_desordenado[(*contador2)] < vector_desordenado[(*contador2)+1]) swap(vector_desordenado, (*contador2), (*contador2)+1);
    }
    (*contador2)++;
    bubble_sort_recursivo2(vector_desordenado,vector_ordenado,tope,ascendente,contador1,contador2);
}
void bubble_sort_recursivo1(int vector_desordenado[MAX_VECTOR], int vector_ordenado[MAX_VECTOR], int tope, bool ascendente, int *contador1){
    if((*contador1) >= tope-1){
        return;
     }
    int contador2 = 0;
    bubble_sort_recursivo2(vector_desordenado,vector_ordenado,tope, ascendente,contador1, &contador2);
    vector_ordenado[tope-(*contador1)] = vector_desordenado[tope-(*contador1)];
   
    (*contador1)++;

bubble_sort_recursivo1(vector_desordenado,vector_ordenado,tope,ascendente,contador1);
}

void bubble_sort(int vector_desordenado[MAX_VECTOR], int vector_ordenado[MAX_VECTOR], int tope, bool ascendente){

    int contador1 = 1;
    bubble_sort_recursivo1(vector_desordenado,vector_ordenado,tope,ascendente,&contador1);
    vector_ordenado[0] = vector_desordenado[0];
}

int main(){

  int array[MAX_VECTOR] = {3,2,4};
  int ordenado[MAX_VECTOR] = {0};
  int tope = 3;

  bool ascendente = false;
  bubble_sort(array,ordenado,tope,ascendente);

  for (int i = 0; i < tope; i++) {
  
    printf("%i", ordenado[i]);
  }
  
  return 0;
}

