# Heapsort

Dado un vector con los siguientes elementos:
```c
V = [9,8,7,6,5]
```
 Aplique el algoritmo **heapsort** para ordenarlo de mayor a menor
 
 Luego de insertar todos los elementos y aplicar sfit_up quedan de esta manera 
 ```
         9
        /  \
       8    7
      / \   
     6  5 

```
Aplicamos Sift_down()

```
     5
    / \
   6   7 
  / \
 9   8
```


``` 
     6    
    / \
   8   7
  / 
 9   

Vector ordenado:
 [6,8,7,9,  5]
```

``` 
     7    
    / \
   8   9
    

Vector ordenado:
 [7,8,9,  6,5]
```

``` 
     8    
    / 
   9   
    

Vector ordenado:
 [9,8,7,6,5]
```






