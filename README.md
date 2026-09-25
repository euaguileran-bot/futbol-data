# Analizador de estadísticas — Premier League 2025-2026

**Proyecto de Estructuras de Datos y Algoritmos — Avance 1**

Programa de consola en C++ que carga, ordena, filtra y despliega las estadísticas de **300 jugadores reales de la Premier League 2025-2026** (15 por cada uno de los 20 equipos).

## 1. Descripción del avance

El programa lee un archivo CSV con las estadísticas de cada jugador (goles, asistencias, minutos, partidos, tarjetas, etc.) y, desde un menú de consola, permite:

- **Cargar** los datos del archivo `data/jugadores.csv`.
- **Mostrar** los jugadores en una tabla, incluyendo un atributo calculado: **goles por cada 90 minutos**.
- **Ordenar** por 5 criterios (goles, asistencias, edad, minutos o nombre), de forma ascendente o descendente, eligiendo entre **Bubble Sort** y **Merge Sort** (los dos programados desde cero).
- **Filtrar** por equipo, por posición o por rango de goles.

### ¿Por qué elegí este tema?

Me gusta el fútbol y sigo la Premier League, así que trabajar con sus datos hace que el proyecto sea más interesante para mí. Además, las estadísticas de jugadores son un buen caso para practicar los algoritmos y temas de la materia:

- Cada jugador tiene **atributos numéricos** (goles, minutos, edad…) y **de texto** (nombre, equipo, nacionalidad), así que un mismo algoritmo de ordenamiento se puede probar con criterios muy diferentes.
- Son preguntas que realmente se hacen los aficionados: ¿quién es el máximo goleador?, ¿qué jugadores de Arsenal tienen más asistencias?, ¿quiénes jugaron más minutos?
- Con ~300 registros ya se nota claramente la diferencia entre un algoritmo O(n²) y uno O(n log n).

### Sobre los datos

- `data/jugadores.csv` tiene 300 jugadores reales de la temporada 2025-2026. Las estadísticas son **aproximaciones**, no cifras oficiales.
- Los nombres se escriben sin acentos (por ejemplo `Martin Odegaard`) para que la tabla se vea bien en cualquier terminal.
- Cabecera del CSV:

```
nombre,equipo,posicion,edad,nacionalidad,partidos_jugados,partidos_titular,minutos,goles,asistencias,tarjetas_amarillas,tarjetas_rojas
```

### Estructura de archivos

```
src/
  Jugador.h / Jugador.cpp              Clase Jugador: atributos, getters, mostrar() y golesPor90Min()
  Registro.h / Registro.cpp            Clase Registro: carga el CSV, muestra la tabla y los 3 filtros
  Ordenamientos.h / Ordenamientos.cpp  bubbleSort y mergeSort
  main.cpp                             Menú del programa
data/
  jugadores.csv                        Datos de los 300 jugadores
```

## 2. Cómo usar el programa

Desde la carpeta principal del proyecto (la que tiene `src` y `data`):

```bash
g++ src/*.cpp -o analizador
./analizador          # Linux / Mac
.\analizador.exe      # Windows
```

Menú:

```
==== ANALIZADOR PREMIER LEAGUE ====
1. Cargar jugadores desde CSV
2. Mostrar todos los jugadores
3. Ordenar jugadores
4. Filtrar jugadores
0. Salir
```

1. **Cargar:** lee `data/jugadores.csv`. Si una línea tiene campos faltantes o un número inválido, la ignora y avisa.
2. **Mostrar todos:** muestra los 300 jugadores en el orden del archivo.
3. **Ordenar:** se elige el criterio (1 = goles, 2 = asistencias, 3 = edad, 4 = minutos, 5 = nombre), el orden (1 = ascendente, 2 = descendente) y el algoritmo (1 = Bubble Sort, 2 = Merge Sort). El programa muestra qué algoritmo usó y cuántos jugadores procesó, y pregunta cuántos mostrar (0 = todos).
4. **Filtrar:** por equipo (se elige de una lista), por posición (Portero, Defensa, Mediocampista o Delantero) o por rango de goles (mínimo y máximo).
0. **Salir.**

