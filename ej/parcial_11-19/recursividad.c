#include <stdio.h>
int imprimir_raro_n(const char* string, int n){
  if(!*string){
    return -1;
  }
  
  if( (n % 2) != 0){
    printf("%c",*string); 
  }
  imprimir_raro_n(string+1, n+1);
  if (*string == ':') {
    return 0;
  }
  if (n % 2 == 0) {
    printf("%c", *string);
  }
  return 0;
}
void imprimir_raro(const char* string){
  imprimir_raro_n(string, 1);
}
int main(){
  imprimir_raro("A2lsgoomrti");
  printf(" ");
  imprimir_raro("Aopnr:oobda");
}
