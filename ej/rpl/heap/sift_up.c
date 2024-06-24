
void swap(int* vector, int pos1, int pos2){
  int aux = vector[pos1];
  vector[pos1] = vector[pos2];
  vector[pos2] = aux;
}

void sift_up(int* vector, int pos_actual){

  if (!vector || pos_actual == 0){
    return;
  }
  int padre = (pos_actual-1)/2;
  if(vector[pos_actual] > vector[padre])
  {
    swap(vector, pos_actual, padre);
    sift_up(vector, padre);
  }
}
