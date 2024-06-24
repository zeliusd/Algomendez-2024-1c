void swap(int* vector, int pos1, int pos2){
  int aux = vector[pos1];
  vector[pos1] = vector[pos2];
  vector[pos2] = aux;
}
void sift_down(int* vector, int tope, int pos_actual){
  
  int hijo_izq = 2*pos_actual + 2;
  int hijo_der = 2*pos_actual + 1;
  int mayor = hijo_izq;
  
  if (hijo_izq >= tope){
    return;
  }

  if(vector[hijo_izq] < vector[hijo_der]){
    mayor = hijo_der;
  }

  if(vector[mayor] > vector[pos_actual]){
    swap(vector, pos_actual, mayor);

    sift_down(vector, tope, mayor);
  }

}
