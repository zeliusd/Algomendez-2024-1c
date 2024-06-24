# Bubble Sort recursivo

Escriba un algoritmo bubble sort recursivo (sin utilizar for, while, etc) para un vector de enteros.

```c 
void swap(int *vector, int pos1, int pos2){
    int aux = vector[pos1];
    vector[pos1] = vector[pos2];
    vector[pos2] = aux;
}

void bubble_sort_recursivo2(int *vector_desordenado, int *vector_ordenado, int tope, bool ascendente, int *contador1, int* contador2){
    if((*contador2) > tope - (*contador1)){
        return;
    }
    if(ascendente){
        if(vector_desordenado[(*contador2)] > vector_desordenado[(*contador2)+1]) swap(vector_desordenado, (*contador2), (*contador2)+2);
    }else{
        if(vector_desordenado[(*contador2)] < vector_desordenado[(*contador2)+1]) swap(vector_desordenado, (*contador2), (*contador2)+1);
    }
    (*contador2)++;
    bubble_sort_recursivo2(vector_desordenado,vector_ordenado,tope,ascendente,contador1,contador2);
}
void bubble_sort_recursivo1(int *vector_desordenado, int *vector_ordenado, int tope, bool ascendente, int *contador1){
    if((*contador1) >= tope-1){
        return;
    }
    int contador2 = 0;
    bubble_sort_recursivo2(vector_desordenado,vector_ordenado,tope, ascendente,contador1, &contador2);
    vector_ordenado[tope-(*contador1)] = vector_desordenado[tope-(*contador1)]
    (*contador1)++;
    bubble_sort_recursivo1(vector_desordenado,vector_ordenado,tope,ascendente,contador1);
}

void bubble_sort(int *vector_desordenado, int *vector_ordenado, int tope, bool ascendente){

    int contador1 = 1;
    bubble_sort_recursivo1(vector_desordenado,vector_ordenado,tope,ascendente,&contador1);
    vector_ordenado[0] = vector_desordenado[0];
}

```


