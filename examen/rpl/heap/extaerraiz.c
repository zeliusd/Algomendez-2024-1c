extern void sift_down(int* vector, int tope, int pos_actual);

void swapo(int* vector, int pos1,int pos2){

  int aux = vector[pos1];
  vector[pos1] = vector[pos2];
  vector[pos2] = aux;
}
int heap_extraer_raiz(int* vector, int* tope){
  if (!vector || *tope == 0){
    return 0;
  }
  int elemento = vector[0];
  swapo(vector, 0, (*tope)-1);
  (*tope)--;
  sift_down(vector, *tope,0);
  return elemento;
}
