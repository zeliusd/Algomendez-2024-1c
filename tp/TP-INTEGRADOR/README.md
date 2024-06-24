# TP: Carrera de obstáculos

## Repositorio de (Miguel Zorrilla) - (110619) - (<mzorrilla@fi.uba.ar>)

- Para compilar:

```bash
make juego
```

- Para ejecutar:

```bash
./juego
```

- Para ejecutar con valgrind:

```bash
make juego-valgrind
```

---

## Funcionamiento de TP.c

Se crearon dos tdas para el funcionamiento del juego que son `pista.h` y `jugador.h`. Se empieza leyendo un archivo `.txt` que contenga datos de pokemones del estilo `pikachu,2,3,4` y se agregan en un `abb` para el manejo del `struct pokemon_info` y se crean los dos jugadores. Dentro de `jugador.c` se crea una pista y con su pokemon. En el tda `pista.h` se usa una lista (doblemente) enlazada para implementar la pista.

```c
TP *tp_crear(const char *nombre_archivo)
{
 FILE *fp = fopen(nombre_archivo, "r");
 if (!fp) {
  return NULL;
 }
 TP *juego = (TP *)calloc(1, sizeof(TP));
 if (!juego) {
  fclose(fp);
  return NULL;
 }
 juego->jugador_1 = jugador_crear(JUGADOR_1);
 if (!juego->jugador_1) {
  free(juego);
  fclose(fp);
  return NULL;
 }
 juego->jugador_2 = jugador_crear(JUGADOR_2);
 if (!juego->jugador_2) {
  jugador_destructor(juego->jugador_1);
  free(juego);
  fclose(fp);
  return NULL;
 }
 juego->abb_pokemon = abb_crear(cmp_pokemones);
 if (!juego->abb_pokemon) {
  jugador_destructor(juego->jugador_1);
  jugador_destructor(juego->jugador_2);
  free(juego);
  fclose(fp);
  return NULL;
 }
 if (!llenar_abb_pokemones(juego, fp)) {
  jugador_destructor(juego->jugador_1);
  jugador_destructor(juego->jugador_2);
  abb_destruir_todo(juego->abb_pokemon, destructor_pokemones);
  free(juego);

  fclose(fp);
  return NULL;
 }
 fclose(fp);
 return juego;
}

```

### Jugador

```c

player_t *jugador_crear(enum TP_JUGADOR id)
{
 if (id > JUGADOR_2) {
  return NULL;
 }
 player_t *jugador = (player_t *)calloc(1, sizeof(player_t));
 if (!jugador) {
  return NULL;
 }
 jugador->pista = pista_crear();
 if (!jugador->pista) {
  free(jugador);
  return NULL;
 }
 return jugador;
}
```

### Pista

```c
pista_t *pista_crear()
{
 pista_t *pista = (pista_t *)calloc(1, sizeof(pista_t));
 if (!pista) {
  return NULL;
 }
 pista->lista = lista_crear();
 return pista;
}
```

---

## Respuestas a las preguntas teóricas

**Explicación primera pregunta**:

En el tp.c para almacenar los pokemons recibidos a través del archivo de texto, Vi conveniente usar un `ABB` debido a que `tp_seleccion_pokemon`, `tp_buscar_pokemon` y `tp_nombres_disponibles`, me resultaba mejor en complejidad algoritmica ya que las operaciones de un abb son O(logn) en su mejor escenario.

Tomé la decisión de crear dos tdas aparte `jugador.h` y `pista.h` para tener mas orden en el código y este mejor estructurado.

Dentro de `pista.h` se usó la lista implementada durante la cursada, lo cual me pareció conveniente ya que las operaciones de este tda se parecían a la de la lista.

**Segunda pregunta**:

<table>
    <thead>
        <tr>
            <th>Función</th>
            <th>Complejidad</th>
            <th>Justificación</th>
        </tr>
    </thead>
    <tbody>
        <tr>
            <td>Crear()</td>
            <td>O(n)</td>
            <td>Esta función crea el tp, ya que se crea un abb y se llena con todos los pokemones que hay en el archivo de texto y va formateando cada char en el nombre, quedaría O(cantidad_pokemones) + O(cantidad_caractares_nombre) en la complejidad.</td>
        </tr>
        <tr>
            <td>cantidad_pokemon()</td>
            <td>O(1)</td>
            <td>ya que abb_tamanio es O(1)</td>
        </tr>
        <tr>
            <td>buscar_pokemon()</td>
            <td>O(n). Mejor caso O(logn)</td>
            <td>Este busca el pokemon mandado por parametro en el abb que es O(logn), sin embargo ya que acá uso transformar_texto que puede ser O(n) dependiendo de la cantidad de caracteres que el usuario ingrese entonces es O(cantidad_caracteres_nombre) + O(logn)</td>
        </tr>
        <tr>
            <td>nombres_disponibles()</td>
            <td>O(n)</td>
            <td>Devuelve todos los pokemones en inorden del abb, por lo tnato termina siendo O(cantidad_pokemones_disponibles)</td>
        </tr>
        <tr>
            <td>tp_seleccionar_pokemon()</td>
            <td>O(n). Mejor caso O(logn)</td>
            <td>Ya que usa buscar_pokemon que es O(n) en el peor caso</td>
        </tr>
        <tr>
            <td>pokemon_seleccionado()</td>
            <td>O(1)</td>
            <td>Es O(1) debido a que el pokemon se encuentra dentro de la estructura del jugador.</td>
        </tr>
        <tr>
            <td>agregar_obstaculo()</td>
            <td>O(n)</td>
            <td>Ya que se usa una lista para implementar la pista donde n es la cantidad MAX_OBSTACULOS permitodos, debido al enunciado el maximo es 100 por lo tanto seria O(100) en el peor caso.</td>
        </tr>
        <tr>
            <td>obstaculos_pista()</td>
            <td>O(n)</td>
            <td>Este recorre todos los elementos de la pista por lo tanto termina siendo O(n)</td>
        </tr>
        <tr>
            <td>limpiar_pista()</td>
            <td>O(n)</td>
            <td>Elimina y libera todos los elementos de las pista dando un O(n)</td>
        </tr>
        <tr>
            <td>calcular_tiempo_pista()</td>
            <td>O(n)</td>
            <td>Recorre todos los elementos de la pista asi que es O(n)</td>
        <tr>
            <td>tiempo_por_obstaculo()</td>
            <td>O(n)</td>
            <td>Recorre todos los elementos de la pista asi que termina siendo O(n)</td>
        </tr>
        </tr>
    </tbody>
</table>
