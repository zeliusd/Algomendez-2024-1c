void swap(void **vector, int pos1, int pos2) {
  void *aux = vector[pos1];
  vector[pos1] = vector[pos2];
  vector[pos2] = aux;
}

int Pivotear(void **vector, int tamanio, int (*cmp)(void *, void *)) {

  int pivote_posicion = tamanio - 1;
  int pivote_posicion_final = 0;

  for (int i = 0; i < tamanio; i++) {

    if (cmp(vector[i], vector[pivote_posicion]) > 0) {
      swap(vector, i, pivote_posicion_final);
      pivote_posicion_final++;
    }
  }
  swap(vector, pivote_posicion_final, pivote_posicion);
  return pivote_posicion_final;
}

void sort_semi_generico(void **vector, int cant_elementos,
                        int (*comparador)(void *, void *)) {
  if (cant_elementos <= 1 || !comparador) {
    return;
  }
  int pivote_posicion = Pivotear(vector, cant_elementos, comparador);

  sort_semi_generico(vector, pivote_posicion, comparador);
  sort_semi_generico(vector + 1 + pivote_posicion,
                     cant_elementos - 1 - pivote_posicion, comparador);
}
