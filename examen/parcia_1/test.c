#include <stdio.h>
#include <stdlib.h>
const size_t MAX_VECTOR = 5;
int main(){
char*** frase = malloc(MAX_VECTOR*sizeof(char*));
char letra = 'P';
for (size_t i = 0; i < MAX_VECTOR; i++){
frase[i] = malloc((i+1)*sizeof(char*));
char* p_letra = malloc(sizeof(char));
*p_letra = letra;
for (size_t j = 0; j < i+1; j++){
frase[i][j] = p_letra;
}
letra++;
}
*(frase[0][0]) = 'A';
*(frase[1][0]) = *(frase[0][0]) + 10;
printf("%c%c%c%c%c\n", frase[3][0][0], frase[4][0][0],
frase[0][0][0], frase[2][0][0], frase[1][0][0]);
  
  for (size_t i = 0; i < MAX_VECTOR; i++){
    free(frase[i][i]);
    free(frase[i]);
  }
free(frase);
return 0;
}