Las opciones 2, 3 y 4 piden cargar los datos primero. Si se escribe una letra o un número fuera de rango, el programa vuelve a preguntar sin romperse.

### Ejemplo de ejecución

```
Elige una opcion (0-4): hola
Entrada invalida. Escribe un numero entre 0 y 4: 1
>> Se cargaron 300 jugadores desde data/jugadores.csv

Elige una opcion (0-4): 3

--- ORDENAR JUGADORES ---
Criterio: 1 = goles, 2 = asistencias, 3 = edad, 4 = minutos, 5 = nombre
Elige el criterio (1-5): 1
Orden: 1 = ascendente (menor a mayor / A-Z), 2 = descendente (mayor a menor / Z-A)
Elige el orden (1-2): 2
Algoritmo: 1 = Bubble Sort, 2 = Merge Sort
Elige el algoritmo (1-2): 1

>> Algoritmo usado: Bubble Sort | Jugadores procesados: 300 | Criterio: goles (descendente)
Cuantos jugadores quieres ver? (0 = todos): 5

#    Nombre                  Equipo            Posicion      Edad  Nacionalidad        PJ  PT   Min   G   A  TA  TR   G/90
--------------------------------------------------------------------------------------------------------------------------
1    Erling Haaland          Manchester City   Delantero       25  Noruega             36  35  2738  27   4   2   0   0.89
2    Igor Thiago             Brentford         Delantero       24  Brasil              36  35  2777  19   3   4   0   0.62
3    Viktor Gyokeres         Arsenal           Delantero       27  Suecia              35  31  2520  14   3   3   0   0.50
4    Jean-Philippe Mateta    Crystal Palace    Delantero       28  Francia             36  33  2627  13   2   3   0   0.45
5    Hugo Ekitike            Liverpool         Delantero       23  Francia             35  28  2309  13   4   3   0   0.51
--------------------------------------------------------------------------------------------------------------------------
Mostrando 5 de 300 jugadores.

Elige una opcion (0-4): 4

--- FILTRAR JUGADORES ---
1. Por equipo
2. Por posicion
3. Por rango de goles
Elige el filtro (1-3): 3
Goles minimos: 12
Goles maximos: 5
Entrada invalida. Escribe un numero entre 12 y 100: 30

#    Nombre                  Equipo            Posicion      Edad  Nacionalidad        PJ  PT   Min   G   A  TA  TR   G/90
--------------------------------------------------------------------------------------------------------------------------
1    Viktor Gyokeres         Arsenal           Delantero       27  Suecia              35  31  2520  14   3   3   0   0.50
2    Ollie Watkins           Aston Villa       Delantero       30  Inglaterra          36  31  2543  12   5   2   0   0.42
3    Igor Thiago             Brentford         Delantero       24  Brasil              36  35  2777  19   3   4   0   0.62
...
--------------------------------------------------------------------------------------------------------------------------
Mostrando 8 de 8 jugadores.
```

(PJ = partidos jugados, PT = partidos de titular, Min = minutos, G = goles, A = asistencias, TA/TR = tarjetas amarillas/rojas, G/90 = goles por 90 minutos)

## 3. Sub-competencias

### SICT0301: Evalúa los componentes — Análisis de complejidad

**n** es el número de jugadores que se ordenan (300).

#### Bubble Sort

Compara cada par de vecinos y los intercambia si están en el orden incorrecto. Después de cada pasada, el elemento que debe ir al final queda en su lugar.

| Caso | Tiempo | ¿Cuándo pasa? |
|---|---|---|
| Mejor | **O(n)** | Los datos ya están ordenados |
| Promedio | **O(n²)** | Datos en desorden |
| Peor | **O(n²)** | Datos en orden inverso |
| **Espacio** | **O(1)** | |

