# Analizador de estadísticas — Premier League 2025-2026

**Estructuras de Datos y Algoritmos — Avance 1**

## 1. Descripción del avance

Programa en C++ que carga desde un CSV las estadísticas de **300 jugadores reales de la Premier League 2025-2026** (15 por equipo) y permite:

- **Mostrarlos** en una tabla, incluyendo los goles por cada 90 minutos.
- **Ordenarlos** por goles, asistencias, edad, minutos o nombre, de forma ascendente o descendente, con **Bubble Sort** o **Merge Sort** (programados desde cero).
- **Filtrarlos** por equipo, posición o rango de goles.

Elegí este tema porque me gusta el fútbol y sigo la Premier League. Además, cada jugador tiene muchos atributos, así que un mismo algoritmo se puede probar con distintos criterios. Las estadísticas del archivo son aproximadas.

## 2. Cómo usar el programa

Desde la carpeta del proyecto:

```bash
g++ src/*.cpp -o analizador
.\analizador.exe      # Windows  (./analizador en Linux/Mac)
```

Menú:

1. **Cargar** los jugadores de `data/jugadores.csv` (hay que hacerlo primero).
2. **Mostrar** todos los jugadores.
3. **Ordenar:** se elige el criterio, el orden y el algoritmo. El programa indica qué algoritmo usó, cuántos jugadores procesó y cuántas comparaciones hizo.
4. **Filtrar** por equipo, posición o rango de goles.
0. **Salir.**

## 3. Sub-competencias

### SICT0301: Análisis de complejidad

| Algoritmo | Mejor caso | Promedio | Peor caso | Espacio |
|---|---|---|---|---|
| Bubble Sort | O(n) | O(n²) | O(n²) | O(1) |
| Merge Sort | O(n log n) | O(n log n) | O(n log n) | O(n) |

**Bubble Sort:** compara cada par de vecinos y los intercambia si están en desorden.
- **O(n²):** la primera pasada hace n−1 comparaciones, la segunda n−2, y así hasta 1, lo que da n(n−1)/2 comparaciones en total. Con n = 300 son 44,850.
- **O(n) en el mejor caso:** si en una pasada no hay intercambios (`huboIntercambio` es falso), los datos ya están ordenados y el ciclo termina.
- **Espacio O(1):** ordena dentro del mismo vector; solo usa una variable temporal para intercambiar.

**Merge Sort:** divide el vector a la mitad, ordena cada mitad de forma recursiva y luego las mezcla (`merge`).
- **O(n log n) en todos los casos:** siempre divide a la mitad, así que hay log₂ n niveles, y en cada nivel `merge` recorre los n elementos. Eso da n × log n, sin importar cómo vengan los datos.
- **Espacio O(n):** `merge` copia las mitades en los vectores auxiliares `izquierda` y `derecha`.

El programa cuenta las comparaciones de cada ordenamiento. Por ejemplo, al ordenar los 300 jugadores por goles (descendente), Bubble Sort hace **44,444** y Merge Sort **1,962**.

### SICT0302: Selección del algoritmo

Elegí **Merge Sort** como el algoritmo principal porque:

- Con 300 jugadores hace más de 20 veces menos comparaciones que Bubble Sort.
- Su tiempo es O(n log n) siempre, sin importar el orden inicial de los datos.
- La memoria extra que usa (O(n)) es poca para 300 jugadores.

**Bubble Sort** también está en el programa para comparar los dos algoritmos. Solo conviene con pocos datos o con datos casi ordenados.

Los dos algoritmos reciben un parámetro `criterio` (un `switch` decide qué atributo comparar) y un parámetro `ascendente`. Así, un solo código sirve para los 5 criterios. Además, ordenan una copia, así que los datos originales no se alteran.
