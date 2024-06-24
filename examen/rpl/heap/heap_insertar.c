extern void sift_up(int* vector, int tope);

void heap_insertar(int* vector, int* tope, int elemento){
  if(!vector){
    return;  
  }
  vector[(*tope)] = elemento;
  (*tope)++;
  sift_up(vector, (*tope)-1);
}