- **Peor y promedio, O(n²):** la primera pasada hace n−1 comparaciones, la segunda n−2, y así hasta 1. En total son (n−1) + (n−2) + … + 1 = **n(n−1)/2** comparaciones. En el peor caso, cada comparación termina en un intercambio. Con n = 300 son 300·299/2 = **44,850 comparaciones**.
- **Mejor caso, O(n):** el programa usa la variable `huboIntercambio`. Si en una pasada no se intercambió nada, los datos ya están ordenados y el ciclo termina (`break`). Con datos ya ordenados, solo se hace una pasada de n−1 comparaciones.
- **Espacio, O(1):** ordena dentro del mismo vector. Solo usa unas cuantas variables (`pasada`, `j`, `huboIntercambio` y un `Jugador temporal` para el intercambio), sin importar cuántos jugadores haya.

#### Merge Sort

Divide el vector a la mitad, ordena cada mitad llamándose a sí mismo (recursión) y después mezcla (`merge`) las dos mitades ya ordenadas.

| Caso | Tiempo |
|---|---|
| Mejor | **O(n log n)** |
| Promedio | **O(n log n)** |
| Peor | **O(n log n)** |
| **Espacio** | **O(n)** |

- **¿Por qué O(n log n)?** Al dividir siempre a la mitad (n → n/2 → n/4 → … → 1), hay **log₂ n niveles** de división. En cada nivel, `merge` acomoda en total los n elementos. Entonces el costo es **n por nivel × log₂ n niveles = O(n log n)**.
- **¿Por qué es igual en todos los casos?** Siempre divide a la mitad, sin importar cómo vengan los datos, y `merge` siempre recorre todos los elementos.
- **Espacio, O(n):** `merge` copia cada mitad a los vectores auxiliares `izquierda` y `derecha`. En la última mezcla, esos vectores guardan los n elementos.
- Con n = 300: log₂ 300 ≈ 8.2, así que hay 9 niveles, y como máximo unas 300 × 9 = 2,700 comparaciones.

#### Comprobación con los datos reales

Agregué temporalmente un contador de comparaciones para ordenar los 300 jugadores con los dos algoritmos:

| Prueba (n = 300) | Bubble Sort | Merge Sort |
|---|---:|---:|
| Goles, descendente | 44,444 | 1,962 |
| Nombre, ascendente | 44,679 | 2,103 |
| Datos ya ordenados (mejor caso de Bubble Sort) | 299 | 1,308 |
| Datos en orden inverso (peor caso de Bubble Sort) | 44,850 | 1,180 |

Los resultados coinciden con el análisis: el peor caso de Bubble Sort es exactamente n(n−1)/2 = 44,850, su mejor caso es n−1 = 299, y Merge Sort siempre queda por debajo de 2,700.

### SICT0302: Toma decisiones — Selección del algoritmo

**Elegí Merge Sort como el algoritmo principal** para ordenar los 300 jugadores:

1. **Es mucho más rápido con este volumen de datos:** hace unas 2,000 comparaciones, contra unas 44,000 de Bubble Sort, más de 20 veces menos. Con más datos (por ejemplo, varias temporadas) la diferencia crecería todavía más, porque O(n²) crece mucho más rápido que O(n log n).
2. **Su tiempo es predecible:** es O(n log n) en todos los casos, sin importar cómo vengan ordenados los datos.
3. **Su desventaja no afecta aquí:** usa memoria extra O(n), pero para 300 jugadores es muy poca memoria.

**Bubble Sort** también está en el programa para compararlo con Merge Sort. Conviene cuando hay **pocos datos** o los datos están **casi ordenados**: gracias a la optimización con `huboIntercambio`, en esos casos termina en pocas pasadas. También usa menos memoria (O(1)).

| Situación | Algoritmo recomendado |
|---|---|
| Muchos datos (cientos o miles) | Merge Sort |
| Datos en desorden o en orden inverso | Merge Sort |
| Pocos datos o datos casi ordenados | Bubble Sort |
| Memoria muy limitada | Bubble Sort |

**Cómo se usan correctamente en el programa:**

- Un mismo algoritmo sirve para los 5 criterios: el parámetro `criterio` elige con un `switch` qué atributo comparar, y el parámetro `ascendente` decide el orden.
- Se ordena una **copia** de los jugadores, así el registro original conserva el orden del archivo.
- Comprobé que Bubble Sort y Merge Sort dan exactamente el mismo resultado en los 5 criterios, en orden ascendente y descendente.
