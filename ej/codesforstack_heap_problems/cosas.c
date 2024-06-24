#include <stdio.h>
#include <stdlib.h>

#define MAX_VECTOR 5 


typedef struct cosa{
  int campo1;
  int*** valores;

}cosa_azul_t;

int main(){

  cosa_azul_t* cosa_azul = malloc(sizeof(cosa_azul_t));

  cosa_azul->valores = malloc(MAX_VECTOR*sizeof(int**));
  int numero = 4;
  int i = 0,j = 0;
  int* pnumero = malloc(sizeof(int));
  *pnumero = 3;
  for (i = 0;i < MAX_VECTOR ; i++) {
    cosa_azul->valores[i] = malloc((i+1)*sizeof(int*));
    for (j = 0;j < i+1;j++){ 
    
      if(j%2 == 0){
        cosa_azul->valores[i][j] = pnumero;
        
      }else{
        cosa_azul->valores[i][j] = &numero;
      }
    }
  }

}
