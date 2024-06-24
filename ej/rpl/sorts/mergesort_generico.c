#include <string.h>
#include <stdio.h>
void merge(char* v1, int cantidad1, char* v2, int cantidad2,char* v3,int (*comparador)(const void *, const void*), int tamanio_un_elemento){
  int x = 0, y = 0, z = 0;
  while (x < cantidad1 && y < cantidad2) {
    if (comparador(v1+x*tamanio_un_elemento, v2+y*tamanio_un_elemento) <= 0) {
      memcpy(v3+z*tamanio_un_elemento,v1+x*tamanio_un_elemento,(size_t)tamanio_un_elemento);
      x++;
    }else {
      memcpy(v3+z*tamanio_un_elemento,v2+y*tamanio_un_elemento,(size_t)tamanio_un_elemento);
      y++;
    }
    z++;
  }
  
  while (x < cantidad1) {
    memcpy(v3+z*tamanio_un_elemento,v1+x*tamanio_un_elemento,(size_t)tamanio_un_elemento);
    x++;
    z++;
  } 

  while (y < cantidad2) {
    memcpy(v3+z*tamanio_un_elemento,v2+y*tamanio_un_elemento,(size_t)tamanio_un_elemento);
    z++;
    y++;
  }

}

void sort_generico(void *vector, int cant_elementos, int tamanio_un_elemento, int (*comparador)(const void *, const void*)){
  
  if (cant_elementos <= 1 || !comparador) {
    return;
  }
  int cantidad1 = cant_elementos/2;
  int cantidad2 = cant_elementos - cantidad1;

  void *v1 = vector;
  void *v2 = (char*)vector+cantidad1*tamanio_un_elemento;

  sort_generico(v1, cantidad1,tamanio_un_elemento,comparador);
  sort_generico(v2, cantidad2,tamanio_un_elemento,comparador);

  char mezclado[cant_elementos*tamanio_un_elemento];
  
  merge(v1,cantidad1,v2,cantidad2,mezclado,comparador, tamanio_un_elemento);
 
  memcpy(vector,mezclado,(size_t)cant_elementos * (size_t)tamanio_un_elemento);

}

int comparador(const void* _il, const void* _i2){
  const int* i1 = _il;
  const int* i2 = _i2;
  return (*i1) - (*i2);
}

int main()
{
    int numeros[] = {3, 4, 2, 5, 7, 9};
    int cantidad = sizeof(numeros) / sizeof(*numeros);

    sort_generico((void *)numeros, cantidad, sizeof(int), comparador);

    for (int i = 0; i < cantidad; i++)
    {
        printf("%i ", numeros[i]);
    }
    return 0;
}
