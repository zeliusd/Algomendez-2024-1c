#include <stdio.h>
#include <stdlib.h>
#define MAX_VECTOR 5

typedef struct cosa{
  int campo1;
  struct cosa** vector;
}cosa_azul_t; 


int main()
{
  cosa_azul_t* v1 = malloc(sizeof(cosa_azul_t));
  
  if (!v1) return 1;

  v1->vector = malloc(MAX_VECTOR*sizeof(cosa_azul_t*));
  
  if(!v1->vector){
    free(v1);
    return 1;
  } 

  for (int i = 0; i < MAX_VECTOR; i++) {
    v1->vector[i] = malloc(sizeof(cosa_azul_t));
    if(!v1->vector[i]){
      // Limpieza de todo
      i++;
      for (int j = 0; j < i; j++) {
        free(v1->vector[j]);
      }
      free(v1->vector);
      free(v1);
      return 1;
    }
  }

  for(int i = 0; i < MAX_VECTOR;i++){
    free(v1->vector[i]);
  }

  free(v1->vector);
  free(v1);
  
  return 0;
}
