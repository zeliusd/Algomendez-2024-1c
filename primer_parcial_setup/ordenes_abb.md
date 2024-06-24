
```c
void mostrar_abb(abb_t* abb)
{

    puts("INORDEN: ");
    abb_con_cada_elemento(abb, INORDEN, mostrar_elemento, NULL);

    puts("\nPREORDEN: ");
    abb_con_cada_elemento(abb, PREORDEN, mostrar_elemento, NULL);

    puts("\nPOSTORDEN: ");
    abb_con_cada_elemento(abb, POSTORDEN, mostrar_elemento, NULL);
}

```

SALIDA: 

```bash
INORDEN: 1 8 6 0 9 18 13 25
PREORDEN: 0 1 6 8 9 13 18 25
```

La línea que falta es la de `POSTORDEN`, pero hay que tomar en cuenta que la salida también es incorrecta ya que `PREORDEN` y `INORDEN` Están invertidos
