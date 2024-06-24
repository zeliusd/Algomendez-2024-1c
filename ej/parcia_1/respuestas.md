### PARCIAL 
---

Calcular la complejidad:
```
A) T1(n) =2T(n/2) + O(1)
B) T2(n)= 2T(n/2) + O(n)

```
**A)**
Teniendo que `A = 2 B= 2 C=0` tenemos el caso en el que `log2(2) = 1` entonces
la complejidad queda tal que `O(n)`.

**B)** Teniendo `A=2 B=2 C=1` tenemos el caso donde `n^log2(2)` y `O(n)`
Nos quedaría de esta manera `O(nlog(n))`


Determinar el orden de crecimiento de la siguiente función:

```c
void ejercicio_uno(int n){
    int i, j, k, contador=0;
    for( i=0; i<=n; i++)
        for( j=n ; j>=0; j--)
            for( k=1; k<n; k*=2)
                contador++;
}
```
Tomando en cuenta que los dos for recorren se recorren **n veces** y el segundo for se recorre con **n*n** y el último for tiene una complejidad de `O(log(n))` ya que no itera **n veces**, sino hasta que k < n con k*2 en cada iteración.

Entonces la operación seria `O(n²log(n))`

### Ordenamientos

---

Dado el siguiente vector: 
`[6,3,9,13,88,33,56,2,4,21,57]`
<br>
Ordenarlo ascendentemente mediante **Quicksort** y **MergeSort** mostrando todos los pasos intermedios. 


**Algoritmo Quicksort**

```
Tomamos el último como pivote y pivoteamos 
Pivote: 57
[88,*3,9,13,6,33,56,2,4,21,57]
[88,*57,9,13,6,33,56,2,4,21,3]
```
Nos queda que los elementos que estan del lado derecho al 57 son mayores que este y los izquierdo son menores a este.

```
Es un sólo elemento ya está ordenado
[88]
Tomamos el último como pivote y pivoteamos:
Pivote: 3
[*9,13,6,33,56,2,4,21,3]
[9,13,6,33,56, 4, 21, *3, 2]
```
Nos queda los elementos que están del lado derecho 3 son mayores que este y a la izquierda menores.


```

Tomamos el último como pivote y pivoteamos:
Pivote: 21 

[*9,13,6,33,56,4,21]

[33,*13,5,9,56,4,21]

[33,56,*5,9,13,4,21]

[33,56]|*21|[9,13,4,5]


```
Lo mismo pero con el 21.

Separamos dos casos ya que quedan dos array con varios elementos.

**[33,56]**
```
Pivote: 56
[*33,56]

|*56|[33]

|*33|

El 33 queda ordenado ya que es un solo elemento

```
**[9,13,4,5]**

``` 
Pivote: 5 

[9,13]|*5|[4]


Pivote: 13

[13,9]

|*13| [9]

|*9|


Es un solo elemento ya está ordenado.
[2]

```

Resultado:

`[,3,2]`

### Diagrama 

<-!diagrama->

Este programa no libera los punteros de las letras que fueron creado con `char *p_letra = malloc(sizeof(char))`

Entonces lo que se debería agregar en el último for es:
```c 
free(frase[i][i]);
```
Ya que todos los valores del vector aputan al mismo con solo dar un free se liberan todos. :)

### Recursividad
---

```c
void invertir(pila_t pila, pila_t aux){
    if(vacia(pila)){
        return;
    }
    apilar(aux, desapilar(pila));
}

void mostrar(pila_t aux){
    printf("%i\n", desapilar(aux))
}
void invertir_y_mostrar(pila_t pila){
    pila_t pila_auxiliar;
    invertir(pila, aux);
    mostrar(aux);
}
```











 














