#include <stdio.h>
#include <stdlib.h>

#define MAX_3 3 

typedef struct cosa_roja{
  char vector[MAX_3];
  char* puntero_palabra;
}rojo_t;

typedef struct cosa_azul{
  struct cosa_azul* siguiente;
  rojo_t* izquierda;
  rojo_t* derecha;
  
}cosa_azul_t;

int generar_cosas_azules(cosa_azul_t* cosa_azul, int i){
  if(!cosa_azul){
    return 0;
  }

  if(i < MAX_3){
    cosa_azul->siguiente = calloc(1, sizeof(cosa_azul_t));
    if(cosa_azul->siguiente){
      return 1;
    }
    i++;
  }
  generar_cosas_azules(cosa->siguiente, i+1);

}

int main(){
  cosa_azul_t* cosa_azul = calloc(1, sizeof(cosa_azul_t));
  if(generar_cosas_azules()
  char* abc = "ABCD";

  if (){

  }

  return 0;
}
