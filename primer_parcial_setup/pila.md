# Ejercicio1 



```c
void f1(pila_t* pila)
{
                                
    while (!pila_vacia(pila))   | T(S1)
        pila_quitar(pila);      | T(S2) 
}
```
Tenemos en T(S1) que:
T(S1) = O(tamanio_pila)*T(S2)

Donde tomando el caso de que pila_quitar() sea O(1), entonces

T(S1) = O(1). 

Complejidad total O(n)*O(1) = O(n)

```c
int f2(int n)
{
    int k=0;                      | T(S1) = O(1)
 
    for (int i=0; i<n; i++)       | T(S2) = O(n)
        for (int j=0;j<n/2;j++)   | T(S3) = (O(n)/2)*T(S2)
            k++;                  | T(S4) = T(S2)*T(S3)*O(1)

    return k;                     | T(S5) = O(1)
}

```
Entonces la función f2 nos queda:

T(F2) = O(1) + O(n)*(O(n)/2)*O(1)+O(1) = O(n²)






