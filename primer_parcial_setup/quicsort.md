# Quicksort 

Quicksort ordena elemento mediante un pivote seleccionado por el que hace la implementación este va pivoteando el pivote y hace una división de los elementos que son mayores que este y otro con los menores a este, va iterando de esa manera hasta que queden todos ordenados. 

`V = [2, 3, 5, 0, 2, 1, 9, 7];`

Cantidad de elementos = 8  
Mitad = 4 

```
Pivote: 0

|[0]|[3,5,2,2,1,9,7] -> termina de pivotear el 0
            \
Pivote: 2 de la posición 3 

            [3,5,2,2,1,9,7]
                   |
            [2,1]|[2]|[3,5,9,7] -> Termina de pivotear el 2
             /           \
        Pivote:1        Pivote: 9  
        [2,1]            [3,5,7]|[9]|
        /                  / 
    |1|[2]               Pivote= 5
         \                [3]|[5]|[7]
        Pivote = 2         /        \
         |2|             Pivote=3    Pivote = 7
                         |[3]|        |[7]]

Entonces nos queda el vector de esta manera:

[0,1,2,2,3,5,7,9]
```
